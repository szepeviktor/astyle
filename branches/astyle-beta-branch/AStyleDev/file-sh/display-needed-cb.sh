#!/bin/bash
# display the NEEDED for astyle examples in the codeblocks build files

asdev=$HOME/Projects/AStyleDev/build

cd  $asdev

echo cb-clang
objdump -p cb-clang/bin/ExampleSo    | grep NEEDED | grep libastyle
objdump -p cb-clang/bin/ExampleOCSo  | grep NEEDED | grep libastyle
echo cb-clang debug
objdump -p cb-clang/bin/ExampleSod   | grep NEEDED | grep libastyle
objdump -p cb-clang/bin/ExampleOCSod | grep NEEDED | grep libastyle
echo cb-gcc
objdump -p cb-gcc/bin/ExampleSo      | grep NEEDED | grep libastyle
objdump -p cb-gcc/bin/ExampleOCSo    | grep NEEDED | grep libastyle
echo cb-gcc debug
objdump -p cb-gcc/bin/ExampleSod     | grep NEEDED | grep libastyle
objdump -p cb-gcc/bin/ExampleOCSod   | grep NEEDED | grep libastyle
echo cb-intel
objdump -p cb-intel/bin/ExampleSo    | grep NEEDED | grep libastyle
echo cb-intel debug
objdump -p cb-intel/bin/ExampleSod   | grep NEEDED | grep libastyle


echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
