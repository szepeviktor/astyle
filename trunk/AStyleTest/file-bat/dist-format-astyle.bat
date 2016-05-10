@REM formats the astyle source code
@echo off

set PATH=PATH;"C:\Program Files\AStyle
set prog=AStyle.exe

REM  t - indent=tab
REM xn - attach-namespaces
REM  S - indent-switches
REM xW - indent-preproc-block
REM  w - indent-preproc-define
REM  p - pad-oper
REM  H - pad-header
REM k1 - align-pointer=type
REM  O - keep-one-line-blocks

REM M60- max-instatement-indent=60

REM  Q - formatted (print)
REM z1 - windows lineends


REM OLD set options= -A1xntpHSOwxWk1 -M60  -Qz1 --options=none
set options= -A1txnSxWwpHk1O  -M60  -Qz1 --options=none

echo Formatting AStyle
echo options %options%
echo.

%prog%  %options%  ..\..\AStyle\src\*.cpp
echo.
%prog%  %options%  ..\..\AStyle\src\*.h
echo.

echo.
echo * * * *  end of format  * * * *
pause
