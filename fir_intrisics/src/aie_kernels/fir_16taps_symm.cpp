//<copyright-disclaimer-start>
//  **************************************************************************************************************
//  * © 2023 Advanced Micro Devices, Inc. All rights reserved.                                                   *
//  * DISCLAIMER                                                                                                 *
//  * The information contained herein is for informational purposes only, and is subject to change              *
//  * without notice. While every precaution has been taken in the preparation of this document, it              *
//  * may contain technical inaccuracies, omissions and typographical errors, and AMD is under no                *
//  * obligation to update or otherwise correct this information.  Advanced Micro Devices, Inc. makes            *
//  * no representations or warranties with respect to the accuracy or completeness of the contents of           *
//  * this document, and assumes no liability of any kind, including the implied warranties of noninfringement,  *
//  * merchantability or fitness for particular purposes, with respect to the operation or use of AMD            *
//  * hardware, software or other products described herein.  No license, including implied or                   *
//  * arising by estoppel, to any intellectual property rights is granted by this document.  Terms and           *
//  * limitations applicable to the purchase or use of AMD’s products are as set forth in a signed agreement     *
//  * between the parties or in AMD's Standard Terms and Conditions of Sale. GD-18                               *
//  *                                                                                                            *
//  **************************************************************************************************************
//<copyright-disclaimer-end>

/**
 * 16-tap symmetric FIR filter
 *
 * Coefficients:            c0 c1 c2 c3 c4 c5 c6 c7 c7 c6 c5 c4 c3 c2 c1 c0
 * Data:                    d0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 ...
 * Intermediate:           o0  = c0*( 0+15) + c1*( 1+14) + c2*( 2+13) + c3*( 3+12)
 *                         o1  = c0*( 1+16) + c1*( 2+15) + c2*( 3+14) + c3*( 4+13)
 *                         o2  = c0*( 2+17) + c1*( 3+16) + c2*( 4+15) + c3*( 5+14)
 *                         o3  = c0*( 3+18) + c1*( 4+17) + c2*( 5+16) + c3*( 6+15)
 *
 *                         o0 += c4*( 4+11) + c5*( 5+10) + c6*( 6+ 9) + c7*( 7+ 8)
 *                         o1 += c4*( 5+12) + c5*( 6+11) + c6*( 7+10) + c7*( 8+ 9)
 *                         o2 += c4*( 6+13) + c5*( 7+12) + c6*( 8+11) + c7*( 9+10)
 *                         o3 += c4*( 7+14) + c5*( 8+13) + c6*( 9+12) + c7*(10+11)
 *
 * o0..3  = f(c0..3, d0..6,  d12..18)
 * o0..3 += f(c4..7, d4..10, d8..14)
 *
 * Operator Definition
 *		using mulop = aie::sliding_mul_sym_xy_ops<  4  ,  16   ,      1     ,      1    ,   int16   , cint16>;
 *		                                            ^      ^          ^            ^          ^          ^
 *		                                         Lanes   Points   CoeffStep   DataStepXY  CoeffType  DataType
 *
 * Function
 *		auto acc = mulop::mul_sym(coeff,       0,   sbuff,     0);
 *		                            ^          ^      ^        ^
 *                            Coefficient   Coeff   Data     Data
 *                            Vector        Start   Vector   Start
 *
 */

#include <adf.h>
#include "system_settings.h"
#include "aie_kernels.h"

using namespace adf;

alignas(32) int16_t taps[FIR_LEN] = {-1000, 2000, -3000, 4000, -5000, 6000, -7000, 8000, 8000, -7000, 6000, -5000, 4000, -3000, 2000, -1000};

