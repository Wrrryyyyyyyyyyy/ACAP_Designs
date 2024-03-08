#include <adf.h>
#include "kernels.h"

using namespace adf;

class simpleGraph : public adf::graph {
private:
  kernel thash_f1;  
  kernel sha2561;
  kernel sha256_mask1;
  kernel sha256_f1;
    
  kernel thash_f2;  
  kernel sha2562;
  kernel sha256_mask2;
  kernel sha256_f2; 

  kernel thash_f3;  
  kernel sha2563;
  kernel sha256_mask3;
  kernel sha256_f3;   

  kernel thash_f4;  
  kernel sha2564;
  kernel sha256_mask4;
  kernel sha256_f4;  
  
  kernel thash_f5;  
  kernel sha2565;
  kernel sha256_mask5;
  kernel sha256_f5; 

  kernel thash_f6;  
  kernel sha2566;
  kernel sha256_mask6;
  kernel sha256_f6; 

  kernel thash_f7;  
  kernel sha2567;
  kernel sha256_mask7;
  kernel sha256_f7; 

  kernel thash_f8;  
  kernel sha2568;
  kernel sha256_mask8;
  kernel sha256_f8; 

  kernel thash_f9;  
  kernel sha2569;
  kernel sha256_mask9;
  kernel sha256_f9;

  kernel thash_f10;  
  kernel sha25610;
  kernel sha256_mask10;
  kernel sha256_f10;

  kernel thash_f11;  
  kernel sha25611;
  kernel sha256_mask11;
  kernel sha256_f11;

  kernel thash_f12;  
  kernel sha25612;
  kernel sha256_mask12;
  kernel sha256_f12;

  kernel thash_f13;  
  kernel sha25613;
  kernel sha256_mask13;
  kernel sha256_f13;

  kernel thash_f14;  
  kernel sha25614;
  kernel sha256_mask14;
  kernel sha256_f14;

  kernel thash_f15;  
  kernel sha25615;
  kernel sha256_mask15;
  kernel sha256_f15;
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
    //out0 = output_plio::create(plio_32_bits, "data/output_1.txt");
    //connect<stream> net95 (sha256_f15.out[0], out0.in[0]);

    datain = input_gmio::create("datain",256,1000); //burst_length
    addrin = input_gmio::create("addrin",256,1000); //burst_length

    dataout = output_gmio::create("dataout",256,1000);
    addrout = output_gmio::create("addrout",256,1000);
    
    thash_f1 = kernel::create(thash_f);
    sha2561 = kernel::create(sha256);
    sha256_mask1 = kernel::create(sha256_mask);
    sha256_f1 = kernel::create(sha256_f);

    thash_f2 = kernel::create(thash_f);
    sha2562 = kernel::create(sha256);
    sha256_mask2 = kernel::create(sha256_mask);
    sha256_f2 = kernel::create(sha256_f);

    thash_f3 = kernel::create(thash_f);
    sha2563 = kernel::create(sha256);
    sha256_mask3 = kernel::create(sha256_mask);
    sha256_f3 = kernel::create(sha256_f);
    
    thash_f4 = kernel::create(thash_f);
    sha2564 = kernel::create(sha256);
    sha256_mask4 = kernel::create(sha256_mask);
    sha256_f4 = kernel::create(sha256_f);

    thash_f5 = kernel::create(thash_f);
    sha2565 = kernel::create(sha256);
    sha256_mask5 = kernel::create(sha256_mask);
    sha256_f5 = kernel::create(sha256_f);

    thash_f6 = kernel::create(thash_f);
    sha2566 = kernel::create(sha256);
    sha256_mask6 = kernel::create(sha256_mask);
    sha256_f6 = kernel::create(sha256_f);

    thash_f7 = kernel::create(thash_f);
    sha2567 = kernel::create(sha256);
    sha256_mask7 = kernel::create(sha256_mask);
    sha256_f7 = kernel::create(sha256_f);

    thash_f8 = kernel::create(thash_f);
    sha2568 = kernel::create(sha256);
    sha256_mask8 = kernel::create(sha256_mask);
    sha256_f8 = kernel::create(sha256_f);

