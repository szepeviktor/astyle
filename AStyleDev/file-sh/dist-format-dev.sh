#!/bin/bash
# run astyle on the AStyleDev source

NORMAL="[0;39m"
RED="[1;31m"

bindir=$HOME/bin
projdir=$HOME/Projects

# override standard options with --style=horstmann  --indent=spaces
options=--options="$projdir/AStyleTest/file-sh/astyle-options.ini  -A9s"

echo Formatting AStyleDev
echo override standard options with --style=horstmann  --indent=spaces
echo $options
echo

if [ ! -x $bindir/astyle ]; then
	echo $RED"Executable not available!"
	read -sn1 -p $NORMAL"Press Enter to end . . .";
	echo; exit;
fi

# must quote paths with wildcards
$bindir/astyle  $options  "$projdir/AStyleDev/src-c/*.cpp"
echo
$bindir/astyle  $options  "$projdir/AStyleDev/src-j/*.java"
echo
$bindir/astyle  $options  "$projdir/AStyleDev/src-o/*.m"
echo
$bindir/astyle  $options  "$projdir/AStyleDev/src-s/*.cs"
echo
$bindir/astyle  $options  "$projdir/AStyleDev/src-s2/*.cs"
echo

echo
read -sn1 -p "Press Enter to end . . ."
