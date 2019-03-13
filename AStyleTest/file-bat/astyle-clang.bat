@echo off
REM Compare an astyle formatted source to a clang-formatted source.
REM Use VS Code or clang-format-astyle.bat to format a source file with clang-format.
REM Then use this batch file to format a source file with astyle.
REM Compare the files with a diff program.

set astyle=..\..\AStyle\build\vs2017\x64\debug\AStyled
:: set astyle=..\..\AStyle\build\vs2017\bin\AStyle

set options=..\..\AStyle\file
set filec=..\..\AStyle\test-data\*.cpp
set fileh=..\..\AStyle\test-data\*.h

REM Coding style: Visual Studio, LLVM, Google, Chromium, Mozilla, WebKit.
"%astyle%"  --options=%options%/visualstudio.ini -R  %filec% %fileh%


echo.
pause
