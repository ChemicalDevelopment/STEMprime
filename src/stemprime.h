/* stemprime.h -- header for stemprime.c

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


#ifndef __STEMPRIME_H__
#define __STEMPRIME_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <time.h>
#include <sys/time.h>

#include <unistd.h>

#include <math.h>

#include <gmp.h>

#include <cargs.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


typedef struct ll_test_fmt_t {

    struct timeval stime, etime, lptime, ctim;
  
    long iter_print_freq;

} ll_test_fmt_t;



#if GMP_LIMB_BITS == 64
typedef struct ll_res64_t {
  mp_limb_t res;
} ll_res64_t;
#elif GMP_LIMB_BITS == 32
typedef struct ll_res64_t {
  // value = res0 + 2^32 * res1
  mp_limb_t res0, res1;
} ll_res64_t;
#else
#error GMP_LIMB_BITS is neither 32 or 64 bit
#endif

typedef struct ll_test_mpz_t {
    mpz_t L_i, _tmp, _2expnm1;
} ll_test_mpz_t;

typedef struct ll_test_mpn_t {
    long xl, e2xl;
    mp_limb_t *L_i, *_tmp, *_2expnm1;
} ll_test_mpn_t;


typedef struct ll_test_t {
    long exp;

    double _extra_time;

    long start_iter, cur_iter, max_iter;
    
    // if true, use _mpn, else use _mpz
    bool _use_mpn;

    ll_test_mpn_t _mpn;
    ll_test_mpz_t _mpz;

    bool is_prime;
  
    ll_res64_t cur_res;
    ll_test_fmt_t fmt;

} ll_test_t;


#include "math_util.h"
#include "prime_util.h"
#include "stemprime_util.h"
#include "stemprime_print.h"
#include "progress.h"

#define SP_TLMS_SECOND       (1000)
#define SP_TLMS_MINUTE       (SP_TLMS_SECOND * 60)
#define SP_TLMS_HOUR         (SP_TLMS_MINUTE * 60)
#define SP_TLMS_DAY          (SP_TLMS_HOUR * 24)

#define SP_TLMS_MAXLEN       (1000)

int main(int argc, char *argv[]);

#endif
