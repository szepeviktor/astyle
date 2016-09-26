#!/bin/bash
# install packages for the  gworkspace test files
# this includes the objective c compiler and gnustep

# load library file
if [ -f libTYSP.sh ]; then source libTYSP.sh
else  source $HOME/bin/libTYSP.sh
fi

# check for running on Windows under MSYS
if [ $TERM = "cygwin" ]; then echo "This script is Linux only! "; exit; fi

#define $result variable here
result=:
unset result

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                        updating package list                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
promptYESNO  "Do you want to update the package list" "n"
if [ ! $YESNO ] || [ $YESNO = "y" ]; then
	sudo  apt  update
	result=$?; echo ; echo RESULT=$result
	if [ $result -ne 0 ] && [ $result -ne 100 ]; then  read -sn1 -p "Error updating package list! "; echo; fi
	unset result
fi
unset YESNO

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       installing objective c                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
sudo apt install gobjc
result=$? ; echo ; echo RESULT=$result
if [ ! $result ] || [ $result -ne 0 ]; then read -sn1 -p "Error installing packages! "; echo; fi
unset result

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                         installing gnustep                          *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
sudo apt install gnustep-core-devel
result=$? ; echo ; echo RESULT=$result
if [ ! $result ] || [ $result -ne 0 ]; then read -sn1 -p "Error installing packages! "; echo; fi
unset result

echo
read -sn1 -p "Press Enter to end . . ."
