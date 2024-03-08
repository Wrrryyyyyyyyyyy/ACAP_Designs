#include "project.h"
#include <fstream>
#include <cstdlib>
#include <string.h>

simpleGraph mygraph;




int main(int argc, char **argv) 
{
    volatile int mlen = 128; 
    //volatile int new_len = package_msg(mlen);
    
    //unsigned char input[] = {1,2,3,4,5,6,7,8,9,10,00,00};
    unsigned char input[128] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};

    unsigned char buff[32];  

    uint8_t  *inputbuf  = (uint8_t*) GMIO::malloc(mlen*sizeof(uint8_t)); //GMIO 只能用这种方式输入
    uint8_t *outputbuf = (uint8_t*) GMIO::malloc(32*sizeof(uint8_t));


    
  printf("\nThe sha256 hash is :\n");
    	for(int i=0;i<mlen;i++)
	{
        inputbuf[i]=input[i];
		printf("%x",inputbuf[i]);	
	}


    mygraph.init();
    
    
    mygraph.run(1);
    for(int i=0;i<1;i++){
        mygraph.in.gm2aie_nb(&inputbuf[0],mlen*sizeof(uint8_t));
        mygraph.update(mygraph.mlen, mlen);
  	    //mygraph.wait(); 
        mygraph.out.aie2gm_nb(&outputbuf[0],32*sizeof(uint8_t));
        mygraph.out.wait(); //important !! wait for data move to DDR
    }
    mygraph.end();
    printf("\nThe sha256 hash is :\n");
    	for(int i=0;i<32;i++)
	{
 
		printf("%02x",outputbuf[i]);	
	}
    printf("\n");

    GMIO::free(inputbuf);
    GMIO::free(outputbuf);
  return 0;
} 
