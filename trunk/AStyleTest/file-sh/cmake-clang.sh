#!/bin/bash

# Executable
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       AStyle Clang Executable                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-clang-exe
cd  as-clang-exe
CXX=clang++  cmake  ../
make

# So
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                           AStyle Clang So                           *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-clang-so
cd  as-clang-so
CXX=clang++  cmake  -DBUILD_SHARED_LIBS=1  ../
make

# Java
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                          AStyle Clang Java                          *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  as-clang-java
cd  as-clang-java
CXX=clang++  cmake  -DBUILD_JAVA_LIBS=1  ../
make

# Static
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                         AStyle Clang Static                         *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-clang-a
cd  as-clang-a
CXX=clang++  cmake  -DBUILD_STATIC_LIBS=1  ../
make

copy=true
if [ "$copy" = "true" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                 Copy Files to AStyleDev for Testing                 *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	cd ../
	cp --verbose --force  as-clang-exe/astyle                ../AStyleDev/src-p/
	cp --verbose --force  as-clang-so/libastyle.so.*         ../AStyleDev/src-o/
	cp --verbose --force  as-clang-so/libastyle.so.?.?.?     ../AStyleDev/src-p/
	cp --verbose --force  as-clang-so/libastyle.so.?.?.?     ../AStyleDev/src-s/
	cp --verbose --force  as-clang-so/libastyle.so.?.?.?     ../AStyleDev/src-s2/
	cp --verbose --force  as-clang-java/libastylej.so.?.?.?  ../AStyleDev/src-j/
fi


echo
echo "* * * * * *  end of cmake  * * * * * *"
read -sn1 -p "Press any key to end . . ."
echo
