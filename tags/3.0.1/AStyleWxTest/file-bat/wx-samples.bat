@REM build ALL wxWidgets samples with Visual C compiler
@REM NOTE - uses Debug Unicode DLL configuration
@color 0E
@echo off

REM set variables for vc version
set version=2010

set WXWIN=C:\Programs\wxWidgets-2.9.4_vs%version%

REM load environment variables
if %version% == 2010 (
call "%VS100COMNTOOLS%\vsvars32.bat"
) else (
if %version% == 2008 (
call "%VS90COMNTOOLS%\vsvars32.bat"
) else (
if %version% == 2005 (
call "%VS80COMNTOOLS%\vsvars32.bat"
) else (
echo invalid version %version%
pause
exit 1
)
)
)
echo -
echo Compiling with VS %version%
pause

REM run make
cd %WXWIN%\samples

if not exist makefile.vc (
echo Cannot find makefile.vc
pause
exit 1
)

REM compile all samples with Release Unicode configuration
set wxOpts=  MONOLITHIC=1  BUILD=release  UNICODE=1
nmake  -f  makefile.vc  MAKEDIR=%WXWIN%\samples  %wxOpts%

echo -
echo * * * * * *  end of make  * * * * * *
pause
