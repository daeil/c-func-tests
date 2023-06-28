#!/bin/sh

# Create configure.ac
echo "AC_INIT([Quick-sort Test], 1.0)
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_CONFIG_FILES(Makefile)
AC_OUTPUT" > configure.ac


# Create Makefile.am
echo "bin_PROGRAMS = qsort_test
qsort_test_SOURCES = qsort_test.c" > Makefile.am



# aclocal

# autoconf

# automake --add-missing --foreign

# ./configure && make
