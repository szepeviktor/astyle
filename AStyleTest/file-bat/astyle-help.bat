@echo off

set astyle=%PROGRAMFILES%\AStyle\AStyle
:: set astyle=..\..\AStyle\build\vs2013\x64\debug\AStyled
:: set astyle=..\..\AStyle\build\vs2013\bin\AStyle

:: call  libCompile.bat  %astyle%

"%astyle%"  -h


echo.
pause
