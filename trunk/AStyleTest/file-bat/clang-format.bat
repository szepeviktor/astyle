@echo off

set progdir=C:\Programs\clang+llvm-3.2-x86-mingw32-EXPERIMENTAL\bin
set srcdir=%USERPROFILE%\Projects\aaastyle-test

echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                     clang-format                      *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

echo.
echo Copying .clang-format to %srcdir%
copy .clang-format  %srcdir%  > NUL
echo.

set options=-style=file
set file=astyle_main.h

echo Running clang-format  %options%  %file%
"%progdir%\clang-format" %options%  "%srcdir%\%file%"  >  "%srcdir%\zz-new.cpp"

echo.
pause
