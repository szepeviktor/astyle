#!/bin/bash
# run clang tidy on the astyle source

# use "clang-tidy-3.9 -checks=* -list-checks" to list list all available checks

srcdir=$HOME/Projects/AStyle/src
progdir=clang-tidy-3.9
# options  -fix or -fix-errors,  -header-filter=.*
options="-fix-errors  -header-filter=.*"

# modernize-* are temporary.  Remove for c++11 update.
# google-readability-casting replaces c-style casts with c++ casts
# cert-err34-c warns of using atoi errors - astyle checks the input length to avoid
checks=-checks=*,\
-cert-err34-c,\
-cppcoreguidelines-pro-bounds-array-to-pointer-decay,\
-cppcoreguidelines-pro-bounds-pointer-arithmetic,\
-cppcoreguidelines-pro-type-member-init,\
-cppcoreguidelines-pro-type-reinterpret-cast,\
-google-build-using-namespace,\
-google-default-arguments,\
-google-readability-braces-around-statements,\
-google-readability-function,\
-google-readability-namespace-comments,\
-google-readability-todo,\
-google-runtime-int,\
-google-runtime-references,\
-llvm-header-guard,\
-llvm-namespace-comment,\
-misc-misplaced-widening-cast,\
-readability-braces-around-statements,\
-readability-implicit-bool-cast,\
-readability-named-parameter,\
-readability-simplify-boolean-expr,\
-google-readability-casting,\
-modernize-use-auto,\
-modernize-loop-convert,\
-modernize-use-default,\
-modernize-use-nullptr


echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                       clang tidy                        *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir
if [ -f  "clang-*" ]; then
	rm "clang-*"
fi

for filename in *.cpp
do
	echo
	echo  -e  $filename
	$progdir  $checks  $options  $filename    --  > xclang-$filename.txt
done


echo
echo "* * * * * *  end of tidy  * * * * * *"
read -sn1 -p "Press Enter to end . . ."
