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
echo *                AStyle MinGW Executable                *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
rmdir /s /q as-mingw-exe
md  as-mingw-exe
cd  as-mingw-exe
cmake  -G "MinGW Makefiles"  %opts%  ../
mingw32-make
timeout /t 1 > nul

REM DLL
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                   AStyle MinGW DLL                    *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
rmdir /s /q as-mingw-dll
md  as-mingw-dll
cd  as-mingw-dll
cmake  -G "MinGW Makefiles"  -DBUILD_SHARED_LIBS=1  %opts%  ../
mingw32-make
timeout /t 1 > nul

REM Java
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                   AStyle MinGW Java                   *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
rmdir /s /q as-mingw-java
md  as-mingw-java
cd  as-mingw-java
cmake  -G "MinGW Makefiles"  -DBUILD_JAVA_LIBS=1  %opts%  ../
mingw32-make
timeout /t 1 > nul

REM Static
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                  AStyle MinGW Static                  *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
rmdir /s /q as-mingw-a
md  as-mingw-a
cd  as-mingw-a
cmake  -G "MinGW Makefiles"  -DBUILD_STATIC_LIBS=1  %opts%  ../
mingw32-make
timeout /t 1 > nul

set copy=true
if %copy% ==true (
	echo.
	echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	echo *          Copy Files to AStyleDev for Testing          *
    echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	cd ../
	xcopy /y /q  as-mingw-exe\AStyle.exe     ..\AStyleDev\src-p\
	xcopy /y /q  as-mingw-dll\AStyle*.dll    ..\AStyleDev\src-o\
	xcopy /y /q  as-mingw-dll\AStyle*.dll    ..\AStyleDev\src-p\
	xcopy /y /q  as-mingw-dll\AStyle*.dll    ..\AStyleDev\src-s\
	xcopy /y /q  as-mingw-dll\AStyle*.dll    ..\AStyleDev\src-s2\
	xcopy /y /q  as-mingw-java\AStyle*j.dll  ..\AStyleDev\src-j\
)


echo.
pause
