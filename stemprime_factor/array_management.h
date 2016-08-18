#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include <stdint.h>

int INT_BITS;

void set_index_true(long idx, int *bitarray);
void set_index_false(long idx, int *bitarray);

unsigned int get_index(long idx, int *bitarray);

#endif
