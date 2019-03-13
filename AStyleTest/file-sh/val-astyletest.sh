#!/bin/bash
# Run Valgrind Memcheck on AStyleTest
# CodeBlocks command line arguments are at the following link
# http://wiki.codeblocks.org/index.php/Code::Blocks_command_line_arguments

# ANSI COLORS
NORMAL="[0;39m"
GREEN="[1;32m" # bold
RED="[1;31m"

#define $result variable here
result=:
unset result

projdir=$HOME/Projects

echo -n $GREEN
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                 Build GCC AStyleTest                  *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo -n $NORMAL
if [ ! -f $projdir/AStyleTest/build/cb-gcc/bin/libgtestd.a ]; then
	gmpath="$projdir/AStyleTest/build/cb-gcc/Gcc GTest A.cbp"
	codeblocks --build --target=Debug "$gmpath"
	result=$? ; echo RESULT=$result
	if [ ! $result ] || [ $result -ne 0 ]; then
		read -sn1 -p $RED"Error compiling GTest A! "$NORMAL
		echo
		exit 1
	fi
	unset result
fi
# always compile in case a file has changed
aspath="$projdir/AStyleTest/build/cb-gcc/Gcc AStyleTest.cbp"
codeblocks --build --target=Debug "$aspath"
result=$? ; echo RESULT=$result
if [ ! $result ] || [ $result -ne 0 ]; then
	read -sn1 -p $RED"Error compiling AStyleTest! "$NORMAL
	echo
	exit 1
fi
unset result

echo -n $GREEN
echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                  Valgrind AStyleTest                  *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo -n $NORMAL
atpath="$projdir/AStyleTest/build/cb-gcc/bin/AStyleTestd"

valgrind --leak-check=yes  $atpath --terse_output

# valgrind  --leak-check=yes  --track-origins=yes  --show-reachable=yes \
#   --gen-suppressions=all \
#   $atpath --xxxterse_output

echo
read -sn1 -p "Press Enter to end . . ."
echo
