# STEMprime
Mersenne prime testing done quickly! 

With compiled file stemprime.out, or stemprime.exe, you can run:
"stemprime.out <exp>"
and it tests wether 2^exp - 1 is infact a prime. Definite test using lucas-lehmer sequence.

# Building
You will need GMP (GNU MP Lib) to use this program. You can download it here: https://gmplib.org/
then, simply run
```
make
```
The outputs are in ./out/

# Usage

## STEMprime.o
run `./stemprime.o $number` to test whether 2^$number-1 is prime.

## STEMprime_factor.o
Coming soon

