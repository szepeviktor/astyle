#!/bin/bash

# run astyle formatter on the astyle source

progdir=$HOME/Projects/AStyle/build/clang/bin/astyle
srcdir=$HOME/Projects/AStyle/src
style=-A14s2M60HUpSck3

# A14- style=google
# s2 - indent=spaces=2
# M60- max-instatement-indent=60
# H  - pad-header
# U  - unpad-paren
# p  - pad-oper
# S  - indent-switches
# c  - convert-tabs
# the following is optional (not used by clang-format)
# D  - pad-paren-in
# Google allows either k1 or k3 pointers (k3 inconsistently used by clang-format).
# k1 - align-pointer=type
# k3 - align-pointer=name
# Google alows either format of boolean operators (boolean expressions),
#        && and || are usually at the end of the line, but at the beginning is also allowed.

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      astyle format                      *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

if [ ! -x $progdir ]; then
	echo "executable not available - run astyle-build.sh!"
	#read -sn1 -p "Press Enter to end . . .";
	echo; exit;
fi

cd $srcdir

echo

echo ASBeautifier.cpp
$progdir  $style  ASBeautifier.cpp > astyle-out.txt
mv  ASBeautifier.cpp  astyle-asbeautifier.cpp
mv  ASBeautifier.cpp.orig  ASBeautifier.cpp

echo ASEnhancer.cpp
$progdir  $style  ASEnhancer.cpp > astyle-out.txt
mv  ASEnhancer.cpp  astyle-asenhancer.cpp
mv  ASEnhancer.cpp.orig  ASEnhancer.cpp

echo ASFormatter.cpp
$progdir  $style  ASFormatter.cpp > astyle-out.txt
mv  ASFormatter.cpp  astyle-asformatter.cpp
mv  ASFormatter.cpp.orig  ASFormatter.cpp

echo ASLocalizer.cpp
$progdir  $style  ASLocalizer.cpp > astyle-out.txt
mv  ASLocalizer.cpp  astyle-aslocalizer.cpp
mv  ASLocalizer.cpp.orig  ASLocalizer.cpp

echo ASResource.cpp
$progdir  $style  ASResource.cpp > astyle-out.txt
mv  ASResource.cpp  astyle-asresource.cpp
mv  ASResource.cpp.orig  ASResource.cpp

echo astyle_main.cpp
$progdir  $style  astyle_main.cpp > astyle-out.txt
mv  astyle_main.cpp  astyle-astyle_main.cpp
mv  astyle_main.cpp.orig  astyle_main.cpp

echo astyle.h
$progdir  $style  astyle.h > astyle-out.txt
mv  astyle.h  astyle-astyle.h
mv astyle.h.orig  astyle.h

echo astyle_main.h
$progdir  $style  astyle_main.h > astyle-out.txt
mv  astyle_main.h  astyle-astyle_main.h
mv astyle_main.h.orig  astyle_main.h

echo ASLocalizer.h
$progdir  $style  ASLocalizer.h > astyle-out.txt
mv  ASLocalizer.h  astyle-aslocalizer.h
mv ASLocalizer.h.orig  ASLocalizer.h

echo
#~ read -sn1 -p "Press Enter to end . . ."
