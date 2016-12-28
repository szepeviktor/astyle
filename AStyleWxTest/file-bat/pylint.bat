@REM run pylint for selected files
@echo off

REM to install pylint:
REM     from:   c:\Program Files\Python 3.5\Scripts
REM     enter:  pip install pylint
REM uses file pylintrc in astyletest\file-py

set pydir=C:\Program Files\Python 3.5

::set file=aswx_aboutdlg.py
::set file=aswx_astyledlg.py
::set file=aswx_astyleiface.py
::set file=aswx_editordlg.py
::set file=aswx_virtual.py

set file=change_static_wx30.py
::set file=change_static_wx3.1.py
::set file=cppcheck_wx.py
::set file=dist_copy_wx.py
::set file=dist_copy_wx_xp.py

::set file=gendlg_astyledlgbase_lnx.py
::set file=gendlg_editordlgbase_lnx.py
::set file=libastylewx.py
::set file=to_xxbook.py
::set file=xpm_fix.py


echo.
cd ..\file-py
"%pydir%\Scripts\pylint"  %options%  %file%

::"%pydir%\Scripts\pylint" --help

::"%pydir%\Scripts\pylint" --generate-rcfile > pylintrc_gen

echo.
echo * * * *   end of %file%   * * * *
pause
