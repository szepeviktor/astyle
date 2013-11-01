@color 0E
@echo off
REM Test that the astyle piping ability has been restored.
REM This works OK on Windows.
REM This may fail if cin is piped to AStyle "cat txt.cpp | ./astyled".
REM But is OK for redirection "./astyled < txt.cpp".

REM Copy files to the following directory.
cd c:\users\jimp
REM app.cpp is in CodeBlocks\src\src
set progdir=C:\Users\jimp\Projects\AStyle\build\vs2010\debug
set filein=app.cpp
set pipeout=app.pipe.cpp
set redirout=app.redir.cpp

if exist "%pipeout%"  (
echo deleting output %pipeout%
del  "%pipeout%"
)
if exist "%redirout%"  (
echo deleting output %redirout%
del  "%redirout%"
)

REM B - Match pattern at the Beginning of a line.
REM V - Output lines that do NOT contain a match.
echo pipe test
findstr  /BV  ")])"  "%filein%"  |  "%progdir%\astyled" -eO  --suffix=none > "%pipeout%" 

echo redirection test
"%progdir%\astyled" -eO  --suffix=none  <  "%filein%"  >  "%redirout%" 

echo end of test
pause

