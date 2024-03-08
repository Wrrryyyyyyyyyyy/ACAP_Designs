#include "stdio.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../aes.h"
//#include "../api.h"
#include "../cbd.h"
#include "../compat.h"
#include "../crypto_declassify.h"
#include "../fips202.h"
#include "../indcpa.h"
#include "../kem.h"
#include "../nistseedexpander.h"
#include "../ntt.h"
#include "../params.h"
#include "../poly.h"
#include "../polyvec.h"
#include "../randombytes.h"
#include "../reduce.h"
#include "../sha2.h"
#include "../sp800-185.h"
#include "../symmetric.h"
#include "../verify.h"


inline static void* malloc_s(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("Malloc failed!");
        exit(1);
    }
    return ptr;
}


/*************************************************
* Name:        PQCLEAN_KYBER512_CLEAN_verify
*
* Description: Compare two arrays for equality in constant time.
*
* Arguments:   const uint8_t *a: pointer to first byte array
*              const uint8_t *b: pointer to second byte array
*              size_t len:       length of the byte arrays
*
* Returns 0 if the byte arrays are equal, 1 otherwise
**************************************************/
int main(){
	
	uint8_t *pk_aligned    = malloc_s(KYBER_PUBLICKEYBYTES + 16 + 1);
	uint8_t *sk_a_aligned  = malloc_s(KYBER_SECRETKEYBYTES + 16 + 1);
	uint8_t *sendb_aligned = malloc_s(KYBER_CIPHERTEXTBYTES + 16 + 1);
	uint8_t *key_a_aligned = malloc_s(32 + 16 + 1);
    	uint8_t *key_b_aligned = malloc_s(32 + 16 + 1);
	
	uint8_t *pk    = (uint8_t *) ((uintptr_t) pk_aligned|(uintptr_t) 1);
	uint8_t *sk  = (uint8_t *) ((uintptr_t) sk_a_aligned|(uintptr_t) 1);
	uint8_t *sendb = (uint8_t *) ((uintptr_t) sendb_aligned|(uintptr_t) 1);	
   	uint8_t *key_a = (uint8_t *) ((uintptr_t) key_a_aligned|(uintptr_t) 1);
    	uint8_t *key_b = (uint8_t *) ((uintptr_t) key_b_aligned|(uintptr_t) 1);
    	
    	uint8_t *random  [KYBER_SYMBYTES];
    	
    	unsigned int j;
    	
	printf("keypair start\n");
	PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(pk + 8, sk + 8);
	
	printf("pk=");
	for ( j = 0; j < KYBER_PUBLICKEYBYTES + 16 + 1; j++)		
		printf("%02X",pk[j]);		
	printf("\n");
	
	printf("sk=");
	for ( j = 0; j < KYBER_SECRETKEYBYTES + 16 + 1; j++)		
		printf("%02X",sk[j]);		
	printf("\n");
		
	printf("keypair done\n");
	
	printf("encryption start\n");
	PQCLEAN_KYBER512_CLEAN_crypto_kem_enc(sendb + 8, key_b + 8, pk + 8);
	printf("sendb=");
	for ( j = 0; j < KYBER_CIPHERTEXTBYTES + 16 + 1; j++)		
		printf("%02X",sendb[j]);		
	printf("\n");
	
	printf("key_b=");
	for (j = 0; j < 32 + 16 + 1; j++)		
		printf("%02X",key_b[j]);		
	printf("\n");
	printf("encryption end\n");
	
	printf("decryption start\n");
        PQCLEAN_KYBER512_CLEAN_crypto_kem_dec(key_a + 8, sendb + 8, sk + 8);

	
	printf("key_a=");
	for ( j = 0; j < 32 + 16 + 1; j++)		
		printf("%02X",key_a[j]);		
	printf("\n");
	printf("decryption end\n");
	return 0;
}
