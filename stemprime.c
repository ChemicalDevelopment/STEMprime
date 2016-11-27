#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>

/*

	© ChemicalDevelopment

*/

bool LL(int32_t exponent) {
	mpz_t MOD, LN;

	mpz_init2(MOD, exponent+1);
	mpz_ui_pow_ui(MOD, 2, exponent);
	mpz_sub_ui(MOD, MOD, 1); 


	mpz_init2(LN, 2*exponent+1);
	mpz_set_ui(LN, 4);

	int32_t i;
	for (i = 0; i < exponent - 2; i++) {
		mpz_mul(LN, LN, LN);
		mpz_sub_ui(LN, LN, 2);
		mpz_tdiv_r(LN, LN, MOD);
		if (i % (exponent/100) == 0 || i == exponent - 3) {
			printf("%%%f\r", (100.*i) / (exponent-3));
			fflush(stdout);
		}
	}
	printf("\n");
	return mpz_cmp_si(LN, 0) == 0;
}

int main(int argcount, char *argv[])
{
	int32_t exponent = 1398269;
	bool res;
	clock_t s, e;
	s = clock();
	res = LL(exponent);
	e = clock();
	if (res) {
		printf("2^%d-1 is prime\n", exponent);
	}
	printf("took %lf seconds\n", (double)(e-s)/1000000);
	
}

