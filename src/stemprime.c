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

    cargs_add_arg("-d", "--directory", 1, CARGS_ARG_TYPE_STR, "storage directory for intermediate results");
    cargs_add_default("-d", ".");
    

    cargs_add_arg("-t", NULL, 1, CARGS_ARG_TYPE_INT, "print out every N trials");
    cargs_add_default("-t", "1000");
    

    cargs_add_arg("", NULL, 1, CARGS_ARG_TYPE_INT, "exponent");


    cargs_parse();

    if (cargs_get_flag("")) {

        long exponent = cargs_get_int("");
        ll_test_t test = get_test(exponent);
        init_test(&test);

        if (sp_test_stored(exponent)) {
            sp_load_test(&test, exponent);
        }
        printf("%d;\n", test.cur_iter);
        LL_test(&test);
        
        print_test_result(test);
    }



    return 0;
}

