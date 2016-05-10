#!/bin/bash

# run clang formatter on the astyle source

srcdir=$HOME/Projects/AStyle/src
# NOTE: use option -export-fixes=clang-asbeautifier.yaml to get the suggested fix
# NOTE: fix -google-readability-casting
checks=-checks=*,\
-google-build-using-namespace,\
-google-readability-braces-around-statements,\
-google-readability-namespace-comments,\
-google-readability-todo,\
-llvm-header-guard,\
-llvm-namespace-comment,\
-readability-braces-around-statements,\
-clang-analyzer-security.insecureAPI.strcpy,\
-google-readability-casting

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       clang tidy                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo $checks

cd $srcdir

echo -e "\nASBeautifier.cpp"
clang-tidy-3.7  $checks  -header-filter='.*'  ASBeautifier.cpp  --  > clang-asbeautifiertxt

echo -e "\nASEnhancer.cpp"
clang-tidy-3.7  $checks  -header-filter='.*'  ASEnhancer.cpp  --  > clang-asenhancer.txt

echo -e "\nASFormatter.cpp"
clang-tidy-3.7  $checks  -header-filter='.*'  ASFormatter.cpp  --  > clang-asformatter.txt

echo -e "\nASLocalizer.cpp"
clang-tidy-3.7  $checks  -header-filter='.*'  ASLocalizer.cpp  --  > clang-aslocalizer.txt

echo -e "\nASResource.cpp"
clang-tidy-3.7  $checks  -header-filter='.*'  ASResource.cpp  --  > clang-asresource.txt

echo -e "\nastyle_main.cpp"
clang-tidy-3.7  $checks  -header-filter='.*'  astyle_main.cpp  --  > clang-astyle_main.txt

echo
#~ read -sn1 -p "Press Enter to end . . ."
