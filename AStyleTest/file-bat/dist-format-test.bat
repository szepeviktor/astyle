@REM formats the astyletest source code in the test directory
@echo off

set PATH=PATH;"C:\Program Files\AStyle
set prog=AStyle

REM  T - indent=force-tab
REM  H - pad-header
REM  C - indent-classes
REM  O - keep-one-line-blocks
REM k1 - align-pointer=type
REM W3 - align-reference=name
REM M50- max-instatement-indent=50
REM  v - verbose
REM  p - pad-oper
REM  Q - formatted
REM  w - indent-preproc-define
REM xn - attach-namespaces
REM xl - attach inlines
REM xW - indent-preproc-block
REM z1 - windows lineends

set options=  -A1xnTpHCOwxWk1  -M50  -Qz1  --options=none

echo Formatting AStyleTest
echo options %options%
echo.

%prog%  %options%  ..\src\*.cpp
echo.
%prog%  %options%  ..\src\*.h
echo.
%prog%  %options%  ..\srccon\*.cpp
echo.
%prog%  %options%  ..\srccon\*.h
echo.
%prog%  %options%  ..\srci18n\*.cpp
echo.
%prog%  %options%  ..\srclib\*.cpp
echo.
%prog%  %options%  ..\srclib\*.h
echo.
REM override force-tabs with tabs
%prog%  %options%  -t  ..\srcx\*.cpp
echo.
%prog%  %options%  -t  ..\srcx\*.h

echo.
echo * * * *  end of format  * * * *
pause
