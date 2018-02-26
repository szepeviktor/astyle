@echo off

REM MinGW download  https://sourceforge.net/projects/mingw-w64/

REM SET PATH VARIABLE TO INCLUDE CMAKE AND MINGW COMPILER
set PATH=C:\Program Files\CMake\bin;%PATH%
set PATH=C:\Programs\TDM-GCC-64\bin;%PATH%
:: set PATH=C:\Programs\mingw-w64\x86_64-7.1.0-win32-seh-rt_v5-rev2\mingw64\bin;%PATH%

REM USE ONE OF THESE OPTIONS
set opts=
:: set opts=-DCMAKE_VERBOSE_MAKEFILE=1
:: set opts=-DCMAKE_BUILD_TYPE=Debug  -DCMAKE_VERBOSE_MAKEFILE=1
:: set opts=-DCMAKE_BUILD_TYPE="MinSizeRel"
:: echo %opts%

REM Executable
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *               AStyleWx MinGW Executable               *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyleWx"
rmdir /s /q aswx-mingw-exe
md  aswx-mingw-exe
cd  aswx-mingw-exe
cmake  -G "MinGW Makefiles"  %opts%  ../
mingw32-make

echo.
pause
