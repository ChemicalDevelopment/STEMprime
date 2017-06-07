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


void mpn_get_res64(ll_res64_t *r, mp_limb_t *z) {
#if GMP_LIMB_BITS == 64
    (*r).res = z[0];
#elif GMP_LIMB_BITS == 32
    (*r).res0 = z[0];
    (*r).res1 = z[1];
#else
    #error GMP_LIMB_BITS is neither 32 or 64 bit
#endif
}

void mpz_get_res64(ll_res64_t *r, mpz_t z) {
#if GMP_LIMB_BITS == 64
    (*r).res = z->_mp_d[0];
#elif GMP_LIMB_BITS == 32
    (*r).res0 = z->_mp_d[0];
    (*r).res1 = z->_mp_d[1];
#else
    #error GMP_LIMB_BITS is neither 32 or 64 bit
#endif
}

void _pmpn(mp_limb_t *nn ,int xl) {
    char * res = (char *)malloc(10000);
    int num = mpn_get_str(res, 10, nn, xl);
    size_t j;
    for (j = 0; j < num; ++j) {
        res[j] = res[j] + '0';
    } 
    res[j] = 0;
    printf("%s;\n", res);

}

void init_test(ll_test_t *test) {
    if (test->_use_mpn) {
        long xl = test->exp / GMP_LIMB_BITS + 1;
        //printf("%d'\n", xl);
        test->_mpn.xl = xl;

        test->_mpn.L_i = (mp_limb_t *)malloc((xl) * sizeof(mp_limb_t));
        mpn_zero(test->_mpn.L_i, xl);

        mpn_add_1(test->_mpn.L_i, test->_mpn.L_i, xl + 1, 4);

        test->_mpn._tmp = (mp_limb_t *)malloc(2 * xl * sizeof(mp_limb_t));
        mpn_zero(test->_mpn._tmp, 2 * xl);

        test->_mpn._2expnm1 = (mp_limb_t *)malloc(xl * sizeof(mp_limb_t));
        mpn_zero(test->_mpn._2expnm1, xl);


        mpn_add_1(test->_mpn._2expnm1, test->_mpn._2expnm1, xl, 1);
        long tshift = test->exp;
        while (tshift >= GMP_LIMB_BITS) {
            mpn_lshift(test->_mpn._2expnm1, test->_mpn._2expnm1, xl, GMP_LIMB_BITS - 1);
            tshift -= GMP_LIMB_BITS - 1;
        }
        mpn_lshift(test->_mpn._2expnm1, test->_mpn._2expnm1, xl, tshift);

        mpn_sub_1(test->_mpn._2expnm1, test->_mpn._2expnm1, xl, 1);

        long e2xl = xl, jj = xl - 1;
        while (test->_mpn._2expnm1[jj] == 0) {
            jj--;
            e2xl--;
        }

        test->_mpn.e2xl = e2xl;

    } else {
        mpz_init2(test->_mpz.L_i, 2 * test->exp + 1);
        mpz_set_ui(test->_mpz.L_i, 4);

        mpz_init(test->_mpz._tmp);

        //  _2expnm1 = 2^exp - 1, so store that many bits
        mpz_init2(test->_mpz._2expnm1, test->exp+1);
        mpz_ui_pow_ui(test->_mpz._2expnm1, 2, test->exp);
        mpz_sub_ui(test->_mpz._2expnm1, test->_mpz._2expnm1, 1); 
    }
}


void clear_test(ll_test_t *test) {
    if (test->_use_mpn) {
        free(test->_mpn.L_i);
        free(test->_mpn._tmp);
        free(test->_mpn._2expnm1);
    } else {
        mpz_clear(test->_mpz._2expnm1);
        mpz_clear(test->_mpz._tmp);
        mpz_clear(test->_mpz.L_i);
    }
}

void LL_test(ll_test_t *test) {
    gettimeofday(&test->fmt.stime, NULL); 
    gettimeofday(&test->fmt.lptime, NULL); 

    // ith term of LucasLehmer sequence, mod (2^exp-1)
    //long exponent = test->exp;

    if (test->_use_mpn) {
        LL_stest_mpn(test);
    } else {
        LL_stest_mpz(test);
    }

    gettimeofday(&test->fmt.etime, NULL); 

    clear_test(test);
}



