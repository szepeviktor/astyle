@echo off

REM MinGW download  https://sourceforge.net/projects/mingw-w64/

set PATH=C:\Program Files\CMake\bin;%PATH%
set PATH=C:\Programs\TDM-GCC-64\bin;%PATH%
:: set PATH=C:\Programs\mingw-w64\x86_64-7.1.0-win32-seh-rt_v5-rev2\mingw64\bin;%PATH%


REM Executable
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                AStyle MinGW Executable                *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-mingw-exe
cd  as-mingw-exe
cmake  -G "MinGW Makefiles"  ../
mingw32-make

REM DLL
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                   AStyle MinGW DLL                    *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-mingw-dll
cd  as-mingw-dll
cmake  -G "MinGW Makefiles"  -DBUILD_SHARED_LIBS=1  ../
mingw32-make

REM Java
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                   AStyle MinGW Java                   *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-mingw-java
cd  as-mingw-java
cmake  -G "MinGW Makefiles"  -DBUILD_JAVA_LIBS=1  ../
mingw32-make

REM Static
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                  AStyle MinGW Static                  *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-mingw-a
cd  as-mingw-a
cmake  -G "MinGW Makefiles"  -DBUILD_STATIC_LIBS=1  ../
mingw32-make

set copy=true
if %copy% ==true (
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                            Copying Files                            *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
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
