@REM formats the astylex Java source code
@echo off

set progdir=C:\Program Files\AStyle
set srcdir1=..\src-j
set srcdir2=..\src-jx

REM  H - pad-header
REM  U - unpad-paren
REM k1 - align-pointer=type
REM  c - convert-tabs
REM  v - verbose
REM  p - pad-oper
REM  Q - formatted
REM z1 - windows lineends

"%progdir%\AStyle"  -A9HUk1c -Qz1  --options=none  %srcdir1%\*.java 
"%progdir%\AStyle"  -A9HUk1c -Qz1  --options=none  %srcdir2%\*.java 

echo -
echo -
echo * * * *  end of Format Java  * * * *
pause
