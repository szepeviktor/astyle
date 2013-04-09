@REM formats the astylex Java source code
@echo off

set progdir=C:\Program Files\AStyle
set srcdir1=..\src-j
set srcdir2=..\src-jx


"%progdir%\AStyle"  -A9ck1 -Qz1  --options=none  %srcdir1%\*.java 
"%progdir%\AStyle"  -A9ck1 -Qz1  --options=none  %srcdir2%\*.java 

echo -
echo -
echo * * * *  end of Format Java  * * * *
pause
