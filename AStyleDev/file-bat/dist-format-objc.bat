@REM formats the AStyleX C++ source code
@echo off

set progdir=C:\Program Files\AStyle
:: set progdir=%USERPROFILE%\Projects\AStyle\build\vs2010\bin
set srcdir1=..\src-o

REM  H - pad-header
REM  U - unpad-paren
REM k1 - align-pointer=type
REM  c - convert-tabs
REM  v - verbose
REM  p - pad-oper
REM  Q - formatted
REM z1 - windows lineends

"%progdir%\AStyle"  -A9HUk1cp  -Qz1  --options=none  %srcdir1%\*.m

echo -
echo -
echo * * * *  end of Format Obj-C  * * * *
pause
