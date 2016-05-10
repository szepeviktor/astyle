@REM make example program distribution directories
@echo off

set distdir=..\DistExamples
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
if exist ..\test-data\*.orig  del ..\test-data\*.orig  /q

REM copy astyle-cpp
echo.
echo %distcpp%
if not exist %distcpp%  md  %distcpp%
if exist %distcpp%\doc\*  del %distcpp%\doc\*  /q
if exist %distcpp%\src-c\*  del %distcpp%\src-c\*  /q
if exist %distcpp%\test-data\*  del %distcpp%\test-data\*  /q
xcopy ..\doc\cpp.html  %distcpp%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\aiseered.css  %distcpp%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\styles.css  %distcpp%\doc\  /q
if errorlevel 2 pause
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
if exist %distjava%\doc\*  del %distjava%\doc\*  /q
if exist %distjava%\src-j\*  del %distjava%\src-j\*  /q
if exist %distjava%\test-data\*  del %distjava%\test-data\*  /q
xcopy ..\doc\jni.html  %distjava%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\greenlcd.css  %distjava%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\styles.css  %distjava%\doc\  /q
if errorlevel 2 pause
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
if exist %distobjc%\doc\*  del %distobjc%\doc\*  /q
if exist %distobjc%\src-o\*  del %distobjc%\src-o\*  /q
if exist %distobjc%\test-data\*  del %distobjc%\test-data\*  /q
xcopy ..\doc\objc.html  %distobjc%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\navy.css  %distobjc%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\styles.css  %distobjc%\doc\  /q
if errorlevel 2 pause
xcopy ..\src-o\*.m  %distobjc%\src-o\  /q
if errorlevel 2 pause
xcopy ..\test-data\*  %distobjc%\test-data\  /q
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
xcopy ..\doc\python.html  %distpython%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\manxome.css  %distpython%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\styles.css  %distpython%\doc\  /q
if errorlevel 2 pause
REM copy only the required programs
xcopy ..\src-p\ExampleByte.py  %distpython%\src-p\  /q
if errorlevel 2 pause
:: xcopy ..\src-p\ExampleExe.py  %distpython%\src-p\  /q
:: if errorlevel 2 pause
xcopy ..\src-p\ExampleUnicode.py  %distpython%\src-p\  /q
if errorlevel 2 pause
REM copy the files
xcopy ..\test-data\*  %distpython%\test-data\  /q
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
xcopy ..\doc\sharp.html  %distsharp%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\olive.css  %distsharp%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\styles.css  %distsharp%\doc\  /q
if errorlevel 2 pause
xcopy ..\src-s\*.cs  %distsharp%\src-s\  /q
if errorlevel 2 pause
xcopy ..\test-data\*  %distsharp%\test-data\  /q
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
xcopy ..\doc\sharp2.html  %distsharp2%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\anotherdark.css  %distsharp2%\doc\  /q
if errorlevel 2 pause
xcopy ..\doc\styles.css  %distsharp2%\doc\  /q
if errorlevel 2 pause
xcopy ..\src-s2\*.cs  %distsharp2%\src-s2\  /q
if errorlevel 2 pause
xcopy ..\test-data\*  %distsharp2%\test-data\  /q
if errorlevel 2 pause
"%zippath%"  "a"  "%distsharp2%.zip"  "%distsharp2%\*" > NUL
echo %distsharp2%.zip created
set distsharp2=

echo.
echo.
echo * * * *  end of DistCopy  * * * *
pause
