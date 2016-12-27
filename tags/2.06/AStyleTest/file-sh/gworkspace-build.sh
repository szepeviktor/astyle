#!/bin/bash
# build  gworkspace test files

# load library file
if [ -f libTYSP.sh ]; then source libTYSP.sh
else  source $HOME/bin/libTYSP.sh
fi

projdir=$HOME/Projects/TestData/GWorkspace

#define variable here
result=:
unset result

cd $projdir
if [ ! -d GWorkspace ]; then
	echo "GWorkspace not installed!"
	read -sn1 -p "Press Enter to end . . ."; echo; exit;
fi

# check for "source  /usr/share/GNUstep/Makefiles/GNUstep.sh" in profile
if [ -z $GNUSTEP_MAKEFILES ]; then
	echo "GNUstep.sh not sourced in profile!"
	read -sn1 -p "Press Enter to end . . ."; echo; exit;
fi

# do this if not a makefile or if it is requested
askconfig=yes
if [ ! -f GNUmakefile ] || [ $askconfig == yes ]; then
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                          running configure                          *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	if [ ! -f GNUmakefile ]; then
		YESNO="y"
	else
		promptYESNO  "Do you want to rebuild the GNUmakefile?" "n"
	fi

	if [ ! $YESNO ] || [ $YESNO = "y" ]; then
        sh configure
    fi

	result=$?; echo ; echo RESULT=$result
	if [ $result -ne 0 ] && [ $result -ne 100 ]; then  read -sn1 -p "Error running config! "; exit; fi
	unset result
	unset YESNO
fi

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                        compiling gworkspace                         *"
echo "* * * ** * * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *"
# Most common options for make:
#     messages=yes (prints verbosely all commands being executed)
#     debug=no (turns off generation of debug symbols)
#     strip=yes (strips executables and objects before installing)
#     shared=no (builds static executable and objects)
TIMEFORMAT=$'\nreal\t%0lR'
time  make

result=$?; echo ; echo RESULT=$result
if [ $result -ne 0 ] && [ $result -ne 100 ]; then  read -sn1 -p "Error running make! "; echo; exit; fi
unset result

echo
echo "The executable is in .../Gworkspace/Gworkspace/GWorkspace.app."
echo "To run the executable an install must be done thru the console."
# check for running on Windows under MSYS
if [ $TERM = "cygwin" ]; then
	echo "The installed executable will be in"
	echo "    .../GNUstep/GNUstep/System/Applications/GWorkspace.app."
	echo "To uninstall kill the processes ddbd.exe and fswatcher.exe."
else
	echo "Run a console program in root."
	echo "Enter 'source /usr/share/GNUstep/Makefiles/GNUstep.sh'."
	echo "Then enter 'make install'."
	echo "The installed executable will be in /usr/bin."
	echo "The uninstall must also be sourced and run in root."
fi

echo
read -sn1 -p "Press Enter to end . . ."
