@REM make example program distribution directories
@echo off

set distdir=..\..\DistExamples
set distcpp=example-cpp
set distjava=example-java
set distobjc=example-objc
set distpython=example-python
set distsharp=example-sharp
set distsharp2=example-sharp2
set zippath=%PROGRAMFILES%\7-Zip\7z.exe

REM create the distribution directory
echo create %distdir%
if not exist %distdir%  md  %distdir%
cd %distdir%

REM remove orig files in test-data
if exist ..\AStyleDev\test-data\*.orig  del ..\AStyleDev\test-data\*.orig  /q

REM copy astyle-cpp
echo.
echo %distcpp%
if not exist %distcpp%  md  %distcpp%
if exist %distcpp%\doc\*  del %distcpp%\doc\*  /q
if exist %distcpp%\src-c\*  del %distcpp%\src-c\*  /q
if exist %distcpp%\test-data\*  del %distcpp%\test-data\*  /q
xcopy ..\AStyleDev\doc\cpp.html  %distcpp%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\aiseered.css  %distcpp%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\styles.css  %distcpp%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-c\*.cpp  %distcpp%\src-c\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\test-data\*    %distcpp%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distcpp%.zip"  "%distcpp%\*" > NUL
echo %distcpp%.zip created
set distcpp=

REM copy astyle-java
echo.
echo %distjava%
if not exist %distjava%  md  %distjava%
if exist %distjava%\doc\*  del %distjava%\doc\*  /q
if exist %distjava%\src-j\*  del %distjava%\src-j\*  /q
if exist %distjava%\test-data\*  del %distjava%\test-data\*  /q
xcopy ..\AStyleDev\doc\jni.html  %distjava%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\greenlcd.css  %distjava%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\styles.css  %distjava%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-j\*.java  %distjava%\src-j\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\test-data\*  %distjava%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distjava%.zip"  "%distjava%\*" > NUL
echo %distjava%.zip created
set distjava=

REM copy astyle-objc
echo.
echo %distobjc%
if not exist %distobjc%  md  %distobjc%
if exist %distobjc%\doc\*  del %distobjc%\doc\*  /q
if exist %distobjc%\src-o\*  del %distobjc%\src-o\*  /q
if exist %distobjc%\test-data\*  del %distobjc%\test-data\*  /q
xcopy ..\AStyleDev\doc\objc.html  %distobjc%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\navy.css  %distobjc%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\styles.css  %distobjc%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-o\*.m  %distobjc%\src-o\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\test-data\*  %distobjc%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distobjc%.zip"  "%distobjc%\*" > NUL
echo %distobjc%.zip created
set distobjc=

REM copy astyle-python
echo.
echo %distpython%
if not exist %distpython%  md  %distpython%
if exist %distpython%\doc\*  del %distpython%\doc\*  /q
if exist %distpython%\src-p\*  del %distpython%\src-p\*  /q
if exist %distpython%\test-data\*  del %distpython%\test-data\*  /q
xcopy ..\AStyleDev\doc\python.html  %distpython%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\manxome.css  %distpython%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\styles.css  %distpython%\doc\  /q
if errorlevel 2 pause
REM copy only the required programs
xcopy ..\AStyleDev\src-p\ExampleByte.py  %distpython%\src-p\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-p\ExampleExe.py  %distpython%\src-p\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-p\ExampleUnicode.py  %distpython%\src-p\  /q
if errorlevel 2 pause
REM copy the files
xcopy ..\AStyleDev\test-data\*  %distpython%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distpython%.zip"  "%distpython%\*" > NUL
echo %distpython%.zip created
set distpython=

REM copy astyle-sharp
echo.
echo %distsharp%
if not exist %distsharp%  md  %distsharp%
if exist %distsharp%\doc\*  del %distsharp%\doc\*  /q
if exist %distsharp%\src-s\*  del %distsharp%\src-s\*  /q
if exist %distsharp%\test-data\*  del %distsharp%\test-data\*  /q
xcopy ..\AStyleDev\doc\sharp.html  %distsharp%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\olive.css  %distsharp%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\styles.css  %distsharp%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-s\*.cs  %distsharp%\src-s\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\test-data\*  %distsharp%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distsharp%.zip"  "%distsharp%\*" > NUL
echo %distsharp%.zip created
set distsharp=

REM copy astyle-sharp2
echo.
echo %distsharp2%
if not exist %distsharp2%  md  %distsharp2%
if exist %distsharp2%\doc\*  del %distsharp2%\doc\*  /q
if exist %distsharp2%\src-s2\*  del %distsharp2%\src-s2\*  /q
if exist %distsharp2%\test-data\*  del %distsharp2%\test-data\*  /q
xcopy ..\AStyleDev\doc\sharp2.html  %distsharp2%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\andes.css  %distsharp2%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\doc\styles.css  %distsharp2%\doc\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\src-s2\*.cs  %distsharp2%\src-s2\  /q
if errorlevel 2 pause
xcopy ..\AStyleDev\test-data\*  %distsharp2%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distsharp2%.zip"  "%distsharp2%\*" > NUL
echo %distsharp2%.zip created
set distsharp2=

echo.
echo.
echo * * * *  end of DistCopy  * * * *
pause
