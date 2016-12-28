@REM formats the astyleWx source code
@echo off

set progdir=C:\Program Files\AStyle
set options=--options=..\..\AStyle\file\astyle.ini

echo Formatting AStyleWx
echo.

"%progdir%\AStyle"  %options%  -Q  ..\..\AStyleWx\src\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\..\AStyleWx\src\*.h
echo.


echo.
pause
