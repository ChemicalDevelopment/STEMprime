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


unsigned long long mpz_get_ll(mpz_t z) {
    return (z->_mp_d[0]);
}


void init_test(ll_test_t *test) {

    mpz_init2((*test).L_i, 2 * (*test).exp + 1);
    mpz_set_ui((*test).L_i, 4);

    mpz_init((*test)._tmp);

    (*test)._e2n.exp = (*test).exp;
    (*test).cur_res = 2;

    //  _2expnm1 = 2^exp - 1, so store that many bits
    mpz_init2((*test)._e2n._2expnm1, (*test).exp+1);
    mpz_ui_pow_ui((*test)._e2n._2expnm1, 2, (*test).exp);
    mpz_sub_ui((*test)._e2n._2expnm1, (*test)._e2n._2expnm1, 1); 

}


void clear_test(ll_test_t *test) {
    mpz_clear((*test)._e2n._2expnm1);
    mpz_clear((*test)._tmp);
    mpz_clear((*test).L_i);
}

void LL_test(ll_test_t *test) {
    gettimeofday(&(*test).stime, NULL); 

    // ith term of LucasLehmer sequence, mod (2^exp-1)
    long exponent = (*test).exp;

    (*test).cur_res = 4;
    
    init_test(test);

    uint32_t i;
    for (i = 0; i < exponent - 2; i++) {
        // sets iteration information
        (*test).current_iter = i;

        // Ln = L(n-1)**2-2
        mpz_mul((*test).L_i, (*test).L_i, (*test).L_i);
        mpz_sub_ui((*test).L_i, (*test).L_i, 2);

        // % (2^exponent-1)
        //mpz_mod((*test).L_i, (*test).L_i, (*test)._e2n._2expnm1);
        mpz_mod_2nm1((*test).L_i, (*test).L_i, (*test)._e2n, (*test)._tmp);

        (*test).cur_res = mpz_get_ll((*test).L_i);

        if (i % (*test).printout_each == 0 && i != 0) {
            print_test(*test);
        }
    }

    (*test).is_finished = true;
    (*test).is_prime = mpz_cmp_si((*test).L_i, 0) == 0;

    clear_test(test);

    gettimeofday(&(*test).etime, NULL); 


    print_test_result(*test);
}


// computes to = num % (mod._2expnm1), using accelerated methods
void mpz_mod_2nm1(mpz_t ret, mpz_t num, exp_2expnm1_t mod, mpz_t tmp) {
    mpz_tdiv_q_2exp(tmp, num, mod.exp);
    mpz_mod_2exp(ret, num, mod.exp);
    mpz_add(ret, ret, tmp);

    if (mpz_cmp(ret, mod._2expnm1) >= 0) {
        mpz_sub(ret, ret, mod._2expnm1);
    }
}


// x - y in ms
double ms_diff(struct timeval x, struct timeval y) {
    return (x.tv_sec - y.tv_sec) * 1000.0 + (x.tv_usec - y.tv_usec) / 1000.0;
}


