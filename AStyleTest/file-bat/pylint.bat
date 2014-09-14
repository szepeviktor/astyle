@REM run pylint for selected files
@echo off

set pydir=C:\Program Files\Python27

::set file=astyle_beautifier.py
::set file=astyle_console.py
::set file=astyle_enhancer.py
::set file=astyle_formatter.py
::set file=astyle_localizer.py
::set file=astyle_protected.py
::set file=astyle_resource.py
::set file=astyle_streamiter.py

set file=cppcheck.py
::set file=diff1_print.py
::set file=diff2_print.py
::set file=dist_copy.py
::set file=file_extract.py

::set file=libastyle.py
::set file=libextract.py
::set file=libtest.py
::set file=locale_enum_i18n.py
::set file=locale_testi18n_ec.py
::set file=locale_testi18n_mingw.py
::set file=locale_testi18n_vc.py
::set file=regression1_test.py
::set file=regression2_test.py
::set file=system_test.py


echo.
cd ..\file-py
"%pydir%\Scripts\pylint"  %options%  %file%


echo.
echo * * * *   end of %file%   * * * *
pause
