#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "../Inc/generator.h"
#include "../Inc/main.h"


/* Anchor data */
uint8_t  anchor_seqnb = 5;
uint64_t anchor_tx_ts = 99309044900;
float x_pos = 4.5, y_pos = 8000.5, z_pos = 5.45;
uint8_t num_remote_data = 7;

/* Remote Anchor Data */
uint16_t remote_id[7]    = {0x3e01, 0xbbe9, 0xed8d, 0x4ff3, 0x10ed, 0x699f, 0xed8d};
uint64_t remote_rx_ts[7] = {99309042760, 99309042780, 99309042800, 99309042820, 99309042840, 99309042860, 99309042880};
float remote_tof[7]      = {3.5/SPEED_OF_LIGHT, 5/SPEED_OF_LIGHT, 6.2/SPEED_OF_LIGHT, 7.2/SPEED_OF_LIGHT, 
                            2.7/SPEED_OF_LIGHT, 4.6/SPEED_OF_LIGHT, 8.8/SPEED_OF_LIGHT};
uint8_t remote_seqnb[7]  = {1, 3, 4, 6, 1, 2, 3};

/* Function to Set 16bits Data to UWB Frame */
void set_data16(uint16_t data16, uint8_t* data, uint8_t idx) {
    for(int i = 0; i < DATA16_LEN; i++) {
        *(data + (i + idx)) = (data16 >> (i * 8)) & 0xFF;
    }
}

/* Function to Set 32bits Data to UWB Frame */
void set_data32(uint32_t data32, uint8_t* data, uint8_t idx) {
    for(int i = 0; i < DATA32_LEN; i++) {
        *(data + (i + idx)) = (data32 >> (i * 8)) & 0xFF;
    }
}

void set_datats(uint64_t ts, uint8_t* data, uint8_t ts_idx) {
    for(int i = 0; i < DATATS_LEN; i++) {
        *(data + (i + ts_idx)) = (ts >> (i * 8)) & 0xFF;
    }
}


/* Function to Set float Data to UWB frame */
void set_datafloat(float floatdata, uint8_t* data, uint8_t idx) {
    uint32_t data32;
    if(floatdata > 0.1 ) {
        // position data 
        data32 = (uint32_t)(floatdata * FLOAT_POS_CONV);
    } else {
        // tof data
        data32 = (uint32_t)(floatdata * FLOAT_TOF_CONV);
    }
    set_data32(data32, data, idx);
}


/* Function to generate Dummy UWB Frame */
void dummyDataGenerator(uint8_t* data, uint16_t anchor_id) {
    // Set Anchor ID data
    set_data16(anchor_id, data, ANCHOR_ID_IDX);

    // Set Anchor SeqNb data
    *(data + ANCHOR_SN_IDX) = anchor_seqnb;

    // Set Anchor TX_TS Data
    set_datats(anchor_tx_ts, data, ANCHOR_TXTS_IDX);

    // Set Anchor Positions data
    set_datafloat(x_pos, data, ANCHOR_XPOS_IDX);
    set_datafloat(y_pos, data, ANCHOR_YPOS_IDX);
    set_datafloat(z_pos, data, ANCHOR_ZPOS_IDX);

    // Add number of remote data in anchor frame
    *(data + NUM_REMDAT_IDX)  = 7;

    // Set All start byte data
    *(data + REMOTE_ID_IDX)   = START_REMOTE_ID_BYTE;
    *(data + REMOTE_RXTS_IDX) = START_REMOTE_RX_TS_BYTE;
    *(data + REMOTE_TOF_IDX)  = START_REMOTE_TOF_BYTE;
    *(data + REMOTE_SEQN_IDX) = START_REMOTE_SEQNB_BYTE;

    // Set remote ID Data
    int step = 1;
    for(int i = 0; i < (NUM_ANCHOR_MAX - 1); i++) {
        set_data16(remote_id[i], data, REMOTE_ID_IDX + i + step);
        ++step;
    }

    // Set remote rx_ts data
    step = 1;
    uint64_t random_tx_ts;
    for(int i = 0; i < (NUM_ANCHOR_MAX - 1); i++) {
        random_tx_ts = rand();
        set_datats(random_tx_ts, data, REMOTE_RXTS_IDX + i + step);
        step += 4;
    }

    // Set remote tof data
    step = 1;
    for(int i = 0; i < (NUM_ANCHOR_MAX - 1); i++) {
        set_datafloat(remote_tof[i], data, REMOTE_TOF_IDX + i + step);
        step += 3;
    }

    // Set remote_sq_number data
    for(int i = 0; i < (NUM_ANCHOR_MAX - 1); i++) {
        *(data + REMOTE_SEQN_IDX + i + 1) = remote_seqnb[i];
    }

    return;
}

