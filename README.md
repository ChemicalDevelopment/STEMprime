# STEMprime

Mersenne prime testing done quickly! 

## Requirements 

[GMP](https://gmplib.org/#DOWNLOAD)

[cargs](https://github.com/chemicaldevelopment/cargs)

libpthread


# Usage

Run `stemprime $number` to test whether 2^$number-1 is prime.

Run `stemprime --help` to view usage and help info

Run `stemprime N0 N1 N2 N3 ...` to test a series of exponents, in parallel (i.e. `stemprime 31 67 127 128` would test 2^31-1, 2^67-1, 2^127-1, and 2^128-1).


## Options

| Option | Takes | Function |
|:------------- |:------------- |:----- |
| `--info` | N/A | Prints version and name info about the program |
| `-h, --help` | N/A | Prints help and usage information |
| `--authors` | N/A | Prints authors name and email addresses |
| `-t, --time-interval` | number | Sets the number of seconds to wait for each output |
| No prefix | list of numbers | Gives the list of numbers to check primality of `2^N-1` for each N |


# Building

## Release (downloaded)

Run `./configure && make && make install`

Run `stemprime --help` to view the help info.

An example usage would be like: `stemprime 31` to test 2^31-1


## Development (source)

You will need autotools, GMP, , and pthreads.

Then, run `autoconf -i`.

And, finally, install like any other.

i.e. `./configure && make`

The binary is `./src/stemprime`

## Configure Options

| Option | Description | Note |
|:------------- |:------------- |:----- |
| `--enable-static` | Builds a static executable (for distributing) | Doesn't always work on macOS |
| `--with-X=XDIR` | Gives info for finding library `X` in `XDIR` | See the next section |


## Non Standard Locations

If you have installed GMP, cargs, or pthreads in a non standard location, you can modify the configure step like so:

`./configure --with-gmp=GMPDIR --with-cargs=CARGSDIR ...`

GMPDIR should be what you set `--prefix` while configuring GMP, CARGSDIR should be what you set `--prefix` to while configuring cargs, etc.

Then, run `make` like the examples give, and you should be good!

