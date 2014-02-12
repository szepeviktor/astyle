#!/bin/bash

# run clang analyze on the astyle source

srcdir=$HOME/Projects/AStyle/src

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      clang analyze                      *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

echo
echo astyle.h
clang++ "$srcdir/astyle.h" --analyze
echo
echo astyle_main.h
clang++ "$srcdir/astyle_main.h" --analyze
echo
echo ASLocalizer.h
clang++ "$srcdir/ASLocalizer.h" --analyze
echo
echo ASBeautifier
clang++ "$srcdir/ASBeautifier.cpp" --analyze
echo
echo ASEnhancer
clang++ "$srcdir/ASEnhancer.cpp" --analyze
echo
echo ASFormatter
clang++ "$srcdir/ASFormatter.cpp" --analyze
echo
echo ASLocalizer
clang++ "$srcdir/ASLocalizer.cpp" --analyze
echo
echo ASResource
clang++ "$srcdir/ASResource.cpp" --analyze
echo
echo astyle_main
clang++ "$srcdir/astyle_main.cpp" --analyze

echo
echo Removing .gch files
rm  $srcdir/*.gch
echo Removing .plist files
rm  *.plist

echo
read -sn1 -p "Press Enter to end . . ."
