###  configure.ac -- Autoconf configuration script
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


AC_PREREQ([2.55])
AC_INIT([STEMprime], [0.1.0], [group@chemicaldevelopment.us])
AM_INIT_AUTOMAKE()

AC_CONFIG_SRCDIR([src/stemprime.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h stdio.h stdbool.h string.h math.h sys/time.h time.h unistd.h])

# Checks for libraries.

AC_CHECK_LIB(m, log)


# these are all required

LIBS="-lcargs -lgmp -lm $LIBS"


# mpi for titan supercomputer

AC_ARG_WITH(
  mpi, 
  AS_HELP_STRING([--with-mpi],
  [Provide cargs directory]), [
  case "$with_mpi" in
    yes)
      withval=/usr/local
      ;;
  esac

  LDFLAGS="$LDFLAGS -L$withval/lib"
  CFLAGS="$CFLAGS -I$withval/include"

  AC_DEFINE([USE_MPI], [], [Use MPI])
  AC_MSG_CHECKING(mpi)
  AC_MSG_RESULT(yes ($withval))
], [ ])



# cargs is required

AC_ARG_WITH(
  cargs, 
  AS_HELP_STRING([--with-cargs],
  [Provide cargs directory]), [
  case "$with_cargs" in
    yes)
      withval=/usr/local
      ;;
  esac

  LDFLAGS="$LDFLAGS -L$withval/lib"
  CFLAGS="$CFLAGS -I$withval/include"

  AC_MSG_CHECKING(cargs)
  AC_MSG_RESULT(yes ($withval))
], [ ])


AC_CHECK_HEADER(cargs.h, [], [
  AC_MSG_ERROR(cargs header not found (looking for cargs.h))
])

AC_CHECK_LIB(cargs, cargs_init)


# GMP can be supplied to use multiprecision support

AC_ARG_WITH(
  gmp, 
  AS_HELP_STRING([--with-gmp],
  [Use GMP for multiprecision]), [
  case "$with_gmp" in
    yes)
      withval=/usr/local
      ;;
  esac

  LDFLAGS="$LDFLAGS -L$withval/lib"
  CFLAGS="$CFLAGS -I$withval/include"

  AC_CHECK_HEADER(gmp.h, [], [
    AC_MSG_ERROR(GMP header not found (looking for gmp.h))
  ])
  AC_MSG_CHECKING(GMP)
  AC_MSG_RESULT(yes ($withval))

  AC_DEFINE([USE_GMP], [1], [Use GMP library code])
], [ ])



AH_TEMPLATE(USE_GMP,[GMP support is available])

AC_DEFINE([MAX_ITI], [60], [Maximum internal time interval (in s)])


AC_MSG_CHECKING("whether timeval should be used")

AC_TRY_RUN([
  #include <time.h>
  #include <sys/time.h>
  int main() { struct timeval x; return 0; }
], [
    AC_DEFINE(USE_TIMEVAL, [], [Use timeval struct]) 
    AC_MSG_RESULT("yes")
], AC_MSG_RESULT("no") )


AC_ARG_ENABLE([static], AS_HELP_STRING([--enable-static], [Enable static building]))

AS_IF([test "x$enable_static" = "xyes"], [
  LDFLAGS="-static $LDFLAGS"
], [
])


AC_DEFINE(MAX_STRLEN_LONG, [60], [Max length for a long]) 

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC



# todo, add tests
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT


