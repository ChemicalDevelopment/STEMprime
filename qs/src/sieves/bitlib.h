
#define SIZE_BS(max) (1 + max / 8)

#define MALLOC_BS(max) (char *)malloc(SIZE_BS(max))

#define getbit(set, idx) ((set[idx/8] >> (idx % 8)) & 1)

#define setbit(set, idx, val) set[idx>>3] ^= (-val ^ set[idx>>3] ) & (1 << (idx % 8))

#define setbit_0(set, idx) set[idx>>3] &= ~(1 << (idx & 0b111))
#define setbit_1(set, idx) set[idx>>3] |= 1 << (idx & 0b111)


long int count(char *set, long int max);




