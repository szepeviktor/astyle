@echo off
REM Generate clang-format yaml configuration files

set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.9.2\LLVM\bin
set options=-dump-config -style=Google

if not exist "%progdir%" (
echo no directory "%progdir%"
pause
exit 1
)

"%progdir%\clang-format"  -version
echo Generating clang-format configuration file

REM change the -style option to Chromium, Google, LLVM, Mozilla, WebKit
"%progdir%\clang-format"  -dump-config -style=google  > clang-google.yaml

pause
