#include <adf.h>

//#ifndef FUNCTION_KERNELS_H
//#define FUNCTION_KERNELS_H
#ifndef sha256_h
#define sha256_h

// len is the len of message, new_len should be pckaged message
void sha256(input_stream<uint32> *bufin, int len,  output_stream_uint32* bufout);



#endif
