@REM run whatstyle for selected files
@echo off

REM astyle must be in the same directory as whatstyle.py

set pydir=C:\Program Files\Python 3.5
set file=c:/users/jimp/projects/astyle/src/astyle_main.cpp
set options=--formatter astyle --mode resilient

echo.
cd "c:/users/jimp/projects/whatstyle/whatstyle-master
"%pydir%\python"  whatstyle.py  %options%  %file%


echo.
echo * * * *   end of whatstyle   * * * *
pause
