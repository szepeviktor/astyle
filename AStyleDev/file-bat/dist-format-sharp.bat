@REM formats the astylex Java source code
@echo off

set progdir=C:\Program Files (x86)\AStyle
set srcdir1=..\src-s
set srcdir2=..\src-sx


"%progdir%\AStyle"  -A9ck1 -Qz1  --options=none  %srcdir1%\*.cs
"%progdir%\AStyle"  -A9ck1 -Qz1  --options=none  %srcdir2%\*.cs 

echo -
echo -
echo * * * *  end of Format Sharp  * * * *
pause
