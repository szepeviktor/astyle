#!/bin/bash

# run clang formatter on test source

srcdir=$HOME
style=-style=file            # uses .clang-format in $srcdir

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      clang format                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo

cd $srcdir

# copy clang-google.cfg and rename
cp -f -v  $HOME/Projects/AStyle/cfg/clang-google.cfg  .clang-format
echo

echo test10.m
clang-format-3.5  $style   test10.m  > clang-test10.m

echo test11.m
clang-format-3.5  $style   test11.m  > clang-test11.m

echo test12.m
clang-format-3.5  $style   test12.m  > clang-test12.m

echo
read -sn1 -p "Press Enter to end . . ."
