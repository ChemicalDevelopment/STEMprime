#include <malloc.h>
#include <stdint.h>
#include "array_management.h"
/*

This int array stores whether 2[bit] + 1 is prime.
2 is not shown as being prime in this array.

It uses the native arcitecture of the computer size.

*/

void set_prime_array(unsigned int max, unsigned int ** prime_array) {
    unsigned int *temp_array = (unsigned int *)malloc(sizeof(unsigned int) * max + 1);
    long i, j;
    for (i = 0; i < max; ++i) {
        set_index_true(i, temp_array);
    }

    set_index_false(0, temp_array);
    set_index_false(1, temp_array);
    for (i = 2; i <= max; ++i) {
        if (get_index(i, temp_array)) {
            for (j = 2 * i; j <= max; j += i) {
                set_index_false(j, temp_array);
            }
        }
    }
    set_index_false(2, temp_array);
    *prime_array = (unsigned int *)malloc(sizeof(unsigned int) * max + 1);
    j = 1;
    for (i = 3; i <= max; i += 2) {
        if (get_index(i, temp_array)) {
            set_index_true(j, *prime_array);
        }
        ++j;
    }
    free(temp_array);
}

