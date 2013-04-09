@REM formats the AStyleX C++ source code
@echo off

set progdir=C:\Program Files\AStyle
set srcdir1=..\src-c
set srcdir2=..\src-cx


"%progdir%\AStyle"  -A9ck1  -Qz1  --options=none  %srcdir1%\*.cpp
"%progdir%\AStyle"  -A9ck1  -Qz1  --options=none  %srcdir2%\*.cpp  %srcdir2%\*.h

echo -
echo -
echo * * * *  end of Format Cpp  * * * *
pause
