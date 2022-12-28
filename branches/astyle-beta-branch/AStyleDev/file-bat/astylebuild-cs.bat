@echo off
REM build the AStyle Release Dll Configuration using the AStyle project file
REM copy the output to the AStyleDev\build\%1\bin or debug  folder
REM always uses the release build of the Dll
REM %1 should be the Visual Studio version number (release date before vs11)
REM %2 should be the Visual Studio configuration (Release or Debug)

set astyle=..\..\AStyle\build\%1
REM TEMPORARY? for vs11 preview? Uses vs2010 instead of vs11
if %1 == vs11  set astyle=..\..\AStyle\build\vs2010
REM END TEMPORARY
set bindir=..\build\%1\bin
if %2 == Debug  set bindir=..\build\%1\debug
REM the %sdk% below can be obtained from the macro $(MSBuildRuntimeVersion)
REM default is vs2010
set sdk=v4.0.30319
if %1 == vs2005  set sdk=v2.0.50727
if %1 == vs2008  set sdk=v3.5
set errors=no
set called=no

REM if called from a compile, the directory structure is different
if not exist astylebuild-dll.bat (
set called=yes
set astyle=..\..\%astyle%
set bindir=..\..\%bindir%
)

echo BUILDING ASTYLE DLL
%windir%\microsoft.net\framework\%sdk%\msbuild  /nologo  /noconsolelogger  "/property:Configuration=Release"  "/property:Platform=Win32"  "%astyle%\AStyle Dll.sln"
if %ERRORLEVEL% NEQ 0  set errors=yes

REM don't copy if compile errors
if not %errors%==yes (
echo -
echo COPYING
if not exist "%bindir%"  mkdir "%bindir%"
xcopy "%astyle%\bin\AStyle.dll"  "%bindir%\"  /y /q
if %ERRORLEVEL% NEQ 0  set errors=yes
)

if %errors%==yes (
echo * * * *  ERRORS IN PROCESSING SCRIPT  * * * *
)

if %called%==yes  (
if %errors% == yes exit 100
) else (
echo -
pause
)
