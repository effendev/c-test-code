#include <stdint.h>
#include <string.h>

#include "../Inc/getter.h"


uint16_t get_data16(uint8_t* data, uint8_t idx) 
{
  uint16_t data16 = (uint16_t)(*(data + idx + 1) << 8) | data[idx];
  return data16;
}


uint32_t get_data32(uint8_t* data, uint8_t idx) 
{
  uint32_t data32 = 0;

    for (int i = 3; i >= 0; i--)
    {
        data32 <<= 8;
        data32 |= *(data + (i + idx));
    }
    return data32;
}

/* Function to get timestamps data from frame */
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


float get_datafloat(uint8_t* data, uint8_t idx, uint8_t floattype){
  float floatdata;
  uint32_t data32;

  data32 = get_data32(data, idx);
  if(floattype == FLOAT_TOF_DATA) {
    floatdata = (float)(data32) / FLOAT_TOF_CONV;
  } else if(floattype == FLOAT_POS_DATA) {
    floatdata = (float)(data32) / FLOAT_POS_CONV;
  } else {
    floatdata = 0.0;
  }
  
  return floatdata;
}

