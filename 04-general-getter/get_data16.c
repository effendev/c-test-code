/*
Author  : Muhammad Arifin
Date    : 07 Jan 2021
Desc    : Modul program untuk mengambil data 16bit dari frame uwb. 
          Fungsi access_data16 mensimulasikan fungsi lain yang akan
          memanggil fungsi get_data16 untuk memperoleh data 16bits. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t data[4] = {0x1A, 0x1B, 0x1C, 0x1D};
uint16_t data16;

uint16_t get_data16(uint8_t* data, uint8_t idx) {
    uint16_t data16 = (uint16_t)(*(data + idx) << 8) | data[idx+1];
    return data16;
}

uint16_t access_data16 (uint8_t* data) {
    uint16_t data16 = get_data16(data, 1);
    return data16;
}

int main()
{
    data16 = access_data16(data);
    printf("data16: %#x\n", data16);
    printf("Hello World");

    return 0;
}

