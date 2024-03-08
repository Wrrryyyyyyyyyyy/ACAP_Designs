#include <adf.h>

//#ifndef FUNCTION_KERNELS_H
//#define FUNCTION_KERNELS_H
#ifndef sha256_h
#define sha256_h

// len is the len of message, new_len should be pckaged message
void sha256(input_stream<uint32> *bufin,  output_stream<uint32>* bufout);
void thash_f(input_stream<uint32> *  data, input_stream<uint32> * addr,  output_stream<uint32>*  dout1, output_stream<uint32>*  dout2);
void sha256_mask(input_stream<uint32> * bufin, /*int len , */ output_stream<uint32>*  bufout);
void sha256_f(input_stream<uint32> *  prf_in, input_stream<uint32> * mask_in,  output_stream<uint32>*  dout, output_stream<uint32>*  addr_out);
uint32_t swap32(uint32_t data);


#endif
