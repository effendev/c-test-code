/*
Author  : Muhammad Arifin
Date    : 07 Jan 2021
Desc    : Modul program untuk mengubah data tof double menjadi
          data tof dalam bentuk uint64_t agar dapat disisipkan
          ke frame uwb. 
*/

#include <stdio.h>      // for basic io 
#include <stdint.h>     // for uint data type
#include <inttypes.h>   // for printing uint64_t
#include <float.h>      // for printing float value
#include <string.h>     // for memcpy

int Digs = DECIMAL_DIG; // for printing double value

double tof_raw = 0.6 / 299792458;   // Raw tof value: 2.001384571188912338666e-09
uint64_t tof64;                     // Penampung nilai tof untuk dikirimkan dengan frame uwb
double tof_recv;                    // Penampung nilai tof yang diterima dari frame uwb

// Fungsi untuk mengubah nilai double menjadi uint64_t
void doubleToUint64(double* data_double, uint64_t* data64) {
    memcpy(data64, data_double, sizeof(data_double));
}

// Fungsi untuk mengubah nilai uint64_t menjadi double
void uint64ToDouble(uint64_t* data64, double* data_double) {
    memcpy(data_double, data64, sizeof(data64));
}


int main()
{   
    // Konversi nilai double ke uint64_t dan sebaliknya
    doubleToUint64(&tof_raw, &tof64);
    uint64ToDouble(&tof64, &tof_recv);
    
    // Print semua hasil 
    printf("tof: %.*e\n", Digs, tof_raw);
    printf("tof: %" PRIu64 "\n", tof64);    // nilainya akan aneh tapi gapapa. 
    printf("tof: %.*e\n", Digs, tof_recv);

    return 0;
}
