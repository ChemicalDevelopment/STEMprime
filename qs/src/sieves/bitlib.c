#include "bitlib.h"

long int count(char *set, long int max) {
	int i, total = 0;
	for (i = 0; i <= max; ++i) {
		if (getbit(set, i)) {
			++total;
		}
	}
	return total;
}




