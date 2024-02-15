#include "../kernels.h"
#include <adf.h>
#include <aie_api/aie.hpp>


void matrix256(input_stream_int32* __restrict datain1, input_stream_int32* __restrict datain2, output_stream_int32* dataout ){
  
  int32_t Ina=0;
  int32_t Inb=0;
  int32_t sum = 0 ;
  //int32_t time1,time2;

  for(int i = 0; i < 256; i++)
  chess_prepare_for_pipelining
  chess_loop_range(16, 64)
  {
    Ina = readincr(datain1);
    Inb = readincr(datain2);
    sum = sum + Ina * Inb;
    
  }

  writeincr(dataout,sum);
}
