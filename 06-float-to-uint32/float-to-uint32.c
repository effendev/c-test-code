/*
Author  : Muhammad Arifin
Date    : 08 Jan 2021
Desc    : Modul program untuk mengubah data tof float menjadi
          data tof dalam bentuk uint32_t agar dapat disisipkan
          ke frame uwb. 
          
          Modul ini dibuat untuk menggantikan modul double to 
          uint64_t karena konversi ke 64bit butuh 8 bytes data 
          dan float cukup sebenarnya tidak perlu harus double. 
          Rentang nilainya cukup untuk tof sampai 1000 m. 
*/

#include <stdio.h>      // for basic io 
#include <stdint.h>     // for uint data type
#include <inttypes.h>   // for printing uint64_t
#include <float.h>      // for printing float value
#include <string.h>     // for memcpy

int Digs = DECIMAL_DIG; // for printing double value

// Fungsi untuk mengubah nilai float menjadi uint32_t
void doubleToUint32(float* data_float, uint32_t* data32) {
    memcpy(data32, data_float, sizeof(data_float));
}

// Fungsi untuk mengubah nilai uint32_t menjadi nilai float 
void uint32ToDouble(uint32_t* data32, float* data_float) {
    memcpy(data_float, data32, sizeof(data32));
}


int main()
{   
    // time of flight data
    float tof_raw = 100.12/ 299792458;   // Raw tof value. Nilai pembilang harus xx.yz (harus ada komanya)
    uint32_t tof32;                      // sent uint64_t tof value
    float tof_recv;                      // received and converted tof value from uint32_t
    
    // Change double to uint32
    doubleToUint32(&tof_raw, &tof32);
    
    // change tof data 
    uint32ToDouble(&tof32, &tof_recv);
    
    printf("tof: %.*e\n", Digs, tof_raw);
    printf("tof: %" PRIu32 "\n", tof32);
    printf("tof: %.*e\n", Digs, tof_recv);
    

    return 0;
}

