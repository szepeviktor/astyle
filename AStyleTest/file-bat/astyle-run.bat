@echo off

:: set astyle=%PROGRAMFILES%\AStyle\AStyle
:: set astyle=..\..\AStyle\build\vs2010\debug\AStyled
:: set astyle=..\..\AStyle\build\vs2010\bin\AStyle
set astyle=..\..\AStyle\build\vs2013\debug\AStyle

:: call  libCompile.bat  %astyle%
:: "%astyle%"  -!
"%astyle%"  -A5s3xe  c:\users\jimp\projects\testdata\codeblocks\src\src\*.cpp

echo.
pause
