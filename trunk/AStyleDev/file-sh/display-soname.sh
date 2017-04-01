#!/bin/bash
# display the soname for astyle shared libraries in the src files

asdev=$HOME/Projects/AStyleDev/
sonamevar=3.0

cd  $asdev

echo src-c
objdump -p src-c/libastyle.so.$sonamevar  | grep SONAME
echo src-j
objdump -p src-j/libastylej.so.$sonamevar | grep SONAME
echo src-o
objdump -p src-o/libastyle.so.$sonamevar  | grep SONAME
echo src-p
objdump -p src-p/libastyle.so.$sonamevar  | grep SONAME
echo src-s
objdump -p src-s/libastyle.so.$sonamevar  | grep SONAME
echo src-s2
objdump -p src-s2/libastyle.so.$sonamevar  | grep SONAME

echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
