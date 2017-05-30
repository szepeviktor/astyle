@echo off
REM create releases files from the current trunk
REM change "set rel=" to the current release

REM do NOT use backslashes in the file:/// statement
REM do NOT use %USERPROFILE% because of the backslashes
set repos=https://svn.code.sf.net/p/astyle/code
set svndir=%repos%/tags
set svnprog=F:\Program Files (x86)\SlikSvn\bin
set rel=3.0


REM do NOT use backslashes in the file:/// statement
echo -
echo --------------------------
echo creating tags %rel% directory
echo --------------------------
"%svnprog%\svn"  mkdir  "%svndir%/%rel%"   -m "Create directory."
if errorlevel 1 (
echo -
echo file not copied
) else (
echo -
echo --------------------------
echo copying trunk to %rel% directory
echo --------------------------
"%svnprog%\svn"  copy  "%repos%/trunk/AStyleTest"  "%svndir%/%rel%/AStyleTest"  -m "Create AStyleTest release %rel%"
"%svnprog%\svn"  copy  "%repos%/trunk/AStyle"  "%svndir%/%rel%/AStyle"  -m "Create AStyle release %rel%"
)

echo -
echo -
echo * * * * *  end of create release  * * * * *
pause
