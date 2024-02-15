#include "../kernels.h"
#include <adf.h>
#include <aie_api/aie.hpp>


void matrix256(input_stream_int32* __restrict datain1, input_stream_int32* __restrict datain2, output_stream_int32* __restrict dataout ){
  
  int32_t Ina=0;
  int32_t Inb=0;
  int32_t sum = 0,temp=0 ;
  //int32_t time1,time2;
  // unsigned long long time1=tile.cycles();
  for(int i = 0; i < 256; i++)
  chess_prepare_for_pipelining
  chess_loop_range(16, 64)
  {
    Ina = readincr(datain1);
    Inb = readincr(datain2);
    sum = sum + Ina * Inb;
    //sum = temp;
    //temp=0;
  }
   
  writeincr(dataout,sum);
  //sum = 0 ;
}

