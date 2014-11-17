@echo off

set progdir=C:\Programs\clang+llvm-3.2-x86-mingw32-EXPERIMENTAL\bin
set srcdir=%USERPROFILE%\Projects\aaastyle-test

echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                      clang help                       *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo.
"%progdir%\clang++"  -help

echo.
pause
