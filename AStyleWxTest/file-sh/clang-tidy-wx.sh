#!/bin/bash
# run clang tidy on the astylewx source

# use "clang-tidy-3.9 -checks=* -list-checks" to list list all available checks

srcdir=$HOME/Projects/AStyleWx/src
progdir=clang-tidy-3.9
# options  -fix or -fix-errors,  -header-filter=.*
options="-header-filter=.*"

# modernize-* are temporary.  Remove for c++11 update.
# google-readability-casting replaces c-style casts with c++ casts
# cert-err34-c warns of using atoi errors - astyle checks the input length to avoid
# cppcoreguidelines-pro-type-member-init is a false positive which may be fixed in the future
#     and if used with -fix will cause compile errors
# misc-unused-parameters is a false positive which may be fixed in the future
#     and if used with -fix will cause compile errors
# llvm-include-order is a false positive which may be fixed in the future
checks=-checks=*,\
-cppcoreguidelines-pro-type-member-init,\
-google-global-names-in-headers,\
-google-readability-braces-around-statements,\
-google-readability-todo,\
-google-runtime-int,\
-google-runtime-references,\
-llvm-header-guard,\
-llvm-include-order,\
-misc-unused-parameters,\
-readability-braces-around-statements,\
-readability-named-parameter,\
-readability-simplify-boolean-expr,\
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
