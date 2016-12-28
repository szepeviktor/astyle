#!/bin/bash
# run astyle on the AStyleWxTest source

NORMAL="[0;39m"
RED="[1;31m"

bindir=$HOME/bin
projdir=$HOME/Projects

options=--options=$projdir/AStyle/file/astyle.ini

echo Formatting AStyleWxTest
echo $options
echo

if [ ! -x $bindir/astyle ]; then
	echo $RED"Executable not available!"
	read -sn1 -p $NORMAL"Press Enter to end . . .";
	echo; exit;
fi

# must quote paths with wildcards
$bindir/astyle  $options   "$projdir/AStyleWxTest/src/*.cpp"
echo
$bindir/astyle  $options   "$projdir/AStyleWxTest/src/*.h"
echo

echo
read -sn1 -p "Press Enter to end . . ."