    thash_f9 = kernel::create(thash_f);
    sha2569 = kernel::create(sha256);
    sha256_mask9 = kernel::create(sha256_mask);
    sha256_f9 = kernel::create(sha256_f);

    thash_f10 = kernel::create(thash_f);
    sha25610 = kernel::create(sha256);
    sha256_mask10 = kernel::create(sha256_mask);
    sha256_f10 = kernel::create(sha256_f);

    thash_f11 = kernel::create(thash_f);
    sha25611 = kernel::create(sha256);
    sha256_mask11 = kernel::create(sha256_mask);
    sha256_f11 = kernel::create(sha256_f);

    thash_f12 = kernel::create(thash_f);
    sha25612 = kernel::create(sha256);
    sha256_mask12 = kernel::create(sha256_mask);
    sha256_f12 = kernel::create(sha256_f);

    thash_f13 = kernel::create(thash_f);
    sha25613 = kernel::create(sha256);
    sha256_mask13 = kernel::create(sha256_mask);
    sha256_f13 = kernel::create(sha256_f);

    thash_f14 = kernel::create(thash_f);
    sha25614 = kernel::create(sha256);
    sha256_mask14 = kernel::create(sha256_mask);
    sha256_f14 = kernel::create(sha256_f);

    thash_f15 = kernel::create(thash_f);
    sha25615 = kernel::create(sha256);
    sha256_mask15 = kernel::create(sha256_mask);
    sha256_f15 = kernel::create(sha256_f);
    //connect<parameter> (pubseed, thash_f1.in[2]);
    //connect<parameter> (pubseed, thash_f2.in[2]);

    connect<stream> net0 (datain.out[0], thash_f1.in[0]);  //net connections for stream-stream 
    connect<stream> net1 (addrin.out[0], thash_f1.in[1]);
    connect<stream> net2 (thash_f1.out[0], sha2561.in[0]);
    connect<stream> net3 (thash_f1.out[1], sha256_mask1.in[0]);   
    connect<stream> net4 (sha2561.out[0], sha256_f1.in[0]);
    connect<stream> net5 (sha256_mask1.out[0], sha256_f1.in[1]);

    connect<stream> net6 (sha256_f1.out[0], thash_f2.in[0]);
    connect<stream> net7 (sha256_f1.out[1], thash_f2.in[1]);
    connect<stream> net10 (thash_f2.out[0], sha2562.in[0]);
    connect<stream> net11 (thash_f2.out[1], sha256_mask2.in[0]);   
    connect<stream> net12 (sha2562.out[0], sha256_f2.in[0]);
    connect<stream> net13 (sha256_mask2.out[0], sha256_f2.in[1]);


    connect<stream> net14 (sha256_f2.out[0], thash_f3.in[0]);
    connect<stream> net15 (sha256_f2.out[1], thash_f3.in[1]);
    connect<stream> net16 (thash_f3.out[0], sha2563.in[0]);
    connect<stream> net17 (thash_f3.out[1], sha256_mask3.in[0]);  
    connect<stream> net18 (sha2563.out[0], sha256_f3.in[0]);
    connect<stream> net19 (sha256_mask3.out[0], sha256_f3.in[1]);


    connect<stream> net20 (sha256_f3.out[0], thash_f4.in[0]);
    connect<stream> net21 (sha256_f3.out[1], thash_f4.in[1]);
    connect<stream> net22 (thash_f4.out[0], sha2564.in[0]);
    connect<stream> net23 (thash_f4.out[1], sha256_mask4.in[0]);
    connect<stream> net24 (sha2564.out[0], sha256_f4.in[0]);
    connect<stream> net25 (sha256_mask4.out[0], sha256_f4.in[1]);
   

    connect<stream> net26 (sha256_f4.out[0], thash_f5.in[0]);
    connect<stream> net27 (sha256_f4.out[1], thash_f5.in[1]);
    connect<stream> net28 (thash_f5.out[0], sha2565.in[0]);
    connect<stream> net29 (thash_f5.out[1], sha256_mask5.in[0]);   
    connect<stream> net30 (sha2565.out[0], sha256_f5.in[0]);
    connect<stream> net31 (sha256_mask5.out[0], sha256_f5.in[1]);


