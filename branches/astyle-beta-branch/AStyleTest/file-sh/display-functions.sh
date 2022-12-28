#!/bin/bash
# display the entry functions for astyle shared libraries in the codeblocks build files
# Exported symbols are indicated by a T

astyle=$HOME/Projects/AStyle/build
solibver=3.0.1

cd  $astyle

echo clang
nm -D --defined-only clang/bin/libastyle.so.$solibver   | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only clang/bin/libastylej.so.$solibver  | grep ' T ' | head -20 | cut -c -70

echo
echo clang debug
nm -D --defined-only clang/bin/libastyled.so.$solibver  | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only clang/bin/libastylejd.so.$solibver | grep ' T ' | head -20 | cut -c -70

echo
echo gcc
nm -D --defined-only gcc/bin/libastyle.so.$solibver      | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only gcc/bin/libastylej.so.$solibver     | grep ' T ' | head -20 | cut -c -70

echo
echo gcc debug
nm -D --defined-only gcc/bin/libastyled.so.$solibver     | grep ' T ' | head -20 | cut -c -70
echo
nm -D --defined-only gcc/bin/libastylejd.so.$solibver    | grep ' T ' | head -20 | cut -c -70

echo
echo intel
nm -D --defined-only intel/bin/libastyle.so.$solibver    | grep ' T ' | head -20 | cut -c -70
echo
echo intel debug
nm -D --defined-only intel/bin/libastyled.so.$solibver   | grep ' T ' | head -20 | cut -c -70


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
