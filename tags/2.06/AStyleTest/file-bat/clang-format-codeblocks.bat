@REM Format CodeBlocks using clang-format.
@REM Then format CodeBlocks using AStyle.
@REM Then the two formats can be compared.
@echo off

REM style options are Chromium, Google, LLVM, Mozilla, WebKit
set styleopt=google
set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.9.2\LLVM\bin
set compdir=C:\Program Files (x86)\WinMerge
set testdir=%USERPROFILE%\Projects\TestData\CodeBlocks
set astyle=%USERPROFILE%\Projects\AStyle\build\vs2015\debug\AStyled.exe
::set astyle=%USERPROFILE%\Projects\AStyle\build\vs2015\bin\AStyle.exe


REM check that the programs are available
REM The directory contains the release number, so check that it is current.
if not exist "%progdir%" (
echo no directory "%progdir%"
pause
exit 1
)
if not exist "%astyle%" (
echo no file "%astyle%"
pause
exit 1
)

if exist %testdir% (
echo.
echo Removing TestData\CodeBlocks
rd  /s /q  %testdir%
timeout 4
)

echo.
echo Extracting TestData\CodeBlocks
"C:/Program Files/7-Zip/7z.exe"  x  -r  -y    -o"%USERPROFILE%\Projects\TestData\"  "%USERPROFILE%\Projects\TestArchives\codeblocks_13.12-1.tar" *cpp *h  > NUL
move  %testdir%-13.12  %testdir%

echo.
cd  %testdir%

REM copy clang format file and rename
echo Copying clang-%styleopt%.yaml configurating file
copy ..\..\AStyle\file\clang-%styleopt%.yaml  _clang-format
echo.

echo Formatting with clang-format
if exist *-clang  del /s /q  *-clang > NUL
for /R %%v in (*.cpp) do (
:: echo %%v-clang
"%progdir%\clang-format"  -style=file %%v  > %%v-clang
)

echo.
"%astyle%"  --options=..\..\AStyle\file\%styleopt%.ini  -vRQ  *.cpp
:: echo.
:: "%astyle%"  --options=..\..\AStyle\file\%styleopt%.ini  -vRQ  *.h

echo.
echo Displaying files
for /R %%v in (*.cpp) do (
"%compdir%\WinMergeU"  %%v  %%v-clang
)

REM ~ echo.
REM ~ echo Displaying specific files
REM ~ for /D %%v in (%testdir%\FSNode\FSNBrowser.m,
               REM ~ %testdir%\FSNode\FSNIcon.m) do (
REM ~ "%compdir%\WinMergeU"  %%v  %%v-clang
REM ~ )

echo.
echo * * * *   end of clang-format-codeblocks   * * * *
pause
