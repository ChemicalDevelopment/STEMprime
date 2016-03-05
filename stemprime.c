#include <stdio.h>
#include <gmp.h>

int main(int argcount, char *argv[])
{
    /*printf("Welcome to STEMprime (in C!).\n");
    printf("This tests the primality of 2^n - 1 (mersenne primes).\n");
    printf("Please enter exponent:\n");*/
    int exponent;
    exponent = atoi(argv[1]);
    mpz_t mersenneNum;
    mpz_init_set_si(mersenneNum, 2);
    mpz_pow_ui(mersenneNum, mersenneNum, exponent);
    mpz_sub_ui(mersenneNum, mersenneNum, 1);
    printf("Testing primality of: 2^%d-1\n",exponent);
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
    return 0;
}
