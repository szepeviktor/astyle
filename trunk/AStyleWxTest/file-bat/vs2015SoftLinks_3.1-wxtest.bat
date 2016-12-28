@echo off

REM Make wxWidgets symlinks from Windows 7 to Windows 10.
REM THIS FILE MUST BE RUN FROM WINDOWS 10.
REM THIS FILE MUST BE RUN AN ADMINISTRATOR.
REM the Windows 10 partition must have the volume label WINDOWS10.

echo.

REM check the volume label of this disk
for /f "tokens=6" %%g  in ('vol C:') do set v_vol=%%g
REM set drive letters for Windows 10
if not %v_vol% == WINDOWS10 (
echo This file must be run from Windows 10
echo The volume label must be WINDOWS10
echo.
pause
exit 1
)

REM check for run as an administrator
net session >nul 2>&1
if not %errorLevel% == 0 (
echo THIS FILE MUST BE RUN AS AN ADMINISTRATOR TO UPDATE
echo.
pause
exit 1
)

echo Win32 DLL Debug

if not exist "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug"  md "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxbase31ud_vc_custom.dll"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31ud_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxbase31ud_vc_custom.pdb"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31ud_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_adv_vc_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_adv_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_adv_vc_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_adv_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_aui_vc_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_aui_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_aui_vc_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_aui_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_core_vc_custom.dll" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_core_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_core_vc_custom.pdb" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_core_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_stc_vc_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_stc_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\debug\wxmsw31ud_stc_vc_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_stc_vc_custom.pdb"

echo.
echo Win32 DLL Release

if not exist "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin"  md "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxbase31u_vc_custom.dll"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31u_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxbase31u_vc_custom.pdb"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31u_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_adv_vc_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_adv_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_adv_vc_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_adv_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_aui_vc_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_aui_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_aui_vc_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_aui_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_core_vc_custom.dll" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_core_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_core_vc_custom.pdb" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_core_vc_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_stc_vc_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_stc_vc_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\bin\wxmsw31u_stc_vc_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_stc_vc_custom.pdb"

echo.
echo x64 DLL Debug

if not exist "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug"  md "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxbase31ud_vc_x64_custom.dll"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31ud_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxbase31ud_vc_x64_custom.pdb"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31ud_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_adv_vc_x64_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_adv_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_adv_vc_x64_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_adv_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_aui_vc_x64_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_aui_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_aui_vc_x64_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_aui_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_core_vc_x64_custom.dll" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_core_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_core_vc_x64_custom.pdb" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_core_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_stc_vc_x64_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_stc_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\debug\wxmsw31ud_stc_vc_x64_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_stc_vc_x64_custom.pdb"

echo.
echo x64 DLL Release

if not exist "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin"  md "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxbase31u_vc_x64_custom.dll"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31u_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxbase31u_vc_x64_custom.pdb"     "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31u_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_adv_vc_x64_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_adv_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_adv_vc_x64_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_adv_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_aui_vc_x64_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_aui_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_aui_vc_x64_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_aui_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_core_vc_x64_custom.dll" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_core_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_core_vc_x64_custom.pdb" "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_core_vc_x64_custom.pdb"

mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_stc_vc_x64_custom.dll"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_stc_vc_x64_custom.dll"
mklink  "F:\Users\%USERNAME%\Projects\AStyleWxTest\build\vs2015_3.1\x64\bin\wxmsw31u_stc_vc_x64_custom.pdb"  "C:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_stc_vc_x64_custom.pdb"

echo.

REM check for run as an administrator
net session >nul 2>&1
if not %errorLevel% == 0 (
echo THIS FILE MUST BE RUN AS AN ADMINISTRATOR TO UPDATE
echo.
)

pause
