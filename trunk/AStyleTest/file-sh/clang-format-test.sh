#!/bin/bash

# run clang formatter on test source

# style options at http://clang.llvm.org/docs/ClangFormatStyleOptions.html
# file = _clang-format

style=-style=file

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      clang format                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $HOME

# copy clang format file and rename
cp -f -v  Projects/AStyle/file/clang-webkit.yaml  _clang-format

echo test10.m
clang-format-3.7  $style   test10.m  > clang-test10.m

echo test11.m
clang-format-3.7  $style   test11.m  > clang-test11.m

echo test12.m
clang-format-3.7  $style   test12.m  > clang-test12.m

echo test13.m
clang-format-3.7  $style   test13.m  > clang-test13.m

echo test14.m
clang-format-3.7  $style   test14.m  > clang-test14.m

echo test15.m
clang-format-3.7  $style   test15.m  > clang-test15.m

echo test16.m
clang-format-3.7  $style   test16.m  > clang-test16.m

echo test17.m
clang-format-3.7  $style   test17.m  > clang-test17.m

echo test18.m
clang-format-3.7  $style   test18.m  > clang-test18.m


echo
read -sn1 -p "Press Enter to end . . ."
