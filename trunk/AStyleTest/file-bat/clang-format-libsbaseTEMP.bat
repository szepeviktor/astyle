@REM Format libsBase using clang-format.
@REM Then format libsBase using AStyle.
@REM Then the two formats can be compared.
@echo off

REM style options are Chromium, Google, LLVM, Mozilla, WebKit
set styleopt=gnu-test
set progdir=%USERPROFILE%\.vscode\extensions\ms-vscode.cpptools-0.12.0\LLVM\bin
::set comp=C:\Program Files (x86)\WinMerge\WinMergeU
set comp=C:\Program Files (x86)\Diffinity\Diffinity
set basename=libs-base-release-0_6_6
set testdir=%USERPROFILE%\Projects\TestData\libsBase
set astyle=%USERPROFILE%\Projects\AStyle\build\vs2017\debug\AStyled.exe
::set astyle=%USERPROFILE%\Projects\AStyle\build\vs2017\bin\AStyle.exe


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

if exist "%testdir%" (
echo.
echo Removing TestData\libsBase
rd  /s /q  "%testdir%"
timeout 2
)

echo.
echo Extracting TestData\libsBase
"C:/Program Files/7-Zip/7z.exe"  x  -r  -y  -o"%USERPROFILE%\Projects\TestData\"  "%USERPROFILE%\Projects\TestArchives\%basename%.zip" *m *h  > NUL
move  "%USERPROFILE%\Projects\TestData\%basename%"  %testdir%

echo.
cd  %testdir%

REM copy clang format file and rename
echo Copying clang-%styleopt%.yaml configurating file
copy ..\..\AStyle\file\clang-%styleopt%.yaml  _clang-format
echo.

REM NOTE: THE -clang IN THE REDIRECTION CAUSES A WARNING
echo Formatting with clang-format
if exist *-clang  del /s /q  *-clang > NUL
for /R %%v in (*.m) do (
:: echo %%v-clang
"%progdir%\clang-format"  -style=file %%v  > %%v-clang
)

echo.
"%astyle%"  --options=..\..\AStyle\file\gnu.ini  -vRQ  *.m
:: echo.
:: "%astyle%"  --options=..\..\AStyle\file\%styleopt%.ini  -vRQ  *.h

REM ~ echo.
REM ~ echo Displaying files
REM ~ cd  %testdir%
REM ~ for /R %%v in (*.m) do (
REM ~ "%comp%"  %%v  %%v-clang
REM ~ )

REM ~ echo.
REM ~ echo Displaying specific files
REM ~ for /D %%v in (%testdir%\FSNode\FSNBrowser.m,
               REM ~ %testdir%\FSNode\FSNIcon.m) do (
REM ~ "%comp%\WinMergeU"  %%v  %%v-clang
REM ~ )

echo.
echo * * * *   end of clang-format-libsbase   * * * *
pause
