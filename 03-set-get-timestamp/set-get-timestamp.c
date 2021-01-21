#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define MSG_TS_LEN 5

// Simulated timestamp value
uint64_t tx_ts = 99309042740;

// Simulated received frame from anchor
uint8_t rx_buffer[8] = {0xC5, 0xA1, 0x1A, 0, 0, 0, 0, 0};
uint8_t ts_idx = 3;

// received anchor timestamp data
uint64_t anchor_tx_ts; 

// function declarations
void printData(uint8_t* data);
void set_ts(uint64_t ts, uint8_t* frame, uint8_t ts_idx);
static uint64_t get_ts(uint8_t* data, uint8_t ts_idx);

int main()
{
    //  Set timestamp value to data frame
    set_ts(tx_ts, rx_buffer, ts_idx);
    
    // Print the stored timestamp value
    printData(rx_buffer);
    
    // Get timestamp data from frame to 64 bits variable
    anchor_tx_ts = get_ts(rx_buffer, ts_idx);
    printf("anchor_tx_ts: %" PRIu64 "\n", anchor_tx_ts);
    printf("anchor_tx_ts: 0x%" PRIx64 "\n", anchor_tx_ts);
    
    return 0;
}

// Function definitions 
void set_ts(uint64_t ts, uint8_t* data, uint8_t ts_idx) {
    for(int i = 0; i < MSG_TS_LEN; i++) {
        *(data + (i + ts_idx)) = (ts >> (i * 8)) & 0xFF;
    }
}

void printData(uint8_t* data) {
   for(int i = ts_idx; i < (ts_idx + MSG_TS_LEN); i++) {
        printf("rx_buffer[%d]: %#x\n", i, *(data + i));
    }
}

uint64_t get_ts(uint8_t* data, uint8_t ts_idx)
{
    uint64_t ts = 0;

    for (int i = 4; i >= 0; i--)
    {
        ts <<= 8;
        ts |= *(data + (i + ts_idx));
    }
    return ts;
}


