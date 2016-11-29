#ifndef BITSET_T_DEF
#define BITSET_T_DEF
/*

our type for bitset. The default one is just simply a list in little endian order.

*/
typedef struct bitset_t {
   char *data;
} bitset_t;

#endif