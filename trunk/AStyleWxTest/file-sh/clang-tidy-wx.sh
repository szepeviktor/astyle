#!/bin/bash
# run clang tidy on the astylewx source

# use "clang-tidy-3.9 -checks=* -list-checks" to list list all available checks

srcdir=$HOME/Projects/AStyleWx/src
progdir=clang-tidy-3.9
# options  -fix or -fix-errors,  -header-filter=.*
options="-header-filter=.*"

# modernize-* are temporary.  Remove for c++11 update.
# cppcoreguidelines-pro-type-member-init gives constructor does not initialize warning
# cppcoreguidelines-pro-type-vararg don't use printf in astyle_main
# google-global-names-in-headers, don't like the restriction (std::vector)
# google-build-using-namespace gives warning for "using namespace"
# google-readability-casting replaces c-style casts with c++ casts
# google-readability-todo adds username to todo comments
# google-runtime-int values are determined by wxWidgets
# google-runtime-references 'const' is determined by wxWidgets, cannot fix
# llvm-header-guard adds the filepath to the header guard name
# misc-misplaced-widening-cast is casting size_t to int instead of int to size_t
# misc-unused-parameters, false positive in constructors
# readability-simplify-boolean-expr returns a conditional statement
# modernize-loop-convert, vs2010 does not recognize for-each loop
# modernize-use-default, vs2010 does not recognize default

checks=-checks=*,\
-cppcoreguidelines-pro-type-member-init,\
-google-global-names-in-headers,\
-google-readability-braces-around-statements,\
-google-readability-todo,\
-google-runtime-int,\
-google-runtime-references,\
-llvm-header-guard,\
-misc-unused-parameters,\
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

for filename in *.cpp
do
	echo
	echo  -e  $filename
	$progdir  $checks  $options  $filename    --  > xclang-$filename.txt
done


echo
echo "* * * * * *  end of tidy  * * * * * *"
read -sn1 -p "Press Enter to end . . ."
