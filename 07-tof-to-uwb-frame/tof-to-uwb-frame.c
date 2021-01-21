#include <stdio.h>      // for basic io 
#include <stdint.h>     // for uint data type
#include <inttypes.h>   // for printing uint64_t
#include <float.h>      // for printing float value
#include <string.h>     // for memcpy

#define MSG_TS_LEN 5

int Digs = DECIMAL_DIG; // for printing double value

// UWB Frame 
uint8_t rx_buffer[7] = {0xC5, 0xA1, 0x1A, 0, 0, 0, 0};

// Fungsi untuk mengubah nilai double menjadi uint64_t
void doubleToUint32(float* data_float, uint32_t* data32) {
    memcpy(data32, data_float, sizeof(data_float));
}

void uint32ToDouble(uint32_t* data32, float* data_float) {
    memcpy(data_float, data32, sizeof(data32));
}

void set_data32(uint32_t data, uint8_t* buff, uint8_t idx) {
    for(int i = 0; i < 4; i++) {
        *(buff + (i + idx)) = (data >> (i * 8)) & 0xFF;
    }
}

uint32_t get_data32(uint8_t* buff, uint8_t idx)
{
    uint32_t data32 = 0;

    for (int i = 3; i >= 0; i--)
    {
        data32 <<= 8;
        data32 |= *(buff + (i + idx));
    }
    return data32;
}

int main()
{
    // time of flight data 
    float tof_raw = 1000.12/ 299792458;   // Raw tof value. Nilai pembilang harus xx.yz (harus ada komanya)
    uint32_t tof32_send;                // sent uint64_t tof value
    uint32_t tof32_recv;                // received uint64_t tof value
    float tof_recv;                    // received and converted tof value
    
    // Change double to uint32
    doubleToUint32(&tof_raw, &tof32_send);
    
    // Embed tof data to uwb frame
    set_data32(tof32_send, rx_buffer, 3);
    
    // get tof data from frame
    tof32_recv = get_data32(rx_buffer, 3);
    
    // // change tof data 
    uint32ToDouble(&tof32_recv, &tof_recv);
    
    printf("tof: %.*e\n", Digs, tof_raw);
    printf("tof: %" PRIu32 "\n", tof32_send);
    printf("tof: %.*e\n", Digs, tof_recv);
    printf("tof: %" PRIu32 "\n", tof32_recv);
    
    return 0;
}

