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


void mpz_get_res64(ll_res64_t *r, mpz_t z) {
#if GMP_LIMB_BITS == 64
    (*r).res = z->_mp_d[0];
#elif GMP_LIMB_BITS == 32
    (*r).res0 = z->_mp_d[0];
    (*r).res1 = z->_mp_d[1];
#else
    #error sizeof(long) is SIZEOF_LONG, dont know how to use this
#endif
}


void init_test(ll_test_t *test) {

    mpz_init2((*test).L_i, 2 * (*test).exp + 1);
    mpz_set_ui((*test).L_i, 4);

    mpz_init((*test)._tmp);

    //  _2expnm1 = 2^exp - 1, so store that many bits
    mpz_init2((*test)._2expnm1, (*test).exp+1);
    mpz_ui_pow_ui((*test)._2expnm1, 2, (*test).exp);
    mpz_sub_ui((*test)._2expnm1, (*test)._2expnm1, 1); 
}


void clear_test(ll_test_t *test) {
    mpz_clear((*test)._2expnm1);
    mpz_clear((*test)._tmp);
    mpz_clear((*test).L_i);
}

void LL_test(ll_test_t *test) {
    gettimeofday(&(*test).fmt.stime, NULL); 
    gettimeofday(&(*test).fmt.lptime, NULL); 

    // ith term of LucasLehmer sequence, mod (2^exp-1)
    //long exponent = (*test).exp;

    mpz_get_res64(&(*test).cur_res, (*test).L_i);

    uint32_t i;
    for (i = (*test).cur_iter; i <= (*test).max_iter; i++) {
        // sets iteration information
        (*test).cur_iter = i;

        if ((*test).fmt.iter_print_freq != 0 && i % (*test).fmt.iter_print_freq == 0 && i != 0) {
            mpz_get_res64(&(*test).cur_res, (*test).L_i);
            print_test(*test);
            sp_dump_test(*test);
            gettimeofday(&(*test).fmt.lptime, NULL);     
        }

        // Ln = L(n-1)**2-2
        mpz_mul((*test).L_i, (*test).L_i, (*test).L_i);
        mpz_sub_ui((*test).L_i, (*test).L_i, 2);


        // % (2^exponent-1)
        // computes to = num % (mod._2expnm1), using accelerated methods
        mpz_tdiv_q_2exp((*test)._tmp, (*test).L_i, (*test).exp);
        mpz_mod_2exp((*test).L_i, (*test).L_i, (*test).exp);
        mpz_add((*test).L_i, (*test).L_i, (*test)._tmp);
        if (mpz_cmp((*test).L_i, (*test)._2expnm1) >= 0) {
            mpz_sub((*test).L_i, (*test).L_i, (*test)._2expnm1);
        }

    }

    mpz_get_res64(&(*test).cur_res, (*test).L_i);

    (*test).is_prime = mpz_cmp_si((*test).L_i, 0) == 0;

    gettimeofday(&(*test).fmt.etime, NULL); 

    clear_test(test);

}


// x - y in ms
double ms_diff(struct timeval x, struct timeval y) {
    return (x.tv_sec - y.tv_sec) * 1000.0 + (x.tv_usec - y.tv_usec) / 1000.0;
}