    connect<stream> net32 (sha256_f5.out[0], thash_f6.in[0]);
    connect<stream> net33 (sha256_f5.out[1], thash_f6.in[1]);
    connect<stream> net34 (thash_f6.out[0], sha2566.in[0]);
    connect<stream> net35 (thash_f6.out[1], sha256_mask6.in[0]);   
    connect<stream> net36 (sha2566.out[0], sha256_f6.in[0]);
    connect<stream> net37 (sha256_mask6.out[0], sha256_f6.in[1]);

    connect<stream> net38 (sha256_f6.out[0], thash_f7.in[0]);
    connect<stream> net39 (sha256_f6.out[1], thash_f7.in[1]);
    connect<stream> net40 (thash_f7.out[0], sha2567.in[0]);
    connect<stream> net41 (thash_f7.out[1], sha256_mask7.in[0]);   
    connect<stream> net42 (sha2567.out[0], sha256_f7.in[0]);
    connect<stream> net43 (sha256_mask7.out[0], sha256_f7.in[1]);

    connect<stream> net44 (sha256_f7.out[0], thash_f8.in[0]);
    connect<stream> net45 (sha256_f7.out[1], thash_f8.in[1]);
    connect<stream> net46 (thash_f8.out[0], sha2568.in[0]);
    connect<stream> net47 (thash_f8.out[1], sha256_mask8.in[0]);   
    connect<stream> net48 (sha2568.out[0], sha256_f8.in[0]);
    connect<stream> net49 (sha256_mask8.out[0], sha256_f8.in[1]);

    connect<stream> net50 (sha256_f8.out[0], thash_f9.in[0]);
    connect<stream> net51 (sha256_f8.out[1], thash_f9.in[1]);
    connect<stream> net52 (thash_f9.out[0], sha2569.in[0]);
    connect<stream> net53 (thash_f9.out[1], sha256_mask9.in[0]);   
    connect<stream> net54 (sha2569.out[0], sha256_f9.in[0]);
    connect<stream> net55 (sha256_mask9.out[0], sha256_f9.in[1]);

    connect<stream> net56 (sha256_f9.out[0], thash_f10.in[0]);
    connect<stream> net57 (sha256_f9.out[1], thash_f10.in[1]);
    connect<stream> net58 (thash_f10.out[0], sha25610.in[0]);
    connect<stream> net59 (thash_f10.out[1], sha256_mask10.in[0]);   
    connect<stream> net60 (sha25610.out[0], sha256_f10.in[0]);
    connect<stream> net61 (sha256_mask10.out[0], sha256_f10.in[1]);

    connect<stream> net62 (sha256_f10.out[0], thash_f11.in[0]);
    connect<stream> net63 (sha256_f10.out[1], thash_f11.in[1]);
    connect<stream> net64 (thash_f11.out[0], sha25611.in[0]);
    connect<stream> net65 (thash_f11.out[1], sha256_mask11.in[0]);   
    connect<stream> net66 (sha25611.out[0], sha256_f11.in[0]);
    connect<stream> net67 (sha256_mask11.out[0], sha256_f11.in[1]);

    connect<stream> net68 (sha256_f11.out[0], thash_f12.in[0]);
    connect<stream> net69 (sha256_f11.out[1], thash_f12.in[1]);
    connect<stream> net70 (thash_f12.out[0], sha25612.in[0]);
    connect<stream> net71 (thash_f12.out[1], sha256_mask12.in[0]);   
    connect<stream> net72 (sha25612.out[0], sha256_f12.in[0]);
    connect<stream> net73 (sha256_mask12.out[0], sha256_f12.in[1]);

    connect<stream> net74 (sha256_f12.out[0], thash_f13.in[0]);
    connect<stream> net75 (sha256_f12.out[1], thash_f13.in[1]);
    connect<stream> net76 (thash_f13.out[0], sha25613.in[0]);
    connect<stream> net77 (thash_f13.out[1], sha256_mask13.in[0]);   
    connect<stream> net78 (sha25613.out[0], sha256_f13.in[0]);
    connect<stream> net79 (sha256_mask13.out[0], sha256_f13.in[1]);
    
