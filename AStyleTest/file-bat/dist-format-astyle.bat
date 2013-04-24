@REM formats the astyle source code
@echo off

set PATH=PATH;"C:\Program Files\AStyle
set prog=AStyle

REM  t - indent=tab
REM  H - pad-header
REM  C - indent-classes
REM  O - keep-one-line-blocks
REM k1 - align-pointer=type
REM W3 - align-reference=name
REM M50- max-instatement-indent=50
REM  v - verbose
REM  p - pad-oper
REM  Q - formatted
REM  w - indent-preprocessor
REM xn - indent-namespaces
REM xi - indent inlines
REM z1 - windows lineends

set options=  -A1xnxitHCOwk1W3  -M50  -Qz1  --options=none

echo Formatting AStyle
echo options %options%  
echo -

%prog%  %options%  ..\..\AStyle\src\*.cpp  ..\..\AStyle\src\*.h 


echo -
echo * * * *  end of format  * * * *
pause
