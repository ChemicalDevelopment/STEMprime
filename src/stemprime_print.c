/* stemprime_print.c -- printing information is handled here

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

void print_res64(ll_res64_t res) {
    #if GMP_LIMB_BITS == 64
    gmp_printf("0x%016MX", res.res);
    #elif GMP_LIMB_BITS == 32
    gmp_printf("0x%08MuX%08MX", res.res1, res.res0);
    #else
    #error sizeof(long) is SIZEOF_LONG, dont know how to use this
    #endif
}

void print_test_result(ll_test_t test) {
    printf("[exp %ld]\n", test.exp);
    if (test.is_prime) {
        printf("  is_prime: true\n");
    } else {
        printf("  is_prime: false\n");
    }
    char * res = get_timelen_str(ms_diff(test.fmt.etime, test.fmt.stime));
    printf("  iter: %ld/%ld\n", test.cur_iter, test.max_iter);
    printf("  time: %s\n", res);
    printf("  residual: ");
    print_res64(test.cur_res);
    printf("\n");
    printf("  ms/iter: %.4lf\n\n", ms_diff(test.fmt.etime, test.fmt.stime)/test.cur_iter);
    free(res);
    fflush(stdout);
}

void print_test(ll_test_t test) {
    gettimeofday(&test.fmt.ctim, NULL);
    double elapsed_time_ms = ms_diff(test.fmt.ctim, test.fmt.stime);
    double portion_done = (1.0*test.cur_iter)/(test.max_iter);
    char * time_left_str = get_timelen_str(get_time_left(test));
    
    printf("[exp %ld] iter=%ld/%ld [%%%2.2lf], ms/iter=%.4lf, [%s left] [res ", test.exp, test.cur_iter, test.max_iter, 100*portion_done, elapsed_time_ms / test.cur_iter, time_left_str);
    print_res64(test.cur_res);
    printf("]\n");
    free(time_left_str);
    fflush(stdout);
}

