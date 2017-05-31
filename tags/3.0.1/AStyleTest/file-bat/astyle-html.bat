@echo off

:: set astyle=%PROGRAMFILES%\AStyle\AStyle
:: set astyle=..\..\AStyle\build\vs2015\debug\AStyled
set astyle=..\..\AStyle\build\vs2015\bin\AStyle

:: call  libCompile.bat  %astyle%
:: "%astyle%"  -!
"%astyle%"  --html="c:\users\jimp\projects\astyle\doc\astyle.html"

echo.
pause
