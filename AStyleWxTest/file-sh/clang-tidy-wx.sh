#!/bin/bash
# run clang tidy on the astylewx source

# use "clang-tidy-5.0 -checks=* -list-checks" to list list all available checks

srcdir=$HOME/Projects/AStyleWx/src
progdir=clang-tidy-5.0
# add "-fix-errors" option to apply fixes to the source, include it in the quotes
options="-header-filter=.* -fix-errors"
# important compiler options
# do NOT use -I/usr/include/c++/5/tr1/, it will generate errors
compiler="-std=c++11"

# cppcoreguidelines-pro-type-member-init gives constructor does not initialize warning
# cppcoreguidelines-pro-type-vararg don't use printf in astyle_main
# google-global-names-in-headers, don't like the restriction (std::vector)
# google-build-using-namespace gives warning for "using namespace"
# google-readability-braces-around-statements
# google-readability-casting replaces c-style casts with c++ casts
# google-readability-todo adds username to todo comments
# google-runtime-int values are determined by wxWidgets
# google-runtime-references 'const' is determined by wxWidgets, cannot fix
# hicpp-member-init adds braces to member variables for initialization
# llvm-header-guard adds the filepath to the header guard name
# misc-misplaced-widening-cast is casting size_t to int instead of int to size_t
# misc-unused-parameters caused several false positives, is checked by compiler
# readability-braces-around-statements
# readability-simplify-boolean-expr returns a conditional statement
# modernize-use-auto recomments using auto for variable types

checks=-checks=*,\
-cppcoreguidelines-pro-type-member-init,\
-google-global-names-in-headers,\
-google-readability-braces-around-statements,\
-google-readability-todo,\
-google-runtime-int,\
-google-runtime-references,\
-hicpp-member-init,\
-llvm-header-guard,\
-misc-unused-parameters,\
-readability-braces-around-statements,\
-readability-simplify-boolean-expr,\
-modernize-use-auto


echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       clang tidy                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir
if [ -f  "clang-*" ]; then
	rm "clang-*"
fi

echo copy headers to src
cp  -v  /media/jimp/SANDISK/USB/Projects/AStyleWx/src/*.h  ./

for filename in *.cpp
do
	echo
	echo  -e  $filename
	cp  -v  /media/jimp/SANDISK/USB/Projects/AStyleWx/src/$filename  $filename
	$progdir  $checks  $options  $filename  --  $compiler  > xclang-$filename.txt
done


echo
echo "* * * * * *  end of tidy  * * * * * *"
read -sn1 -p "Press Enter to end . . ."
