@echo off

set testdata=..\..\TestData

:: set astyle=..\..\AStyle\build\cb-borland\bin\AStyle
:: set astyle=..\..\AStyle\build\cb-dmars\bin\AStyle
:: set astyle=..\..\AStyle\build\cb-mingw\bin\AStyle
:: set astyle=..\..\AStyle\build\vs2003\bin\AStyle
:: set astyle=..\..\AStyle\build\vs2005\bin\AStyle
set astyle=..\..\AStyle\build\vs2010\bin\AStyle

set excludes=

:: set options= -vRQ
REM indent-brackets (B), add-brackets (j), break-blocks=all (F), align-pointer=type (k1)
set options= -vR
REM indent-blocks (G), add-one-line-brackets (J), break-blocks (f), align-pointer=middle (k2)
:: set options= -CSKGNLwM50m10yeJoOcfpPHUxEk2 -vRQ


call  libCompile.bat  %astyle%
echo Formatting GWorkspace %options%

%astyle%  %options%  %excludes%  "%testdata%\GWorkspace\*.m" > testm.txt
%astyle%  %options%  %excludes%  "%testdata%\GWorkspace\*.h" > testh.txt


echo -
pause
