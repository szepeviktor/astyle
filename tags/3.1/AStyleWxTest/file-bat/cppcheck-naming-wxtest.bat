@echo off

cd "%USERPROFILE%/Projects/AStyleWxTest"

REM Can replace --force with -D_WIN32 to for faster testing.
if not exist "src/AStyleDisplay_Test.cpp.dump" (
echo Creating dump files
"C:/Program Files/Cppcheck/cppcheck.exe"  --dump --force  src/ > src\dump.txt
del src\dump.txt
)

echo.
REM Verify the number of files checked
REM Must manually add any files that are missing to the checks and change the value below.
set count=0
for %%v in (src\*.cpp) do set /a count += 1
echo checking %count% files
set /a count = %count% - 5
echo %count% files missing

echo.
REM  naming.py
REM Variables start with lower case OR underscore plus lower case OR all caps with underline allowed.
REM BOMSize is an allowed exception
REM ErrorHandler and MemoryAlloc are function pointers.
set var="[a-z].*|_[a-z].*|.[A-Z_]*$|BOMSize|ErrorHandler|MemoryAlloc"
REM Functions names start with upper case.
REM Exceptions are getters, setters and main.
set func="[A-Z].*|get|set|main"
REM Class names start with upper case.
set class="[A-Z].*"
echo running naming.py
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleDisplay_Test.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleFormat_Test.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleIFace_Test.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/Config_Test.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/Main_Test.cpp.dump"

echo.
pause
