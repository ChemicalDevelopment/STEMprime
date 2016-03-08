#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

int main(int argcount, char *argv[])
{
    int exponent;
    exponent = atoi(argv[1]);
    mpz_t mersenneNum;
    mpz_init_set_si(mersenneNum, 2);
    mpz_pow_ui(mersenneNum, mersenneNum, exponent);
    mpz_sub_ui(mersenneNum, mersenneNum, 1);
    
    mpz_t exp_mpz;
    mpz_init(exp_mpz);
    mpz_set_ui(exp_mpz, exponent);
    printf("Testing primality of: 2^%d-1\n",exponent);
    if (mpz_probab_prime_p(exp_mpz, 1) == 0) {
        printf("2^%d-1 isn't prime :(\n", exponent);
        return 0;
    }
    mpz_t llModMersenne;
    mpz_init_set_si(llModMersenne, 4);
    int n;
    for (n = 0; n <= exponent - 3; n++) {
    	printf("%%%f\r", (100.0 * n) / (exponent - 3));
	    mpz_mul(llModMersenne, llModMersenne, llModMersenne);
        mpz_sub_ui(llModMersenne, llModMersenne, 2);
    	mpz_mod(llModMersenne, llModMersenne, mersenneNum);
    }
    printf("\n");
    if (mpz_cmp_ui(llModMersenne, 0) == 0 || exponent == 2) {
    	printf("2^%d-1 is prime!\n", exponent);
    } else {
    	printf("2^%d-1 isn't prime :(\n", exponent);
    }
    //mpz_clears(exp_mpz, mersenneNum, llModMersenne);
    return 0;
}
