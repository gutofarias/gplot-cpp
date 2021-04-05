#!/bin/bash

# Script for uninstalling dynamic libraries on computer.
# Files uninstalled from ~/.include and ~/.lib.
# To uninstall from different paths, change the variables below.

INCLUDE="${HOME}/.include"
LIB="${HOME}/.lib"

# $1: dynamic library name
# Example:
# ./uninstall.sh rk4

if [ -n "$1" ]
then
    
    if [ -f ${HOME}/.include/${1}.h ] && [ -f ${HOME}/.lib/lib${1}.dylib ]
    then
	rm -f ${HOME}/.include/${1}.h ${HOME}/.lib/lib${1}.dylib
	echo "Library '${1}' uninstalled!"
    elif
	[ -f ${HOME}/.include/${1}.h -a ! -f ${HOME}/.lib/lib${1}.dylib ]
    then
	rm -f ${HOME}/.include/${1}.h
	echo "Only ${1}.h was installed..."
	echo "Library '${1}' uninstalled!"
    elif
	[ ! -f ${HOME}/.include/${1}.h -a -f ${HOME}/.lib/lib${1}.dylib ]
    then
	rm -f ${HOME}/.lib/lib${1}.dylib
	echo "Only lib${1}.dylib was installed..."
	echo "Library '${1}' uninstalled!"
    else
	echo "Library '${1}' was not installed!"
    fi
    
    exit 0
    
fi

exit 1
