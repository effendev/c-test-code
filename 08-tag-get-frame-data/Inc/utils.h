#ifndef UTILS_H_
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* General Library Includes */
#include "main.h"
#include "getter.h"

// #define DEBUG_MSG"a

/* Function to initialize receivedAnchorData values with zeros */ 
void initReceivedAnchorData(receivedAnchorData_t* receivedAnchorData);

/* Function to find received anchor in struct storage */
bool checkAnchorInStorage(uint8_t* rx_buffer, receivedAnchorData_t receivedAnchorData[]);

/* Function to store received anchor data in struct storage */
void addAnchorDataToStorage(bool found, uint8_t* anchor_count, uint16_t* first_received_id, anchor_t* anchor, int idx, receivedAnchorData_t receivedAnchorData[]);

#ifdef __cplusplus
}
#endif
#endif