@echo off

set PATH=C:\Program Files\CMake\bin;%PATH%
set PATH=C:\Programs\Embarcadero\BCC101\bin;%PATH%
REM this is the free clang-based compiler
set CXX=bcc32c

REM NOTE: Borland default build is 'Debug'. The 'Release' build must be explicitely requested.

REM Executable
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *               AStyle Borland Executable               *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-bcc32c-exe
cd  as-bcc32c-exe
cmake  -G "Borland Makefiles"  -DCMAKE_BUILD_TYPE=Release  ../
make

REM DLL
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                  AStyle Borland DLL                   *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-bcc32c-dll
cd  as-bcc32c-dll
cmake  -G "Borland Makefiles"  -DCMAKE_BUILD_TYPE=Release  -DBUILD_SHARED_LIBS=1  ../
make

REM Java
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                  AStyle Borland Java                  *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-bcc32c-java
cd  as-bcc32c-java
cmake  -G "Borland Makefiles"  -DCMAKE_BUILD_TYPE=Release  -DBUILD_JAVA_LIBS=1  ../
make

REM Static
echo.
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
echo *                 AStyle Borland Static                 *
echo * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
cd  "%USERPROFILE%\Projects\AStyle"
md  as-bcc32c-lib
cd  as-bcc32c-lib
cmake  -G "Borland Makefiles"  -DCMAKE_BUILD_TYPE=Release  -DBUILD_STATIC_LIBS=1  ../
make

set copy=true
if %copy% ==true (
	echo
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
	echo "*                            Copying Files                            *"
	echo "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"
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
