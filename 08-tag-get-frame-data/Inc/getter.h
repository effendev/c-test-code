#ifndef GETTER_H_
#define GETTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* General Library Includes */
#include <stdint.h>
#include <string.h>

#define FLOAT_TOF_CONV 10e14 // Float to uint32 conversion factor can handle up to 1200 meters tof value
#define FLOAT_POS_CONV 10e4 

#define FLOAT_TOF_DATA 0xFC
#define FLOAT_POS_DATA 0xCF

/* Getter function to retrieve uint16 data from uwb frame */
uint16_t get_data16(uint8_t* data, uint8_t idx);

/* Getter function to retrieve uint32 data from uwb frame */
uint32_t get_data32(uint8_t* data, uint8_t idx);

/* Getter function to retrieve timestamps data from uwb frame */
uint64_t get_ts(uint8_t* data, uint8_t ts_idx);

/* Function to convert uint32 data in frame to float */
void uint32ToFloat(uint32_t* data32, float* data_float);

/* Getter function to retrieve float data from uwb frame */
float get_datafloat(uint8_t* data, uint8_t idx, uint8_t floattype);


#ifdef __cplusplus
}
#endif
#endif
