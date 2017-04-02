#!/bin/bash
# Display the exported symbols from the makefile so compiles.

NORMAL="[0;39m"
YELLOW="[1;33m"

# directory to display
# ASTYLE
#makedir=~/Projects/AStyle/build/cb-clang/bin
#makedir=~/Projects/AStyle/build/cb-gcc/bin
#makedir=~/Projects/AStyle/build/cb-intel/bin
#makedir=~/Projects/AStyle/build/clang/bin
#makedir=~/Projects/AStyle/build/gcc/bin
#makedir=~/Projects/AStyle/build/intel/bin
#ASTYLEDEV
#makedir=~/Projects/AStyleDev/build/cb-clang/bin
#makedir=~/Projects/AStyleDev/build/cb-gcc/bin
makedir=~/Projects/AStyleDev/build/cb-intel/bin


cd $makedir

echo; echo  $YELLOW$makedir

echo; echo  $YELLOW"Release libastyle.so"
echo -n $NORMAL
nm --dynamic --demangle  libastyle.so |  grep ' T '

echo; echo  $YELLOW"Debug libastyled.so"
echo -n $NORMAL
nm --dynamic --demangle libastyled.so  |  grep ' T '

echo;  echo $YELLOW"Release Java libastylej.so"
echo -n $NORMAL
nm --dynamic --demangle  libastylej.so  |  grep ' T '

echo; echo  $YELLOW"Debug Java libastylejd.so"
echo -n $NORMAL
nm --dynamic --demangle  libastylejd.so  |  grep ' T '

echo
echo "* * * * *  end of symbols  * * * * *"
read -sn1 -p "Press any key to end . . ."
echo; echo
