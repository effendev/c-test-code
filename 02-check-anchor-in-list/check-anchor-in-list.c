/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Anchor & frame buffer information
#define NUM_ANCHOR_MAX 8
#define BUFFER_SIZE    111

// macro for debugging process
#define DEBUG_MSG

// Struct for storing received anchor position
typedef struct receivedAnchorPosition_s {
  float x;
  float y;
  float z;
} __attribute__((packed)) receivedAnchorPosition_t;

// Struct for storing remote anchor data in received-anchor's frame
typedef struct remoteAnchorData_s {
  uint16_t id;
  uint8_t seqnb;
  double tof;
  uint64_t rx_ts; 
}  __attribute__((packed)) remoteAnchorData_t;

// struct for storing received anchor data
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

// Function to initialize receivedAnchorData values with zeros & to check anchor id in storage
static void initReceivedAnchorData(receivedAnchorData_t* receivedAnchorData, int i);
static bool checkAnchorInList(uint8_t* rx_buffer);

int main()
{   

    // Check combining two 8 bits data to 16 bits.     
    uint8_t a = 0x1A;
    uint8_t b = 0xA1;
    uint16_t c = 0x1AA1;
    uint16_t ab = (uint16_t)(a << 8) | b;
    
    if(ab == c) {
        printf("Same!\n");
    }
    
    // Imitasi pesan yang diterima oleh tag dari anchor
    uint8_t rx_buffer_1[4] = {0xC5, 0xA1, 0x1A, 0x01};
    uint8_t rx_buffer_2[4] = {0xC5, 0xB1, 0x1B, 0x01};
    uint8_t rx_buffer_3[4] = {0xC5, 0xC1, 0x1C, 0x01};

    // Initialize receivedAnchorData structs
    for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
        initReceivedAnchorData(&receivedAnchorData[i], i);
    }
    
    // Cari id anchor di storage struct
    bool found1 = checkAnchorInList(rx_buffer_1);
    bool found2 = checkAnchorInList(rx_buffer_2);
    bool found3 = checkAnchorInList(rx_buffer_3);

#ifdef DEBUG_MSG
    if(found1) {
        printf("0xA11A is Found\n");
    } else {
        printf("0xA11A is Not found\n");
    }
    
    if(found2) {
        printf("0xB11B is Found\n");
    } else {
        printf("0xB11B is Not found\n");
    }
    
    if(found3) {
        printf("0xC11C is Found\n");
    } else {
        printf("0xC11C is Not found\n");
    }
#endif

    printf("Hello World");

    return 0;
}


static void initReceivedAnchorData(receivedAnchorData_t* receivedAnchorData, int i) {
    /* received anchor self data */
    receivedAnchorData->isUsed = false;
    receivedAnchorData->seqnb = 0;
    receivedAnchorData->tx_ts = 0;
    
    if(i == 3) {
        receivedAnchorData->id = 0xA11A;
    } else if (i = 6){
        receivedAnchorData->id = 0xB11B;
    } else {
        receivedAnchorData->id = 0;
    }
    
    /* received anchor position data*/
    receivedAnchorData->receivedAnchorPosition.x = 0; 
    receivedAnchorData->receivedAnchorPosition.y = 0;
    receivedAnchorData->receivedAnchorPosition.z = 0;

    /* remote anchor data*/
    receivedAnchorData->first_received_idx = 0;
    receivedAnchorData->num_remote_anchor = 0;
}

static bool checkAnchorInList(uint8_t* rx_buffer) {
	bool found = false;
	for(int i = 0; i < NUM_ANCHOR_MAX; i++) {
		uint16_t temp_id = receivedAnchorData[i].id;
		uint16_t rx_id = (uint16_t)(rx_buffer[1] << 8) | rx_buffer[2];
		if(temp_id == rx_id) {
			found = true;
			break;
		} else {
			continue;
		}
	}
	return found;
}
