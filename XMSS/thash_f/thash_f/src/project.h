#include <adf.h>
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
  kernel thash_f1;  
  kernel sha2561;
  kernel sha256_mask1;
  kernel sha256_f1;
    

public:
  input_gmio datain;
  input_gmio addrin;
  //input_port pubseed; 
  //inout_port factorOutput;
  //output_plio out0;
  output_gmio dataout;
  output_gmio addrout;
  simpleGraph()
  {
   
    thash_f1 = kernel::create(thash_f);
    sha2561 = kernel::create(sha256);
    sha256_mask1 = kernel::create(sha256_mask);
    sha256_f1 = kernel::create(sha256_f);

    datain = input_gmio::create("datain",256,1000); //burst_length
    addrin = input_gmio::create("addrin",256,1000); //burst_length

    dataout = output_gmio::create("dataout",256,1000);
    addrout = output_gmio::create("addrout",256,1000);
    //out0 = output_plio::create(plio_32_bits, "data/output_1.txt");
    
    

    connect<stream> net0 (datain.out[0], thash_f1.in[0]);  //net connections for stream-stream 
    connect<stream> net1 (addrin.out[0], thash_f1.in[1]);

    connect<stream> net2 (thash_f1.out[0], sha2561.in[0]);

    connect<stream> net3 (thash_f1.out[1], sha256_mask1.in[0]);
    
    connect<stream> net4 (sha2561.out[0], sha256_f1.in[0]);
    connect<stream> net5 (sha256_mask1.out[0], sha256_f1.in[1]);

    connect<stream> net6 (sha256_f1.out[0], dataout.in[0]);
    connect<stream> net7 (sha256_f1.out[1], addrout.in[0]);
    fifo_depth(net0) = 128;
    fifo_depth(net1) = 128;
    fifo_depth(net2) = 128;
    fifo_depth(net3) = 128;
    fifo_depth(net4) = 128;
    fifo_depth(net5) = 128;
    fifo_depth(net6) = 128;
    fifo_depth(net7) = 128;
    //connect<parameter> (vectorInput, first.in[2]);    //connection for RTP_array
    //connect<parameter> (sync(first.inout[0]), vectorOutput);
    
   // connect<parameter> (pubseed, thash_f1.in[2]);
    //connect<parameter> (new_len, first.in[2]);
    
    
    source(thash_f1) = "src/kernels/thash_f.cc";
    source(sha2561) = "src/kernels/sha256.cc";
    source(sha256_mask1) = "src/kernels/sha256_mask.cc";
    source(sha256_f1) = "src/kernels/sha256_f.cc";

    runtime<ratio>(thash_f1) = 0.1;
    runtime<ratio>(sha2561) = 0.1;
    runtime<ratio>(sha256_mask1) = 0.1;
    runtime<ratio>(sha256_f1) = 0.1;

    adf::location<kernel>(thash_f1)=adf::tile(26,0); 
    adf::location<kernel>(sha2561)=adf::tile(26,1); 
    adf::location<kernel>(sha256_mask1)=adf::tile(27,1); 
    adf::location<kernel>(sha256_f1)=adf::tile(27,0);   
    }
};