    connect<stream> net80 (sha256_f13.out[0], thash_f14.in[0]);
    connect<stream> net81 (sha256_f13.out[1], thash_f14.in[1]);
    connect<stream> net82 (thash_f14.out[0], sha25614.in[0]);
    connect<stream> net83 (thash_f14.out[1], sha256_mask14.in[0]);   
    connect<stream> net84 (sha25614.out[0], sha256_f14.in[0]);
    connect<stream> net85 (sha256_mask14.out[0], sha256_f14.in[1]);

    connect<stream> net86 (sha256_f14.out[0], thash_f15.in[0]);
    connect<stream> net87 (sha256_f14.out[1], thash_f15.in[1]);
    connect<stream> net88 (thash_f15.out[0], sha25615.in[0]);
    connect<stream> net89 (thash_f15.out[1], sha256_mask15.in[0]);   
    connect<stream> net90 (sha25615.out[0], sha256_f15.in[0]);
    connect<stream> net91 (sha256_mask15.out[0], sha256_f15.in[1]);

    connect<stream> net92 (sha256_f15.out[0], dataout.in[0]);
    connect<stream> net93 (sha256_f15.out[1], addrout.in[0]);

    fifo_depth(net0) = 512;
    fifo_depth(net1) = 512;
    fifo_depth(net2) = 512;
    fifo_depth(net3) = 512;
    fifo_depth(net4) = 512;
    fifo_depth(net5) = 512;

    fifo_depth(net6) = 512;
    fifo_depth(net7) = 512;
    fifo_depth(net10) = 512;
    fifo_depth(net11) = 512;
    fifo_depth(net12) = 512;
    fifo_depth(net13) = 512;

    fifo_depth(net14) = 512;
    fifo_depth(net15) = 512;
    fifo_depth(net16) = 512;
    fifo_depth(net17) = 512;
    fifo_depth(net18) = 512;
    fifo_depth(net19) = 512;

    fifo_depth(net20) = 512;
    fifo_depth(net21) = 512;
    fifo_depth(net22) = 512;
    fifo_depth(net23) = 512;
    fifo_depth(net24) = 512;
    fifo_depth(net25) = 512;

    fifo_depth(net26) = 512;
    fifo_depth(net27) = 512;
    fifo_depth(net28) = 512;
    fifo_depth(net29) = 512;
    fifo_depth(net30) = 512;
    fifo_depth(net31) = 512;

    fifo_depth(net32) = 512;
    fifo_depth(net33) = 512;
    fifo_depth(net34) = 512;
    fifo_depth(net35) = 512;
    fifo_depth(net36) = 512;
    fifo_depth(net37) = 512;

    fifo_depth(net38) = 512;
    fifo_depth(net39) = 512;
    fifo_depth(net40) = 512;
    fifo_depth(net41) = 512;
    fifo_depth(net42) = 512;
    fifo_depth(net43) = 512;

    fifo_depth(net44) = 512;   
    fifo_depth(net45) = 512;
    fifo_depth(net46) = 512;
    fifo_depth(net47) = 512;
    fifo_depth(net48) = 512;
    fifo_depth(net49) = 512;

    fifo_depth(net50) = 512;   
    fifo_depth(net51) = 512;
    fifo_depth(net52) = 512;
    fifo_depth(net53) = 512;
    fifo_depth(net54) = 512;
    fifo_depth(net55) = 512;

    fifo_depth(net56) = 512;   
    fifo_depth(net57) = 512;
    fifo_depth(net58) = 512;
    fifo_depth(net59) = 512;
    fifo_depth(net60) = 512;
    fifo_depth(net61) = 512;

    fifo_depth(net62) = 512;   
    fifo_depth(net63) = 512;
    fifo_depth(net64) = 512;
    fifo_depth(net65) = 512;
    fifo_depth(net66) = 512;
    fifo_depth(net67) = 512;

    fifo_depth(net68) = 512;   
    fifo_depth(net69) = 512;
    fifo_depth(net70) = 512;
    fifo_depth(net71) = 512;
    fifo_depth(net72) = 512;
    fifo_depth(net73) = 512;

    fifo_depth(net74) = 512;   
    fifo_depth(net75) = 512;
    fifo_depth(net76) = 512;
    fifo_depth(net77) = 512;
    fifo_depth(net78) = 512;
    fifo_depth(net79) = 512;

