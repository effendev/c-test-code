#ifndef MAIN_H_
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Comment this kalau tidak ingin print value untuk debug
// #define DEBUG_ID_SN
#define DEBUG_REMOTE_DATA
// #define DEBUG_TOF

#define DUMMY_ANCHOR_NUM 12

/* Constants*/
#define SPEED_OF_LIGHT 299792458.0

/* Anchor information definition */
#define NUM_ANCHOR_MAX 8
#define BUFFER_SIZE 	 111

/* UWB Frame Indices */
#define ANCHOR_ID_IDX   1
#define ANCHOR_SN_IDX   3
#define ANCHOR_TXTS_IDX 4
#define ANCHOR_XPOS_IDX 9
#define ANCHOR_YPOS_IDX 13
#define ANCHOR_ZPOS_IDX 17
#define NUM_REMDAT_IDX  21

#define REMOTE_ID_IDX   22
#define REMOTE_RXTS_IDX 37
#define REMOTE_TOF_IDX  73
#define REMOTE_SEQN_IDX 102

// Multiplication factors to convert carrier integrator value to a frequency offset in Hertz

#define FREQ_OFFSET_MULTIPLIER          (998.4e6/2.0/1024.0/131072.0)
#define FREQ_OFFSET_MULTIPLIER_110KB    (998.4e6/2.0/8192.0/131072.0)

// Multiplication factors to convert frequency offset in Hertz to PPM crystal offset
// NB: also changes sign so a positive value means the local RX clock is running slower than the remote TX device.

#define HERTZ_TO_PPM_MULTIPLIER_CHAN_1     (-1.0e6/3494.4e6)
#define HERTZ_TO_PPM_MULTIPLIER_CHAN_2     (-1.0e6/3993.6e6)
#define HERTZ_TO_PPM_MULTIPLIER_CHAN_3     (-1.0e6/4492.8e6)
#define HERTZ_TO_PPM_MULTIPLIER_CHAN_5     (-1.0e6/6489.6e6)


/* Struct to store received anchor position */
typedef struct receivedAnchorPosition_s {
  float x;
  float y;
  float z;
} __attribute__((packed)) receivedAnchorPosition_t;

/* Struct to store remote data in received anchor packet */
typedef struct remoteAnchorData_s {
  uint16_t id;
  uint8_t seqnb;
  float tof;
  uint64_t rx_ts; 
}  __attribute__((packed)) remoteAnchorData_t;

/* struct to store received anchor data */
typedef struct receivedAnchorData_s {
  /* Received anchor self data */
  bool isUsed;         // Boolean indicator
  uint16_t id;         // Received anchor Id (16 Bits)
  uint8_t seqnb;       // Frame sequence number
  uint64_t tx_ts;      // Packet transmit timestamp from this anchor
  uint64_t rx_ts;      // Received timestamp from this anchor in tag clock
  float cri_value;     // cri value for the anchor
  receivedAnchorPosition_t receivedAnchorPosition;  // Position data

  /* remote anchor data */
  uint8_t num_remote_anchor;  // How many remote anchor data does this anchor have
  uint8_t first_received_idx; // Index of first received anchor by tag in the remote anchor data struct
  remoteAnchorData_t remoteAnchorData[NUM_ANCHOR_MAX - 1]; // Remote anchor data stored in this anchor (7 max)
}  __attribute__((packed)) receivedAnchorData_t;

/* Dummy anchor data buffer */
typedef struct anchor_s {
    uint8_t anchor[BUFFER_SIZE];
    uint16_t id;
} __attribute__((packed)) anchor_t;

#ifdef __cplusplus
}
#endif
#endif