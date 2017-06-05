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

#include "cargs.h"

#include "stemprime.h"


ll_test_t get_test(long expo, long worker_id) {
   ll_test_t res;
   res.exp = expo;
   res.id = worker_id;

   res.current_iter = 0;

   res.is_prime = false;
   res.is_finished = false;
   res.has_printed = false;
   return res;
}


void print_test_result(ll_test_t test) {
    if (!test.is_finished) {
        printf("ERROR: worker %ld not finished\n", test.id);
        exit(3);
    } else {

    printf("[worker %ld]\n", test.id);
    printf("  exp: %ld\n", test.exp);
    if (test.is_prime) {
        printf("  is_prime: true\n");
    } else {
        printf("  is_prime: false\n");
    }
    char * res = get_timelen_str(ms_diff(test.etime, test.stime));
    printf("  iter: %ld/%ld\n", test.current_iter, test.exp - 3);
    printf("  time: %s\n", res);
    printf("  residual: 0x%016llX\n", test.cur_res);
    printf("  ms/iter: %.4lf\n\n", ms_diff(test.etime, test.stime)/test.current_iter);
    free(res);
    fflush(stdout);
    }

}

char * get_timelen_str(double dms) {
    long days = 0, hours = 0, minutes = 0;
    float seconds = 0;
    int ms = dms;
    days = ms / SP_TLMS_DAY;
    ms %= SP_TLMS_DAY;
    hours = ms / SP_TLMS_HOUR;
    ms %= SP_TLMS_HOUR;
    minutes = ms / SP_TLMS_MINUTE;
    ms %= SP_TLMS_MINUTE;
    seconds = ((double)ms) / SP_TLMS_SECOND;
    bool printall = false;
    char * res = (char *)malloc(SP_TLMS_MAXLEN);
    sprintf(res, "");
    if (days > 0 || printall) {
        sprintf(res, "%ld%s ", days, "d");
        printall = true;
    }
    if (hours > 0 || printall) {
        sprintf(res, "%s%ld%s ", res, hours, "hr");
        printall = true;
    }
    if (minutes > 0 || printall) {
        sprintf(res, "%s%ld%s ", res, minutes, "m");
        printall = true;
    }
    sprintf(res, "%s%.1lf%s", res, seconds, "s");
    return res;
}

void print_test(ll_test_t test) {
    if (!test.is_finished) {
        gettimeofday(&test.etime, NULL);
    }
    double elapsed_time_ms = ms_diff(test.etime, test.stime);
    if (test.current_iter == 0) {
        gettimeofday(&test.stime, NULL); 
        test.current_iter = 1;
    }
    double portion_done = (1.0*test.current_iter)/(test.exp-3);
    char * time_left_str = get_timelen_str(elapsed_time_ms * (1 - portion_done) / portion_done);
    printf("[worker %ld] exp=%ld, iter=%ld/%ld [%%%2.2lf], ms/iter=%.4lf, [%s left] [res 0x%016llX]\n", test.id, test.exp, test.current_iter, test.exp - 3, 100*portion_done, elapsed_time_ms / test.current_iter, time_left_str, test.cur_res);
    free(time_left_str);
    fflush(stdout);
}

void * do_process(void * test_v) {
    LL_test((ll_test_t *)test_v);
    return NULL;
}

int main(int argc, char *argv[]) {
    cargs_init(PACKAGE_NAME, VERSION, argc, argv);

    cargs_add_author("Cade Brown", "cade@chemicaldevelopment.us");

    cargs_add_arg("-t", "--time-interval", 1, CARGS_ARG_TYPE_FLOAT, "output interval");
    cargs_add_default("-t", "3.0");
    
    cargs_add_arg("-it", "--internal-time-interval", 1, CARGS_ARG_TYPE_FLOAT, "output interval");
    cargs_add_default("-it", "3.0");
    

    cargs_add_arg("", NULL, CARGS_NUM_ANY, CARGS_ARG_TYPE_INT, "exponents");


    cargs_parse();

    if (cargs_get_len("") > 0) {
        size_t i, len = cargs_get_len("");

        ll_test_t * tests = (ll_test_t *)malloc(sizeof(ll_test_t) * len);
        pthread_t * tests_pt = (pthread_t *)malloc(sizeof(pthread_t) * len);


        for (i = 0; i < len; ++i) {
            tests[i] = get_test(cargs_get_int_idx("", i), i);
            pthread_create(&tests_pt[i], NULL, do_process, (void *)&tests[i]);
        }

        float sleep_s = cargs_get_float("-t");
        float isleep_s = cargs_get_float("-it");

        isleep_s *= floor(isleep_s / sleep_s);

        if (isleep_s > sleep_s) {
            isleep_s = sleep_s;
        }

        if (isleep_s > MAX_ITI) {
            isleep_s = MAX_ITI;
        }

        struct timeval lprint, ctim;
        gettimeofday(&lprint, NULL);

        #ifdef USE_TIMEVAL
        struct timeval isleep_sp, isleep_cp;
        isleep_sp.tv_sec = (long)floor(isleep_s);
        isleep_sp.tv_usec = (long)floor((isleep_s - isleep_sp.tv_sec) * 1000000000.0);
        #else
        struct timespec isleep_sp, isleep_cp;
        isleep_sp.tv_sec = (long)floor(isleep_s);
        isleep_sp.tv_nsec = (long)floor((isleep_s - isleep_sp.tv_sec) * 1000000000.0);
        #endif
        if (sleep_s >= 0) {
            bool all_done = false;
            bool has_printed = false;
            bool do_print = true; 
            while (!all_done) {
                all_done = true;
                gettimeofday(&ctim, NULL);
                if (!has_printed || ms_diff(ctim, lprint) >= sleep_s * 1000.0) {
                    do_print = true;
                    gettimeofday(&lprint, NULL);        
                } else {
                    do_print = false;
                }
                for (i = 0; i < len; ++i) {
                    if (do_print && !tests[i].is_finished) {
                        print_test(tests[i]);
                    }
                    all_done = all_done && tests[i].is_finished;
                }
                if (do_print) {
                    printf("\n");
                }
                nanosleep(&isleep_sp, &isleep_cp);
                has_printed = true;
            }
        }


        for (i = 0; i < len; ++i) {
            pthread_join(tests_pt[i], NULL);
        }

        printf("ALL TESTS DONE\n--------------------------------------------------------------------------------\n");
        
        for (i = 0; i < len; ++i) {
            print_test_result(tests[i]);
        }
    }



    return 0;
}

