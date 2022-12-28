@REM clean ALL wxWidgets files for MinGW compiler
@color 0C
@echo off

REM set the wxWidgets folder for compile
:: set WXWIN=C:\Programs\wxWidgets-2.8.12_mingw
set WXWIN=C:\Programs\wxWidgets-3.0.2_mingw

REM chance to abort
echo.
echo Cleaning ALL MinGW files INCLUDING libraries
echo %WXWIN%
pause
echo.

if not exist %WXWIN%\build\msw (
echo Directory does not exist
pause
exit 1
)

REM loop thru gcc folders in build\msw
cd %WXWIN%\build\msw
for /d  %%v in (gcc_*) do (
if exist %%v (
del /s /q  %%v > NUL
if not errorlevel 0 pause
)
)

REM loop thru gcc folders in lib
cd %WXWIN%\lib
for /d  %%v in (gcc_*) do (
if exist %%v (
del /s /q  %%v > NUL
if not errorlevel 0 pause
)
)

echo.
echo * * * * * *  end of clean  * * * * * *
pause
