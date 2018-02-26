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
echo "*                 AStyle GCC Executable                 *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-gcc-exe
mkdir  --parents  as-gcc-exe
cd  as-gcc-exe
cmake  $opts   ../
make

# So
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                     AStyle GCC So                     *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-gcc-so
mkdir  --parents  as-gcc-so
cd  as-gcc-so
cmake  -DBUILD_SHARED_LIBS=1  $opts   ../
make

# Java
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                    AStyle GCC Java                    *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-gcc-java
mkdir  as-gcc-java
cd  as-gcc-java
cmake  -DBUILD_JAVA_LIBS=1  $opts   ../
make

# Static
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                   AStyle GCC Static                   *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
rm --recursive --force  as-gcc-a
mkdir  --parents  as-gcc-a
cd  as-gcc-a
cmake  -DBUILD_STATIC_LIBS=1  $opts   ../
make

copy=true
if [ "$copy" = "true" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*          Copy Files to AStyleDev for Testing          *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	cd ../
	cp --verbose --force  as-gcc-exe/astyle                ../AStyleDev/src-p/
	cp --verbose --force  as-gcc-so/libastyle.so.*         ../AStyleDev/src-o/
	cp --verbose --force  as-gcc-so/libastyle.so.?.?.?     ../AStyleDev/src-p/
	cp --verbose --force  as-gcc-so/libastyle.so.?.?.?     ../AStyleDev/src-s/
	cp --verbose --force  as-gcc-so/libastyle.so.?.?.?     ../AStyleDev/src-s2/
	cp --verbose --force  as-gcc-java/libastylej.so.?.?.?  ../AStyleDev/src-j/
fi


echo
echo "* * * * * *  end of cmake  * * * * * *"
read -sn1 -p "Press any key to end . . ."
echo
