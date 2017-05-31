/* math_util.c -- math utility functions

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


mpz_t __MATH_UTIL_TMP_MPZ_0, __MATH_UTIL_TMP_MPZ_1;


// LucasLehmer test of 2^exponent - 1

bool LL_mpz_u32(uint32_t exponent) {
    // ith term of LucasLehmer sequence, mod (2^exp-1)
    mpz_t L_i;
    
    // preallocate enough room to square the previous term
    mpz_init2(L_i, 2 * exponent + 1);
    mpz_set_ui(L_i, 4);
    
    // a struct to store a uint and mpz (so that you don't have to convert)
    exp_2expnm1_t MOD;

    MOD.exp = exponent;

    //  _2expnm1 = 2^exp - 1, so store that many bits
    mpz_init2(MOD._2expnm1, exponent+1);
    mpz_ui_pow_ui(MOD._2expnm1, 2, exponent);
    mpz_sub_ui(MOD._2expnm1, MOD._2expnm1, 1); 


    uint32_t i;
    for (i = 0; i < exponent - 2; i++) {
        // Ln = L(n-1)**2-2
        mpz_mul(L_i, L_i, L_i);
        mpz_sub_ui(L_i, L_i, 2);

        // % (2^exponent-1)
        mpz_mod_2nm1(L_i, L_i, MOD);
        
        if (exponent/100 == 0 || i % (exponent/100) == 0 || i == exponent - 3) {
            printf("%%%f\r", (100.*i) / (exponent-3));
            fflush(stdout);
        }
    }
    printf("\n");
    return mpz_cmp_si(L_i, 0) == 0;
}
// initializes math libraries
void init_math_util(uint32_t starting_bits) {
    mpz_init2(__MATH_UTIL_TMP_MPZ_0, starting_bits);
    mpz_init2(__MATH_UTIL_TMP_MPZ_1, starting_bits);
}

// computes to = num % (mod._2expnm1), using accelerated methods
void mpz_mod_2nm1(mpz_t ret, mpz_t num, exp_2expnm1_t mod) {
    mpz_tdiv_q_2exp(__MATH_UTIL_TMP_MPZ_0, num, mod.exp);
    mpz_mod_2exp(__MATH_UTIL_TMP_MPZ_1, num, mod.exp);
    mpz_add(__MATH_UTIL_TMP_MPZ_0, __MATH_UTIL_TMP_MPZ_0, __MATH_UTIL_TMP_MPZ_1);
    mpz_set(ret, __MATH_UTIL_TMP_MPZ_0);

    if (mpz_cmp(ret, mod._2expnm1) >= 0) {
        mpz_sub(ret, ret, mod._2expnm1);
    }
}


