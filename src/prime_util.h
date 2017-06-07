/* prime_util.h -- header for prime_util.c

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


#ifndef __PRIME_UTIL_H__
#define __PRIME_UTIL_H__

#include "stemprime.h"


#define BS_ELEM mp_limb_t

typedef struct sp_bs_t {
    long max, arrlen;

    BS_ELEM *arr;
} sp_bs_t;


#define BS_ELEM_SIZE (sizeof(BS_ELEM))
#define BITS_PER_IDX ((BS_ELEM_SIZE) * 8)


#define BIT(arr, idx) (arr[(idx) / BITS_PER_IDX] >> ((BS_ELEM)((idx) % BITS_PER_IDX))) & 1

#define S_BIT(arr, idx) arr[(idx) / (BITS_PER_IDX)] |= ((BS_ELEM)1) << ((idx) % (BITS_PER_IDX))
#define C_BIT(arr, idx) arr[(idx) / (BITS_PER_IDX)] &= ~(((BS_ELEM)1) << ((idx) % (BITS_PER_IDX)))
#define G_BIT(arr, idx) (BIT(arr, idx))



void init_bs(sp_bs_t *bs, int max);

void bs_erat(sp_bs_t *bs);

long bs_count(sp_bs_t *bs);

void bs_clear(sp_bs_t *bs);

bool testdiv(long x, sp_bs_t bs);

bool testdiv_nobs(long x);

#endif
