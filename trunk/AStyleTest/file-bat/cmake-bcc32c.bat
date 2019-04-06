@echo off

REM SET PATH VARIABLE TO INCLUDE CMAKE AND MINGW COMPILER
set PATH=C:\Program Files\CMake\bin;%PATH%
set PATH=C:\Programs\Embarcadero\BCC101\bin;%PATH%
:: set PATH=C:\Programs\Embarcadero\BCC101\bin;%PATH%
REM this is the free clang-based compiler
set CXX=bcc32c

REM NOTE: Borland default build is 'Debug'. The 'Release' build must be explicitely requested.
REM USE ONE OF THESE OPTIONS
set opts=
:: set opts=-DCMAKE_VERBOSE_MAKEFILE=ON
:: set opts=-DCMAKE_BUILD_TYPE=Debug
:: set opts=-DCMAKE_BUILD_TYPE=Debug  -DCMAKE_VERBOSE_MAKEFILE=ON
:: set opts=-DCMAKE_BUILD_TYPE="MinSizeRel"
:: echo %opts%

REM Executable
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *               AStyle Borland Executable               *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
if exist as-bcc32c-exe  rmdir /s /q as-bcc32c-exe
md  as-bcc32c-exe
cd  as-bcc32c-exe
cmake  -G "Borland Makefiles"  %opts%  ../
make
timeout /t 2 > nul

REM DLL
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                  AStyle Borland DLL                   *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
if exist as-bcc32c-dll  rmdir /s /q as-bcc32c-dll
md  as-bcc32c-dll
cd  as-bcc32c-dll
cmake  -G "Borland Makefiles"  -DBUILD_SHARED_LIBS=ON  %opts%  ../
make
timeout /t 2 > nul

REM Java
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                  AStyle Borland Java                  *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
if exist as-bcc32c-java  rmdir /s /q as-bcc32c-java
md  as-bcc32c-java
cd  as-bcc32c-java
cmake  -G "Borland Makefiles"  -DBUILD_JAVA_LIBS=ON  %opts%  ../
make
timeout /t 2 > nul

REM Static
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                 AStyle Borland Static                 *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
if exist as-bcc32c-lib  rmdir /s /q as-bcc32c-lib
md  as-bcc32c-lib
cd  as-bcc32c-lib
cmake  -G "Borland Makefiles"  -DBUILD_STATIC_LIBS=ON  %opts%  ../
make
timeout /t 2 > nul

set copy=true
if %copy% ==true (
	echo.
    echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	echo *          Copy Files to AStyleDev for Testing          *
    echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	cd ../
	xcopy /y /q  as-bcc32c-exe\AStyle.exe     ..\AStyleDev\src-p\
	xcopy /y /q  as-bcc32c-dll\AStyle*.dll    ..\AStyleDev\src-o\
	xcopy /y /q  as-bcc32c-dll\AStyle*.dll    ..\AStyleDev\src-p\
	xcopy /y /q  as-bcc32c-dll\AStyle*.dll    ..\AStyleDev\src-s\
	xcopy /y /q  as-bcc32c-dll\AStyle*.dll    ..\AStyleDev\src-s2\
	xcopy /y /q  as-bcc32c-java\AStyle*j.dll  ..\AStyleDev\src-j\
)


echo.
pause
