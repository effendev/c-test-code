#ifndef GENERATOR_H_
#define GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Separator Byte Values */
#define START_REMOTE_ID_BYTE      0xAF
#define START_REMOTE_RX_TS_BYTE   0x7F
#define START_REMOTE_TOF_BYTE     0x0D
#define START_REMOTE_SEQNB_BYTE   0x8A  

#define DATA16_LEN 2
#define DATA32_LEN 4
#define DATATS_LEN 5
#define FLOAT_TOF_CONV 10e14 // Float to uint32 conversion factor can handle up to 1200 meters tof value
#define FLOAT_POS_CONV 10e4 

/* Function to Set 16bits Data to UWB Frame */
void set_data16(uint16_t data16, uint8_t* data, uint8_t idx);

/* Function to Set 32bits Data to UWB Frame */
void set_data32(uint32_t data32, uint8_t* data, uint8_t idx);

/* Function to Set 40bits timestamps Data to UWB Frame */
void set_datats(uint64_t datats, uint8_t* data, uint8_t idx);

/* Function to Set float Data to UWB frame */
void set_datafloat(float floatdata, uint8_t* data, uint8_t idx);

/* Function to generate Dummy UWB Frame */
void dummyDataGenerator(uint8_t* data, uint16_t anchor_id);

#ifdef __cplusplus
}
#endif
#endif