#!/bin/bash
# display the soname for astyle shared libraries in the codeblocks build files

asdev=$HOME/Projects/AStyleDev/build
sonamevar=3.0

cd  $asdev

echo cb-clang
objdump -p cb-clang/bin/libastyle.so.$sonamevar  | grep SONAME
objdump -p cb-clang/bin/libastylej.so.$sonamevar | grep SONAME
echo cb-clang debug
objdump -p cb-clang/bin/libastyled.so.$sonamevar  | grep SONAME
objdump -p cb-clang/bin/libastylejd.so.$sonamevar | grep SONAME
echo cb-gcc
objdump -p cb-gcc/bin/libastyle.so.$sonamevar  | grep SONAME
objdump -p cb-gcc/bin/libastylej.so.$sonamevar | grep SONAME
echo cb-gcc debug
objdump -p cb-gcc/bin/libastyled.so.$sonamevar  | grep SONAME
objdump -p cb-gcc/bin/libastylejd.so.$sonamevar | grep SONAME
echo cb-intel
objdump -p cb-intel/bin/libastyle.so.$sonamevar  | grep SONAME
objdump -p cb-intel/bin/libastylej.so.$sonamevar | grep SONAME
echo cb-intel debug
objdump -p cb-intel/bin/libastyled.so.$sonamevar  | grep SONAME
objdump -p cb-intel/bin/libastylejd.so.$sonamevar | grep SONAME


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
