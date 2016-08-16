#include <malloc.h>
#include <stdint.h>
#include "primes.h"
#include <stdio.h>
/*

This int array stores whether 2[bit] + 1 is prime.
2 is not shown as being prime in this array.

It uses the native arcitecture of the computer size.

*/

int INT_BITS = 8 * sizeof(unsigned int);

unsigned int *primearray;

void set_index_true(long idx, int *bitarray) {
    bitarray[idx / INT_BITS] |= (1 << (idx % INT_BITS));
}

void set_index_false(long idx, int *bitarray) {
    bitarray[idx / INT_BITS] &= ~(1 << (idx % INT_BITS));
}

unsigned int get_index(long idx, int *bitarray) {
    return bitarray[idx / INT_BITS] >> (idx % INT_BITS) & 1;
}

void set_bitarray(long max) {
    free(primearray);
    unsigned int *temparray = (unsigned int *)malloc(max / INT_BITS + 20);
    long i, j;
    for (i = 0; i <= max; ++i) {
        set_index_true(i, temparray);
    }
    set_index_false(0, temparray);
    set_index_false(1, temparray);
    for (i = 2; i <= max; ++i) {
        if (get_index(i, temparray)) {
            for (j = 2 * i; j <= max; j += i) {
                set_index_false(j, temparray);
            }
        }
    }
    set_index_false(2, temparray);
    primearray = (unsigned int *)malloc(max / (2 * INT_BITS) + 2);
    j = 1;
    for (i = 3; i <= max; i += 2) {
        if (get_index(i, temparray)) {
            set_index_true(j, primearray);
        }
        ++j;
    }
    free(temparray);
}

unsigned int * prime_array() {
    return primearray;
}


