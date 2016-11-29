#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>

/*

	© ChemicalDevelopment

*/

void mod_2nm1(mpz_t ret, int32_t exponent, mpz_t nm1, mpz_t tmp) {
	mpz_tdiv_q_2exp(tmp, ret, exponent);
	mpz_mod_2exp(ret, ret, exponent);
	mpz_add(ret, ret, tmp);
	
	
	if (mpz_cmp(ret, nm1) >= 0) {
		mpz_sub(ret, ret, nm1);
	}

	if (mpz_cmp(ret, nm1) >= 0) {
		mpz_mod(ret, ret, nm1);
	}
}

bool LL(int32_t exponent) {
	mpz_t MOD, LN, tmp;

	mpz_init2(MOD, exponent+1);
	mpz_init2(LN, exponent+1);
	mpz_init2(tmp, exponent+1);
	
	mpz_ui_pow_ui(MOD, 2, exponent);
	mpz_sub_ui(MOD, MOD, 1); 

	mpz_set_ui(LN, 4);

	int32_t i;
	for (i = 0; i < exponent - 2; i++) {
		mpz_mul(LN, LN, LN);
		mpz_sub_ui(LN, LN, 2);
		mod_2nm1(LN, exponent, MOD, tmp);
		
		if (exponent/100 == 0 || i % (exponent/100) == 0 || i == exponent - 3) {
			printf("%%%f\r", (100.*i) / (exponent-3));
			fflush(stdout);
		}
	}
	printf("\n");
	return mpz_cmp_si(LN, 0) == 0;
}

int main(int argc, char *argv[])
{
	int32_t exponent = 580673;
	if (argc > 1) exponent = strtol(argv[1], NULL, 10);
	bool res;
	clock_t s, e;
	s = clock();
	res = LL(exponent);
	e = clock();
	if (res) {
		printf("2^%d-1 is prime\n", exponent);
	}
	printf("took %lf seconds\n", (double)(e-s)/1000000);
	return 0;
}

