#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "output/string_out.h"
#include "sieves/eratosthenes.h"
#include "sieves/bitlib.h"


#define QS_VERSION "0.0.1"


int main(int argc, char *argv[]) {
	printf("QS v%s\n", QS_VERSION);
	long int max = 1000;
	char *set;
	bitset_erat(&set, max);
	printf("%ld\n", count(set, max));

	int i;
	for (i = 0; i <= max; ++i) {
		if (getbit(set, i)) {
			printf("%d, ", i);
		}
	}
	printf("\n");

	return 0;
}




