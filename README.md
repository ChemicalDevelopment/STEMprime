# STEMprime

Mersenne prime testing done quickly! 


# Building

## Release (downloaded)

Run `./configure --with-gmp=... && make && make install`

Now, run `stemprime 31` to test 2^31-1

## Development (source)

You will need autotools.

Then, run `autoconf -i`.

And, finally, install like any other.

i.e. `./configure --with-gmp=... && make`

The binary is `./src/stemprime`


# Usage

Run `stemprime $number` to test whether 2^$number-1 is prime.


