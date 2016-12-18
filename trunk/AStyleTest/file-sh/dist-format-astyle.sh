#!/bin/bash
# run astyle fon the AStyle source

NORMAL="[0;39m"
RED="[1;31m"

bindir=$HOME/bin
projdir=$HOME/Projects

options=--options=$projdir/AStyle/file/astyle.ini

echo Formatting AStyle
echo $options
echo

if [ ! -x $bindir/astyle ]; then
	echo $RED"Executable not available!"
	read -sn1 -p $NORMAL"Press Enter to end . . .";
	echo; exit;
fi

# must quote paths with wildcards
$bindir/astyle  $options   "$projdir/AStyle/src/*.cpp"
echo
$bindir/astyle  $options   "$projdir/AStyle/src/*.h"
echo

echo
read -sn1 -p "Press Enter to end . . ."
