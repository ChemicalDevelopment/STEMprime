#include "string_out.h"

#include "../bstypes.h"
#include "../sieves/bitlib.h"

#include <math.h>

char BASE_STR[64] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@#";

void print_primes(bitset_t bs, int max, char* sep, int _nlz) {
	print_primes_base(bs, max, sep, 10, _nlz);
}

void print_single_int(int x, int base, int _size) {
	int res = x, id = 63, _switch = 0;
	int r[64];
	while (res > 0) {
		r[id--] = res % base;
		res /= base;
	}
	while (id >= 0) {
		r[id--] = 0;
	}
	for (id = 0; id < 64; ++id) {
		if (_switch) {
			printf("%c", BASE_STR[r[id]]);
		} else if (r[id] != 0 || (_size > 0 && id >= 64 - _size)) {
			printf("%c", BASE_STR[r[id]]);
			_switch = 1;			
		}
	}
}

void print_primes_base(bitset_t bs, int max, char* sep, int base, int _nlz) {
	if (base > MAX_BASE) 
		printf("Error. Base too large: %d. Max base is %ld\n", base, MAX_BASE);
	
	int i, max_size = (_nlz) ? 0 : (int) ceill(log(max) / log(base));
	for (i = 0; i <= max; ++i) {
		if (getbit(bs, i)) {
			print_single_int(i, base, max_size);
			printf("%s", sep);
		}
	}
	printf("\n");
}

