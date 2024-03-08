#include "../kernels.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <adf.h>
#include <aie_api/aie.hpp>
#include "aie_api/aie_types.hpp"


#define rightrotate(w,n) ((w>>n) | (w)<< (32-(n)))
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define copy_uint32(p, val) *((uint32_t *)p) = __builtin_bswap32((val))//gcc 内建函数__builtin_bswap32，
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define copy_uint32(p, val) *((uint32_t *)p) = (val)
#else
#error "Unsupported target architecture endianess!"
#endif

static const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


// GMIO 送进来的数据必须是32的整数倍，否则会导致无法全部读取而死锁，所以决定在外面打包全部的sha数据后再送进来
void sha256(input_stream<uint32> * __restrict bufin, int len , output_stream<uint32>* __restrict bufout)
{
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    aie::tile tile=aie::tile::current();
    unsigned long long time1=tile.cycles();
    //v8uint32 H = concat(0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19);

    int r = (int)(len * 8 % 512); //rest number of data
    int append = ((r < 448) ? (448 - r) : (448 + 512 - r)) / 8;    
    size_t new_len = len + append + 8;// 原始数据+填充+64bit位数 
    
    unsigned char buf[new_len];//unsigned char buf[new_len]; 
    memset(buf + len,0,append); //padding清零<string.h>
    printf("\n");
    uint32_t temp[len/4];
    for(int j=0;j<((len-1)/4)+1;j++){  //we can not use function ceil() in AIE, so we have to manually extract the int. //wyz add in 2024.2.23
        temp[j]=readincr(bufin);  // important !! every instruction reads 32bit data, so DDR must instore the data in mltiple of 32-bit, or it causes deadlock!! //wyz add in 2024.2.23   	
    }
       
    if (len > 0) {
        memcpy(buf, temp, len); // 
    }

    buf[len] = (unsigned char)0x80;
    
    uint64_t bits_len = len * 8;
    for (int i = 0; i < 8; i++) 
    chess_prepare_for_pipelining
    chess_loop_range(8, 8)
    {
        buf[len + append + i] = (bits_len >> ((7 - i) * 8)) & 0xff;
    }
    
    //above process input data, read and package 

    //below process hash function, compress and write
    uint32_t w[64];
    memset(w ,0,64); //change bzero to memset
   
    size_t chunk_len = new_len / 64; //分512bit区块
   
    
    for (int idx = 0; idx < chunk_len; idx++) {
        uint32_t val = 0;
        for (int i = 0; i < 64; i++) {//将块分解为16个32-bit的big-endian的字，记为w[0], …, w[15]
            val =  val | (*(buf + idx * 64 + i) << (8 * (3 - i%4))); //2024.2.21 wyz modify (3-i) -> (3-i%4)
            if (i % 4 == 3) {
                w[i / 4] = val;
                val = 0;
            }
        }

        
        
        for (int i = 16; i < 64; i++) {//前16个字直接由以上消息的第i个块分解得到，其余的字由如下迭代公式得到：
            uint32_t s0 = rightrotate(w[i - 15], 7) ^ rightrotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
            uint32_t s1 = rightrotate(w[i - 2], 17) ^ rightrotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
         
            
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;


        for (int i = 0; i < 64; i++) {//
            uint32_t s_1 = rightrotate(e, 6) ^ rightrotate(e, 11) ^ rightrotate(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + s_1 + ch + k[i] + w[i];
            uint32_t s_0 = rightrotate(a, 2) ^ rightrotate(a, 13) ^ rightrotate(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = s_0 + maj;
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
               
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
        
    }


  
    //uint8_t out[32];
    //copy_uint32(out, h0);
    //copy_uint32(out+1, h1);
    //copy_uint32(out+2, h2);
    //copy_uint32(out+3, h3);
    //copy_uint32(out+4, h4);
    //copy_uint32(out+5, h5);
    //copy_uint32(out+6, h6);
    //copy_uint32(out+7, h7);

    unsigned long long time2=tile.cycles();
    printf("&cycles=%lld",time2-time1);

    writeincr(bufout, h0);
    writeincr(bufout, h1);
    writeincr(bufout, h2);
    writeincr(bufout, h3);
    writeincr(bufout, h4);
    writeincr(bufout, h5);
    writeincr(bufout, h6);
    writeincr(bufout, h7);
    
    //printf("\n result of sha256 is \n");
    //for(int i=0;i<32;i++)
	//{
	//	printf("%02x",out[i]);	
	//}
    //printf("\n");
 
}
