@echo off

cd "%USERPROFILE%/Projects/AStyleTest"

REM Can replace --force with -D_WIN32 to for faster testing.
if not exist "src/AStyleTest_AlignPointer.cpp.dump" (
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
set /a count = %count% - 18
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
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_AlignPointer.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_BracketsCpp1.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_BracketsCpp2.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_BracketsJava.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_BracketsSharp.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_BugFix.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_Format.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_Indent.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_Main.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_MaxCodeLen.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_NEW_OPTIONS.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_ObjC.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_Other.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_Pad.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_StylesCpp1.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_StylesCpp2.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_StylesOther.cpp.dump"
"C:/Program Files/Python 3.5/python.exe"  "%USERPROFILE%/Projects/AStyleTest/file-py/naming.py"  --var=%var% --function=%func% --class=%class%  "src/AStyleTest_Tabs.cpp.dump"

echo.
pause
