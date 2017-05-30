#!/bin/bash
# display the soname for astyle shared libraries in the astyle build files

astyle=$HOME/Projects/AStyle/build
solibver=3.0.1

cd  $astyle

echo clang
objdump -p clang/bin/libastyle.so.$solibver  | grep SONAME
objdump -p clang/bin/libastylej.so.$solibver | grep SONAME
echo clang debug
objdump -p clang/bin/libastyled.so.$solibver  | grep SONAME
objdump -p clang/bin/libastylejd.so.$solibver | grep SONAME
echo gcc
objdump -p gcc/bin/libastyle.so.$solibver  | grep SONAME
objdump -p gcc/bin/libastylej.so.$solibver | grep SONAME
echo gcc debug
objdump -p gcc/bin/libastyled.so.$solibver  | grep SONAME
objdump -p gcc/bin/libastylejd.so.$solibver | grep SONAME
echo intel
objdump -p intel/bin/libastyle.so.$solibver  | grep SONAME
objdump -p intel/bin/libastylej.so.$solibver | grep SONAME
echo intel debug
objdump -p intel/bin/libastyled.so.$solibver  | grep SONAME
objdump -p intel/bin/libastylejd.so.$solibver | grep SONAME

echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
