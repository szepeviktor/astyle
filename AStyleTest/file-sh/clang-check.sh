#!/bin/bash

# run clang modernize on the astyle source

srcdir=$HOME/Projects/AStyle/src

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       clang check                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir

echo -e "\nASBeautifier.cpp"
clang-check-3.7  -analyze  ASBeautifier.cpp  --

echo -e "\nASEnhancer.cpp"
clang-check-3.7  -analyze  ASEnhancer.cpp  --

echo -e "\nASFormatter.cpp"
clang-check-3.7  -analyze  ASFormatter.cpp  --

echo -e "\nASLocalizer.cpp"
clang-check-3.7  -analyze  ASLocalizer.cpp  --

echo -e "\nASResource.cpp"
clang-check-3.7  -analyze  ASResource.cpp  --

echo
#~ read -sn1 -p "Press Enter to end . . ."
