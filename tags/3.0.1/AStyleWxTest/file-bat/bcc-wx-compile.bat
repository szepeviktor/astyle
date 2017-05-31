@REM build wxWidgets for the MinGW compiler
@color 0E
@echo off

set progdir=C:\Programs\Embarcadero\EC6.80

set PATH=%progdir%\bin;%PATH%

REM set the wxWidgets folder for compile
:: set WXWIN=C:\Programs\wxWidgets-2.8.12_ec
set WXWIN=C:\Programs\wxWidgets-3.0.2_bcc

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
for /f "tokens=*" %%v in ('bcc32 --version') do (
set ver!count!=%%v
set /a count=!count!+1
)
echo %ver1:~0,30%
ENDLOCAL

echo Compiling WxWidgets %wxVersion%
pause


REM COMPILE NOTES * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM FOR 3.0 DLL COMPILES
REM Release builds DO include debug information by default.
REM defaults are MONOLITHIC=0  UNICODE=1  BUILD=debug  SHARED= 0

REM FOR 3.0.2 COMPILES
REM -std=gnu++11 and -Wno-deprecated-declarations are needed.
REM -std=gnu++11 must be used and NOT -std=c++11 which disables some extensions
REM and causes "undefined reference" errors.
REM set xtra= CXXFLAGS="-Wno-deprecated-declarations -std=gnu++11"
set idirs=-I%progdir%\include\dinkumware -I%progdir%\include\windows\crtl -I%progdir%\include\windows\sdk
set xtra=CFLAGS="%idirs%"  CXXFLAGS="%idirs%"  LDFLAGS="-L%progdir%\lib\win32\release"

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

if not exist makefile.bcc (
echo Cannot find makefile.bcc
pause
exit 1
)

if defined wxOpts1  make  -f  makefile.bcc  %wxOpts1%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts2  make  -f  makefile.bcc  %wxOpts2%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts3  make  -f  makefile.bcc  %wxOpts3%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts4  make  -f  makefile.bcc  %wxOpts4%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts5  make  -f  makefile.bcc  %wxOpts5%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts6  make  -f  makefile.bcc  %wxOpts6%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts7  make  -f  makefile.bcc  %wxOpts7%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts8  make  -f  makefile.bcc  %wxOpts8%   %wxOptsX%
if errorlevel 2 pause

REM delete extra files
if exist %WXWIN%\lib\ec_dll\*.il?    del %WXWIN%\lib\ec_dll\*.il?
if exist %WXWIN%\lib\ec_dll\*.map    del %WXWIN%\lib\ec_dll\*.map
if exist %WXWIN%\lib\ec_dll\*.tds    del %WXWIN%\lib\ec_dll\*.tds

echo.
echo * * * * * *  end of make  * * * * * *
pause
