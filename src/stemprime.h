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

#include <pthread.h>

#include <gmp.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "math_util.h"


#define SP_TLMS_SECOND       (1000)
#define SP_TLMS_MINUTE       (SP_TLMS_SECOND * 60)
#define SP_TLMS_HOUR         (SP_TLMS_MINUTE * 60)
#define SP_TLMS_DAY          (SP_TLMS_HOUR * 24)
#define SP_TLMS_MAXLEN       (1000)


ll_test_t get_test(long expo, long worker_id);

void print_test_result(ll_test_t test);

char * get_timelen_str(double ms);

void print_test(ll_test_t test);

void * do_process(void * test_v);

int main(int argc, char *argv[]);

#endif
