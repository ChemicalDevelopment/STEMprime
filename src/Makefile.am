###  src/Makefile.am -- Makefile for automake compiling main executables
#  
#    Copyright 2016-2017 ChemicalDevelopment
#  
#    This file is part of the STEMprime project
#  
#    STEMprime source code, as well as any other resources in this project are 
#  free software; you are free to redistribute it and/or modify them under 
#  the terms of the GNU General Public License; either version 3 of the 
#  license, or any later version.
#  
#    These programs are hopefully useful and reliable, but it is understood 
#  that these are provided WITHOUT ANY WARRANTY, or MERCHANTABILITY or FITNESS
#  FOR A PARTICULAR PURPOSE. See the GPLv3 or email at 
#  <info@chemicaldevelopment.us> for more info on this.
#  
#    Here is a copy of the GPL v3, which this software is licensed under. You 
#  can also find a copy at http://www.gnu.org/licenses/.
###  

# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99 -O2
AM_LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
bin_PROGRAMS = stemprime


stemprime_SOURCES = stemprime.h stemprime_util.h stemprime_print.h math_util.h prime_util.h progress.h stemprime.c stemprime_util.c prime_util.c stemprime_print.c math_util.c progress.c
stemprime_LDADD =
