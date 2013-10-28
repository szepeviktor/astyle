@REM make example program distribution directories
@echo off

set distdir=..\examples
set distcpp=example-cpp_2.04
set distjava=example-java_2.04
set distobjc=example-objc_2.04
set distsharp=example-sharp_2.04
set distpython=example-python_2.04
set zippath=%PROGRAMFILES%\7-Zip\7z.exe

REM create the distribution directory
echo create %distdir%
if not exist %distdir%  md  %distdir%
cd %distdir%

REM copy astyle-cpp
echo.
echo %distcpp%
if not exist %distcpp%  md  %distcpp%
if exist %distcpp%\src-c\*  del %distcpp%\src-c\*  /q
if exist %distcpp%\test-data\*  del %distcpp%\test-data\*  /q
xcopy ..\src-c\*.cpp  %distcpp%\src-c\  /q
if errorlevel 2 pause
xcopy ..\test-data\*    %distcpp%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distcpp%.zip"  "%distcpp%\*" > NUL
echo %distcpp%.zip created
set distcpp=

REM copy astyle-java
echo.
echo %distjava%
if not exist %distjava%  md  %distjava%
if exist %distjava%\src-j\*  del %distjava%\src-j\*  /q
if exist %distjava%\test-data\*  del %distjava%\test-data\*  /q
xcopy ..\src-j\*.java  %distjava%\src-j\  /q
if errorlevel 2 pause
xcopy ..\test-data\*  %distjava%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distjava%.zip"  "%distjava%\*" > NUL
echo %distjava%.zip created
set distjava=

REM copy astyle-objc
echo.
echo %distobjc%
if not exist %distobjc%  md  %distobjc%
if exist %distobjc%\src-o\*  del %distobjc%\src-o\*  /q
if exist %distobjc%\test-data\*  del %distobjc%\test-data\*  /q
xcopy ..\src-o\*.m  %distobjc%\src-o\  /q
if errorlevel 2 pause
xcopy ..\test-data\*  %distobjc%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distobjc%.zip"  "%distobjc%\*" > NUL
echo %distobjc%.zip created
set distobjc=

REM copy astyle-sharp
echo.
echo %distsharp%
if not exist %distsharp%  md  %distsharp%
if exist %distsharp%\src-s\*  del %distsharp%\src-s\*  /q
if exist %distsharp%\test-data\*  del %distsharp%\test-data\*  /q
xcopy ..\src-s\*.cs  %distsharp%\src-s\  /q
if errorlevel 2 pause
xcopy ..\test-data\*  %distsharp%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distsharp%.zip"  "%distsharp%\*" > NUL
echo %distsharp%.zip created
set distsharp=

REM copy astyle-python
echo.
echo %distpython%
if not exist %distpython%  md  %distpython%
if exist %distpython%\src-py\*  del %distpython%\src-py\*  /q
if exist %distpython%\test-data\*  del %distpython%\test-data\*  /q
REM copy only the required programs
xcopy ..\src-py\ExampleByte.py  %distpython%\src-py\  /q
if errorlevel 2 pause
xcopy ..\src-py\ExampleExe.py  %distpython%\src-py\  /q
if errorlevel 2 pause
xcopy ..\src-py\ExampleUnicode.py  %distpython%\src-py\  /q
if errorlevel 2 pause
REM copy the files
xcopy ..\test-data\*  %distpython%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distpython%.zip"  "%distpython%\*" > NUL
echo %distpython%.zip created
set distpython=

echo.
echo.
echo * * * *  end of DistCopy  * * * *
pause
