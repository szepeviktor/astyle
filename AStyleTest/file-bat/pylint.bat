@REM run pylint for selected files
@echo off

REM to install pylint:
REM     from:   c:\Program Files\Python 3.5\Scripts
REM     enter:  pip install pylint
REM uses file pylintrc in astyletest\file-py

set pydir=C:\Program Files\Python 3.5

::set file=astyle_beautifier.py
::set file=astyle_console.py
::set file=astyle_enhancer.py
::set file=astyle_formatter.py
::set file=astyle_localizer1.py
::set file=astyle_localizer2.py
::set file=astyle_protected.py
::set file=astyle_resource.py
::set file=astyle_streamiter.py

::set file=cppcheck.py
::set file=csharp_testdata.py
::set file=diff1_print.py
::set file=diff2_print.py
::set file=dist_copy.py
::set file=dist_copy_xp.py
::set file=file_extract.py
::set file=format_project.py

::set file=libastyle.py
::set file=libextract.py
::set file=libtest.py

::set file=locale_enum_i18n.py
::set file=locale_testi18n_bcc.py
::set file=locale_testi18n_mingw.py
::set file=locale_testi18n_vc.py
::set file=modify_html.py
::set file=modify_java_release.py
::set file=modify_shared_version.py
::set file=naming.py

::set file=regression1_test.py
::set file=regression2_test.py
set file=system_test.py


echo.
cd ..\file-py
"%pydir%\Scripts\pylint"  %options%  %file%

::"%pydir%\Scripts\pylint" --help

::"%pydir%\Scripts\pylint" --generate-rcfile > pylintrc_gen

echo.
echo * * * *   end of %file%   * * * *
pause
