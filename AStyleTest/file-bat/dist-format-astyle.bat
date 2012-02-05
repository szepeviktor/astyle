@REM formats the astyle source code
@echo off

set PATH=PATH;"C:\Program Files (x86)\AStyle
set prog=AStyle

REM  t - indent=tab
REM  H - pad-header
REM  C - indent-classes
REM  O - keep-one-line-blocks
REM k1 - align-pointer=type
REM M50- max-instatement-indent=50
REM  v - verbose
REM  Q - formatted
REM z1 - windows lineends

set options=  -A1tHCOk1  -M50  -Qz1  --options=none
set optionsh= -A3tHCOk1  -M50  -Qz1  --options=none

echo Formatting AStyle
echo source %options%  
echo headers%optionsh%
echo -

%prog%  %options%  ..\..\AStyle\src\*.cpp
echo -
%prog%  %optionsh%  ..\..\AStyle\src\*.h 


echo -
echo * * * *  end of format  * * * *
pause
