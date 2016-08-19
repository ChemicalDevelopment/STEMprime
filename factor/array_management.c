#include <stdint.h>
/*

This int array stores whether 2[bit] + 1 is prime.
2 is not shown as being prime in this array.

It uses the native arcitecture of the computer size.

*/

int INT_BITS = 8 * sizeof(unsigned int);

void set_index_true(long idx, unsigned int *bitarray) {
    bitarray[idx / INT_BITS] |= (1 << (idx % INT_BITS));
}

void set_index_false(long idx, unsigned int *bitarray) {
    bitarray[idx / INT_BITS] &= ~(1 << (idx % INT_BITS));
}

unsigned int get_index(long idx, unsigned int *bitarray) {
    return bitarray[idx / INT_BITS] >> (idx % INT_BITS) & 1;
}

