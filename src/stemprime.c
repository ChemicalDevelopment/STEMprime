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

#include "stemprime.h"



int main(int argc, char *argv[]) {
    cargs_init(PACKAGE_NAME, VERSION, argc, argv);

    cargs_add_author("Cade Brown", "cade@chemicaldevelopment.us");

    cargs_add_arg("-v", NULL, 1, CARGS_ARG_TYPE_INT, "verbosity level");
    cargs_add_default("-v", "2");

    cargs_add_arg("-d", "--directory", 1, CARGS_ARG_TYPE_STR, "storage directory for intermediate results");
    cargs_add_default("-d", ".");
    
    cargs_add_flag("-sieve", NULL, "print a sieve");

    cargs_add_flag("-mpn", NULL, "use MPN functions");
    cargs_add_flag("-nc", NULL, "do not use checkpoint files, creating or loading");

    cargs_add_flag("-tdiv", NULL, "test divide number");
    cargs_add_flag("-ns", NULL, "no sieve");

    cargs_add_arg("-t", NULL, 1, CARGS_ARG_TYPE_INT, "print out every N trials");
    cargs_add_default("-t", "10000");
    

    cargs_add_arg("", NULL, 1, CARGS_ARG_TYPE_INT, "exponent");


    cargs_parse();

    if (cargs_get_int("-v") >= 3) {
        print_extended_info();
    }

    if (cargs_get_flag("-sieve")) {
        long max = cargs_get_int("");
        sp_bs_t bits;

        init_bs(&bits, max);
        bs_erat(&bits);

        printf("primes < %ld is %ld\n", max, bs_count(&bits));
        bs_clear(&bits);

    } else if (cargs_get_flag("-tdiv")) {
        long num = cargs_get_int("");
        if (cargs_get_flag("-ns")) {
            if (testdiv_nobs(num)) {
                printf("%d is prime\n", num);
            } else {
                printf("%d is not prime\n", num);
            }
        } else {
            sp_bs_t bits;
            init_bs(&bits, 2+(long)sqrt(num));
            bs_erat(&bits);

            if (testdiv(num, bits)) {
                printf("%d is prime\n", num);
            } else {
                printf("%d is not prime\n", num);
            }

            bs_clear(&bits);
        }

    } else if (cargs_get_flag("")) {

        long exponent = cargs_get_int("");
        ll_test_t test = get_test(exponent);

        test._use_mpn = cargs_get_flag("-mpn");

        if (!cargs_get_flag("-mpn") && !cargs_get_flag("-nc") && sp_test_stored(exponent)) {
            sp_load_test(&test, exponent);
        } else {
            init_test(&test);
        }

        LL_test(&test);
        
        print_test_result(test);
    }

    return 0;
}

