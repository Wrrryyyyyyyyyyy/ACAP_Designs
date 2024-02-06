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

#include "graph.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#include <unistd.h>

using namespace std;
using namespace adf;

FirGraph2 F2;

#if defined(__AIESIM__) || defined(__X86SIM__)

int main(){
	F2.init();
	F2.run(NITERATIONS);
	F2.end();

#if defined(__X86SIM__)

#define OUTFILE "./x86simulator_output/data/output.txt"
#define REF_OUTFILE "../data/refOutput.txt"

	ifstream fin1,fin2;
	char l1[256],l2[256];

//	char cwd[256];
//	if (getcwd(cwd, sizeof(cwd)) == NULL)
//	      perror("getcwd() error");
//	    else
//	      printf("current working directory is: %s\n", cwd);

	fin1.open(REF_OUTFILE);
	if(!fin1.is_open())
	{
		cerr << "Cannot open '" << REF_OUTFILE << "'" << endl;
		cin >> l1;
		return(1);
	}



	fin2.open(OUTFILE);
	if(!fin2.is_open())
	{
		cerr << "Cannot open '" << OUTFILE <<  "'" << endl;
		cin >> l1;
		return(1);
	}

	int ntot=0;
	int nerr=0;

	while(!fin1.eof() && !fin2.eof())
	{
		fin1.getline(l1,256);
		fin2.getline(l2,256);
		if(strlen(l1)>0 && strlen(l2)>0)
		{
			if(!strcmp(l1,l2))
				cout << "Line " << setw(4) << ntot << "     OK" << endl;
			else
			{
				cout << "Line " << setw(4) << ntot << "          ERROR     Ref: " << l1 << "     Simulation: " << l2 << endl;
				nerr++;
			}
			ntot++;
		}
	}

	fin1.close();
	fin2.close();

	cout << endl << endl;
	cout << "Number of Output: " << ntot << endl;
	cout << "Number of CORRECT output: " << ntot-nerr << endl;
	cout << "Number of WRONG   output: " << nerr << endl;
#endif
	return(0);
}

#endif
