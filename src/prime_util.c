/* prime_util.c -- prime utility functions

  Copyright 2016-2017 ChemicalDevelopment

  This file is part of the STEMprime project.

  STEMprime source code, as well as any other resources in this project are 
free software; you are free to redistribute it and/or modify them under 
the terms of the GNU General Public License; either version 3 of the 
license, or any later version.

  These programs are hopefully useful and reliable, but it is understood 
that these are provided WITHOUT ANY WARRANTY, or MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GPLv3 or email at 
<info@chemicaldevelopment.us> for more info on this.

  Here is a copy of the GPL v3, which this software is licensed under. You 
can also find a copy at http://www.gnu.org/licenses/.

*/


#include "stemprime.h"


void init_bs(sp_bs_t *bs, int max) {
    bs->max = max;
    bs->arrlen = (max) / BITS_PER_IDX + 1;
    bs->arr = (BS_ELEM *)malloc(BS_ELEM_SIZE * bs->arrlen);
    long i;
    for (i = 0; i < bs->arrlen; ++i) {
        bs->arr[i] = 0;
    }
}

void bs_erat(sp_bs_t *bs) {
    long i, j;
    BS_ELEM set_each = 0;
    for (i = 1; i < BITS_PER_IDX; i += 2) {
        S_BIT((&set_each), i);
    }
    for (i = 0; i < bs->arrlen; ++i) {
        bs->arr[i] = set_each;
    }
    C_BIT(bs->arr, 1);
    S_BIT(bs->arr, 2);
    for (i = 3; i < bs->max; i += 2) {
        if (G_BIT(bs->arr, i)) {
            for (j = 3 * i; j < bs->max; j += 2 * i) {
                C_BIT(bs->arr, j);
            }
        }
    }
}

bool testdiv_nobs(long x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if ((x & 1) != 1) return false;

    long i;
    for (i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool testdiv(long x, sp_bs_t bs) {
    if (x < 2) return false;
    if (x == 2) return true;
    if ((x & 1) != 1) return false;

    long i;
    for (i = 3; i < bs.max; i += 2) {
        if (G_BIT(bs.arr, i) && x % i == 0) {
            return false;
        }
    }
    for (; i * i <= x; i += 2) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

long bs_count(sp_bs_t *bs) {
    long i, sum = 0;
    for (i = 0; i < bs->max; ++i) {
        if (G_BIT(bs->arr, i)) {
            sum++;
        }
    }
    return sum;
}

void bs_clear(sp_bs_t *bs) {
    bs->max = 0;
    bs->arrlen = 0;
    free(bs->arr);
    bs-> arr = NULL;
}


