#!/bin/bash
# run clang tidy on the astyle source

# NOTE: use option -fix-errors to get the suggested fix
# NOTE: use "clang-tidy-3.7 -checks=* -list-checks  ASBeautifier.cpp --"
#       to list list all available checks
# NOTE: fix -google-readability-casting

srcdir=$HOME/Projects/AStyle/src

checks=-checks=*,\
-google-build-using-namespace,\
-google-readability-braces-around-statements,\
-google-readability-function,\
-google-readability-namespace-comments,\
-google-readability-todo,\
-llvm-header-guard,\
-llvm-namespace-comment,\
-readability-braces-around-statements,\
-readability-named-parameter,\
-clang-analyzer-security.insecureAPI.strcpy,\
-google-readability-casting

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       clang tidy                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir

echo -e "\nASBeautifier.cpp"
clang-tidy-3.7  $checks  ASBeautifier.cpp    --  > clang-asbeautifier.txt

echo -e "\nASEnhancer.cpp"
clang-tidy-3.7  $checks  ASEnhancer.cpp  --  > clang-asenhancer.txt

echo -e "\nASFormatter.cpp"
clang-tidy-3.7  $checks  ASFormatter.cpp  --  > clang-asformatter.txt

echo -e "\nASLocalizer.cpp"
clang-tidy-3.7  $checks  ASLocalizer.cpp  --  > clang-aslocalizer.txt

echo -e "\nASResource.cpp"
clang-tidy-3.7  $checks  ASResource.cpp  --  > clang-asresource.txt

echo -e "\nastyle_main.cpp"
clang-tidy-3.7  $checks  astyle_main.cpp  --  > clang-astyle_main.txt

echo
echo "* * * * * *  end of tidy  * * * * * *"
#~ read -sn1 -p "Press Enter to end . . ."
