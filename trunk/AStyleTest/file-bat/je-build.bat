@echo off

REM build jEdit using ant

REM build.properties.sample must be modified to
REM build.dir=build and dist.dir=dist (not used)
REM and saved as build.properties

REM set directory of build.properties and build.xml
set testdata=..\..\TestDataSys\jEdit3

REM set variables for ant
set ANT_HOME=%PROGRAMFILES(x86)%\Java\apache-ant-1.9.4
set JAVA_HOME=%PROGRAMFILES(x86)%\Java\jdk1.7.0_67
set PATH=%PATH%;%ANT_HOME%\bin

if not exist "%testdata%" (
echo no directory "%testdata%"
pause
exit
)

cd   "%testdata%"

if exist build  (
echo deleting build files
del  /s /q  build  > NUL
)

REM must start a separate process so the window does not close at EOJ
echo starting build in a separate process
start  ant  build

echo -
pause
