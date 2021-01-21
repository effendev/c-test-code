/*
Author  : Muhammad Arifin
Date    : 08 Jan 2021
Desc    : Modul program untuk mengambil data 32bit dari frame uwb 
          dan untuk menyisipkan data 32bit ke frame uwb. 
*/

#include <stdio.h>      // for basic io 
#include <stdint.h>     // for uint data type
#include <inttypes.h>   // for printing uint type

uint8_t data_buffer[7] = {0xC5, 0xA1, 0x1A, 0, 0, 0, 0};

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

int main() {

    // hex data
    uint32_t hexdata = 0x281cb9f4;

    // set 32-bits hexdata to frame
    set_data32(hexdata, data_buffer, 3);

    // get_data 32bits from frame 
    uint32_t rethex = get_data32(data_buffer, 3);

    // Print the result
    printf("hexdata: 0x%" PRIx32 "\n", hexdata);
    printf("rethex : 0x%" PRIx32 "\n", rethex);

}
