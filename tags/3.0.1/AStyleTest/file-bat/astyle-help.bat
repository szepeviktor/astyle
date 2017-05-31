@echo off

::set astyle=%PROGRAMFILES%\AStyle\AStyle
set astyle=..\..\AStyle\build\vs2015\debug\AStyled

:: call  libCompile.bat  %astyle%

"%astyle%"  -h


echo.
pause
