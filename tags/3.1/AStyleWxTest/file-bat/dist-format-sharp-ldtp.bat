@REM formats the ldtpx C# source code
@echo off

set progdir=C:\Program Files\AStyle
set options=--options=..\..\AStyle\file\astyle.ini

echo.

"%progdir%\AStyle"  %options%  -Q  ..\ldtp-s\*.cs
echo.
"%progdir%\AStyle"  %options%  -Q  ..\ldtp-sx\*.cs
echo.

echo.
pause
