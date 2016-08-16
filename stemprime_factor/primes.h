#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

int INT_BITS;

unsigned int *primearray;

void set_index_true(long idx, int *bitarray);
void set_index_false(long idx, int *bitarray);

unsigned int get_index(long idx, int *bitarray);

void set_bitarray(long max);

unsigned int * prime_array();
#endif
