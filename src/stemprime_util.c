/* stemprime_util.h    gettimeofday(&(*test).fmt.etime, NULL); 

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

ll_test_t get_test(long expo) {
   ll_test_t res;
   res.exp = expo;

   res._extra_time = 0;

   res.start_iter = 1;
   res.cur_iter = 1;

   res.max_iter = expo - 2;
   res.fmt.iter_print_freq = cargs_get_int("-t");

   res.is_prime = false;

   return res;
}

double get_time_left(ll_test_t test) {
    // basic method
   /* double elapsed_time_ms = ms_diff(test.fmt.etime, test.fmt.stime);
    double portion_done = (1.0*test.cur_iter)/(test.max_iter);
    char * time_left_str = get_timelen_str(elapsed_time_ms * (1 - portion_done) / portion_done);*/

    // more advanced
    double elapsed_time_ms = ms_diff(test.fmt.ctim, test.fmt.stime) + test._extra_time;
    double elapsed_time_freq_ms = ms_diff(test.fmt.ctim, test.fmt.lptime);
    double portion_done = (1.0*test.cur_iter)/(test.max_iter);
    double freq_portion = (1.0*test.fmt.iter_print_freq)/(test.max_iter);
    double f0 = elapsed_time_ms * (1 - portion_done) / portion_done;
    double f1 = elapsed_time_freq_ms * (1 - portion_done) / freq_portion;
    double time_left = .8 * f0 + .2 * f1;
    return time_left;

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
    sprintf(res, "%c", 0);
    if (days > 0 || printall) {
        sprintf(res, "%ld%s", days, "d");
        printall = true;
    }
    if (hours > 0 || printall) {
        sprintf(res, "%s%ld%s", res, hours, "hr");
        printall = true;
    }
    if (minutes > 0 || printall) {
        sprintf(res, "%s%ld%s", res, minutes, "m");
        printall = true;
    }
    sprintf(res, "%s%.1lf%s", res, seconds, "s");
    return res;
}

