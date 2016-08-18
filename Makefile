MAIN_SOURCES = ./stemprime_main/stemprime.c

FACTOR_SOURCES = ./stemprime_factor/main.c ./stemprime_factor/primes.c ./stemprime_factor/mersenne_factor.c ./stemprime_factor/array_management.c ./stemprime_factor/primes.h ./stemprime_factor/mersenne_factor.h ./stemprime_factor/array_management.h   

LIB = -lm -lgmp

all: main factor

main: $(MAIN_SOURCES); gcc $(MAIN_SOURCES) $(LIB) -o ./out/STEMprime.o

factor: $(FACTOR_SOURCES); gcc $(FACTOR_SOURCES) $(LIB) -o ./out/STEMprime_factor.o
