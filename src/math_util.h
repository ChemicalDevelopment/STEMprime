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


// structure to contain exponent and 2^(exponent)-1 
typedef struct exp_2expnm1_t {

    uint32_t exp;
    mpz_t _2expnm1;

} exp_2expnm1_t;



typedef struct ll_test_t {
    long exp;
    long id;

    unsigned long long cur_res;

    struct timeval stime, etime;

    mpz_t L_i, _tmp;

    exp_2expnm1_t _e2n;

    long current_iter;
  
    bool is_finished;
    bool has_printed;
    bool is_prime;
} ll_test_t;



unsigned long long mpz_get_ll(mpz_t z);

void init_exp_2expnm1(exp_2expnm1_t *MOD, long exponent);

void clear_exp_2expnm1(exp_2expnm1_t *MOD);



// LucasLehmer test of 2^exponent - 1
void LL_test(ll_test_t *test);


// initializes math libraries
void init_math_util(uint32_t starting_bits);


// computes to = num % (mod._2expnm1), using accelerated methods
void mpz_mod_2nm1(mpz_t ret, mpz_t num, exp_2expnm1_t mod, mpz_t tmp);


// x - y in ms
double ms_diff(struct timeval x, struct timeval y);


#endif

