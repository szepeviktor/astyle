@color 0E
@echo off
REM Test that the astyle piping ability has been restored.
REM This works OK on Windows.
REM This may fail if cin is piped to AStyle "cat txt.cpp | ./astyled".
REM But is OK for redirection "./astyled < txt.cpp".

REM Copy all files to the following directory, including astyle.
cd c:\users\jimp
REM app.cpp is in CodeBlocks\src\src
set filein=app.cpp
set fileout=app.astyle.cpp

echo.
if exist "%fileout%"  (
echo deleting output %fileout%
del  "%fileout%"
)

REM B - Match pattern at the Beginning of a line.
REM V - Output lines that do NOT contain a match.
echo use findstr to pipe %filein% to astyle and output %fileout%
findstr  /BV  ")])"  "%filein%"  |  astyle -e  --suffix=none > "%fileout%" 

echo.
echo end of test
pause

