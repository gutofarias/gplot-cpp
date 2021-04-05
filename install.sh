#!/bin/bash

# Script for installing dynamic libraries on computer.
# Files installed to ~/.include and ~/.lib.
# To use different install paths, change the variables below.

INCLUDE="${HOME}/.include"
LIB="${HOME}/.lib"

# $1: dynamic library name
# Example:
# ./install.sh rk4

if [ -n "$1" ]
then
    mkdir -p $INCLUDE
    mkdir -p $LIB
    cp -f ${1}.h $INCLUDE
    cp -f ./dylib/lib${1}.dylib $LIB
    install_name_tool -id ${LIB}/lib${1}.dylib ${LIB}/lib${1}.dylib
    echo "Library '${1}' installed!"
    exit 0
fi

exit 1


# Note that the LC_ID_DYLIB of the dynamic library was changed so it would
# point to the same location as the newly installed .dylib file.
