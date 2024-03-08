#include "indcpa.h"
#include "kem.h"
#include "params.h"
#include "randombytes.h"
#include "symmetric.h"
#include "verify.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*************************************************
* Name:        PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair
*
* Description: Generates public and private key
*              for CCA-secure Kyber key encapsulation mechanism
*
* Arguments:   - uint8_t *pk: pointer to output public key
*                (an already allocated array of KYBER_PUBLICKEYBYTES bytes)
*              - uint8_t *sk: pointer to output private key
*                (an already allocated array of KYBER_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(uint8_t *pk,
        uint8_t *sk) {
    size_t i;
    
    PQCLEAN_KYBER512_CLEAN_indcpa_keypair(pk, sk);
    
    for (i = 0; i < KYBER_INDCPA_PUBLICKEYBYTES; i++) {
        sk[i + KYBER_INDCPA_SECRETKEYBYTES] = pk[i];
    }
    hash_h(sk + KYBER_SECRETKEYBYTES - 2 * KYBER_SYMBYTES, pk, KYBER_PUBLICKEYBYTES);
    /* Value z for pseudo-random output on reject */
    randombytes(sk + KYBER_SECRETKEYBYTES - KYBER_SYMBYTES, KYBER_SYMBYTES);
    return 0;
}

/*************************************************
* Name:        PQCLEAN_KYBER512_CLEAN_crypto_kem_enc
*
* Description: Generates cipher text and shared
*              secret for given public key
*
* Arguments:   - uint8_t *ct: pointer to output cipher text
*                (an already allocated array of KYBER_CIPHERTEXTBYTES bytes)
*              - uint8_t *ss: pointer to output shared secret
*                (an already allocated array of KYBER_SSBYTES bytes)
*              - const uint8_t *pk: pointer to input public key
*                (an already allocated array of KYBER_PUBLICKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int PQCLEAN_KYBER512_CLEAN_crypto_kem_enc(uint8_t *ct,
        uint8_t *ss,
        const uint8_t *pk) {
    uint8_t buf[2 * KYBER_SYMBYTES];
    /* Will contain key, coins */
    uint8_t kr[2 * KYBER_SYMBYTES];
      
    //m random number
    randombytes(buf, KYBER_SYMBYTES);     
    
    /* Multitarget countermeasure for coins + contributory KEM */
    hash_h(buf + KYBER_SYMBYTES, pk, KYBER_PUBLICKEYBYTES);
    hash_g(kr, buf, 2 * KYBER_SYMBYTES);

    /* coins are in kr+KYBER_SYMBYTES */
    PQCLEAN_KYBER512_CLEAN_indcpa_enc(ct, buf, pk, kr + KYBER_SYMBYTES);

    memcpy(ss,kr,KYBER_SYMBYTES);//wuyz add in 2023.11.8
    
    return 0;
}

/*************************************************
* Name:        PQCLEAN_KYBER512_CLEAN_crypto_kem_dec
*
* Description: Generates shared secret for given
*              cipher text and private key
*
* Arguments:   - uint8_t *ss: pointer to output shared secret
*                (an already allocated array of KYBER_SSBYTES bytes)
*              - const uint8_t *ct: pointer to input cipher text
*                (an already allocated array of KYBER_CIPHERTEXTBYTES bytes)
*              - const uint8_t *sk: pointer to input private key
*                (an already allocated array of KYBER_SECRETKEYBYTES bytes)
*
* Returns 0.
*
* On failure, ss will contain a pseudo-random value.
**************************************************/
int PQCLEAN_KYBER512_CLEAN_crypto_kem_dec(uint8_t *ss,
        const uint8_t *ct,
        const uint8_t *sk) {
    size_t i;
    int fail;
    uint8_t buf[2 * KYBER_SYMBYTES];
    /* Will contain key, coins */
    uint8_t kr[2 * KYBER_SYMBYTES];
    uint8_t cmp[KYBER_CIPHERTEXTBYTES];
    uint8_t z_c[KYBER_CIPHERTEXTBYTES + KYBER_SYMBYTES]; //z||ct
    const uint8_t *pk = sk + KYBER_INDCPA_SECRETKEYBYTES;

    PQCLEAN_KYBER512_CLEAN_indcpa_dec(buf, ct, sk);

    /* Multitarget countermeasure for coins + contributory KEM */
    for (i = 0; i < KYBER_SYMBYTES; i++) {
        buf[KYBER_SYMBYTES + i] = sk[KYBER_SECRETKEYBYTES - 2 * KYBER_SYMBYTES + i];
    }
    hash_g(kr, buf, 2 * KYBER_SYMBYTES);

    /* coins are in kr+KYBER_SYMBYTES */
    PQCLEAN_KYBER512_CLEAN_indcpa_enc(cmp, buf, pk, kr + KYBER_SYMBYTES);

    fail = PQCLEAN_KYBER512_CLEAN_verify(ct, cmp, KYBER_CIPHERTEXTBYTES);

    if(fail) //invalid out
    	{
            //we may transfer data as line 117 does if no <string.h> exists. 
            memcpy(z_c,sk + KYBER_SECRETKEYBYTES - KYBER_SYMBYTES, KYBER_SYMBYTES);
            memcpy(z_c + KYBER_SYMBYTES , ct, KYBER_CIPHERTEXTBYTES);
            kdf(ss, z_c, KYBER_SYMBYTES + KYBER_CIPHERTEXTBYTES);
        }
    else //valid out
    	memcpy(ss,kr,KYBER_SYMBYTES);
        

    return 0;
}