    fifo_depth(net80) = 512;   
    fifo_depth(net81) = 512;
    fifo_depth(net82) = 512;
    fifo_depth(net83) = 512;
    fifo_depth(net84) = 512;
    fifo_depth(net85) = 512;

    fifo_depth(net86) = 512;   
    fifo_depth(net87) = 512;
    fifo_depth(net88) = 512;
    fifo_depth(net89) = 512;
    fifo_depth(net90) = 512;
    fifo_depth(net91) = 512;

    fifo_depth(net92) = 512;
    fifo_depth(net93) = 512;

    
    source(thash_f1) = "src/kernels/thash_f.cc";
    source(sha2561) = "src/kernels/sha256.cc";
    source(sha256_mask1) = "src/kernels/sha256_mask.cc";
    source(sha256_f1) = "src/kernels/sha256_f.cc";

    source(thash_f2) = "src/kernels/thash_f.cc";
    source(sha2562) = "src/kernels/sha256.cc";
    source(sha256_mask2) = "src/kernels/sha256_mask.cc";
    source(sha256_f2) = "src/kernels/sha256_f.cc";

    source(thash_f3) = "src/kernels/thash_f.cc";
    source(sha2563) = "src/kernels/sha256.cc";
    source(sha256_mask3) = "src/kernels/sha256_mask.cc";
    source(sha256_f3) = "src/kernels/sha256_f.cc";

    source(thash_f4) = "src/kernels/thash_f.cc";
    source(sha2564) = "src/kernels/sha256.cc";
    source(sha256_mask4) = "src/kernels/sha256_mask.cc";
    source(sha256_f4) = "src/kernels/sha256_f.cc";

    source(thash_f5) = "src/kernels/thash_f.cc";
    source(sha2565) = "src/kernels/sha256.cc";
    source(sha256_mask5) = "src/kernels/sha256_mask.cc";
    source(sha256_f5) = "src/kernels/sha256_f.cc";

    source(thash_f6) = "src/kernels/thash_f.cc";
    source(sha2566) = "src/kernels/sha256.cc";
    source(sha256_mask6) = "src/kernels/sha256_mask.cc";
    source(sha256_f6) = "src/kernels/sha256_f.cc";

    source(thash_f7) = "src/kernels/thash_f.cc";
    source(sha2567) = "src/kernels/sha256.cc";
    source(sha256_mask7) = "src/kernels/sha256_mask.cc";
    source(sha256_f7) = "src/kernels/sha256_f.cc";

    source(thash_f8) = "src/kernels/thash_f.cc";
    source(sha2568) = "src/kernels/sha256.cc";
    source(sha256_mask8) = "src/kernels/sha256_mask.cc";
    source(sha256_f8) = "src/kernels/sha256_f.cc";

    source(thash_f9) = "src/kernels/thash_f.cc";
    source(sha2569) = "src/kernels/sha256.cc";
    source(sha256_mask9) = "src/kernels/sha256_mask.cc";
    source(sha256_f9) = "src/kernels/sha256_f.cc";

    source(thash_f10) = "src/kernels/thash_f.cc";
    source(sha25610) = "src/kernels/sha256.cc";
    source(sha256_mask10) = "src/kernels/sha256_mask.cc";
    source(sha256_f10) = "src/kernels/sha256_f.cc";

    source(thash_f11) = "src/kernels/thash_f.cc";
    source(sha25611) = "src/kernels/sha256.cc";
    source(sha256_mask11) = "src/kernels/sha256_mask.cc";
    source(sha256_f11) = "src/kernels/sha256_f.cc";

    source(thash_f12) = "src/kernels/thash_f.cc";
    source(sha25612) = "src/kernels/sha256.cc";
    source(sha256_mask12) = "src/kernels/sha256_mask.cc";
    source(sha256_f12) = "src/kernels/sha256_f.cc";

    source(thash_f13) = "src/kernels/thash_f.cc";
    source(sha25613) = "src/kernels/sha256.cc";
    source(sha256_mask13) = "src/kernels/sha256_mask.cc";
    source(sha256_f13) = "src/kernels/sha256_f.cc";

    source(thash_f14) = "src/kernels/thash_f.cc";
    source(sha25614) = "src/kernels/sha256.cc";
    source(sha256_mask14) = "src/kernels/sha256_mask.cc";
    source(sha256_f14) = "src/kernels/sha256_f.cc";

