#include <adf.h>
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
  kernel first;     
  //parameter lut0;

public:
  input_plio datain1, datain2;
  //input_port vectorInput, factorInput; 
  //inout_port vectorOutput, factorOutput;
  output_plio dataout;
  simpleGraph()
  {
    datain1 = input_plio::create("datain1",plio_32_bits, "data/inputmatrixa.txt",500);
    datain2 = input_plio::create("datain2",plio_32_bits, "data/inputmatrix.txt",500);

    dataout = output_plio::create("dataout",plio_32_bits, "data/output_1.txt",500);
   
    //datain1 = input_gmio::create("datain1",32, 1000);
    //datain2 = input_gmio::create("datain2",32, 1000);

    //dataout = output_gmio::create("dataout",32, 1000);
    
    first = kernel::create(matrix256);
    //connect(in0.out[0], first.in[0]); 
    //dimensions(first.in[0]) = { 8 };
    //single_buffer(first.in[0]);               //uncomment for single buffer, by default double buffer will be used.
    //connect(first.out[0], out0.in[0]);
    //dimensions(first.out[0]) = { 8 };

    //lut0 = parameter::array (LUT);
    //connect<> (lut0, first);

    connect<stream> net0 (datain1.out[0], first.in[0]);  //net connections for stream-stream 
    connect<stream> net1 (datain2.out[0], first.in[1]);
    connect<stream> net2 (first.out[0], dataout.in[0]);
    //connect<parameter> (vectorInput, first.in[2]);    //connection for RTP_array
    //connect<parameter> (sync(first.inout[0]), vectorOutput);
    
    //connect<parameter> (factorInput, first.in[3]);
    //connect<parameter> (sync(first.inout[1]), factorOutput);
    
    source(first) = "src/kernels/vitis_single_node_templates.cc";
    
    runtime<ratio>(first) = 0.8;
    }
};

