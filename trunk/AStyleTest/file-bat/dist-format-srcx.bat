@REM formats the astyletest source code in the srcx directory
@echo off

set progdir=C:\Program Files\AStyle
set options=--options=..\..\AStyleTest\file-py\astyle-options.ini

echo Formatting AStyleTest\srcx
echo %options%
echo.

"%progdir%\AStyle"  %options%  -Q  ..\srcx\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\srcx\*.h
echo.

echo.
pause
