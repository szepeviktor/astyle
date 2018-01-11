#!/bin/bash

# run clang analyze on the astylewx source

srcdir=$HOME/Projects/AStyleWx/src
dlgdir=$HOME/Projects/AStyleWx/dialog

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                  Clang Static Analyzer                  *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

# lists of source files without the directory
src=`find $srcdir -name "*.cpp" | sed -e "s@$srcdir/@@"`
dlg=`find $dlgdir -name "*.cpp" | sed -e "s@$dlgdir/@@"`
echo $src
echo $dlg

# cannot use -fno-rtti because it reports errors
opts="-fno-exceptions -std=c++11 -I$srcdir -I$dlgdir -I$srcdir/../image"

for v in  $src
do
	echo
	echo $v
	clang++  --analyze $opts `wx-config --version=3.0 --cflags` "$srcdir/$v"
done
unset v

for v in  $dlg
do
	echo
	echo $v
	clang++  --analyze $opts `wx-config --version=3.0 --cflags` "$dlgdir/$v"
done

#~ echo
#~ echo Removing .gch files
#~ rm  $srcdir/../file-sh/*.gch
#~ echo Removing .plist files
#~ rm  $srcdir/../file-sh/*.plist

echo
read -sn1 -p "Press Enter to end . . ."
