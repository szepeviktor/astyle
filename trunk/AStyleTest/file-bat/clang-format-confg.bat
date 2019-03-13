@echo off
REM Generate clang-format yaml configuration files

set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.20.1\LLVM\bin

if not exist "%progdir%" (
echo no directory "%progdir%"
pause
exit 1
)

"%progdir%\clang-format"  -version
echo Generating clang-format configuration file

REM change the -style option to Chromium, Google, LLVM, Mozilla, WebKit
"%progdir%\clang-format"  -dump-config -style=webkit  > clang-webkit.yaml

pause
