@echo off

cd "%USERPROFILE%/Projects/AStyleTest"

REM Can replace --force with -D_WIN32 to for faster testing.
if not exist "srccon\AStyleTestCon_Console1.cpp.dump" (
echo Creating dump files
"C:/Program Files/Cppcheck/cppcheck.exe"  --dump --force  srccon/ > srccon\dump.txt
del srccon\dump.txt
)

echo.
REM Verify the number of files checked
REM Must manually add any files that are missing to the checks and change the value below.
set count=0
for %%v in (srccon\*.cpp) do set /a count += 1
echo checking %count% files
set /a count = %count% - 5
echo %count% files missing

echo.
REM  naming.py
REM Variables start with lower case OR underscore plus lower case OR AS_ or _AS_ followed by all caps with underline allowed.
REM _CRT_glob is a required name to turn off MinGW automatic file globbing
set var="[a-z].*|_[a-z].*|[AS_|_AS_].[A-Z_]*$|_CRT_glob"
REM Functions names start with lower case.
set func="[a-z].*"
REM Class names start with upper case.
REM eState is an allowed enum exception
set class="[A-Z].*|eState"
echo running naming.py
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "srccon/AStyleTestCon_Console1.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "srccon/AStyleTestCon_Console2.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "srccon/AStyleTestCon_Console3.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "srccon/AStyleTestCon_Main.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "srccon/AStyleTestCon_Print.cpp.dump"

echo.
pause
