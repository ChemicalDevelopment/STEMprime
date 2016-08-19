#ifndef MERSENNE_FACTOR_H_INCLUDED
#define MERSENNE_FACTOR_H_INCLUDED
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>

//unsigned int * product_array;

//void set_product_array(unsigned int * primes, long long max_product);

int test_num(mpz_t prime_cand, int64_t *to_div);

#endif
