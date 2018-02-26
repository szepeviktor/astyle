@REM formats ALL AStyleDev source code
@echo off

set progdir=C:\Program Files\AStyle
REM override standard options with --style=horstmann  --indent=spaces
set options=--options=..\..\AStyle\file\astyle.ini  -A9s

echo Formatting AStyleDev
echo override standard options with --style=horstmann  --indent=spaces
echo.

"%progdir%\AStyle"  %options%  -Q  ..\src-c\*.cpp
echo.
"%progdir%\AStyle"  %options%  -Q  ..\src-j\*.java
echo.
"%progdir%\AStyle"  %options%  -Q  ..\src-o\*.m
echo.
"%progdir%\AStyle"  %options%  -Q  ..\src-s\*.cs
echo.
"%progdir%\AStyle"  %options%  -Q  ..\src-s2\*.cs
echo.

echo.
pause
