@REM build wxWidgets for Visual C compiler
@REM builds for all versions and platforms can be in one directory
@REM must use the COMMUNITY edition for 64 bit compiles
@color 0E
@echo off

REM CHANGE THESE VARIABLES BEFORE RUNNING
REM vcVersion:  vs2013 = 120, vs2015 = 140
REM vcPlatform:  x86 or x64
set WXWIN=C:\Programs\wxWidgets-3.0.2_vsAll
set vcVersion=140
set vcPlatform=x86

REM load environment variables
if %vcVersion% == 120 (
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" %vcPlatform%
) else (
if %vcVersion% == 140 (
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" %vcPlatform%
) else (
echo Invalid Visual Studio version %vcVersion%
pause
exit 1
)
)

REM verify variables were set
if "%VSINSTALLDIR%" == "" (
echo.
echo Compiler variables were not set for platform %vcPlatform%
pause
exit 1
)

REM set variables for wxWidgets version from the environment variable
if %WXWIN:~27,1% == _ (
set wxVersion=%WXWIN:~22,5%
) else (
set wxVersion=%WXWIN:~22,6%
)
REM correction for "rc" releases - checks for "-" and includes the rc number
if %WXWIN:~27,1% == - (
set wxVersion=%WXWIN:~22,9%
)
if %wxVersion:~0,3% == 2.8 set wx=28
if %wxVersion:~0,3% == 2.9 set wx=29
if %wxVersion:~0,3% == 3.0 set wx=30
if not defined wx (
echo Cannot determine wxWidgets version
pause
exit 1
)

echo.
echo Compiling with VS %vcVersion% %vcPlatform%
echo Compiling WxWidgets %wxVersion%
pause

REM LIB CONFIGURATIONS * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set wxOptsA= COMPILER_VERSION=%vcVersion%  TARGET_CPU=%vcPlatform%  DEBUG_INFO=default  DEBUG_FLAG=default

REM LIB DEBUG configuration
:: if not exist "%WXWIN%\lib\vc%vcVersion%_lib\wxbase%wx%ud.lib" (
:: set wxOpts4=  BUILD=debug  %wxOptsA%
:: )

REM LIB RELEASE configuration
REM ~ if not exist "%WXWIN%\lib\vc%vcVersion%_lib\wxbase%wx%u.lib" (
set wxOpts4=  BUILD=release  %wxOptsA%
REM ~ )

REM DLL CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * * * *

set wxOptsB= SHARED=1  OFFICIAL_BUILD=1

REM ~ REM DLL DEBUG configuration
REM ~ if not exist "%WXWIN%\lib\vc%vcVersion%_lib\wxbase%wx%ud.lib" (
REM ~ set wxOpts1= BUILD=debug  %wxOptsA% %wxOptsB%
REM ~ )

REM ~ REM DLL RELEASE configuration
REM ~ if not exist "%WXWIN%\lib\vc_dll\wxmsw%wx%d.lib" (
REM ~ set wxOpts2= BUILD=release %wxOptsA% %wxOptsB%
REM ~ )

REM STATIC CONFIGURATIONS  * * * * * * * * * * * * * * * * * * * * * * * * * * *

REM Static Unicode configuration (static library)
REM Releases before wxWidgets 2.9 need UNICODE=1
:: if not exist "%WXWIN%\lib\vc_libs\wxmsw%wx%u.lib" (
set wxOpts6= BUILD=release  RUNTIME_LIBS=static  CFG=s  %wxOptsA%
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
REM release 2.8 default is UNICODE=0 USE_OPENGL=0 (none).
REM release 2.9 default is UNICODE=1 USE_OPENGL=1 USE_STC=1.
REM
REM These will be removed from the non-monolithic build, but NOT the monolithic.
REM They do NOT affect the compiled program size.
set wxOptsX= USE_OPENGL=0 USE_HTML=0 USE_MEDIA=0 USE_PROPGRID=0 USE_QA=0 USE_RIBBON=0 USE_RICHTEXT=0 USE_WEBVIEW=0 USE_XRC=0

REM The following can be removed from monolithic and non-monolithic build.
REM Must also use the compile option wxNO_EXCEPTIONS in AStyleWx.
REM USE_EXCEPTIONS=0 decreases program size by about 650 KB.
REM Cannot zero USE_THREADS because wxUSE_FSWATCHER needs USE_THREADS.
set wxOptsXX= USE_EXCEPTIONS=0  USE_RTTI=0

REM run make
cd "%WXWIN%\build\msw"

if not exist makefile.vc (
echo Cannot find makefile.vc
pause
exit 1
)

REM The monolithic build does not recognize most of the %wxOptsX%  options.
if defined wxOpts1  nmake  -f  makefile.vc  %wxOpts1% %wxOptsX%
if errorlevel 2 pause
if defined wxOpts2  nmake  -f  makefile.vc  %wxOpts2% %wxOptsX%
if errorlevel 2 pause
if defined wxOpts3  nmake  -f  makefile.vc  %wxOpts3% %wxOptsX%
if errorlevel 2 pause
if defined wxOpts4  nmake  -f  makefile.vc  %wxOpts4% %wxOptsX% %wxOptsXX%
if errorlevel 2 pause
if defined wxOpts5  nmake  -f  makefile.vc  %wxOpts5% %wxOptsX%
if errorlevel 2 pause
REM Static build does not use exceptions (saves 650 KB).
REM must also use the compile option wxNO_EXCEPTIONS in AStyleWx.
if defined wxOpts6  nmake  -f  makefile.vc  %wxOpts6% %wxOptsX% %wxOptsXX%
if errorlevel 2 pause
if defined wxOpts7  nmake  -f  makefile.vc  %wxOpts7% %wxOptsX%
if errorlevel 2 pause
if defined wxOpts8  nmake  -f  makefile.vc  %wxOpts8% %wxOptsX%
if errorlevel 2 pause

REM delete exports library, incremental linker, and manifest files
if exist "%WXWIN%\lib\vc_dll\*.exp"    del "%WXWIN%\lib\vc_dll\*.exp"
if exist "%WXWIN%\lib\vc_dll\*.ilk"    del "%WXWIN%\lib\vc_dll\*.ilk"
if exist "%WXWIN%\lib\vc_dll\*.manifest"    del "%WXWIN%\lib\vc_dll\*.manifest"

echo.
echo * * * * * *  end of make  * * * * * *
pause
