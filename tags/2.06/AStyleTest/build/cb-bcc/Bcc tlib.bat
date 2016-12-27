@echo off

REM This file runs TLIB with quotes around the object file path.
REM The dash (-) in the pathname apparently is mistaken for a minus sign.
REM File paths WITHOUT a dash work ok with TLIB.

REM CALL THIS FILE  AS A PRE-BUILD STEP  FOR GTEST RELEASE
REM cmd /c echo RUN TLIB.BAT TO LINK GTEST.LIB

set binpath=C:\Programs\Embarcadero\EC6.80\bin

if not exist "obj\Release\googletest\src\gtest-all.obj" (
echo Must compile GMock Lib Release before running
pause
exit 1
)
if exist bin\gmock.lib  del bin\gmock.lib

echo Linking gmock.lib
%binpath%\tlib64.exe /C /P64 bin\gmock.lib /a "obj\Release\googlemock\src\gmock-all.obj" "obj\Release\googletest\src\gtest-all.obj"

echo.
::pause
