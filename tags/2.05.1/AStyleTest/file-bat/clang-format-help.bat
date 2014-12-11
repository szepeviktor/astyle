@echo off

set progdir=C:\Programs\clang+llvm-3.2-x86-mingw32-EXPERIMENTAL\bin
set srcdir=%USERPROFILE%\Projects\aaastyle-test

echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                   clang-format help                   *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo.
"%progdir%\clang-format"  -help

echo.
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                   clang-format file                   *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo.

if exist .clang-format (
copy .clang-format con > NUL
)

echo.
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *              clang-format configuration               *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM print the configuration including the options file
"%progdir%\clang-format" -dump-config

echo.
pause
