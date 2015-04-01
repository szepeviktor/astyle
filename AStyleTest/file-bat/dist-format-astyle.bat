@REM formats the astyle source code
@echo off

set PATH=PATH;"C:\Program Files\AStyle
set prog=AStyle.exe

REM  t - indent=tab
REM  H - pad-header
REM  C - indent-classes
REM  O - keep-one-line-blocks
REM k1 - align-pointer=type
REM W3 - align-reference=name
REM M60- max-instatement-indent=60
REM  v - verbose
REM  p - pad-oper
REM  Q - formatted
REM  w - indent-preproc-define
REM xn - attach-namespaces
REM xl - attach inlines
REM xW - indent-preproc-block
REM z1 - windows lineends

REM OLD options=  -A1xnxltpHCOwxWk1W3  -M60  -Qz1  --options=none
set options= -A1xntpHSOwxWk1 -M60  -Qz1 --options=none

echo Formatting AStyle
echo options %options%
echo.

%prog%  %options%  ..\..\AStyle\src\*.cpp  ..\..\AStyle\src\*.h


echo.
echo * * * *  end of format  * * * *
pause
