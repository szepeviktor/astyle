#!/bin/bash

# Executable
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                        AStyle GCC Executable                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-gcc-exe
cd  as-gcc-exe
cmake  ../
make

# So
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                            AStyle GCC So                            *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-gcc-so
cd  as-gcc-so
cmake  -DBUILD_SHARED_LIBS=1  ../
make

# Java
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                           AStyle GCC Java                           *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  as-gcc-java
cd  as-gcc-java
cmake  -DBUILD_JAVA_LIBS=1  ../
make

# Static
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                          AStyle GCC Static                          *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
cd  "$HOME/Projects/AStyle"
mkdir  --parents  as-gcc-a
cd  as-gcc-a
cmake  -DBUILD_STATIC_LIBS=1  ../
make

copy=true
if [ "$copy" = "true" ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                 Copy Files to AStyleDev for Testing                 *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
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
