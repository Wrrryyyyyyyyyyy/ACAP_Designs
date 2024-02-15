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

    
    



    cyc0 = cpucycles(); 
    gettimeofday(&start,NULL);

    mygraph.init();
  


            
    //mygraph.run(65536);
    mygraph.run(32);
    mygraph.wait();
    //GMIO::free(outputarray);	 
    mygraph.end();
    
gettimeofday(&end,NULL);
timer = 1000000* (end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
printf("time = %ld us\n", timer);

cyc1 =  cpucycles();
printf("\ncycles of matrix : %" PRIu64 "\n\n", cyc1-cyc0);

  
  
    
    return 0;
} 
