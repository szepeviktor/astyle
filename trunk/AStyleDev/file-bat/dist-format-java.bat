@REM formats the astylex Java source code
@echo off

set progdir=C:\Program Files\AStyle
set srcdir1=..\src-j

REM  H - pad-header
REM  O - keep-one-line-blocks
REM  U - unpad-paren
REM k1 - align-pointer=type
REM  c - convert-tabs
REM  v - verbose
REM  p - pad-oper
REM  Q - formatted
REM z1 - windows lineends

"%progdir%\AStyle"  -A9HOUk1cp -Qz1  --options=none  %srcdir1%\*.java

echo -
echo -
echo * * * *  end of Format Java  * * * *
pause
