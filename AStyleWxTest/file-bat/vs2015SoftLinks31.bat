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

echo vs2015 Win32 DLL Debug

if not exist "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug"  md "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxbase31ud_vc_custom.dll"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31ud_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxbase31ud_vc_custom.pdb"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31ud_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_adv_vc_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_adv_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_adv_vc_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_adv_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_aui_vc_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_aui_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_aui_vc_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_aui_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_core_vc_custom.dll" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_core_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_core_vc_custom.pdb" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_core_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_stc_vc_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_stc_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\debug\wxmsw31ud_stc_vc_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31ud_stc_vc_custom.pdb"

echo.
echo vs2015 Win32 DLL Release

if not exist "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin"  md "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxbase31u_vc_custom.dll"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31u_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxbase31u_vc_custom.pdb"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxbase31u_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_adv_vc_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_adv_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_adv_vc_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_adv_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_aui_vc_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_aui_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_aui_vc_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_aui_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_core_vc_custom.dll" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_core_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_core_vc_custom.pdb" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_core_vc_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_stc_vc_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_stc_vc_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\bin\wxmsw31u_stc_vc_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_dll\wxmsw31u_stc_vc_custom.pdb"

echo.
echo vs2015 x64 DLL Debug

if not exist "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug"  md "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxbase31ud_vc_x64_custom.dll"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31ud_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxbase31ud_vc_x64_custom.pdb"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31ud_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_adv_vc_x64_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_adv_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_adv_vc_x64_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_adv_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_aui_vc_x64_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_aui_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_aui_vc_x64_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_aui_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_core_vc_x64_custom.dll" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_core_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_core_vc_x64_custom.pdb" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_core_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_stc_vc_x64_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_stc_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\debug\wxmsw31ud_stc_vc_x64_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31ud_stc_vc_x64_custom.pdb"

echo.
echo vs2015 x64 DLL Release

if not exist "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin"  md "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxbase31u_vc_x64_custom.dll"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31u_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxbase31u_vc_x64_custom.pdb"     "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxbase31u_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_adv_vc_x64_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_adv_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_adv_vc_x64_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_adv_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_aui_vc_x64_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_aui_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_aui_vc_x64_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_aui_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_core_vc_x64_custom.dll" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_core_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_core_vc_x64_custom.pdb" "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_core_vc_x64_custom.pdb"

mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_stc_vc_x64_custom.dll"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_stc_vc_x64_custom.dll"
mklink  "C:\Users\%USERNAME%\Projects\AStyleWx\build\vs2015_3.1\x64\bin\wxmsw31u_stc_vc_x64_custom.pdb"  "F:\Programs\wxWidgets-3.1.0_vs2015\lib\vc_x64_dll\wxmsw31u_stc_vc_x64_custom.pdb"

echo.
pause
