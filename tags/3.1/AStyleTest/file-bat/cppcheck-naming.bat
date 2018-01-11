@echo off

cd "%USERPROFILE%/Projects/AStyle"

REM Can replace --force with -D_WIN32 to for faster testing.
if not exist "src/astyle_main.cpp.dump" (
echo Creating dump files
"C:/Program Files/Cppcheck/cppcheck.exe"  --dump --force  src/ > src\dump.txt
del src\dump.txt
) else (
echo Using existing dump files
)

echo.
REM Verify the number of files checked
REM Must manually add any files that are missing to the checks and change the value below.
set count=0
for %%v in (src\*.cpp) do set /a count += 1
echo checking %count% files
set /a count = %count% - 6
echo %count% files missing

echo.
REM  naming.py
REM Variables start with lower case OR underscore plus lower case OR AS_ or _AS_ followed by all caps with underline allowed.
REM _CRT_glob is a required name to turn off MinGW automatic file globbing
set var="[a-z].*|_[a-z].*|[AS_|_AS_].[A-Z_]*$|_CRT_glob"
REM Functions names start with lower case.
REM The others are allowed DLL entry-point exceptions.
set func="[a-z].*|AStyleMain|AStyleGetVersion|Java_AStyleInterface"
REM Class names start with upper case.
REM eState is an allowed enum exception
set class="[A-Z].*|eState"
echo running naming.py
echo.
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/ASBeautifier.cpp.dump"
echo.
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/ASEnhancer.cpp.dump"
echo.
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/ASFormatter.cpp.dump"
echo.
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/ASLocalizer.cpp.dump"
echo.
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/ASResource.cpp.dump"
echo.
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/astyle_main.cpp.dump"

REM echo.
REM cert.py
REM echo running cert.py
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/cert.py"  "src/ASBeautifier.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/cert.py"  "src/ASEnhancer.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/cert.py"  "src/ASFormatter.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/cert.py"  "src/ASLocalizer.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/cert.py"  "src/ASResource.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/cert.py"  "src/astyle_main.cpp.dump"

REM echo.
REM threadsafety.py
REM echo running threadsafety.py
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/threadsafety.py"  "src/ASBeautifier.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/threadsafety.py"  "src/ASEnhancer.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/threadsafety.py"  "src/ASFormatter.cpp.dump"
REM  "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/threadsafety.py"  "src/ASLocalizer.cpp.dump"
REM "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/threadsafety.py"  "src/ASResource.cpp.dump"
REM "C:/Program Files/Python 3.5/python.exe"  "C:/Program Files/Cppcheck/addons/threadsafety.py"  "src/astyle_main.cpp.dump"

echo.
pause
