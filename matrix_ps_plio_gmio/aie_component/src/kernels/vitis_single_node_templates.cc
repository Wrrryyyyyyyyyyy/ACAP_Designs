#include "../kernels.h"
#include <adf.h>
#include <aie_api/aie.hpp>


void matrix256(input_stream_int32* __restrict datain1, input_stream_int32* __restrict datain2, output_stream_int32* dataout ){
  
  //int32_t Ina=0;
  //int32_t Inb=0;
  //int32_t sum = 0 ;
    aie::vector<int32,8>  Ina;
    aie::vector<int32,8>  Inb;
    aie::accum<acc64,8>  temp0;
    aie::vector<int32,8>  temp1;
    int32_t sum;
  //int32_t time1,time2;

  for(int i = 0; i < 256/8; i++)
  chess_prepare_for_pipelining
  chess_loop_range(8, 64)
  {
    Ina = readincr_v<8>(datain1);
    Inb = readincr_v<8>(datain2);
    temp0 = aie::mac(temp0,Ina,Inb);
    //temp1 = aie::add(temp1 , temp0);
    
  }
    temp1 = temp0.to_vector<int32>(0);
    sum = aie::reduce_add(temp1);

    writeincr(dataout,sum);
}
