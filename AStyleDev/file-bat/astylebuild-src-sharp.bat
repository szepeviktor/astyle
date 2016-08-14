@echo off
REM build the AStyle Release Dll Configuration using the AStyle project file
REM copy the output to the AStyleDev\test-s(x) folder

REM %1 should be the Visual Studio version (release date before vs11)
REM the %sdk% below can be obtained from the macro $(MSBuildRuntimeVersion)
set astyle=..\..\AStyle\build\vs2005
set bindir1=..\src-s
set bindir2=..\src-sx
set sdk=v3.5
if %astyle:~-6% == vs2005  set sdk=v2.0.50727
if %astyle:~-6% == vs2008  set sdk=v3.5
if %astyle:~-6% == vs2010  set sdk=v4.0.30319
if %astyle:~-6% == vs11    set sdk=v4.0.30319
set errors=no

echo BUILDING ASTYLE DLL
%windir%\microsoft.net\framework\%sdk%\msbuild  /nologo  "/property:Configuration=Release"  "%astyle%\AStyle Dll.sln"
if %ERRORLEVEL% NEQ 0  set errors=yes

REM don't copy if compile errors
if not %errors%==yes (
echo -
echo COPYING
xcopy "%astyle%\bin\AStyle.dll"  "%bindir1%\"  /y /q
if %ERRORLEVEL% NEQ 0  set errors=yes
xcopy "%astyle%\bin\AStyle.dll"  "%bindir2%\"  /y /q
if %ERRORLEVEL% NEQ 0  set errors=yes
)

if %errors%==yes (
echo -
echo * * * *  ERRORS IN PROCESSING SCRIPT  * * * *
)

echo -
pause