    source(thash_f15) = "src/kernels/thash_f.cc";
    source(sha25615) = "src/kernels/sha256.cc";
    source(sha256_mask15) = "src/kernels/sha256_mask.cc";
    source(sha256_f15) = "src/kernels/sha256_f.cc";

    runtime<ratio>(thash_f1) = 0.8;
    runtime<ratio>(sha2561) = 0.8;
    runtime<ratio>(sha256_mask1) = 0.8;
    runtime<ratio>(sha256_f1) = 0.8;

    runtime<ratio>(thash_f2) = 0.8;
    runtime<ratio>(sha2562) = 0.8;
    runtime<ratio>(sha256_mask2) = 0.8;
    runtime<ratio>(sha256_f2) = 0.8;

    runtime<ratio>(thash_f3) = 0.8;
    runtime<ratio>(sha2563) = 0.8;
    runtime<ratio>(sha256_mask3) = 0.8;
    runtime<ratio>(sha256_f3) = 0.8;

    runtime<ratio>(thash_f4) = 0.8;
    runtime<ratio>(sha2564) = 0.8;
    runtime<ratio>(sha256_mask4) = 0.8;
    runtime<ratio>(sha256_f4) = 0.8;

    runtime<ratio>(thash_f5) = 0.8;
    runtime<ratio>(sha2565) = 0.8;
    runtime<ratio>(sha256_mask5) = 0.8;
    runtime<ratio>(sha256_f5) = 0.8;

    runtime<ratio>(thash_f6) = 0.8;
    runtime<ratio>(sha2566) = 0.8;
    runtime<ratio>(sha256_mask6) = 0.8;
    runtime<ratio>(sha256_f6) = 0.8;

    runtime<ratio>(thash_f7) = 0.8;
    runtime<ratio>(sha2567) = 0.8;
    runtime<ratio>(sha256_mask7) = 0.8;
    runtime<ratio>(sha256_f7) = 0.8;

    runtime<ratio>(thash_f8) = 0.8;
    runtime<ratio>(sha2568) = 0.8;
    runtime<ratio>(sha256_mask8) = 0.8;
    runtime<ratio>(sha256_f8) = 0.8;

    runtime<ratio>(thash_f9) = 0.8;
    runtime<ratio>(sha2569) = 0.8;
    runtime<ratio>(sha256_mask9) = 0.8;
    runtime<ratio>(sha256_f9) = 0.8;

    runtime<ratio>(thash_f10) = 0.8;
    runtime<ratio>(sha25610) = 0.8;
    runtime<ratio>(sha256_mask10) = 0.8;
    runtime<ratio>(sha256_f10) = 0.8;

    runtime<ratio>(thash_f11) = 0.8;
    runtime<ratio>(sha25611) = 0.8;
    runtime<ratio>(sha256_mask11) = 0.8;
    runtime<ratio>(sha256_f11) = 0.8;

    runtime<ratio>(thash_f12) = 0.8;
    runtime<ratio>(sha25612) = 0.8;
    runtime<ratio>(sha256_mask12) = 0.8;
    runtime<ratio>(sha256_f12) = 0.8;

    runtime<ratio>(thash_f13) = 0.8;
    runtime<ratio>(sha25613) = 0.8;
    runtime<ratio>(sha256_mask13) = 0.8;
    runtime<ratio>(sha256_f13) = 0.8;

    runtime<ratio>(thash_f14) = 0.8;
    runtime<ratio>(sha25614) = 0.8;
    runtime<ratio>(sha256_mask14) = 0.8;
    runtime<ratio>(sha256_f14) = 0.8;

    runtime<ratio>(thash_f15) = 0.8;
    runtime<ratio>(sha25615) = 0.8;
    runtime<ratio>(sha256_mask15) = 0.8;
    runtime<ratio>(sha256_f15) = 0.8;

    adf::location<kernel>(thash_f1)=adf::tile(0,0); 
    adf::location<kernel>(sha2561)=adf::tile(0,1); 
    adf::location<kernel>(sha256_mask1)=adf::tile(1,1); 
    adf::location<kernel>(sha256_f1)=adf::tile(1,0);   

