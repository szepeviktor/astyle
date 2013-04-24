#!/bin/bash

YELLOW="[1;33m"
echo -n $YELLOW

# Test that the astyle piping ability has been restored.
# ???????????????????????????? This works OK on Windows.
# This may fail if cin is piped to AStyle "cat txt.cpp | ./astyled".
# But is OK for redirection "./astyled < txt.cpp".

# Copy all files to the following directory, including astyle.
cd $HOME
# app.cpp is in CodeBlocks\src\src
filein=app.cpp
fileout=app.astyle.cpp

cat "$filein"  |  astyle -e  --suffix=none > "$fileout" 

echo
read -sn1 -p "Press Enter to end . . ."

