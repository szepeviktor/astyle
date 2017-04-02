#!/bin/bash
# run clang tidy on the astyle source

# use "clang-tidy-3.9 -checks=* -list-checks" to list list all available checks

srcdir=$HOME/Projects/AStyle/src
progdir=clang-tidy-3.9
# add or remove -fix-errors option to apply fixes to the source, include it in the quotes
options="-header-filter=.* "

# modernize-* are temporary.  Remove for c++11 update.
# cert-err34-c warns of using atoi errors - astyle_main checks the input length to avoid
# -cppcoreguidelines-pro-bounds-array-to-pointer-decay is a false positive on asserts
# cppcoreguidelines-pro-bounds-pointer-arithmetic, don't use pointer arithmetic in astyle_main
# cppcoreguidelines-pro-type-member-init gives constructor does not initialize warning
# cppcoreguidelines-pro-type-vararg don't use printf in astyle_main
# google-build-using-namespace gives warning for "using namespace"
# google-readability-casting replaces c-style casts with c++ casts
# google-readability-todo adds username to todo comments
# llvm-header-guard adds the filepath to the header guard name
# misc-misplaced-widening-cast is casting size_t to int instead of int to size_t
# readability-simplify-boolean-expr returns a conditional statement
# modernize-loop-convert, vs2010 does not recognize for-each loop
# modernize-use-default, vs2010 does not recognize default

checks=-checks=*,\
-cert-err34-c,\
-cppcoreguidelines-pro-bounds-array-to-pointer-decay,\
-cppcoreguidelines-pro-bounds-pointer-arithmetic,\
-cppcoreguidelines-pro-type-member-init,\
-cppcoreguidelines-pro-type-vararg,\
-google-build-using-namespace,\
-google-readability-braces-around-statements,\
-google-readability-casting,\
-google-readability-todo,\
-llvm-header-guard,\
-misc-misplaced-widening-cast,\
-readability-braces-around-statements,\
-readability-simplify-boolean-expr,\
-modernize-loop-convert,\
-modernize-use-auto,\
-modernize-use-default


echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       clang tidy                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir
if [ -f  "clang-*" ]; then
	rm "clang-*"
fi

cp  -v  /media/jimp/LEXAR1/USB/Projects/AStyle/src/*.h  ./

for filename in astyle_main.cpp
do
	echo
	echo  -e  $filename
	cp  -v  /media/jimp/LEXAR1/USB/Projects/AStyle/src/$filename  $filename
	$progdir  $checks  $options  $filename    --  > xclang-$filename.txt
done


echo
echo "* * * * * *  end of tidy  * * * * * *"
read -sn1 -p "Press Enter to end . . ."
