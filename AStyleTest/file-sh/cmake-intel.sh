#!/bin/bash

# Executable
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       AStyle Intel Executable                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-intel-exe
cd  as-intel-exe
CXX=icpc  cmake  ../
make

# So
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                           AStyle Intel So                           *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-intel-so
cd  as-intel-so
CXX=icpc  cmake  -DBUILD_SHARED_LIBS=1  ../
make

# Java
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                          AStyle Intel Java                          *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  as-intel-java
cd  as-intel-java
CXX=icpc  cmake  -DBUILD_JAVA_LIBS=1  ../
make

# Static
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                         AStyle Intel Static                         *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-intel-a
cd  as-intel-a
CXX=icpc  cmake  -DBUILD_STATIC_LIBS=1  ../
make

copy=true
if [ "$copy" = "true" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                 Copy Files to AStyleDev for Testing                 *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	cd ../
	cp --verbose --force  as-intel-exe/astyle                ../AStyleDev/src-p/
	cp --verbose --force  as-intel-so/libastyle.so.*         ../AStyleDev/src-o/
	cp --verbose --force  as-intel-so/libastyle.so.?.?.?     ../AStyleDev/src-p/
	cp --verbose --force  as-intel-so/libastyle.so.?.?.?     ../AStyleDev/src-s/
	cp --verbose --force  as-intel-so/libastyle.so.?.?.?     ../AStyleDev/src-s2/
	cp --verbose --force  as-intel-java/libastylej.so.?.?.?  ../AStyleDev/src-j/
fi


echo
echo "* * * * * *  end of cmake  * * * * * *"
read -sn1 -p "Press any key to end . . ."
echo
