#!/bin/bash
# display the entry functions for astyle shared libraries in the codeblocks build files
# Exported symbols are indicated by a T

astyle=$HOME/Projects/AStyle/build
solibver=3.0.1

cd  $astyle

echo cb-clang
nm -D --defined-only cb-clang/bin/libastyle.so.$solibver   | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only cb-clang/bin/libastylej.so.$solibver  | grep ' T ' | head -20 | cut -c -70

echo
echo cb-clang debug
nm -D --defined-only cb-clang/bin/libastyled.so.$solibver  | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only cb-clang/bin/libastylejd.so.$solibver | grep ' T ' | head -20 | cut -c -70

echo
echo cb-gcc
nm -D --defined-only cb-gcc/bin/libastyle.so.$solibver      | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only cb-gcc/bin/libastylej.so.$solibver     | grep ' T ' | head -20 | cut -c -70

echo
echo cb-gcc debug
nm -D --defined-only cb-gcc/bin/libastyled.so.$solibver     | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only cb-gcc/bin/libastylejd.so.$solibver    | grep ' T ' | head -20 | cut -c -70

echo
echo cb-intel
nm -D --defined-only cb-intel/bin/libastyle.so.$solibver    | grep ' T ' | head -20 | cut -c -70
echo
echo cb-intel debug
nm -D --defined-only cb-intel/bin/libastyled.so.$solibver   | grep ' T ' | head -20 | cut -c -70


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
