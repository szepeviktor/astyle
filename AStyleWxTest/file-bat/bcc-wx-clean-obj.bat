@REM clean wxWidgets object files for Embarcadero compiler
@color 0C
@echo off

REM set the wxWidgets folder for compile
:: set WXWIN=C:\Programs\wxWidgets-2.8.12_ec
set WXWIN=C:\Programs\wxWidgets-3.0.2_bcc

REM chance to abort
echo.
echo Cleaning Embarcadero object files only
echo %WXWIN%
pause
echo.

if not exist %WXWIN%\build\msw (
echo Directory does not exist
pause
exit 1
)

REM loop thru bcc folders in build\msw
cd %WXWIN%\build\msw
for /d  %%v in (bcc_*) do (
if exist %%v (
del /s /q  %%v > NUL
if not errorlevel 0 pause
)
)

echo.
echo * * * * * *  end of clean  * * * * * *
pause
