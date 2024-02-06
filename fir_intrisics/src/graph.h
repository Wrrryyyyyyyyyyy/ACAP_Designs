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

#pragma once

#include "aie_kernels.h"
#include "system_settings.h"

using namespace adf;

class FirGraph2 : public graph {
private:
	kernel k1;
public:
	input_plio in;
	output_plio out;

	FirGraph2()
	{
		// Create the PLIO ports
		in = input_plio::create("DataIn", plio_32_bits, "data/input.txt", 500.0);
		out = output_plio::create("DataOut", plio_32_bits, "data/output.txt", 500.0);		

		//Create Kernel
		k1 = kernel::create(fir_16taps_symm);

		// Create nets to connect kernels and IO ports
		connect< > net1 (in.out[0],k1.in[0]);
		connect< > net2 (k1.out[0],out.in[0]);

		// Specify kernel sources
		source(k1) = "aie_kernels/fir_16taps_symm.cpp";

		// Specify kernel runtime
		runtime<ratio>(k1) = 0.8;
	};
};
