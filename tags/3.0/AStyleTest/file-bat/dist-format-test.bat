@REM formats the astyletest source code in the test directories
@echo off

set progdir=C:\Program Files\AStyle
set options=--options=..\..\AStyle\file\astyle.ini

echo Formatting AStyleTest
echo.

"%progdir%\AStyle"  %options%  -Q  ..\src\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\src\*.h
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srccon\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srccon\*.h
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srci18n\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srclib\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srclib\*.h
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srcloc\*.cpp
echo.

echo.
pause
