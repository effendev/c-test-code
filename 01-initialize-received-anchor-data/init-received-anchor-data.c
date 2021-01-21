#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_ANCHOR_MAX 8
#define BUFFER_SIZE    111

#define DEBUG_MSG

// Struct to store received anchor position
typedef struct receivedAnchorPosition_s {
  float x;
  float y;
  float z;
} __attribute__((packed)) receivedAnchorPosition_t;

typedef struct remoteAnchorData_s {
  uint16_t id;
  uint8_t seqnb;
  double tof;
  uint64_t rx_ts; 
}  __attribute__((packed)) remoteAnchorData_t;


// struct to store received anchor data
typedef struct receivedAnchorData_s {
  /* Received anchor self data */
  bool isUsed;         // Boolean indicator
  uint16_t id;         // Received anchor Id (16 Bits)
  uint8_t seqnb;       // Frame sequence number
  uint64_t tx_ts;      // Packet transmit timestamp from this anchor
  float cri_value;     // cri value for the anchor
  receivedAnchorPosition_t receivedAnchorPosition;  // Position data

  /* remote anchor data */
  uint8_t num_remote_anchor;  // How many remote anchor data does this anchor have
  uint8_t first_received_idx; // Index of first received anchor by tag in the remote anchor data struct
  remoteAnchorData_t remoteAnchorData[NUM_ANCHOR_MAX - 1]; // Remote anchor data stored in this anchor (7 max)
}  __attribute__((packed)) receivedAnchorData_t;

// Create an array of receivedAnchorData_t for 8 anchors
static receivedAnchorData_t receivedAnchorData[NUM_ANCHOR_MAX];

// Function to initialize receivedAnchorData values with zeros
static void initReceivedAnchorData(receivedAnchorData_t* receivedAnchorData, int i);

int main()
{   
    // Initialize receivedAnchorData structs
    for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
        initReceivedAnchorData(&receivedAnchorData[i], i);
    }
    
#ifdef DEBUG_MSG    
    for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
        printf("seqnb-%d: %d\n", i,receivedAnchorData[i].seqnb);
    }
#endif
    printf("Hello World");

    return 0;
}


static void initReceivedAnchorData(receivedAnchorData_t* receivedAnchorData, int i) {
    /* received anchor self data */
    receivedAnchorData->isUsed = false;
    receivedAnchorData->id = 1;
    receivedAnchorData->seqnb = i;
    receivedAnchorData->tx_ts = 0;
    
    /* received anchor position data*/
    receivedAnchorData->receivedAnchorPosition.x = 0; 
    receivedAnchorData->receivedAnchorPosition.y = 0;
    receivedAnchorData->receivedAnchorPosition.z = 0;

    /* remote anchor data*/
    receivedAnchorData->first_received_idx = 0;
    receivedAnchorData->num_remote_anchor = 0;
}

