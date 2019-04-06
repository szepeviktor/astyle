@echo off
REM MinGW download  https://sourceforge.net/projects/mingw-w64/

REM SET PATH VARIABLE TO INCLUDE CMAKE AND MINGW COMPILER
set PATH=C:\Program Files\CMake\bin;%PATH%
set PATH=C:\Programs\TDM-GCC-64\bin;%PATH%
REM the following path will be overridden by the WXWIN define
set PATH=C:\Programs\wxWidgets-3.0.2_mingw;%PATH%

set optsx=-DWXWIN="C:/Programs/WxWidgets-3.1.1_mingw"  -DWXSHARED=1

REM USE ONE OF THESE OPTIONS
set opts=
:: set opts=-DCMAKE_VERBOSE_MAKEFILE=1
:: set opts=-DCMAKE_BUILD_TYPE=Debug  -DCMAKE_VERBOSE_MAKEFILE=1
:: set opts=-DCMAKE_BUILD_TYPE="MinSizeRel"
:: echo %opts%

REM Executable
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *             AStyleWx MinGW DLL Executable             *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyleWx"
if exist aswx-mingw-exe-dll  rmdir /s /q aswx-mingw-exe-dll
md  aswx-mingw-exe-dll
cd  aswx-mingw-exe-dll
cmake  -G "MinGW Makefiles"  %opts%  %optsx%  ../
mingw32-make

echo.
pause
