#!/bin/bash

# run clang modernize on the astyle source

srcdir=$HOME/Projects/AStyle/src

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                     clang modernize                     *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir

echo -e "\nASBeautifier.cpp"
cp -f -v  ASBeautifier.cpp  clang-asbeautifier.cpp
clang-modernize-3.7  -risk=risky  -summary  clang-asbeautifier.cpp

echo -e "\nASEnhancer.cpp"
cp -f -v  ASEnhancer.cpp  clang-asenhancer.cpp
clang-modernize-3.7  -risk=risky  -summary  clang-asenhancer.cpp

echo -e "\nASFormatter.cpp"
cp -f -v  ASFormatter.cpp  clang-asformatter.cpp
clang-modernize-3.7  -risk=risky  -summary  clang-asformatter.cpp

echo -e "\nASLocalizer.cpp"
cp -f -v  ASLocalizer.cpp  clang-aslocalizer.cpp
clang-modernize-3.7  -risk=risky  -summary  clang-aslocalizer.cpp

echo -e "\nASResource.cpp"
cp -f -v  ASResource.cpp  clang-asresource.cpp
clang-modernize-3.7  -risk=risky  -summary  clang-asresource.cpp

echo -e "\nastyle_main.cpp"
cp -f -v  astyle_main.cpp  clang-astyle_main.cpp
clang-modernize-3.7  -risk=risky  -summary  clang-astyle_main.cpp

# NOTE: header extension must be .hpp to use c++
echo -e "\nASLocalizer.h"
cp -f -v  ASLocalizer.h  clang-aslocalizer.hpp
clang-modernize-3.7  -risk=risky  -summary  clang-aslocalizer.hpp

# NOTE: header extension must be .hpp to use c++
echo -e "\nastyle.h"
cp -f -v  astyle.h  clang-astyle.hpp
clang-modernize-3.7  -risk=risky  -summary  clang-astyle.hpp

# NOTE: header extension must be .hpp to use c++
echo -e "\nastyle_main.h"
cp -f -v  astyle_main.h  clang-astyle_main.hpp
clang-modernize-3.7  -risk=risky  -summary  clang-astyle_main.hpp

echo
echo "* * * * *  end of modernize  * * * * *"
#~ read -sn1 -p "Press Enter to end . . ."
