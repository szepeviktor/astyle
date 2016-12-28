@REM build wxWidgets for the MinGW compiler
@color 0E
@echo off

:: set PATH=C:\Programs\MinGW\bin;%PATH%
set PATH=C:\Programs\TDM-GCC-64\bin;%PATH%

REM set the wxWidgets folder for compile
:: set WXWIN=C:\Programs\wxWidgets-2.8.12_mingw
set WXWIN=C:\Programs\wxWidgets-3.0.2_mingw

REM set variables for wxWidgets version from the environment variable
set wxVersion=%WXWIN:~22%
if %wxVersion:~0,3% == 2.8 set wx=28
if %wxVersion:~0,3% == 3.0 set wx=30
if not defined wx (
echo Cannot determine wxWidgets version
pause
exit 1
)

echo.
if %wx% == 28 (
echo VERSION 2.8 IS NOT SUPPORTED BY ASTYLEWX
)

REM Display the first of four lines in the g++ compiler version
SETLOCAL ENABLEDELAYEDEXPANSION
set count=1
for /f "tokens=*" %%v in ('g++ --version') do (
set ver!count!=%%v
set /a count=!count!+1
)
echo Compiling with MinGW - %ver1%
ENDLOCAL

echo Compiling WxWidgets %wxVersion%
pause


REM COMPILE NOTES * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM FOR 2.8 DLL COMPILES
REM Must change the command line so that inline functions are not exported:
REM        CFLAGS=-fno-keep-inline-dllexport
REM        CXXFLAGS=-fno-keep-inline-dllexport
REM These are no longer needed.
REM :: set xtra= CFLAGS="-fno-keep-inline-dllexport"  CXXFLAGS="-fno-keep-inline-dllexport"

REM FOR 3.0 DLL COMPILES
REM Release builds DO include debug information by default.
REM defaults are MONOLITHIC=0  UNICODE=1  BUILD=debug  SHARED= 0

REM FOR 3.0.2 COMPILES
REM -std=gnu++11 and -Wno-deprecated-declarations are needed.
REM -std=gnu++11 must be used and NOT -std=c++11 which disables some extensions
REM and causes "undefined reference" errors.
set xtra= CXXFLAGS="-std=gnu++11 -Wno-deprecated-declarations"

REM DLL CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM Release Unicode DLL configuration
REM Release builds DO include debug information by default.
REM Releases before wxWidgets 3.0 need UNICODE=1
REM Releases before wxWidgets 3.0 need BUILD=debug
if not exist %WXWIN%\lib\gcc_dll\libwxbase%wx%u.a (
set wxOpts2= %xtra%  MONOLITHIC=0  UNICODE=1  BUILD=release  SHARED=1
)

REM LIB CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM Release Unicode Lib configuration
REM Release builds DO include debug information by default.
REM Releases before wxWidgets 3.0 need UNICODE=1
REM Releases before wxWidgets 3.0 need BUILD=debug
if not exist "%WXWIN%\lib\gcc_lib\libwxmsw%wx%u.a" (
set wxOpts4= %xtra%  MONOLITHIC=0  UNICODE=1  BUILD=release
)

REM Release Unicode DLL configuration for CODEBLOCKS
:: if not exist "%WXWIN%\lib\gcc_lib\libwxmsw%wx%u.a" (
:: set wxOpts6= %xtra%  MONOLITHIC=1  UNICODE=1  BUILD=release  SHARED=1  VENDOR=cb
:: )

REM * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
REM
REM See docs\msw\install.txt for details.
REM Editing the include/wx/msw/setup.h file can cause compile errors.
REM
REM Set common options.
REM If MONOLITHIC=1 is used then setup.h in the lib folder must be changed also.
REM Using MONOLITHIC=1 will NOT remove libraries from the compile.
REM Using MONOLITHIC=1 will NOT increase compiled program size.
REM Using MONOLITHIC=1 will NOT increase the linking time.
REM
REM DO NOT use -fno-exceptions compiler options to avoid errors and warnings.
REM release 2.8 default is UNICODE=0 USE_OPENGL=0 (stc is an add-on).
REM release 3.0 default is UNICODE=1 USE_OPENGL=1 USE_STC=1.
REM
REM Most of these will be removed from the non-monolithic build, but not the monolithic.
REM The exception is USE_OPENGL which is always built as an additional library.
REM They do not affect the compiled program size.
set wxOptsX= USE_HTML=0 USE_MEDIA=0 USE_OPENGL=0 USE_PROPGRID=0 USE_QA=0 USE_RIBBON=0 USE_RICHTEXT=0 USE_WEBVIEW=0 USE_XRC=0

REM run make
cd "%WXWIN%\build\msw"

if not exist makefile.gcc (
echo Cannot find makefile.gcc
pause
exit 1
)

if defined wxOpts1  mingw32-make  -f  makefile.gcc  %wxOpts1%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts2  mingw32-make  -f  makefile.gcc  %wxOpts2%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts3  mingw32-make  -f  makefile.gcc  %wxOpts3%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts4  mingw32-make  -f  makefile.gcc  %wxOpts4%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts5  mingw32-make  -f  makefile.gcc  %wxOpts5%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts6  mingw32-make  -f  makefile.gcc  %wxOpts6%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts7  mingw32-make  -f  makefile.gcc  %wxOpts7%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts8  mingw32-make  -f  makefile.gcc  %wxOpts8%   %wxOptsX%
if errorlevel 2 pause

echo.
echo * * * * * *  end of make  * * * * * *
pause
