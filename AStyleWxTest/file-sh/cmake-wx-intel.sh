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
echo "*               AStyleWx Intel Executable               *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyleWx"
rm --recursive --force  aswx-intel-exe
mkdir  --parents  aswx-intel-exe
cd  aswx-intel-exe
CXX=icpc  cmake  $opts   ../
make

echo
echo "* * * * * *  end of cmake  * * * * * *"
# read -sn1 -p "Press any key to end . . ."
echo
