OS：Ubuntu 2022

---
# SM4-GCM

sm4 source in direction /src

sm4 include file in direction /include

sm4 test file in direction /test

# Quick Start

    #You may need to install gmssl before the compile,please refer to https://github.com/guanzhi/GmSSL
    #If you refuse to install the gmssl, you may need to change the include direction manually.

    cd test
    cc -o demo_sm4_gcm demo_sm4_gcm.c ../src/*.c
    ./demo_sm4_gcm



---
# KYBER




kyber源码在目录：kyber512_fips203

kyber测试代码在目录：kyber512_fips203/test

可以在test/functest.c 中找到kyber的主函数：


    crypto_kem_keypair(pk, sk_a); #public key generation

    crypto_kem_enc(sendb, key_b, pk); #key encryption

    crypto_kem_dec(key_a, sendb, sk_a); #key decryption


假定A和B是通信双方：
    
    1. A产生一个特定长度的密钥对 pk 和 sk_a.  （keypair）
    2. 接收者 B 根据 pk 产生并发送密钥 key_b 和一个密文 sendb.  （encryption）
    3. A 根据 sk_a 和 B 发送的密文得到她自己的密钥 key_a. （decryption）
    4. 如果 key_a 和 key_b 的值相等，那就是有效的。
    

32-bytes 长的随机数 *z, d, m* 通过随机函数得到：  

    int randombytes(uint8_t *output, size_t n);

其中, *z* 和 *d* 用于密钥对生成； *m* 用于密钥封装. 随机函数可以替换.


**Attention**：各个参数的长度与数据类型请参考代码。


# Quick Start


所有kyber512所需代码在src文件夹，执行：

    cd kyber512_fips203/test
    cc -o verify verify.c ../*c  #Some warning of redefine
    ./verify


---
#  XMSS

因为集成了Murax环境，所以XMSS编译执行主要通过make，如果只需要单独的xmss源码，可能需要修改源码里面的include路径。

# 源文件

XMSS 源代码在目录：src/xmss-reference 

XMSS 测试代码在目录： src/xmss-reference/test.

XMSS主要源文件如下:

    hash.c
    hash.h #hash function, you may choose different lib when use.
    hash_address.c
    hash_address.h #address in XMSS, refer standard for detail.
    params.c
    params.h #default is sha256_10_16
    randombytes.c
    randombytes.h #pseudorandom number
    wots.c
    wots.h # wots function
    utils.c
    utils.h #
    fips202.c
    fips202.h #
    xmss.c
    xmss.h #
    xmss_commons.c
    xmss_commons.h # xmss common used function 
    xmss_core.c
    xmss_core.h # xmss core function
    xmss_core_fast.c
    xmss_core_fast.h #xmss fast implementation

XMSS测试文件如下:
  
    chain.c # test for wots function
    leaf.c # test for leaf function
    xmss.c # test for the whole xmss function

# 函数&参数 

## 函数
如 *test/xmss.c* 所示，可以通过以下方式调用XMSS主函数:
    
       XMSS_KEYPAIR(pk, sk, oid); #密钥生成

       XMSS_SIGN(sk, sm, &smlen, m, XMSS_MLEN); #签名

       XMSS_SIGN_OPEN(mout, &mlen, sm, smlen, pk); #验签



注意，随机函数是可替换的：

    void randombytes(unsigned char *x, unsigned long long xlen);
   


## 参数

以下列举一些重要的参数:

*oid* 是一个XMSS变量，用于选择XMSS类型。默认选择oid=0x0000_0001，此时树高10，wots参数16，具体参考*params.c*;

 *pk* / *sk* 是有特定长度的公钥 / 私钥，以下为密钥的组成：

    pk = oid || root || pub_seed
    sk = oid || index || sk_seed || sk_prf || pub_seed || root

消息 *m* 由测试中由随机数产生，实际使用中可以替换为自己的消息. 

签名 *signature* 由四个部分组成：

    signature = index || sk_prf || wots_signature || authentication

每个部分长度会随着参数而变，具体参考param.h


*sm* 是签名 + 消息. 

    sm = index || sk_prf || wots_signature || authentication || message

*mout* 是验证过的签名，如果通过验签，其值等于 *sm*，若验证不通过，返回0.

# Quick start

在linux系统下运行xmss：

    cd src/xmss
    make TARGET=x86 PROJ=xmss SIM=yes run 

或者直接编译运行：

    cd src/xmss
    cc -o test/x86_xmss params.c hash.c fips202.c hash_address.c randombytes.c wots.c xmss.c xmss_core_fast.c xmss_commons.c utils.c test/xmss.c -lcrypto
    ./test/x86_xmss

# 2023.11.13 You may need sha.h when compile XMSS. Please add it to target direcion. 


