@REM build wxWidgets STC for Visual C compiler
@color 0E
@echo off

REM set the wxWidgets folder for compile
REM this is not needed after version 2.8
set WXWIN=C:\Programs\wxWidgets-2.8.12_vs2010

REM this is not needed after version 2.8
set wxversion=%WXWIN:~22%
if not %wxversion:~0,3% == 2.8 (
echo wxWidgets %wxversion:~0,3% does not need this compile
pause
exit 100
)

REM set variables for vc version
set version=%WXWIN:~-4%

REM load environment variables
if %version% == 2012 (
call "%VS110COMNTOOLS%\vsvars32.bat"
) else (
if %version% == 2010 (
call "%VS100COMNTOOLS%\vsvars32.bat"
) else (
echo invalid version %version%
pause
exit 1
)
)

echo.
echo Compiling with VS %version%
echo Compiling WxWidgets %WXWIN:~22%
pause

REM DEBUG CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM Debug Unicode DLL configuration
::if not exist "%WXWIN%\lib\vc_dll\wxmsw28ud_stc.lib" (
set wxOpts1=  BUILD=debug  SHARED=1  VENDOR=custom  UNICODE=1
::if not exist "%WXWIN%\lib\vc_dll\wxbase28ud.lib" (
::	echo.
::	echo Need compile for Debug Unicode configuration
::	pause
)
)

REM ~ REM Debug ANSI DLL configuration
REM ~ if not exist "%WXWIN%\lib\vc_dll\wxmsw28d_stc.lib" (
REM ~ set wxOpts2=  MONOLITHIC=1  BUILD=debug  UNICODE=0  SHARED=1  VENDOR=all
REM ~ if not exist "%WXWIN%\lib\vc_dll\wxmsw28d.lib" (
	REM ~ echo.
	REM ~ echo Need compile for Debug Unicode configuration
	REM ~ pause
REM ~ )
REM ~ )


REM RELEASE CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * *

REM Release Unicode configuration (static)
if not exist "%WXWIN%\lib\vc_lib\wxmsw28u_stc.lib" (
set wxOpts4=  BUILD=release  UNICODE=1
if not exist "%WXWIN%\lib\vc_lib\wxbase28u.lib" (
	echo.
	echo Need compile for Release Unicode configuration
	pause
)
)

REM STATIC CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM Static Unicode configuration (static library)
if not exist "%WXWIN%\lib\vc_libs\wxmsw28u_stc.lib" (
set wxOpts6=  BUILD=release  UNICODE=1  RUNTIME_LIBS=static  CFG=s
if not exist "%WXWIN%\lib\vc_libs\wxbase28u.lib" (
	echo.
	echo Need compile for Release Unicode configuration
	pause
)
)

REM set common options
REM do NOT zero USE_GUI
set wxOptsX=  USE_HTML=0  USE_MEDIA=0  USE_AUI=0  USE_RICHTEXT=0  USE_OPENGL=0

REM run make
cd "%WXWIN%\contrib\build\stc"

if not exist makefile.vc (
echo.
echo Cannot find makefile.vc
pause
exit 1
)

echo.
if defined wxOpts1  nmake  -f  makefile.vc  %wxOpts1%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts2  nmake  -f  makefile.vc  %wxOpts2%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts3  nmake  -f  makefile.vc  %wxOpts3%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts4  nmake  -f  makefile.vc  %wxOpts4%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts5  nmake  -f  makefile.vc  %wxOpts5%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts6  nmake  -f  makefile.vc  %wxOpts6%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts7  nmake  -f  makefile.vc  %wxOpts7%   %wxOptsX%
if errorlevel 2 pause
if defined wxOpts8  nmake  -f  makefile.vc  %wxOpts8%   %wxOptsX%
if errorlevel 2 pause

REM delete exports library, incremental linker, and manifest files
if exist "%WXWIN%\lib\vc_dll\*.exp"    del "%WXWIN%\lib\vc_dll\*.exp"
if exist "%WXWIN%\lib\vc_dll\*.ilk"    del "%WXWIN%\lib\vc_dll\*.ilk"
if exist "%WXWIN%\lib\vc_dll\*.manifest"    del "%WXWIN%\lib\vc_dll\*.manifest"

echo.
echo * * * * * *  end of make  * * * * * *
pause
