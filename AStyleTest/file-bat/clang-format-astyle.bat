@echo off
REM Format astyle using _clang-format in the src directory

set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.20.1\LLVM\bin

set srcdir=..\..\AStyle\test-data

REM The directory contains the release number, so check that it is current.
if not exist "%progdir%" (
echo no directory "%progdir%"
pause
exit 1
)

cd %srcdir%

echo.
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
echo "*                      clang format                       *"
echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
"%progdir%\clang-format"  -version
echo.

REM copy clang format file and rename
REM style options are Chromium, Google, LLVM, Mozilla, WebKit
::echo Copying clang configurating file
::copy ..\file\clang-chromium.yaml  _clang-format
echo.

REM ~ REM echo "ASBeautifier.cpp"
REM ~ REM "%progdir%\clang-format"  -style=file ASBeautifier.cpp  > clang-asbeautifier.cpp

echo "ASEnhancer.cpp"
"%progdir%\clang-format"  -style=file  ASEnhancer.cpp  > clang-asenhancer.cpp

echo "ASFormatter.cpp"
"%progdir%\clang-format"  -style=file  ASFormatter.cpp  > clang-asformatter.cpp

echo "ASLocalizer.cpp"
"%progdir%\clang-format"  -style=file  ASLocalizer.cpp  > clang-aslocalizer.cpp

echo "ASResource.cpp"
"%progdir%\clang-format"  -style=file  ASResource.cpp  > clang-asresource.cpp

echo "astyle_main.cpp"
"%progdir%\clang-format"  -style=file  astyle_main.cpp  > clang-astyle_main.cpp

echo "astyle.h"
"%progdir%\clang-format"  -style=file  astyle.h > clang-astyle.h

echo "astyle_main.h"
"%progdir%\clang-format"  -style=file  astyle_main.h > clang-astyle_main.h

echo "ASLocalizer.h"
"%progdir%\clang-format"  -style=file   ASLocalizer.h > clang-aslocalizer.h

echo.
pause