void fir_16taps_symm // _single_buf_array_indexing
		(
		input_buffer<cint16, extents<INPUT_SAMPLES>, margin<FIR_LEN>> & _restrict cb_input,
		output_buffer<cint16, extents<OUTPUT_SAMPLES>> & _restrict cb_output
		)
{
	//auto _restrict inIter=aie::begin_vector_random_circular<8>(cb_input);    //only way to read vector data
	//auto _restrict outIter=aie::begin_vector_random_circular<8>(cb_output);
    auto    inIter = in.data();
    auto    outIter = out.data();

	const unsigned samples  = cb_output.size();
	const int shift         = SRS_SHIFT ;

	//const aie::vector<int16,FIR_LEN> coeff = aie::load_v<FIR_LEN>((int16 *)taps) ;
    v16int16 coeff = taps;

	const unsigned LSIZE = (samples >> 2 ); // assuming # of samples is integer power of 2 and >= 64

	for ( unsigned i=0; i<LSIZE; i+=2)
    chess_prepare_for_pipeling
    chess_loop_range(32,64)
	{
		//aie::vector<cint16,32> sbuff;//
		//aie::vector<cint16,8> dataout;//
        v32cint16 sbuff;
        v8cint16 dataout;

        upd_elem(v32cint16 sbuff, 0,*inIter++);
        upd_elem(v32cint16 sbuff, 1,*inIter++);
        upd_elem(v32cint16 sbuff, 2,*inIter++);
        upd_elem(v32cint16 sbuff, 3,*inIter++);
        upd_elem(v32cint16 sbuff, 4,*inIter++);
        upd_elem(v32cint16 sbuff, 5,*inIter++);
        upd_elem(v32cint16 sbuff, 6,*inIter++);
        upd_elem(v32cint16 sbuff, 7,*inIter++);
        upd_elem(v32cint16 sbuff, 8,*inIter++);
        upd_elem(v32cint16 sbuff, 9,*inIter++);
        upd_elem(v32cint16 sbuff, 10,*inIter++);
        upd_elem(v32cint16 sbuff, 11,*inIter++);
        upd_elem(v32cint16 sbuff, 12,*inIter++);
        upd_elem(v32cint16 sbuff, 13,*inIter++);
        upd_elem(v32cint16 sbuff, 14,*inIter++);
        upd_elem(v32cint16 sbuff, 15,*inIter++);
        upd_elem(v32cint16 sbuff, 16,*inIter++);
        upd_elem(v32cint16 sbuff, 17,*inIter++);
        upd_elem(v32cint16 sbuff, 18,*inIter++);
        upd_elem(v32cint16 sbuff, 19,*inIter);

        inIter = inIter -11;

		//sbuff.insert(0, *inIter++); 	// 00++|04++|____|____    ____|____|____|____
		//sbuff.insert(1, *inIter++);		// 00..|04..|08++|12++    ____|____|____|____
		//sbuff.insert(2, *inIter); 		// 00..|04..|08..|12..    16++|20++|____|____

		//constexpr unsigned Lanes=4, Points=16, CoeffStep=1, DataStepXY=1;
		//using mulop = aie::sliding_mul_sym_xy_ops<Lanes, Points, CoeffStep, DataStepXY,int16,cint16>;


		//auto acc = mulop::mul_sym(coeff,0,sbuff,0); // o0..3  =f(c0..7, d0..10,  d8..18)

        auto acc = mul4_sym(sbuff,0,0x3210, 1, 15, coeff,0,0x0000,1);

		dataout.insert(0, acc.to_vector<cint16>(shift)); //shift write 16 bit， suppose acc = 48 bit

		//acc = mulop::mul_sym(coeff,0,sbuff,4); // o4..7  =f(c0..7, d4..14,  d12..22)
        acc = mul4_sym(sbuff,4,0x3210,1,19,coeff,0,0x0000,1);
		dataout.insert(1, acc.to_vector<cint16>(shift));
		*outIter++=dataout;
        *outIter++=dataout;
        *outIter++=dataout;
        *outIter++=dataout;
        *outIter++=dataout;
        *outIter++=dataout;
        *outIter++=dataout;
        *outIter++=dataout;
        
		//inIter=inIter-1;
	}
}
