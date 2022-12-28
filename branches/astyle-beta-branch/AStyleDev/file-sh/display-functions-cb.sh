#!/bin/bash
# display the entry functions for astyle shared libraries in the codeblocks build files
# Exported sumbols are indicated by a T

asdev=$HOME/Projects/AStyleDev/build
sonamevar=3.0

cd  $asdev

echo cb-clang
nm -D --defined-only cb-clang/bin/libastyle.so.$sonamevar   | grep ' T '
echo
nm -D --defined-only cb-clang/bin/libastylej.so.$sonamevar  | grep ' T '

echo
echo cb-clang debug
nm -D --defined-only cb-clang/bin/libastyled.so.$sonamevar  | grep ' T '
echo
nm -D --defined-only cb-clang/bin/libastylejd.so.$sonamevar | grep ' T '

echo
echo cb-gcc
nm -D --defined-only cb-gcc/bin/libastyle.so.$sonamevar      | grep ' T '
echo
nm -D --defined-only cb-gcc/bin/libastylej.so.$sonamevar     | grep ' T '

echo
echo cb-gcc debug
nm -D --defined-only cb-gcc/bin/libastyled.so.$sonamevar     | grep ' T '
echo
nm -D --defined-only cb-gcc/bin/libastylejd.so.$sonamevar    | grep ' T '

echo
echo cb-intel
nm -D --defined-only cb-intel/bin/libastyle.so.$sonamevar    | grep ' T '
echo
echo cb-intel debug
nm -D --defined-only cb-intel/bin/libastyled.so.$sonamevar   | grep ' T '


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
