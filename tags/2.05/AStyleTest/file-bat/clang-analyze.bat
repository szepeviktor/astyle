@echo off

set progdir=C:\Programs\clang+llvm-3.2-x86-mingw32-EXPERIMENTAL\bin
set srcdir=%USERPROFILE%\Projects\AStyle\src

echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                    clang analyze                      *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set I0=-IC:\Programs\MinGW\include
set I1=-IC:\Programs\MinGW\lib\gcc\mingw32\4.6.2\include
set I2=-IC:\Programs\MinGW\lib\gcc\mingw32\4.6.2\include\c++
set I3=-IC:\Programs\MinGW\lib\gcc\mingw32\4.6.2\include\c++\mingw32

echo.
echo astyle.h
"%progdir%\clang++" "%srcdir%\astyle.h" --analyze %I0% %I1% %I2% %I3%
echo.
echo astyle_main.h
"%progdir%\clang++" "%srcdir%\astyle_main.h" --analyze %I0% %I1% %I2% %I3%
echo.
echo ASLocalizer.h
"%progdir%\clang++" "%srcdir%\ASLocalizer.h" --analyze %I0% %I1% %I2% %I3%
echo.
echo ASBeautifier
"%progdir%\clang++" "%srcdir%\ASBeautifier.cpp" --analyze %I0% %I1% %I2% %I3%
echo.
echo ASEnhancer
"%progdir%\clang++" "%srcdir%\ASEnhancer.cpp" --analyze %I0% %I1% %I2% %I3%
echo.
echo ASFormatter
"%progdir%\clang++" "%srcdir%\ASFormatter.cpp" --analyze %I0% %I1% %I2% %I3%
echo.
echo ASLocalizer
"%progdir%\clang++" "%srcdir%\ASLocalizer.cpp" --analyze %I0% %I1% %I2% %I3%
echo.
echo ASResource
"%progdir%\clang++" "%srcdir%\ASResource.cpp" --analyze %I0% %I1% %I2% %I3%
echo.
echo astyle_main
"%progdir%\clang++" "%srcdir%\astyle_main.cpp" --analyze %I0% %I1% %I2% %I3%

echo.
echo Removing .gch files
del  "%srcdir%\*.gch" 
echo Removing .plist files
del  *.plist

echo.
pause
