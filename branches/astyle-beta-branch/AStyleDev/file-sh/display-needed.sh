#!/bin/bash
# display the NEEDED for astyle examples in the src files

asdev=$HOME/Projects/AStyleDev/

cd  $asdev

echo src-c
objdump -p src-c/Example  | grep NEEDED | grep libastyle
echo src-o
objdump -p src-o/Example  | grep NEEDED | grep libastyle

echo
if [ ! $1 ]; then
	read -sn1 -p "Press Enter to end "
	echo
fi
