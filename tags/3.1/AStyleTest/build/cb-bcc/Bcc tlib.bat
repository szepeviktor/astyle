@echo off

REM This file runs TLIB with quotes around the object file path.
REM The dash (-) in the pathname apparently is mistaken for a minus sign.
REM File paths WITHOUT a dash work ok with TLIB.

REM CALL THIS FILE  AS A PRE-BUILD STEP  FOR GTEST RELEASE
REM cmd /c echo RUN TLIB.BAT TO LINK GTEST.LIB

set binpath=C:\Programs\Embarcadero\EC6.80\bin

if not exist "obj\Release\googletest\src\gtest-all.obj" (
echo Must compile gtest Lib Release before running
pause
exit 1
)
if exist bin\gtest.lib  del bin\gtest.lib

echo Linking static library: bin\gtest.lib
%binpath%\tlib64.exe /C /P64 bin\gtest.lib /a "obj\Release\googletest\src\gtest-all.obj"
if errorlevel 0 (
echo Output file is bin\gtest.lib
) else (
echo ERROR: unable to link bin\gtest.lib
)

echo.
pause
