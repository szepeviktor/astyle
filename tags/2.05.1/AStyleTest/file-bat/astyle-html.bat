@echo off

:: set astyle=%PROGRAMFILES%\AStyle\AStyle
set astyle=..\..\AStyle\build\vs2010\debug\AStyled
:: set astyle=..\..\AStyle\build\vs2010\bin\AStyle

:: call  libCompile.bat  %astyle%
:: "%astyle%"  -!
"%astyle%"  --html="c:\users\jimp\projects\astyle\doc\astyle.html"

echo.
pause
