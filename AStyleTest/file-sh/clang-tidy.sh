#!/bin/bash
# run clang tidy on the astyle source

# use "clang-tidy-5.0 -checks=* -list-checks" to list list all available checks

srcdir=$HOME/Projects/AStyle/src
progdir=clang-tidy-5.0
# add "-fix-errors" option to apply fixes to the source, include it in the quotes
options="-header-filter=.*"
# important compiler options
# do NOT use -I/usr/include/c++/5/tr1/, it will generate errors
compiler="-std=c++11"

# cert-err34-c warns of using atoi errors - astyle_main checks the input length to avoid
# cppcoreguidelines-pro-bounds-array-to-pointer-decay is a false positive on asserts
# cppcoreguidelines-pro-bounds-pointer-arithmetic, don't use pointer arithmetic in astyle_main
# cppcoreguidelines-pro-type-member-init gives constructor does not initialize warning
# cppcoreguidelines-pro-type-vararg don't use printf in astyle_main
# cppcoreguidelines-special-member-functions define copy constructor, assignment operator ...
# google-build-using-namespace gives warning for "using namespace"
# google-readability-braces-around-statements
# google-readability-casting replaces c-style casts with c++ casts
# google-readability-todo adds username to todo comments
# google-runtime-references
# hicpp-member-init adds braces to member variables for initialization
# hicpp-special-member-functions same as cppcoreguidelines-special-member-functions
# llvm-header-guard adds the filepath to the header guard name
# misc-misplaced-widening-cast is casting size_t to int instead of int to size_t
# misc-unused-parameters caused several false positives, is checked by compiler
# readability-braces-around-statements
# readability-simplify-boolean-expr returns a conditional statement
# modernize-use-auto recomments using auto for variable types

# to fix one option
#  -checks='-*,modernize-use-override' -fix

checks=-checks=*,\
-cert-err34-c,\
-cppcoreguidelines-pro-bounds-array-to-pointer-decay,\
-cppcoreguidelines-pro-bounds-pointer-arithmetic,\
-cppcoreguidelines-pro-type-member-init,\
-cppcoreguidelines-pro-type-vararg,\
-cppcoreguidelines-special-member-functions,\
-google-build-using-namespace,\
-google-readability-braces-around-statements,\
-google-readability-casting,\
-google-readability-todo,\
-google-runtime-references,\
-hicpp-member-init,\
-hicpp-special-member-functions,\
-llvm-header-guard,\
-misc-misplaced-widening-cast,\
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
cp  -v  /media/jimp/SANDISK/USB/Projects/AStyle/src/*.h  ./

for filename in *.cpp
do
	echo
	echo  -e  $filename
	cp  -v  /media/jimp/SANDISK/USB/Projects/AStyle/src/$filename  $filename
	$progdir  $checks  $options  $filename  --  $compiler  > xclang-$filename.txt
done


echo
echo "* * * * * *  end of tidy  * * * * * *"
read -sn1 -p "Press Enter to end . . ."
