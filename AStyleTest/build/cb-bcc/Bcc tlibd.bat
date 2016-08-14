@echo off

REM This file runs TLIB with quotes around the object file path.
REM The dash (-) in the pathname apparently is mistaken for a minus sign.
REM File paths WITHOUT a dash work ok with TLIB.

REM CALL THIS FILE  AS A PRE-BUILD STEP  FOR GTEST DEBUG
REM cmd /c echo RUN TLIBD.BAT TO LINK GTESTD.LIB

set binpath=C:\Programs\Embarcadero\EC6.80\bin

if not exist "obj\Debug\googletest\src\gtest-all.obj" (
echo Must compile GMock Lib Debug before running
pause
exit 1
)
if exist bin\gmockd.lib  del bin\gmockd.lib

echo Linking gmockd.lib
%binpath%\tlib64.exe /C /P64 bin\gmockd.lib /a "obj\Debug\googlemock\src\gmock-all.obj" "obj\Debug\googletest\src\gtest-all.obj"

echo.
pause
