#!/bin/bash

YELLOW="[1;33m"
echo -n $YELLOW

# Test that the astyle piping ability has been restored.
# This may fail if cin is piped to AStyle "cat txt.cpp | ./astyled".
# But is OK for redirection "./astyled < txt.cpp".
#
# This does NOT work on Linux with the -e (break else-ifs) option.
# It will work without it because cin.tellg() is NOT used.
# This may fail if cin is piped to AStyle "cat txt.cpp | ./astyled".
# But is OK for redirection "./astyled < txt.cpp".

# Copy all files to the following directory
cd $HOME
# app.cpp is in CodeBlocks\src\src
progdir=$HOME/Projects/AStyle/build/cb-gcc/bin
filein=ASFormatter.cpp
pipeout=ASFormatter.cpp.pipe
redirout=ASFormatter.cpp.redir

echo deleting output $pipeout
rm  -f  "$pipeout"

echo pipe test
cat "$filein"  |  $progdir/astyle  -A1txnSxWwM60pHk1O  --suffix=none > "$pipeout"

echo redirection test
$progdir/astyle  -A1txnSxWwM60pHk1O  --suffix=none  <  "$filein"  >  "$redirout"

echo
read -sn1 -p "Press Enter to end . . ."

