#include "../bstypes.h"

#include <stdlib.h>
#include <stdio.h>

#define SIZE_BS(max) (max/8 + 1)

#define MALLOC_BS(max) (char *)malloc(SIZE_BS(max))

#define getbit(set, idx) ((set.data[idx/8] >> (idx % 8)) & 1)

#define setbit(set, idx, val) set.data[idx>>3] ^= (-val ^ set.data[idx>>3] ) & (1 << (idx % 8))

#define setbit_0(set, idx) set.data[idx>>3] &= ~(1 << (idx & 0b111))
#define setbit_1(set, idx) set.data[idx>>3] |= 1 << (idx & 0b111)


long int count(bitset_t set, long int max);



