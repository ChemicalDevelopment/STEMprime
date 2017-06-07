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
    int _b_um = test._use_mpn;
    fprintf(fp, "%d,%ld,%ld,%lf\n", _b_um, test.exp, test.cur_iter, _t_extra_time);
    mpz_out_raw(fp, test._mpz.L_i);
    mpz_out_raw(fp, test._mpz._2expnm1);
    
    fclose(fp);
    free(tofile);
}

void sp_load_test(ll_test_t *test, long exponent) {
    char * tofile = sp_storage_name((*test).exp);
    FILE * fp = fopen(tofile, "r");
    double _t_extra_time = 0;

    init_test(test);

    int _b_um;
    int fsf_res = fscanf(fp, "%d,%ld,%ld,%lf\n", &_b_um, &test->exp, &test->cur_iter, &_t_extra_time);

    test->_use_mpn = _b_um;

    if (fsf_res != 4) {
        fclose(fp);
        int status = remove(tofile);
        if (status == 0) {
            sp_error("sp_load_test: Progress file was corrupt, and was deleted\n");
        } else {
            sp_error("sp_load_test: Progress file was corrupt, but couldn't be deleted\n");
        }
    }



    mpz_inp_raw(test->_mpz.L_i, fp);
    mpz_inp_raw(test->_mpz._2expnm1, fp);

    (*test)._extra_time += _t_extra_time;

    fclose(fp);
    free(tofile);
}

