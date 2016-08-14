@REM formats ALL AStyleDev source code
@echo off

set progdir=C:\Program Files\AStyle
REM override standard options with --style=horstmann  --indent=spaces
set options=--options=..\..\AStyleTest\file-bat\astyle-options.cfg  -A9s

echo Formatting AStyleDev
echo override standard options with --style=horstmann  --indent=spaces
echo.

"%progdir%\AStyle"  %options%  ..\src-c\*.cpp
echo.
"%progdir%\AStyle"  %options%  ..\src-j\*.java
echo.
"%progdir%\AStyle"  %options%  ..\src-o\*.m
echo.
"%progdir%\AStyle"  %options%  ..\src-s\*.cs
echo.
"%progdir%\AStyle"  %options%  ..\src-s2\*.cs
echo.

echo.
pause
