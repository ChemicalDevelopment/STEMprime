
#include <stdlib.h>
#include <stdbool.h>

int argc;
char **argv;

void init_input(int _argc, char *_argv[]) {
	argc = _argc;
	argv = _argv;
}


bool get_flag(char opt[]) {
	int i;
	for (i = 1; i < argc; ++i) {
		if (strcmp(argv[i], opt) == 0) {
			return true;
		}
	}
	return false;
}

int get_int_var(char opt[], int dft) {
	int i;
	for (i = 1; i < argc; ++i) {
		if (strcmp(argv[i], opt) == 0) {
			return strtol(argv[i+1], NULL, 10);
		}
	}
	return dft;
}

char * get_str_var(char opt[], char dft[]) {
	int i;
	for (i = 1; i < argc - 1; ++i) {
		if (strcmp(argv[i], opt) == 0) {
			return argv[i+1];
		}
	}
	return dft;
}
