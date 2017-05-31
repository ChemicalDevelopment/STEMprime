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
    uint32_t exponent = 580673;
    if (argc > 1) exponent = strtol(argv[1], NULL, 10);
    bool res;
    clock_t s, e;
    s = clock();
    res = LL_mpz_u32(exponent);
    e = clock();
    if (res) {
        printf("2^%d-1 is prime\n", exponent);
    }
    printf("took %lf seconds\n", (double)(e-s)/1000000);
    return 0;
}