void LL_stest_mpn(ll_test_t *test) {
    mpn_get_res64(&test->cur_res, test->_mpn.L_i);
    //bool do_check = !cargs_get_flag("-nc");
    bool do_check = true;
    test->start_iter = test->cur_iter;
    
    long tshift = test->exp;

    sp_warn("LL_stest_mpn: mpn mode NOT supported yet");


    uint32_t i;
    for (i = test->cur_iter; i <= test->max_iter; i++) {
        // sets iteration information
        test->cur_iter = i;
        
        mpn_sqr(test->_mpn._tmp, test->_mpn.L_i, test->_mpn.xl);
        mpn_sub_1(test->_mpn._tmp, test->_mpn._tmp, test->_mpn.xl, 2);

        mpn_and_n(test->_mpn.L_i, test->_mpn._tmp, test->_mpn._2expnm1, test->_mpn.e2xl);

        tshift = test->exp;
        
        while (tshift >= GMP_LIMB_BITS) {
            mpn_rshift(test->_mpn._tmp, test->_mpn._tmp, test->_mpn.xl, GMP_LIMB_BITS - 1);
            tshift -= GMP_LIMB_BITS - 1;
        }
        mpn_rshift(test->_mpn._tmp, test->_mpn._tmp, test->_mpn.xl, tshift);
    
        mpn_add_n(test->_mpn.L_i, test->_mpn.L_i, test->_mpn._tmp, test->_mpn.xl);
        mpn_sub_n(test->_mpn.L_i, test->_mpn.L_i, test->_mpn._2expnm1, test->_mpn.e2xl);

        // classic modulo
        //mpn_tdiv_qr(test->_mpn.L_i, test->_mpn._tmp, 0, test->_mpn._tmp, 2*test->_mpn.xl, test->_mpn._2expnm1, test->_mpn.e2xl);
        
        mpn_copyi(test->_mpn.L_i, test->_mpn._tmp, test->_mpn.xl);
    
        if (test->fmt.iter_print_freq != 0 && i % test->fmt.iter_print_freq == 0) {
            mpn_get_res64(&test->cur_res, test->_mpn._tmp);
            
            print_test(*test);
            if (do_check) {
        //        sp_dump_test(*test);
            }
            gettimeofday(&test->fmt.lptime, NULL);     
        }

    }

    mpn_get_res64(&test->cur_res, test->_mpn.L_i);
    
    test->is_prime = mpn_zero_p(test->_mpn.L_i, test->_mpn.xl);


}

void LL_stest_mpz(ll_test_t *test) {

    mpz_get_res64(&test->cur_res, test->_mpz.L_i);
    bool do_check = !cargs_get_flag("-nc");

    test->start_iter = test->cur_iter;

    uint32_t i;

    for (i = test->cur_iter; i <= test->max_iter; i++) {
        // sets iteration information
        test->cur_iter = i;

        if (test->fmt.iter_print_freq != 0 && i % test->fmt.iter_print_freq == 0) {
            mpz_get_res64(&test->cur_res, test->_mpz.L_i);
            print_test(*test);
            if (do_check) {
                sp_dump_test(*test);
            }
            gettimeofday(&test->fmt.lptime, NULL);     
        }

        // Ln = L(n-1)**2-2
        mpz_mul(test->_mpz.L_i, test->_mpz.L_i, test->_mpz.L_i);
        mpz_sub_ui(test->_mpz.L_i, test->_mpz.L_i, 2);


        // % (2^exponent-1)
        // computes to = num % (mod._2expnm1), using accelerated methods
        mpz_tdiv_q_2exp(test->_mpz._tmp, test->_mpz.L_i, test->exp);
        //mpz_mod_2exp(test->_mpz.L_i, test->_mpz.L_i, test->exp);
        mpz_and(test->_mpz.L_i, test->_mpz.L_i, test->_mpz._2expnm1);
        mpz_add(test->_mpz.L_i, test->_mpz.L_i, test->_mpz._tmp);
        //if (mpz_cmp(test->L_i, test->_2expnm1) >= 0) {
            mpz_sub(test->_mpz.L_i, test->_mpz.L_i, test->_mpz._2expnm1);
        //}
    }

    mpz_get_res64(&test->cur_res, test->_mpz.L_i);

    test->is_prime = mpz_cmp_si(test->_mpz.L_i, 0) == 0;
}


// x - y in ms
double ms_diff(struct timeval x, struct timeval y) {
    return (x.tv_sec - y.tv_sec) * 1000.0 + (x.tv_usec - y.tv_usec) / 1000.0;
}


