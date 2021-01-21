/* General Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>

/* Private Library Includes */
#include "../Inc/utils.h"
#include "../Inc/getter.h"
#include "../Inc/generator.h"

/* Create an array of receivedAnchorData_t for 8 anchors */
receivedAnchorData_t receivedAnchorData[NUM_ANCHOR_MAX];

/* Initialize important variables */
uint8_t anchor_count = 0;        // received anchor counter
uint32_t frame_len = 0;          // received frame length
uint16_t first_received_id = 0;  // first received anchor id

/* TDOA Variables */
double delta_tx;
uint16_t first_idx;
double tof_an_ar, tdoa_result;
uint64_t ar_rx_ts, an_tx_ts, an_rx_ts, rx_ar_in_an;

/* Variable for printing float value */
int Digs = DECIMAL_DIG;

anchor_t anchors[DUMMY_ANCHOR_NUM];
uint16_t ids[12]  = {0x4ff3, 0x3e01, 0xbbe9, 0x8a0d, 0x699f, 0x4ff3, 0x10ed, 0x699f, 0xed8d, 0x9ac6, 0x9ac8, 0xed8d};
double tdoa[NUM_ANCHOR_MAX - 1];

/* Debug function declaration */
void debugDataInFrame(uint8_t* data);

int main() {
    /* Initialize receivedAnchorData structs */
    for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
        initReceivedAnchorData(&receivedAnchorData[i]);
    }

    // Generate dummy data for 12 Anchors
    for(int i = 0; i < DUMMY_ANCHOR_NUM; i++) {
        anchors[i].id = ids[i];
        dummyDataGenerator(anchors[i].anchor, anchors[i].id);
    }

    // debugDataInFrame(anchors[1].anchor);

    // Storage process 
    for (int i = 0; i < DUMMY_ANCHOR_NUM; i++) {
        // Check whether we have received message from this anchor before
        bool found = checkAnchorInStorage(anchors[i].anchor, receivedAnchorData);

        // Store anchor data to storage
        addAnchorDataToStorage(found, &anchor_count, &first_received_id, &anchors[i], i, receivedAnchorData);
    }

    // Calculate TDoA with respect to the first received anchor
    for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
        // Check whether this is the first anchor ID or not
        if(receivedAnchorData[i].id == first_received_id) {
            printf("First anchor\n");
            ar_rx_ts = receivedAnchorData[i].rx_ts;
            continue;
        } else {
            // Get all necessary data for tdoa calculation
            first_idx = receivedAnchorData[i].first_received_idx;
            tof_an_ar = (double) (receivedAnchorData[i].remoteAnchorData[first_idx].tof);
            an_tx_ts  = receivedAnchorData[i].tx_ts;
            an_rx_ts  = receivedAnchorData[i].rx_ts;  
            rx_ar_in_an = receivedAnchorData[i].remoteAnchorData[first_idx].rx_ts;

            // Calculate delta_tx and tdoa
            delta_tx  = tof_an_ar + (double) (an_tx_ts) - (double)(rx_ar_in_an);
            tdoa_result = an_rx_ts - ar_rx_ts - delta_tx;
            // Print out the results
            printf("an_tx_ts: %" PRIu64 "\n",an_rx_ts);
            printf("rx_ar_in_an:  %" PRIu64 "\n",rx_ar_in_an);
            printf("delta_tx: %.*e\n", Digs, delta_tx);
            printf("tdoa_result: %.*e\n\n", Digs, tdoa_result);
        }
    }
    
    return 0;
}

void debugDataInFrame(uint8_t* data) {
    #ifdef DEBUG_ID_SN
    /* Print ID Value */
    for(int i = 0; i < DATA16_LEN; i++) {
        printf("id[%d]: %" PRIx8 "\n", i, data[ANCHOR_ID_IDX + i]);
    }
    /* Check get_data16 concantenation result */
    uint16_t test_id = get_data16(data, ANCHOR_ID_IDX);
    printf("id: %" PRIx16 "\n", test_id);

    /* Print Sequence Number*/
    printf("id: %" PRIu8 "\n\n", data[ANCHOR_SN_IDX]);
#endif

#ifdef DEBUG_REMOTE_DATA
    /* Print Remote ID*/
    int step16 = 1, step64 = 1, tofstep = 1;
    uint16_t id16;
    uint64_t datats;
    float tof;
    uint8_t seqnb;

    for(int i = 0; i < (NUM_ANCHOR_MAX - 1); i++) {
        id16 = get_data16(data, REMOTE_ID_IDX + i + step16);
        datats = get_ts(data, REMOTE_RXTS_IDX + i + step64);
        tof = get_datafloat(data, REMOTE_TOF_IDX + i + tofstep, FLOAT_TOF_DATA);
        seqnb = data[REMOTE_SEQN_IDX + i + 1];

        printf("id-%d: 0x%" PRIx16 "\n", i+1,id16);
        printf("ts-%d: %" PRIu64 "\n", i+1,datats);
        // printf("ts_id: %d\n", REMOTE_RXTS_IDX + i + step64);
        printf("tof: %.*e\n", Digs, tof);
        // printf("tof_id: %d\n\n", REMOTE_TOF_IDX + i + tofstep);
        printf("seqnb-%d: %" PRIu8 "\n\n", i+1,seqnb);
        ++step16;
        step64 += 4;
        tofstep += 3;
    }
#endif

#ifdef DEBUG_TOF
    float remote_tof[7] = {3.5/SPEED_OF_LIGHT, 5/SPEED_OF_LIGHT, 6.2/SPEED_OF_LIGHT, 7.2/SPEED_OF_LIGHT, 2.7/SPEED_OF_LIGHT, 4.6/SPEED_OF_LIGHT, 8.8/SPEED_OF_LIGHT};
    for(int i = 0; i < 7; i++) {
        printf("%.*e\n\n", Digs, remote_tof[i]);
    }
#endif
}

