@REM clean all wxWidgets STC files for Visual C compiler

@color 0C
@echo off

REM set the wxWidgets folder for compile
set WXWIN=C:\Programs\wxWidgets-2.8.12_vs2010

REM chance to abort
echo.
echo Cleaning ALL VS STC files INCLUDING executables
echo %WXWIN%
pause
echo.

if not exist "%WXWIN%\contrib\build\stc" (
echo Directory does not exist
pause
exit 1
)

REM loop thru gcc folders in contrib\build\stc
cd "%WXWIN%\contrib\build\stc"
for /d  %%v in (vc_*) do (
if exist %%v (
del /s /q  %%v >  NUL
if not errorlevel 0 pause
)
)

REM loop thru gcc folders in lib
cd "%WXWIN%\lib"
for /d  %%v in (vc_*) do (
if exist %%v (
del /s /q  %%v\*_stc* >  NUL
if not errorlevel 0 pause
)
)

echo.
echo * * * * * *  end of clean  * * * * * *
pause
