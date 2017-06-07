/* math_util.h -- header for math_util.h, defines math functions

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


#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include "stemprime.h"


double ms_diff(struct timeval x, struct timeval y);

void mpn_get_res64(ll_res64_t *r, mp_limb_t *z);

void mpz_get_res64(ll_res64_t *r, mpz_t z);

void init_test(ll_test_t *test);

void clear_test(ll_test_t *test);

void LL_test(ll_test_t *test);

void LL_stest_mpn(ll_test_t *test);

void LL_stest_mpz(ll_test_t *test);


#endif

