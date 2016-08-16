all: main factor

main: ./stemprime_main/stemprime.c; gcc ./stemprime_main/stemprime.c -lm -lgmp -o ./out/STEMprime.o

factor: ./stemprime_factor/main.c ./stemprime_factor/primes.c; gcc ./stemprime_factor/main.c ./stemprime_factor/primes.c ./stemprime_factor/primes.h -lm -o ./out/STEMprime_factor.o
