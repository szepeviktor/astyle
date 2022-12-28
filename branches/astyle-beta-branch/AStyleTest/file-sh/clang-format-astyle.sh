#!/bin/bash

# run clang formatter on the astyle source

# style options at http://clang.llvm.org/docs/ClangFormatStyleOptions.html
# file = _clang-format

srcdir=$HOME/Projects/AStyle/src
style=-style=file            # uses .clang-format in $srcdir

echo
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      clang format                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"

cd $srcdir

# copy clang format file and rename
cp -f -v  $HOME/Projects/AStyle/file/clang-webkit.yaml  _clang-format

echo -e "ASBeautifier.cpp"
clang-format-3.7  $style  ASBeautifier.cpp  > clang-asbeautifier.cpp

echo -e "ASEnhancer.cpp"
clang-format-3.7  $style  ASEnhancer.cpp  > clang-asenhancer.cpp

echo -e "ASFormatter.cpp"
clang-format-3.7  $style  ASFormatter.cpp  > clang-asformatter.cpp

echo -e "ASLocalizer.cpp"
clang-format-3.7  $style  ASLocalizer.cpp  > clang-aslocalizer.cpp

echo -e "ASResource.cpp"
clang-format-3.7  $style  ASResource.cpp  > clang-asresource.cpp

echo -e "astyle_main.cpp"
clang-format-3.7  $style  astyle_main.cpp  > clang-astyle_main.cpp

echo -e "astyle.h"
clang-format-3.7  $style  astyle.h > clang-astyle.h

echo -e "astyle_main.h"
clang-format-3.7  $style  astyle_main.h > clang-astyle_main.h

echo -e "ASLocalizer.h"
clang-format-3.7  $style   ASLocalizer.h > clang-aslocalizer.h

echo
#~ read -sn1 -p "Press Enter to end . . ."
