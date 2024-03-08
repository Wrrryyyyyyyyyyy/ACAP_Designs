/*******************************************************************************
Vendor: Xilinx
Associated Filename: vadd.cpp
Purpose: VITIS vector addition

*******************************************************************************
Copyright (C) 2019 XILINX, Inc.

This file contains confidential and proprietary information of Xilinx, Inc. and
is protected under U.S. and international copyright and other intellectual
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials
distributed herewith. Except as otherwise provided in a valid license issued to
you by Xilinx, and to the maximum extent permitted by applicable law:
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY,
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether
in contract or tort, including negligence, or under any other theory of
liability) for any loss or damage of any kind or nature related to, arising under
or in connection with these materials, including for any direct, or any indirect,
special, incidental, or consequential loss or damage (including loss of data,
profits, goodwill, or any type of loss or damage suffered as a result of any
action brought by a third party) even if such damage or loss was reasonably
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any
application requiring fail-safe performance, such as life-support or safety
devices or systems, Class III medical devices, nuclear facilities, applications
related to the deployment of airbags, or any other applications that could lead
to death, personal injury, or severe property or environmental damage
(individually and collectively, "Critical Applications"). Customer assumes the
sole risk and liability of any use of Xilinx products in Critical Applications,
subject only to applicable laws and regulations governing limitations on product
liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT
ALL TIMES.

*******************************************************************************/



#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include <inttypes.h>
#include <sys/time.h>


static unsigned long long cpucycles(void)
{
    unsigned long long result;
      __asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
              : "=a" (result) ::  "%rdx");
        return result;
}
//#endif


static const std::string error_message =
    "Error: Result mismatch:\n"
    "i = %d CPU result = %d Device result = %d\n";

int main(int argc, char* argv[]) {
    
    uint64_t cyc0; 
    uint64_t cyc1;
    struct timeval start;
    struct timeval end;
    unsigned long timer;

    //unsigned char in[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    
    unsigned char in[128] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
    printf("\nThe input of hash is :\n");
    	for(int i=0;i<sizeof(in);i++)
	{
 
		printf("%02x",in[i]);	
	}
    printf("\n");
    
	unsigned char buff[32];//必须带unsigned ,sha256消息摘要输出为256位,即32字节
	memset(buff,0,32);
	puts("start sha256 hash \n");
	//sha256(in,strlen(in),buff);

    gettimeofday(&start,NULL);
    cyc0 = cpucycles();
    
    sha256(in,sizeof(in),buff);

    cyc1 =  cpucycles();
    gettimeofday(&end,NULL);

	printf("\nThe sha256 hash is :\n");
    	for(int i=0;i<32;i++)
	{
 
		printf("%x",buff[i]);	
	}
	puts("\nend sha256 hash \n");
	
    printf("\ncycles of sha256 : %" PRIu64 "\n\n", cyc1-cyc0);
    timer = 1000000* (end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    printf("time = %ld us\n", timer);

    return 0;

}
