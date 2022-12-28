#!/bin/bash

# USE ONE OF THESE OPTIONS
opts=
# opts=-DCMAKE_VERBOSE_MAKEFILE=1
# opts="-DCMAKE_BUILD_TYPE=Debug  -DCMAKE_VERBOSE_MAKEFILE=1"
# opts=-DCMAKE_BUILD_TYPE="MinSizeRel"
# echo $opts

# Executable
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                AStyle Clang Executable                *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-clang
mkdir  --parents  as-clang
cd  as-clang
CXX=clang++  cmake  $opts  ../
make

# So
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                    AStyle Clang So                    *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-clang-so
mkdir  --parents  as-clang-so
cd  as-clang-so
CXX=clang++  cmake  -DBUILD_SHARED_LIBS=1  $opts  ../
make

# Java
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                   AStyle Clang Java                   *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-clang-java
mkdir  as-clang-java
cd  as-clang-java
CXX=clang++  cmake  -DBUILD_JAVA_LIBS=1  $opts  ../
make

# Static
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                  AStyle Clang Static                  *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-clang-a
mkdir  --parents  as-clang-a
cd  as-clang-a
CXX=clang++  cmake  -DBUILD_STATIC_LIBS=1  $opts  ../
make

copy=true
if [ "$copy" = "true" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                 Copy Files to AStyleDev for Testing                 *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	cd  "$HOME/Projects/AStyle"
	cp  -fpv --no-dereference  as-clang/astyle               ../AStyleDev/src-p/
	cp  -fpv --no-dereference  as-clang-so/libastyle.so*     ../AStyleDev/src-c/
	cp  -fpv --no-dereference  as-clang-so/libastyle.so*     ../AStyleDev/src-o/
	cp  -fpv --no-dereference  as-clang-so/libastyle.so*     ../AStyleDev/src-p/
	cp  -fpv --no-dereference  as-clang-so/libastyle.so*     ../AStyleDev/src-s/
	cp  -fpv --no-dereference  as-clang-so/libastyle.so*     ../AStyleDev/src-s2/
	cp  -fpv --no-dereference  as-clang-java/libastylej.so*  ../AStyleDev/src-j/
fi


echo
echo "* * * * * *  end of cmake  * * * * * *"
read -sn1 -p "Press any key to end . . ."
echo