    adf::location<kernel>(thash_f2)=adf::tile(2,0); 
    adf::location<kernel>(sha2562)=adf::tile(2,1); 
    adf::location<kernel>(sha256_mask2)=adf::tile(3,1); 
    adf::location<kernel>(sha256_f2)=adf::tile(3,0);   

    adf::location<kernel>(thash_f3)=adf::tile(4,0); 
    adf::location<kernel>(sha2563)=adf::tile(4,1); 
    adf::location<kernel>(sha256_mask3)=adf::tile(5,1); 
    adf::location<kernel>(sha256_f3)=adf::tile(5,0); 

    adf::location<kernel>(thash_f4)=adf::tile(6,0); 
    adf::location<kernel>(sha2564)=adf::tile(6,1); 
    adf::location<kernel>(sha256_mask4)=adf::tile(7,1); 
    adf::location<kernel>(sha256_f4)=adf::tile(7,0);

    adf::location<kernel>(thash_f5)=adf::tile(8,0); 
    adf::location<kernel>(sha2565)=adf::tile(8,1); 
    adf::location<kernel>(sha256_mask5)=adf::tile(9,1); 
    adf::location<kernel>(sha256_f5)=adf::tile(9,0);

    adf::location<kernel>(thash_f6)=adf::tile(10,0); 
    adf::location<kernel>(sha2566)=adf::tile(10,1); 
    adf::location<kernel>(sha256_mask6)=adf::tile(11,1); 
    adf::location<kernel>(sha256_f6)=adf::tile(11,0);
    
    adf::location<kernel>(thash_f7)=adf::tile(12,0); 
    adf::location<kernel>(sha2567)=adf::tile(12,1); 
    adf::location<kernel>(sha256_mask7)=adf::tile(13,1); 
    adf::location<kernel>(sha256_f7)=adf::tile(13,0);

    adf::location<kernel>(thash_f8)=adf::tile(14,0); 
    adf::location<kernel>(sha2568)=adf::tile(14,1); 
    adf::location<kernel>(sha256_mask8)=adf::tile(15,1); 
    adf::location<kernel>(sha256_f8)=adf::tile(15,0);

    adf::location<kernel>(thash_f9)=adf::tile(16,0); 
    adf::location<kernel>(sha2569)=adf::tile(16,1); 
    adf::location<kernel>(sha256_mask9)=adf::tile(17,1); 
    adf::location<kernel>(sha256_f9)=adf::tile(17,0);

    adf::location<kernel>(thash_f10)=adf::tile(18,0); 
    adf::location<kernel>(sha25610)=adf::tile(18,1); 
    adf::location<kernel>(sha256_mask10)=adf::tile(19,1); 
    adf::location<kernel>(sha256_f10)=adf::tile(19,0);

    adf::location<kernel>(thash_f11)=adf::tile(20,0); 
    adf::location<kernel>(sha25611)=adf::tile(20,1); 
    adf::location<kernel>(sha256_mask11)=adf::tile(21,1); 
    adf::location<kernel>(sha256_f11)=adf::tile(21,0);

    adf::location<kernel>(thash_f12)=adf::tile(22,0); 
    adf::location<kernel>(sha25612)=adf::tile(22,1); 
    adf::location<kernel>(sha256_mask12)=adf::tile(23,1); 
    adf::location<kernel>(sha256_f12)=adf::tile(23,0);

    adf::location<kernel>(thash_f13)=adf::tile(24,0); 
    adf::location<kernel>(sha25613)=adf::tile(24,1); 
    adf::location<kernel>(sha256_mask13)=adf::tile(25,1); 
    adf::location<kernel>(sha256_f13)=adf::tile(25,0);

    adf::location<kernel>(thash_f14)=adf::tile(26,0); 
    adf::location<kernel>(sha25614)=adf::tile(26,1); 
    adf::location<kernel>(sha256_mask14)=adf::tile(27,1); 
    adf::location<kernel>(sha256_f14)=adf::tile(27,0);

    adf::location<kernel>(thash_f15)=adf::tile(28,0); 
    adf::location<kernel>(sha25615)=adf::tile(28,1); 
    adf::location<kernel>(sha256_mask15)=adf::tile(29,1); 
    adf::location<kernel>(sha256_f15)=adf::tile(29,0);
    }
};

