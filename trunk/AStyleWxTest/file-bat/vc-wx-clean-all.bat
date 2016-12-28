@REM clean all wxWidgets files for Visual C compiler

@color 0C
@echo off

REM set the wxWidgets folder for compile
set WXWIN=C:\Programs\wxWidgets-2.9.4_vs2010

REM chance to abort
echo.
echo Cleaning VS files INCLUDING executables
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

REM loop thru vc folders in lib
cd "%WXWIN%\lib"
for /d  %%v in (vc_*) do (
if exist %%v (
del /s /q  %%v > NUL
if not errorlevel 0 pause
)
)

echo.
echo * * * * * *  end of clean  * * * * * *
pause
