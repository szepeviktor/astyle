#!/bin/bash
# display the NEEDED for astyle examples in the codeblocks build files

astylewx=$HOME/Projects/AStyleWx/build

cd  $astylewx

echo cb-clang
objdump -p cb-clang/wx3.0So/bin/astylewxso   | grep NEEDED | grep libastyle
objdump -p cb-clang/wx3.0So/bin/astylewxsod  | grep NEEDED | grep libastyle
echo cb-gcc
objdump -p cb-gcc/wx3.0So/bin/astylewxso     | grep NEEDED | grep libastyle
objdump -p cb-gcc/wx3.0So/bin/astylewxsod    | grep NEEDED | grep libastyle
echo cb-intel
objdump -p cb-intel/wx3.0So//bin/astylewxso   | grep NEEDED | grep libastyle
objdump -p cb-intel/wx3.0So//bin/astylewxsod  | grep NEEDED | grep libastyle


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
