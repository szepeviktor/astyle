#!/bin/bash
# run astyle the AStyleTest source

NORMAL="[0;39m"
RED="[1;31m"

bindir=$HOME/bin
projdir=$HOME/Projects

options=--options=$projdir/AStyleTest/file-sh/astyle-options.cfg

echo Formatting AStyleTest
echo $options
echo

if [ ! -x $bindir/astyle ]; then
	echo $RED"Executable not available!"
	read -sn1 -p $NORMAL"Press Enter to end . . .";
	echo; exit;
fi

# must quote paths with wildcards
$bindir/astyle  $options  "$projdir/AStyleTest/src/*.cpp"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/src/*.h"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/srccon/*.cpp"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/srccon/*.h"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/srci18n/*.cpp"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/srclib/*.cpp"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/srclib/*.h"
echo
$bindir/astyle  $options  "$projdir/AStyleTest/srcloc/*.cpp"
echo

echo
read -sn1 -p "Press Enter to end . . ."
