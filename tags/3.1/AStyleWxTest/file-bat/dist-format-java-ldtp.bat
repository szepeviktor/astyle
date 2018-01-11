@REM formats the ldtp Java source code
@echo off

set progdir=C:\Program Files\AStyle
set options=--options=..\..\AStyle\file\astyle.ini

echo.

"%progdir%\AStyle"  %options%  -Q  ..\ldtp-jx\*.java
echo.

echo.
pause
