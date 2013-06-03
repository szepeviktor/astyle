@REM make example program distribution directories
@echo off

set distdir=..\examples
set distcpp=example-cpp_2.04
set distjava=example-java_2.04
set distsharp=example-sharp_2.04
set distpython=examples-python_2.04
set zippath=%PROGRAMFILES%\7-Zip\7z.exe

REM create the distribution directory
echo create %distdir%
if not exist %distdir%  md  %distdir%
cd %distdir%

REM copy astyle-cpp
echo -
if not exist %distcpp%  md  %distcpp%
if exist %distcpp%\src-c\*  del %distcpp%\src-c\*  /q
if exist %distcpp%\test-c\*  del %distcpp%\test-c\*  /q
xcopy ..\src-c\*.cpp  %distcpp%\src-c\  /q
if errorlevel 2 pause
xcopy ..\test-c\*.cpp  %distcpp%\test-c\  /q
if errorlevel 2 pause
xcopy ..\test-c\*.h    %distcpp%\test-c\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distcpp%.zip"  "%distcpp%\*" > NUL
echo %distcpp%.zip created
set distcpp=

REM copy astyle-java
echo -
if not exist %distjava%  md  %distjava%
if exist %distjava%\src-j\*  del %distjava%\src-j\*  /q
if exist %distjava%\test-j\*  del %distjava%\test-j\*  /q
xcopy ..\src-j\*.java  %distjava%\src-j\  /q
if errorlevel 2 pause
xcopy ..\test-j\*.java  %distjava%\test-j\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distjava%.zip"  "%distjava%\*" > NUL
echo %distjava%.zip created
set distjava=

REM copy astyle-sharp
echo -
if not exist %distsharp%  md  %distsharp%
if exist %distsharp%\src-s\*  del %distsharp%\src-s\*  /q
if exist %distsharp%\test-s\*  del %distsharp%\test-s\*  /q
xcopy ..\src-s\*.cs  %distsharp%\src-s\  /q
if errorlevel 2 pause
xcopy ..\test-s\*.cs  %distsharp%\test-s\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distsharp%.zip"  "%distsharp%\*" > NUL
echo %distsharp%.zip created
set distsharp=

REM copy astyle-python
echo -
if not exist %distpython%  md  %distpython%
if exist %distpython%\src-py\*  del %distpython%\src-py\*  /q
if exist %distpython%\test-c\*  del %distpython%\test-c\*  /q
REM copy only the required programs
xcopy ..\src-py\ExampleByte.py  %distpython%\src-py\  /q
if errorlevel 2 pause
xcopy ..\src-py\ExampleExe.py  %distpython%\src-py\  /q
if errorlevel 2 pause
xcopy ..\src-py\ExampleUnicode.py  %distpython%\src-py\  /q
if errorlevel 2 pause
REM copy the files
xcopy ..\test-c\*.cpp  %distpython%\test-c\  /q
if errorlevel 2 pause
xcopy ..\test-c\*.h    %distpython%\test-c\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distpython%.zip"  "%distpython%\*" > NUL
echo %distpython%.zip created
set distpython=

echo -
echo -
echo * * * *  end of DistCopy  * * * *
pause
