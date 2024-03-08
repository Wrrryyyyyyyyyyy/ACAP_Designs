This folder includes the modified XMSS software implementation which includes: 

- SHA-256-specific software optimizations 

- `test/` testing functions

TARGET=

- `x86` run the test on x86 CPUs

- `Murax` plain Murax SoC

PROJ =

- `sha256` sha256 test

- `sha_fixed_inlen` sha256 with software `fixed-input-length` optimization test

- `sha_fixed_inlen_precomp` sha256 with `software pre-computation` optimization test

- `sha256xmss` XMSS-specific sha256 test

- `chain` WOTS-chain test

- `leaf` XMSS-leaf test

- `xmss` XMSS full test, including: key generation, signature generation and signature verification
 
Sample instructions:

```sh
# run the leaf test on x86 CPUs
make TARGET=x86 PROJ=leaf clean
make TARGET=x86 PROJ=leaf run
```

```sh
# run the leaf test simulation on a Murax SoC with a Leaf 
make TARGET=Murax SIM=yes PROJ=leaf clean
make TARGET=Murax SIM=yes PROJ=leaf run
```






