# STEMprime
Mersenne prime testing done quickly! 

With compiled file stemprime.out, or stemprime.exe, you can run:
"stemprime.out <exp>"
and it tests wether 2^exp - 1 is infact a prime. Definite test using lucas-lehmer sequence.

#Building
You will need GMP (GNU MP Lib) to use this program. You can download it here: https://gmplib.org/
My personal build file I use:
`echo "Building stemprime..."
gcc ~/Documents/stemprime/stemprime.c -lgmp -lm -o ~/Documents/builds/STEMprime.out
echo "done"`
Then use `~/Documents/builds/STEMprime.out <exp>` to run!

#Easier use
My bash file I use as quick command "stemprime <x>" from terminal is located as "stemprime" under this repository (no file format specified.) Put that in your PATH dir and you can now type in "stemprime 44497" and it colorizes output.
