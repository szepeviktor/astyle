#!/bin/bash

# USE ONE OF THESE OPTIONS
opts=
# opts=-DCMAKE_VERBOSE_MAKEFILE=1
# opts="-DCMAKE_BUILD_TYPE=Debug  -DCMAKE_VERBOSE_MAKEFILE=1"
# opts=-DCMAKE_BUILD_TYPE="MinSizeRel"
# opts="-DWX=3.1  -DTK=gtk3"
# echo $opts

# Executable
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*               AStyleWx Clang Executable               *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyleWx"
rm --recursive --force  aswx-clang-exe
mkdir  --parents  aswx-clang-exe
cd  aswx-clang-exe
CXX=clang++  cmake  $opts   ../
make

echo
echo "* * * * * *  end of cmake  * * * * * *"
# read -sn1 -p "Press any key to end . . ."
echo
