/*******************************************************************************
Vendor: Xilinx
Associated Filename: vadd.cpp
Purpose: VITIS vector addition

*******************************************************************************
a = [1,2,3,4,...,256]
    [2,3,4,5,...,257]
    [...............]
    [256,257,...,511]

b = [1,2,3,4,...,256]
    [2,3,4,5,...,257]
    [...............]
    [256,257,...,511]

*******************************************************************************/


#include "vadd.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>


//#ifdef x86
static unsigned long long cpucycles(void)
{
    unsigned long long result;
      __asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
              : "=a" (result) ::  "%rdx");
        return result;
}
//#endif



int main(int argc, char* argv[]) {

    uint64_t cyc0; 
    uint64_t cyc1;    
    struct timeval start;
    struct timeval end;
    unsigned long timer;

    int a[256][256] = {};
    int b[256][256] = {};

    for(int m = 0 ; m<256; m++){
        for(int n = 0 ; n<256; n++){
            a[m][n]=m+n+1;
            b[m][n]=m+n+1;
        }
    }    


    int c[256][256] = {};

    gettimeofday(&start,NULL);
    cyc0 = cpucycles();

    for(int i = 0 ; i<256; i++){
        for(int j=0;j<256;j++){
            c[i][j]=0;
            for(int k=0;k<256;k++){
                c[i][j] += a[i][k] * b[k][j];
                //c[i][j] += (i+k+1) * (k+j+1);
            }
            
        }
    }        

    cyc1 =  cpucycles();
    gettimeofday(&end,NULL);

    timer = 1000000* (end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    printf("time = %ld us\n", timer);

    printf("\ncycles of matrix : %" PRIu64 "\n\n", cyc1-cyc0);




    printf("result of c\n");
    for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			printf("%d\t", c[i][j]);	
		}
		printf("\n");
	}
	return 0;    

}
