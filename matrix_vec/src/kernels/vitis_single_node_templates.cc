#include "../kernels.h"
#include "aie_api/aie_types.hpp"
#include <adf.h>
#include <aie_api/aie.hpp>


void matrix256(input_stream_int32* __restrict datain1, input_stream_int32* __restrict datain2, output_stream_int32* __restrict dataout ){
  
  //int32_t Ina=0;
  //int32_t Inb=0;
    aie::vector<int32,8>  Ina;
    aie::vector<int32,8>  Inb;
    aie::accum<acc80,8>  temp0= aie::zeros<acc80,8>();
    aie::accum<acc80,8>  temp1;
    aie::vector<int32,8>  temp2,temp3,temp4;
  int32_t sum = 0 ;
//printf("start");
  //aie::tile tile = aie::tile::current();
  //unsigned long long time[2];
  //volatile unsigned long long *p_cycle=time;
    //*p_cycle=tile.cycles();
    //unsigned long long time1=tile.cycles();
    //printf("%lld\n",time1);

  for(int i = 0; i < 256/8; i++)
  chess_prepare_for_pipelining
  chess_loop_range(16, 64)
  {
    Ina = readincr_v<8>(datain1);
    Inb = readincr_v<8>(datain2);
    temp0 = mac(temp0,Ina,Inb);
    temp2 = srs(temp0,0);
    sum = aie::reduce_add(temp2);
   // Ina = readincr_v<8>(datain1);   
   // Inb = readincr_v<8>(datain2);
   // temp1 = mac(temp1,Ina,Inb);

  }
    //*(p_cycle+1)=tile.cycles();
    //printf("%lld\n",time[1]-time[0]);
    
    
    //temp3 = srs(temp1,0);
    //temp4= add(temp2,temp3);
    
  writeincr(dataout,sum);
}


    
  
