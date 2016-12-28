@echo off
REM Run gcov to print the coverage report
REM AStyleWxTestc must be run to create the *.gcno files

REM change the following to the file to be printed
set gcovfile=AStyleIFace
set mingwdir=C:\Programs\MinGW\bin

cd  ..\build\cb-mingw\objc\AStyleWx\src

REM check for the graph file created by the compile
if not exist *.gcno  (
echo Must compile AStyleWxTestc to create the .gcno graph files!
pause
exit 100
)

REM check for the data file created by running the program
if not exist *.gcda  (
echo Must run AStyleWxTestc to create the .gcda data files!
pause
exit 100
)

REM use the source file name to print the report
"%mingwdir%\gcov"  %gcovfile%

REM open the coverage file in SciTE
"C:\Program Files (x86)\SciTE\SciTE"  %USERPROFILE%\Projects\AStyleWx\src\%gcovfile%.cpp.gcov


echo -
echo end of gcov
echo -
pause
