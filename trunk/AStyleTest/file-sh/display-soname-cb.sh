#!/bin/bash
# display the soname for astyle shared libraries in the codeblocks build files

astyle=$HOME/Projects/AStyle/build
solibver=3.0.1

cd  $astyle

echo cb-clang
objdump -p cb-clang/bin/libastyle.so.$solibver  | grep SONAME
objdump -p cb-clang/bin/libastylej.so.$solibver | grep SONAME
echo cb-clang debug
objdump -p cb-clang/bin/libastyled.so.$solibver  | grep SONAME
objdump -p cb-clang/bin/libastylejd.so.$solibver | grep SONAME
echo cb-gcc
objdump -p cb-gcc/bin/libastyle.so.$solibver  | grep SONAME
objdump -p cb-gcc/bin/libastylej.so.$solibver | grep SONAME
echo cb-gcc debug
objdump -p cb-gcc/bin/libastyled.so.$solibver  | grep SONAME
objdump -p cb-gcc/bin/libastylejd.so.$solibver | grep SONAME
echo cb-intel
objdump -p cb-intel/bin/libastyle.so.$solibver  | grep SONAME
objdump -p cb-intel/bin/libastylej.so.$solibver | grep SONAME
echo cb-intel debug
objdump -p cb-intel/bin/libastyled.so.$solibver  | grep SONAME
objdump -p cb-intel/bin/libastylejd.so.$solibver | grep SONAME


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
