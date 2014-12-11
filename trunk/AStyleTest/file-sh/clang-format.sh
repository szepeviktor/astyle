#!/bin/bash

# run clang formatter on the astyle source

srcdir=$HOME/Projects/AStyle/src
style=-style=file            # uses .clang-format in $srcdir

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      clang format                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo

cd $srcdir

# copy clang-google.cfg and rename
cp -f -v  ../cfg/clang-google.cfg  .clang-format
echo

echo ASBeautifier.cpp
clang-format-3.5  $style  ASBeautifier.cpp  > clang-asbeautifier.cpp

echo ASEnhancer.cpp
clang-format-3.5  $style  ASEnhancer.cpp  > clang-asenhancer.cpp

echo ASFormatter.cpp
clang-format-3.5  $style  ASFormatter.cpp  > clang-asformatter.cpp

echo ASLocalizer.cpp
clang-format-3.5  $style  ASLocalizer.cpp  > clang-aslocalizer.cpp

echo ASResource.cpp
clang-format-3.5  $style  ASResource.cpp  > clang-asresource.cpp

echo astyle_main.cpp
clang-format-3.5  $style  astyle_main.cpp  > clang-astyle_main.cpp

echo astyle.h
clang-format-3.5  $style  astyle.h > clang-astyle.h

echo astyle_main.h
clang-format-3.5  $style  astyle_main.h > clang-astyle_main.h

echo ASLocalizer.h
clang-format-3.5  $style   ASLocalizer.h > clang-aslocalizer.h

echo
#~ read -sn1 -p "Press Enter to end . . ."
