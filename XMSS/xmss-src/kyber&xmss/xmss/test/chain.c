/*
 *  
 *
 * Copyright (C) 2019
 * Authors: Wen Wang <wen.wang.ww349@yale.edu>
 *          Ruben Niederhagen <ruben@polycephaly.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

#ifndef x86
#include <Murax.h>
#endif

#include "../wots.h"
#include "../randombytes.h"
#include "../params.h"




#ifdef x86
static unsigned long long cpucycles(void)
{
    unsigned long long result;
      __asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
              : "=a" (result) ::  "%rdx");
        return result;
}
#endif
void gen_chain(const xmss_params *params,
    unsigned char *out, const unsigned char *in,
    unsigned int start, unsigned int steps,
    const unsigned char *pub_seed, uint32_t addr[8]);


int main()
{

	struct timeval start,end;  
	gettimeofday(&start, NULL );

    xmss_params params;
    // TODO test more different OIDs
    uint32_t oid = 0x00000001;

    /* For WOTS it doesn't matter if we use XMSS or XMSSMT. */
    xmss_parse_oid(&params, oid);

    //unsigned char seed[params.n]; 
    unsigned char pub_seed[params.n];
    unsigned char pk[params.n];
    uint32_t addr[8] = {0};

    randombytes(pub_seed, params.n);
    randombytes(pk, params.n);
    randombytes((unsigned char *)addr, 8 * sizeof(uint32_t)); 

    //#ifndef x86
      uint64_t t0 = -cpucycles();
    //#endif

    // if we need a wots, just repeat it for 67 times
    for(int i=0;i<67;i++){
    gen_chain(&params, pk, pk, 0, params.wots_w - 1,//1 
              pub_seed, addr);
    }
    
    //#ifndef x86
      t0 += cpucycles();
    //#endif

    printf("WOTS Public Key: ");
    for (unsigned int j = 0; j < params.n; j++)
      printf("%02x", pk[j]);
    printf("\n\n");

    //#ifndef x86
      printf("\n------------PERFORMANCE------------\n\n");
      printf("cycles for chain: %" PRIu64 "\n\n", t0);
    //#endif
    
        gettimeofday(&end, NULL );  
	long timeuse =1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;  
	printf("time=%f\n",timeuse /1000000.0); //us  
}
 
