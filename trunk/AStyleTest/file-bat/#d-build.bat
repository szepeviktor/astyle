@echo off

REM build SharpDevelop using the releasebuild.bat file

REM set directory
set testdata=..\..\TestDataSys\SharpDevelop3"

cd   "%testdata%"

REM if exist build  (
REM echo deleting build files
REM del  /s /q  build  > NUL
REM )

call releasebuild.bat

echo -
pause
