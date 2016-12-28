@REM clean wxWidgets object files for Visual C compiler

@color 0C
@echo off

REM set the wxWidgets folder for compile
::set WXWIN=C:\Programs\wxWidgets-3.0.1_vs2010
::set WXWIN=C:\Programs\wxWidgets-3.0.1_vs2012
::set WXWIN=C:\Programs\wxWidgets-3.1.0_vs2013
set WXWIN=C:\Programs\wxWidgets-3.0.2_vs2015


REM chance to abort
echo.
echo Cleaning VS OBJECT FILES only
echo %WXWIN%
pause
echo.

if not exist "%WXWIN%\build\msw" (
echo Directory does not exist
pause
exit 1
)

REM loop thru vc folders in build\msw
cd "%WXWIN%\build\msw"
for /d  %%v in (vc_*) do (
if exist %%v (
del /s /q  %%v > NUL
if not errorlevel 0 pause
)
)

echo.
echo * * * * * *  end of clean  * * * * * *
pause
