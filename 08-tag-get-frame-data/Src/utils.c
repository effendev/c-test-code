#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>

#include "../Inc/utils.h"

/* Function to initialize receivedAnchorData values with zeros */ 
void initReceivedAnchorData(receivedAnchorData_t* receivedAnchorData) 
{
    /* received anchor self data */
    receivedAnchorData->isUsed = false;
    receivedAnchorData->id = 0;
    receivedAnchorData->seqnb = 0;
    receivedAnchorData->tx_ts = 0;
    receivedAnchorData->rx_ts = 0;
    
    /* received anchor position data*/
    receivedAnchorData->receivedAnchorPosition.x = 0; 
    receivedAnchorData->receivedAnchorPosition.y = 0;
    receivedAnchorData->receivedAnchorPosition.z = 0;

    /* remote anchor data*/
    receivedAnchorData->first_received_idx = 0;
    receivedAnchorData->num_remote_anchor = 0;
}

/* Function to find received anchor in struct storage */
bool checkAnchorInStorage(uint8_t* rx_buffer, receivedAnchorData_t receivedAnchorData[]) 
{
	bool found = false;
	for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
		uint16_t temp_id = receivedAnchorData[i].id;
		uint16_t rx_id = get_data16(rx_buffer, ANCHOR_ID_IDX);
		if(temp_id == rx_id) {
			found = true;
			break;
		} else {
			continue;
		}
	}
	return found;
}

/* Function to store received anchor data in struct storage */
void addAnchorDataToStorage(bool found, uint8_t* anchor_count, uint16_t* first_received_id, anchor_t* anchor, int idx, receivedAnchorData_t receivedAnchorData[]) {
    if(!found && *(anchor_count) < NUM_ANCHOR_MAX) {
        #ifdef DEBUG_MSG
        printf("Id-%d: %" PRIx16 "", idx+1, anchor->id);
        printf(" has not been stored yet!\n");
        #endif
        for(int j = 0; j < NUM_ANCHOR_MAX; j++) {
            if(receivedAnchorData[j].isUsed) {
                continue;
            } else {
                /* Found an empty storage */
                if(*(anchor_count) == 0) {
                    /* First received anchor found */
                    *(first_received_id) = get_data16(anchor->anchor, ANCHOR_ID_IDX);
                    #ifdef DEBUG_MSG
                    printf("First received Id: 0x%" PRIx16 "\n", *first_received_id);
                    #endif
                }

                /* Store basic anchor data on struct */
                receivedAnchorData[j].isUsed = true;
                receivedAnchorData[j].id = get_data16(anchor->anchor, ANCHOR_ID_IDX);
                receivedAnchorData[j].seqnb = anchor->anchor[ANCHOR_SN_IDX];
                receivedAnchorData[j].tx_ts = get_ts(anchor->anchor, ANCHOR_TXTS_IDX);
                receivedAnchorData[j].rx_ts = receivedAnchorData[j].tx_ts + 300;
                receivedAnchorData[j].cri_value = (FREQ_OFFSET_MULTIPLIER * HERTZ_TO_PPM_MULTIPLIER_CHAN_5 / 1.0e6);
                receivedAnchorData[j].receivedAnchorPosition.x = get_datafloat(anchor->anchor, ANCHOR_XPOS_IDX, FLOAT_POS_DATA);
                receivedAnchorData[j].receivedAnchorPosition.y = get_datafloat(anchor->anchor, ANCHOR_YPOS_IDX, FLOAT_POS_DATA);
                receivedAnchorData[j].receivedAnchorPosition.z = get_datafloat(anchor->anchor, ANCHOR_ZPOS_IDX, FLOAT_POS_DATA);

                /* Check First received Id belongs to this anchor or not*/
                if(receivedAnchorData[j].id  == *(first_received_id)) {
                    receivedAnchorData[j].first_received_idx = 200; // Yes, this is mine not belongs to remote anchor
                    #ifdef DEBUG_MSG
                    printf("first_recv_idx_mine: %d\n", receivedAnchorData[j].first_received_idx);
                    #endif
                }

                /* Store Remote Data from this Anchor */
                // TODO Ini logicnya masih salah
                receivedAnchorData[j].num_remote_anchor = anchor->anchor[NUM_REMDAT_IDX];
                uint8_t id_idx, rx_ts_idx, tof_idx, seqnb_idx;
                int step16 = 1, step64 = 1, tofstep = 1;
                for(int k = 0; k < receivedAnchorData[j].num_remote_anchor; k++) {
                    id_idx    = REMOTE_ID_IDX   + (k + step16);
                    rx_ts_idx = REMOTE_RXTS_IDX + (k + step64);
                    tof_idx   = REMOTE_TOF_IDX  + (k + tofstep);
                    seqnb_idx = REMOTE_SEQN_IDX + (k + 1);
                    receivedAnchorData[j].remoteAnchorData[k].id = get_data16(anchor->anchor, id_idx);
                    receivedAnchorData[j].remoteAnchorData[k].rx_ts = get_ts(anchor->anchor, rx_ts_idx);
                    receivedAnchorData[j].remoteAnchorData[k].tof = get_datafloat(anchor->anchor, tof_idx, FLOAT_TOF_DATA);
                    receivedAnchorData[j].remoteAnchorData[k].seqnb = anchor->anchor[seqnb_idx];

                    /* Check First received Id belongs to this remote anchor or not*/
                    if(receivedAnchorData[j].remoteAnchorData[k].id == *(first_received_id)) {
                        receivedAnchorData[j].first_received_idx = k;
                    }

                    ++step16;
                    step64 += 4;
                    tofstep += 3;
                }
                #ifdef DEBUG_MSG
                printf("Id-%d: %" PRIx16 "", idx+1, anchor->id);
                printf(" is stored successfully!\n\n");
                #endif
                (*anchor_count)++;
                break;
            }
        }
    } else {
        #ifdef DEBUG_MSG
        printf("Id-%d: %" PRIx16 "", idx+1, anchor->id);
        printf(" found in the storage or storage is full!\n\n");
        #endif
        return ;
    }
}