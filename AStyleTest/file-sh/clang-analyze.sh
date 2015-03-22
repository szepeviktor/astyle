#!/bin/bash

# run clang analyze on the astyle source

srcdir=$HOME/Projects/AStyle/src

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                  Clang Static Analyzer                  *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

# list of source files without the directory
src=`find $srcdir -name "*.cpp" | sed -e "s@$srcdir/@@"`
echo $src

# cannot use -fno-rtti because it reports errors
opts="-fno-exceptions -std=c++11 -I$srcdir"

for v in  $src
do
	echo
	echo $v
	clang++  --analyze $opts "$srcdir/$v"
done

#~ echo
#~ echo Removing .gch files
#~ rm  $srcdir/*.gch
#~ echo Removing .plist files
#~ rm  *.plist

echo
read -sn1 -p "Press Enter to end . . ."
