@REM Format GWorkspace using clang-format.
@REM Then format GWorkspace using AStyle.
@REM Then the two formats can be compared.
@echo off

REM style options are Chromium, Google, LLVM, Mozilla, WebKit
set styleopt=google
set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.9.2\LLVM\bin
::set comp=C:\Program Files (x86)\WinMerge\WinMergeU
set comp=C:\Program Files (x86)\Diffinity\Diffinity
set testdir=%USERPROFILE%\Projects\TestData\GWorkspace
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
echo Removing TestData\GWorkspace
rd  /s /q  %testdir%
timeout 1
)

echo.
echo Extracting TestData\GWorkspace
"C:/Program Files/7-Zip/7z.exe"  x  -r  -y  -x!Testing  -o"%USERPROFILE%\Projects\TestData\"  "%USERPROFILE%\Projects\TestArchives\gworkspace-0.8.6.tar" *m *h  > NUL
move  %testdir%-0.8.6  %testdir%

echo.
cd  %testdir%

REM copy clang format file and rename
echo Copying clang-%styleopt%.yaml configurating file
copy ..\..\AStyle\file\clang-%styleopt%.yaml  _clang-format
echo.

echo Formatting with clang-format
if exist *-clang  del /s /q  *-clang > NUL
for /R %%v in (*.m) do (
:: echo %%v-clang
"%progdir%\clang-format"  -style=file %%v  > %%v-clang
)

echo.
"%astyle%"  --options=..\..\AStyle\file\%styleopt%.ini  -vRQ  *.m
:: echo.
:: "%astyle%"  --options=..\..\AStyle\file\%styleopt%.ini  -vRQ  *.h

echo.
echo Displaying files
cd  %testdir%
for /R %%v in (*.m) do (
"%comp%"  %%v  %%v-clang
)

REM ~ echo.
REM ~ echo Displaying specific files
REM ~ for /D %%v in (%testdir%\FSNode\FSNBrowser.m,
               REM ~ %testdir%\FSNode\FSNIcon.m) do (
REM ~ "%comp%\WinMergeU"  %%v  %%v-clang
REM ~ )

echo.
echo * * * *   end of clang-format-gworkspace   * * * *
pause
