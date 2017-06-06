/* progress.c -- records progress, and reads back to resume tests

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

char * sp_storage_name(long exponent) {
    char * res = (char *)malloc(strlen(cargs_get("-d")) + MAX_STRLEN_LONG + 10);
    sprintf(res, "%s/e%ld.result", cargs_get("-d"), exponent);
    return res;
}

bool sp_test_stored(long exponent) {
    char * tofile = sp_storage_name(exponent);
    if (access(tofile, F_OK) != -1) {
        free(tofile);
        return true;
    } else {
        free(tofile);
        return false;
    }
}

void sp_dump_test(ll_test_t test) {
    gettimeofday(&test.fmt.ctim, NULL); 
    double _t_extra_time = test._extra_time + ms_diff(test.fmt.ctim, test.fmt.stime);
    char * tofile = sp_storage_name(test.exp);
    FILE * fp = fopen(tofile, "w+");
    gmp_fprintf(fp, "%ld,%ld,%lf\n%Zd\n%Zd\n", test.exp, test.cur_iter, _t_extra_time, test.L_i, test._2expnm1);
    //gmp_fprintf(fp, "%Zd\n", test.L_i);
    
    fclose(fp);
    free(tofile);
}

void sp_load_test(ll_test_t *test, long exponent) {
    char * tofile = sp_storage_name((*test).exp);
    FILE * fp = fopen(tofile, "r");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET); 
    char *contents = (char *)malloc(fsize + 1);
    fread(contents, fsize, 1, fp);
    fclose(fp);
    contents[fsize] = 0;

    double _t_extra_time = 0;

    gmp_sscanf(contents, "%ld,%ld,%lf\n%Zd\n%Zd\n", &test->exp, &(*test).cur_iter, &_t_extra_time, &test->L_i, &test->_2expnm1);


    (*test)._extra_time += _t_extra_time;
    free(contents);
    free(tofile);
}

