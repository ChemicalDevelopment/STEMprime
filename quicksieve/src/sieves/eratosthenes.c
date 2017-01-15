#include "eratosthenes.h"

#include "bitlib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void __bitset_erat_C(bitset_t list, long int max) {
	long int i, j;
	memset(list.data, 0b10101010, SIZE_BS(max));
	setbit_0(list, 0);
	setbit_0(list, 1);
	setbit_1(list, 2);
	
	for (i = 3; i * i <= max; i += 2) {
		if (getbit(list, i)) {
			for (j = 3 * i; j <= max; j += 2 * i) {
				setbit_0(list, j);
			}
		}
	}
}

void bitset_erat(bitset_t *bs, long int max) {
	(*bs).data = MALLOC_BS(max);
	__bitset_erat_C((*bs), max);
}
