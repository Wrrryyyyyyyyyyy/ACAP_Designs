#include "project.h"
#include "adf/window/types.h"
#include <fstream>
#include <cstdlib>
#include <inttypes.h>
#include <sys/time.h>

simpleGraph mygraph;

static unsigned long long cpucycles(void)
{
    unsigned long long result;
      __asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
              : "=a" (result) ::  "%rdx");
        return result;
}

int main(int argc, char **argv) 
{
    uint64_t cyc0,cyc1;

    struct timeval start;
    struct timeval end;
    unsigned long timer;

    const int block_size = 256;
    int32 *inputarray1=(int32*)GMIO::malloc(512*sizeof(int32));
    int32 *inputarray2=(int32*)GMIO::malloc(512*sizeof(int32));
    int32 *outputarray=(int32*)GMIO::malloc(512*sizeof(int32));


    for(int i=0;i<512;i++){
        inputarray1[i]=i+1;
        inputarray2[i]=i+1;
    }   

    cyc0 = cpucycles(); 
    gettimeofday(&start,NULL);

    mygraph.init();
  

for(int i=0 ; i < block_size;i++){
    
    for(int j=0 ; j < block_size;j++){
            
    mygraph.run(1);
    
    mygraph.datain1.gm2aie_nb(inputarray1+i,block_size*sizeof(int32));
    mygraph.datain2.gm2aie_nb(inputarray2+j,block_size*sizeof(int32));
    mygraph.dataout.aie2gm_nb(outputarray,sizeof(int32));
    
    mygraph.dataout.wait(); // important!
   
    //printf("%d\t",outputarray[0]);
        
    }
  
    //printf("\n");
    
}
gettimeofday(&end,NULL);
timer = 1000000* (end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
printf("time = %ld us\n", timer);

cyc1 =  cpucycles();
printf("\ncycles of matrix : %" PRIu64 "\n\n", cyc1-cyc0);

  //ofsFactor.close();
  //ofsVector.close();
  

    GMIO::free(inputarray1);
    GMIO::free(inputarray2);

  
    GMIO::free(outputarray);	 
    mygraph.end();
    return 0;
} 
