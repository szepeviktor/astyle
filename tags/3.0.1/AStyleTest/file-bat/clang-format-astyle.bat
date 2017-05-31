@echo off
REM Format astyle using _clang-format in the src directory

set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.9.2\LLVM\bin
set astyle=..\..\AStyle\build\vs2015\debug\AStyled
:: set astyle=..\..\AStyle\build\vs2015\bin\AStyle

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
echo Copying clang configurating file
copy ..\file\clang-chromium.yaml  _clang-format
echo.

echo "ASBeautifier.cpp"
"%progdir%\clang-format"  -style=file ASBeautifier.cpp  > clang-asbeautifier.cpp

REM ~ echo "ASEnhancer.cpp"
REM ~ "%progdir%\clang-format"  -style=file  ASEnhancer.cpp  > clang-asenhancer.cpp

REM ~ echo "ASFormatter.cpp"
REM ~ "%progdir%\clang-format"  -style=file  ASFormatter.cpp  > clang-asformatter.cpp

REM ~ echo "ASLocalizer.cpp"
REM ~ "%progdir%\clang-format"  -style=file  ASLocalizer.cpp  > clang-aslocalizer.cpp

REM ~ echo "ASResource.cpp"
REM ~ "%progdir%\clang-format"  -style=file  ASResource.cpp  > clang-asresource.cpp

REM ~ echo "astyle_main.cpp"
REM ~ "%progdir%\clang-format"  -style=file  astyle_main.cpp  > clang-astyle_main.cpp

REM ~ echo "astyle.h"
REM ~ "%progdir%\clang-format"  -style=file  astyle.h > clang-astyle.h

REM ~ echo "astyle_main.h"
REM ~ "%progdir%\clang-format"  -style=file  astyle_main.h > clang-astyle_main.h

REM ~ echo "ASLocalizer.h"
REM ~ "%progdir%\clang-format"  -style=file   ASLocalizer.h > clang-aslocalizer.h

echo.
pause
