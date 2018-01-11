@echo off

REM This file runs TLIB with quotes around the object file path.
REM The dash (-) in the pathname apparently is mistaken for a minus sign.
REM File paths WITHOUT a dash work ok with TLIB.

REM CALL THIS FILE  AS A PRE-BUILD STEP  FOR GTEST DEBUG
REM cmd /c echo RUN TLIBD.BAT TO LINK GTESTD.LIB

set binpath=C:\Programs\Embarcadero\EC6.80\bin

if not exist "obj\Debug\googletest\src\gtest-all.obj" (
echo Must compile gtest Lib Debug before running
pause
exit 1
)
if exist bin\gtestd.lib  del bin\gtestd.lib

echo Linking static library: bin\gtestd.lib
%binpath%\tlib64.exe /C /P64 bin\gtestd.lib /a "obj\Debug\googletest\src\gtest-all.obj"
if errorlevel 0 (
echo Output file is bin\gtestd.lib
) else (
echo ERROR: unable to link bin\gtestd.lib
)

echo.
pause
