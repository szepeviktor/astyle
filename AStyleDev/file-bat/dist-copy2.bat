@REM make example2 program distribution directories
@echo off

set distcpp=..\examples2\example2-cpp_2.03
set distjava=..\examples2\example2-java_2.03
set distsharp=..\examples2\example2-sharp_2.03

REM copy astyle-cpp2
echo -
if not exist %distcpp%  md  %distcpp%
if exist %distcpp%\src-cx\*  del %distcpp%\src-cx\*  /q
if exist %distcpp%\test-c\*  del %distcpp%\test-c\*  /q
xcopy ..\src-cx\*.cpp  %distcpp%\src-cx\  /q
if errorlevel 2 pause
xcopy ..\src-cx\*.h    %distcpp%\src-cx\  /q
if errorlevel 2 pause
xcopy ..\test-c\*.cpp  %distcpp%\test-c\  /q
if errorlevel 2 pause
xcopy ..\test-c\*.h    %distcpp%\test-c\  /q
if errorlevel 2 pause
echo %distcpp:~3% copied
set distcpp=

REM copy astyle-java2
echo -
if not exist %distjava%  md  %distjava%
if exist %distjava%\src-jx\*  del %distjava%\src-jx\*  /q
if exist %distjava%\test-j\*  del %distjava%\test-j\*  /q
xcopy ..\src-jx\*.java  %distjava%\src-jx\  /q
if errorlevel 2 pause
xcopy ..\test-j\*.java  %distjava%\test-j\  /q
if errorlevel 2 pause
echo %distjava:~3% copied
set distjava=

REM copy astyle-sharp2
echo -
if not exist %distsharp%  md  %distsharp%
if exist %distsharp%\src-sx\*  del %distsharp%\src-sx\*  /q
if exist %distsharp%\test-s\*  del %distsharp%\test-s\*  /q
xcopy ..\src-sx\*.cs  %distsharp%\src-sx\  /q
if errorlevel 2 pause
xcopy ..\test-s\*.cs  %distsharp%\test-s\  /q
if errorlevel 2 pause
echo %distsharp:~3% copied
set distsharp=

echo -
echo -
echo * * * *  end of DistCopy2  * * * *
pause
