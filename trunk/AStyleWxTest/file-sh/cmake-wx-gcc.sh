#!/bin/bash

# USE ONE OF THESE OPTIONS
opts=
# opts=-DCMAKE_VERBOSE_MAKEFILE=1
# opts="-DCMAKE_BUILD_TYPE=Debug  -DCMAKE_VERBOSE_MAKEFILE=1"
# opts=-DCMAKE_BUILD_TYPE="MinSizeRel"
# echo $opts

# Executable
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                AStyleWx GCC Executable                *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyleWx"
rm --recursive --force  aswx-gcc-exe
mkdir  --parents  aswx-gcc-exe
cd  aswx-gcc-exe
cmake  $opts  ../
make

echo
echo "* * * * * *  end of cmake  * * * * * *"
# read -sn1 -p "Press any key to end . . ."
echo
