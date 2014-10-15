#! /usr/bin/python
""" Library files for AStyle test modules.
    All directories and filepaths should be in this module.
    Executed as stand-alone it will run a series of tests.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import subprocess
import sys
import time

if os.name == "nt":
	import msvcrt			# Windows only for getch()
else:
	import termios, tty		# Linux only for getch()

# global variables ------------------------------------------------------------

# test project IDs
CODEBLOCKS   = "CodeBlocks"
GWORKSPACE   = "GWorkspace"         # Objective C
JEDIT        = "jEdit"              # Java
#KDEVELOP     = "KDevelop"          # C++- To complicated to compile on Windows
#MONODEVELOP  = "MonoDevelop"       # C# - To complicated to compile on Windows
SCITE        = "SciTE"
SHARPDEVELOP = "SharpDevelop"       # C# - Compile on Windows only
SHARPMAIN    = "SharpDevelopMain"   # C# - 1000 files from SharpDevelop
TESTPROJECT  = "TestProject"

# astyle test options

# OPT0
# no options
OPT0 = ""

# OPT1
# align-pointer=type (k1), add-brackets (j), break-blocks=all (F),
#     min-conditional-indent=0 (m0), pad-oper (p), pad-oparen (P)
OPT1 = "-CSKNLwxwxWYM50m0FpPHUEk1yejOoc"

# OPT2
# align-pointer=name (k3), align-reference=type (W1),
#     add-one-line-brackets (J), break-blocks (f),
#     min-conditional-indent=3 (m3), pad-paren-out(d)
#     pad-oper (p), delete-empty-lines (xe)
# WITHOUT: keep-one-line-blocks (O), keep-one-line-statements (o),
OPT2 = "-xGSKNLwxWM60m3fpdHUxeEk3W1yeJc"

# OPT3
# align-pointer=middle (k2), align-reference=name (W3),
#     min-conditional-indent=1 (m1), pad-paren-in(D)
#     remove-brackets (xj),
# WITHOUT: add-brackets (j,J), break-blocks (f,F),
#     pad-oper (p), delete-empty-lines (xe)
OPT3 = "-CSKNLwxwM80m1DHUEk2W3yxj"

# TEST SEPARATELY
# max-code-length (xC), break-after-logical (xL)
# -xC# -xL

# compile configurations
DEBUG   = "debug"
RELEASE = "release"
STATIC  = "static"

# Visual Studio release
#VS_RELEASE = "vs2008"
#VS_RELEASE = "vs2010"
#VS_RELEASE = "vs2012"
VS_RELEASE = "vs2013"

# test directory name
TEST_DIRECTORY = "TestData"

# -----------------------------------------------------------------------------

def build_astyle_executable(config):
	"""Build the astyle executable.
	"""
	if config == DEBUG:
		print("Building AStyle Debug")
	elif config == RELEASE:
		print("Building AStyle Release")
	elif config == STATIC and os.name == "nt":
		print("Building AStyle Static")
	else:
		system_exit("Bad arg in build_astyle_executable(): " + config)
	slnpath = get_astyle_build_directory(config)
	if os.name == "nt":
		slnpath = slnpath + "/AStyle.sln"
		compile_windows_executable(slnpath, config)
	else:
		compile_linux_executable(slnpath, config)

# -----------------------------------------------------------------------------

def compile_linux_executable(slnpath, config):
	"""Compile the astyle executable for Linux.
	"""
	if config == DEBUG:
		build = ["make", "debug"]
	else:
		build = ["make", "release"]
	buildfile = get_temp_directory() + "build." + config + ".tmp"
	if os.path.exists(buildfile):
		remove_build_file(buildfile)
	outfile = open(buildfile, 'w')
	retval = subprocess.call(build, cwd=slnpath, stdout=outfile)
	if retval:
		system_exit("Bad build return: " + str(retval))
	outfile.close()
	remove_build_file(buildfile)

# -----------------------------------------------------------------------------

def compile_windows_executable(slnpath, config):
	"""Compile the astyle executable for Windows.
	"""
	sdk = "v3.5"
	if VS_RELEASE >= "vs2010":
		sdk = "v4.0.30319"
	# remove the cache file as a precaution
	cachepath = slnpath + "/AStyle.sln.cache"
	if os.path.isfile(cachepath):
		os.remove(cachepath)
	# call MSBuild
	if VS_RELEASE >= "vs2013":
		buildpath = "C:/Program Files (x86)/MSBuild/12.0/Bin/MSBuild.exe"
	else:
		buildpath = (os.getenv("WINDIR")
					+ "/Microsoft.NET/Framework/"
					+ sdk
					+ "/MSBuild.exe")
	if not os.path.isfile(buildpath):
		message = "Cannot find build path: " + buildpath
		system_exit(message)
	if config == DEBUG:
		config_prop = "/property:Configuration=Debug"
	elif config == STATIC:
		config_prop = "/property:Configuration=Static"
	else:
		config_prop = "/property:Configuration=Release"
	platform_prop = "/property:Platform=Win32"
	msbuild = ([buildpath, config_prop, platform_prop, slnpath])
	buildfile = get_temp_directory() + "/build." + config + ".tmp"
	if os.path.exists(buildfile):
		remove_build_file(buildfile)
	outfile = open(buildfile, 'w')
	retval = subprocess.call(msbuild, stdout=outfile)
	if retval:
		system_exit("Bad msbuild return: " + str(retval))
	outfile.close()
	remove_build_file(buildfile)

# -----------------------------------------------------------------------------

def get_7zip_path():
	"""Get the 7zip executable path for the os environment.
	"""
	if os.name == "nt":
		exepath = "C:/Program Files/7-Zip/7z.exe"
	else:
		exepath = "7z"
	return exepath

# -----------------------------------------------------------------------------

def get_archive_directory(endsep=False):
	"""Get the archives directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	arcdir = get_project_directory()  + "/TestArchives"
	if not os.path.isdir(arcdir):
		message = "Cannot find archive directory: " + arcdir
		system_exit(message)
	if endsep:
		arcdir += '/'
	return  arcdir

# -----------------------------------------------------------------------------

def get_astyle_build_directory(config):
	"""Get the AStyle build path for the os environment.
	"""
	if config != DEBUG and config != RELEASE and config != STATIC:
		system_exit("Bad arg in get_astyleexe_directory(): " + config)
	astyledir = get_astyle_directory()
	if os.name == "nt":
		subpath = "/build/" + VS_RELEASE
	else:
		subpath = "/build/gcc"
	astylepath = astyledir + subpath
	if not os.path.isdir(astylepath):
		message = "Cannot find astyle build directory: " + astylepath
		system_exit(message)
	return astylepath

# -----------------------------------------------------------------------------

def get_astyle_directory(endsep=False):
	"""Get the AStyle directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if endsep != True and endsep != False:
		system_exit("Bad arg in get_astyle_directory(): " + endsep)
	astyledir = get_project_directory() + "/AStyle"
	if not os.path.isdir(astyledir):
		message = "Cannot find astyle directory: " + astyledir
		system_exit(message)
	if endsep:
		astyledir += '/'
	return astyledir

# -----------------------------------------------------------------------------

def get_astyleexe_directory(config, endsep=False):
	"""Get the AStyle executable directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if config != DEBUG and config != RELEASE and config != STATIC:
		system_exit("Bad arg in get_astyleexe_directory(): " + config)
	astyledir = get_astyle_directory()
	if os.name == "nt":
		subpath = "/build/" + VS_RELEASE + "/bin"
		if config == DEBUG:
			subpath = subpath.replace("bin", "debug")
		elif  config == STATIC:
			subpath = subpath.replace("bin", "binstatic")
	else:
		subpath = "/build/gcc/bin"
	astylepath = astyledir + subpath
	if not os.path.isdir(astylepath):
		message = "Cannot find astyleexe directory: " + astylepath
		system_exit(message)
	if endsep:
		astylepath += '/'
	return astylepath

# -----------------------------------------------------------------------------

def get_astyleexe_path(config):
	"""Get the AStyle executable path for the os environment.
	"""
	if config != DEBUG and config != RELEASE and config != STATIC:
		system_exit("Bad arg in get_astyle_path(): " + config)
	astyledir = get_astyleexe_directory(config, True)
	if os.name == "nt":
		if config == DEBUG:
			progname = "AStyled.exe"
		else:
			progname = "AStyle.exe"
		astylepath = astyledir + progname
		if not os.path.isfile(astylepath):
			message = "Cannot find astyleexe path: " + astylepath
			system_exit(message)
	else:
		if config == DEBUG:
			progname = "astyled"
		else:
			progname = "astyle"
		astylepath = astyledir + progname
	return astylepath

# -----------------------------------------------------------------------------

def get_astyletest_directory(endsep=False):
	"""Get the AStyleTest directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if endsep != True and endsep != False:
		system_exit("Bad arg in get_astyletest_directory(): " + endsep)
	astyletestdir = get_project_directory() + "/AStyleTest"
	if not os.path.isdir(astyletestdir):
		message = "Cannot find astyletest directory: " + astyletestdir
		system_exit(message)
	if endsep:
		astyletestdir += '/'
	return astyletestdir

# -----------------------------------------------------------------------------

def get_astylewx_directory(endsep=False):
	"""Get the AStyleWx directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if endsep != True and endsep != False:
		system_exit("Bad arg in get_astylewx_directory(): " + endsep)
	astylewxdir = get_project_directory() + "/AStyleWx"
	if not os.path.isdir(astylewxdir):
		message = "Cannot find astylewx directory: " + astylewxdir
		system_exit(message)
	if endsep:
		astylewxdir += '/'
	return astylewxdir

# -----------------------------------------------------------------------------

def get_astylewxtest__directory(endsep=False):
	"""Get the AStyleWx directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if endsep != True and endsep != False:
		system_exit("Bad arg in get_astylewx_directory(): " + endsep)
	astylewxdir = get_project_directory() + "/AStyleWxTest"
	if not os.path.isdir(astylewxdir):
		message = "Cannot find astylewx directory: " + astylewxdir
		system_exit(message)
	if endsep:
		astylewxdir += '/'
	return astylewxdir

# -----------------------------------------------------------------------------

def getch():
	"""getch() for Windows and Linux.
	   This won't work unless run from a terminal.
	"""
	# this must be executed from a terminal
	if not is_executed_from_console():
		system_exit("libastyle.getch() must be run from the console")
	# WINDOWS uses msvcrt
	if os.name == "nt":
		# clear buffer
		while msvcrt.kbhit():
			msvcrt.getch()
		# read char
		ch_in = msvcrt.getch()
	# LINUX uses termios and tty
	else:
		# clear buffer
		sys.stdin.flush()
		# read char
		fd_in = sys.stdin.fileno()
		old_settings = termios.tcgetattr(fd_in)
		try:
			tty.setraw(sys.stdin.fileno())
			ch_in = sys.stdin.read(1)
			if ch_in == '\x1b':			# alt key (27)
				ch_in = sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd_in, termios.TCSADRAIN, old_settings)
	# convert to unicode for Python 3
	return ch_in.decode('utf-8')

# -----------------------------------------------------------------------------

def get_diff_path():
	"""Get the diff executable path for the os environment.
	   endexe = True will add an ending '.exe' to Windows.
	"""
	if os.name == "nt":
		exepath = "/Program Files (x86)" + "/WinMerge/WinMergeU.exe"
		if not os.path.isfile(exepath):
			message = "Cannot find diff path: " + exepath
			system_exit(message)
	else:
		exepath = "diffuse"
	return  exepath

# -----------------------------------------------------------------------------

def get_file_py_directory(endsep=False):
	"""Get the file-py directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	# get the path where this file is located
	pydir = sys.path[0]
	if endsep:
		pydir += '/'
	# verify it is executed from fixed disk and not a USB
	if os.name == "nt":
		if pydir[0:2] != "C:":
			system_exit("File executed from drive " + pydir[0:2])
	else:
		if pydir[0:6] != "/home/":
			sep = pydir[0:].find("/Projects/")
			if sep == -1:
				sep = len(pydir)
			else:
				sep += 1
			system_exit("File executed from drive " + pydir[0:sep])
	return  pydir

# -----------------------------------------------------------------------------

def get_formatted_time():
	"""Get the current time for printing.
	"""
	tm = time.strftime("%I:%M")
	if tm[0] == '0':
		tm = tm.replace('0', ' ', 1)
	return tm

# -----------------------------------------------------------------------------

def get_home_directory(endsep=False):
	"""Get the home directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if os.name == "nt":
		homedir = os.getenv("USERPROFILE")
		homedir = homedir.replace('\\', '/')
	else:
		homedir = os.getenv("HOME")
	if endsep:
		homedir += '/'
	return  homedir

# -----------------------------------------------------------------------------

def get_project_directory(endsep=False):
	"""Get the Project directory for the os environment.
	   Extract the Project directory from path[0]
	   endsep = True will add an ending separator.
	"""
	# get project directory
	pydir = get_file_py_directory()
	projdir = pydir
	tail = pydir
	while len(tail) > 0:
		head, tail = os.path.split(projdir)
		if tail == 'Projects':
			break
		projdir = head
	if len(tail) == 0:
		system_exit("Cannot find project directory " + pydir[0:])
	if endsep:
		projdir += '/'
	return  projdir

# -----------------------------------------------------------------------------

def get_project_excludes(project):
	"""Get the project excludes list for AStyle processing.
	   Argument must be one of the global variables.
	   Returns a list of excludes.
	"""
	excludes = []
	if project == CODEBLOCKS:
		# excludes because of %pythoncode
		# advprops.h is __WXPYTHON__ at line 192
		# propgrid.cpp is the macro IMPLEMENT_GET_VALUE
		# sqplus.h aborts on verifyBeautifierStacks because of unmatched paren
		# sqvm.cpp doesn't compile because of _RET_SUCCEED macro used with --remove-brackets
		excludes.append("--exclude=wx/wxscintilla.h")
		excludes.append("--exclude=wx/propgrid/advprops.h")
		excludes.append("--exclude=wx/propgrid/manager.h")
		excludes.append("--exclude=wx/propgrid/propgrid.h")
		excludes.append("--exclude=sqplus/sqplus.h")
		excludes.append("--exclude=squirrel/sqvm.cpp")
		#excludes.append("--exclude=propgrid/propgrid.cpp")
	elif project == GWORKSPACE:
		excludes.append("--exclude=GNUstep.h")
#	elif project == KDEVELOP:
#		excludes.append("--exclude=app_templates")
#		excludes.append("--exclude=autotools/autotools_lex.cpp")
#		excludes.append("--exclude=qmake/qmake_lex.cpp")
#		excludes.append("--exclude=doxygen/config.cpp")
	elif project == SCITE:
		excludes.append("--exclude=lua")
	elif project == SHARPDEVELOP:
		excludes.append("--exclude=Debugger.Tests")    # xml data
		excludes.append("--exclude=QueryMethod.cs")
	return excludes

# -----------------------------------------------------------------------------

def get_project_filepaths(project):
	"""Get filepath list for AStyle processing.
	   Argument must be one of the global variables.
	   Returns a list of filepaths to process.
	"""
	filepaths = []
	test_directory = get_test_directory()
	if project == CODEBLOCKS:
		filepaths.append(test_directory + "/CodeBlocks/src/*.cpp")
		# filepath.append(test_directory + "/CodeBlocks/src/*.cxx")
		filepaths.append(test_directory + "/CodeBlocks/src/*.h")
	elif project == GWORKSPACE:
		filepaths.append(test_directory + "/GWorkspace/*.m")
		filepaths.append(test_directory + "/GWorkspace/*.h")
	elif project == JEDIT:
		filepaths.append(test_directory + "/jEdit/*.java")
#	elif project == KDEVELOP:
#		filepaths.append(test_directory + "/KDevelop/*.cpp")
#		filepaths.append(test_directory + "/KDevelop/*.h")
#	elif project == MONODEVELOP:
#		filepaths.append(test_directory + "/MonoDevelop/src/*.cs")
	elif project == SCITE:
		filepaths.append(test_directory + "/SciTE/*.cxx")
		filepaths.append(test_directory + "/SciTE/*.h")
	elif project == SHARPDEVELOP:
		filepaths.append(test_directory + "/SharpDevelop/src/*.cs")
	elif project == SHARPMAIN:
		# number of files: Main 1000, Libraries 1200, AddIns 5000, Tools 50, Setup 0
		# also change libextract.py, extract_sharpmain()
		filepaths.append(test_directory + "/SharpDevelopMain/src/Main/*.cs")
		#~ filepaths.append(test_directory + "/SharpDevelopMain/src/Libraries/*.cs")
	elif project == TESTPROJECT:
		# the test file paths can be changed depending n the circumstances
		# if the test is not CodeBlocks change extract_testproject() in libextract.py
		filepaths.append(test_directory + "/TestProject/scite/gtk/*.cxx")
		filepaths.append(test_directory + "/TestProject/scite/gtk/*.h")
	else:
		system_exit("Bad get_project_filepaths() project id: " + project)
	return filepaths

# -----------------------------------------------------------------------------

def get_python_version():
	"""Return the Python version number as a string."""
	version = ""
	if platform.python_implementation() == "CPython":
		version = "Python"
	else:
		version = platform.python_implementation()
	version += " {0}.{1}.{2}  ".format(sys.version_info[0],
									   sys.version_info[1],
									   sys.version_info[2])
	version += "({0})".format(platform.architecture()[0])
	return version

# -----------------------------------------------------------------------------

def get_python_version_number():
	"""Return the Python version number as a number."""
	return sys.version_info[0]

# -----------------------------------------------------------------------------

def get_temp_directory():
	"""Get the temporary directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	if os.name == "nt":
		tempdir = os.getenv("TEMP")
		tempdir = tempdir.replace('\\', '/')
	else:
		tempdir = "./"
	return  tempdir

# -----------------------------------------------------------------------------

def get_test_directory(endsep=False):
	"""Get the test directory for the os environment.
	   endsep = True will add an ending separator.
	"""
	testdir = get_project_directory()  + '/'  + TEST_DIRECTORY
	if not os.path.isdir(testdir):
		message = "Cannot find test directory: " + testdir
		system_exit(message)
	if endsep:
		testdir += '/'
	return  testdir

# -----------------------------------------------------------------------------

def is_executed_from_console():
	"""Check if this script is run is from the console or from an editor.
	   If run from a console the sys.stdin will be a TTY.
	   sys.stdin.fileno() seems to work OK for Windows.
	   The AttributeError exception occurs when run from Visual Studio Shell.
	"""
	try:
		return os.isatty(sys.stdin.fileno())
	except AttributeError:
		return False

# -----------------------------------------------------------------------------

def remove_build_file(buildfile):
	"""Remove the build.CONFIG.tmp file from the astyle compile.
	   If the file cannot be removed it is probably in use by another script.
	   Wait until the other script finishes the compile to fix the problem.
	"""
	try:
		os.remove(buildfile)
	except WindowsError as err:
		print()
		print(err)
		message = ("The file '{0}' must be removed "
					"before continuing").format(buildfile)
		system_exit(message)

# -----------------------------------------------------------------------------

def set_error_color():
	"""Change text color if script is run from the console.
	"""
	if is_executed_from_console():
		if os.name == "nt":
			os.system("color 0C")
		else:
			os.system("echo -n '[1;31m'")

# -----------------------------------------------------------------------------

def set_ok_color():
	"""Change text color if script is run from the console.
	"""
	if is_executed_from_console():
		if os.name == "nt":
			os.system("color 0A")
		else:
			os.system("echo -n '[1;32m'")

# -----------------------------------------------------------------------------

def set_test_directory(test_directory):
	"""Change the name of the global test directory.
	"""
	global TEST_DIRECTORY
	TEST_DIRECTORY = test_directory
	testdir = get_project_directory()  + '/'  + TEST_DIRECTORY
	testdir = testdir.replace('\\', '/')
	if not os.path.isdir(testdir):
		print("Creating: " + testdir)
		os.mkdir(testdir)

# -----------------------------------------------------------------------------

def set_text_color():
	"""Change text color if script is run from the console.
	"""
	if is_executed_from_console():
		if os.name == "nt":
			os.system("color 0E")
		else:
			os.system("echo -n '[1;33m'")

# -----------------------------------------------------------------------------

def system_exit(message=''):
	"""Accept keyboard input to assure a message is noticed.
	"""
	if len(message.strip()) > 0:
		set_error_color()
		print(message)
	# pause if script is run from the console
	if is_executed_from_console():
		print("\nPress any key to end . . .")
		getch()
	else:
		print("\nEnd of script !")
	os._exit(0)

# -----------------------------------------------------------------------------

def test_all_functions():
	"""Test all functions for syntax.
	"""
	build_astyle_executable(DEBUG)		# calls compile_astyle_linux() or ..._windows()
	get_7zip_path()
	get_archive_directory()
	get_astyle_directory()
	get_astyleexe_directory(DEBUG)
	get_astyleexe_path(DEBUG)
	get_astyletest_directory()
	get_diff_path()
	get_file_py_directory()
	get_home_directory()
	get_project_directory()
	get_project_excludes(TESTPROJECT)
	get_project_filepaths(TESTPROJECT)
	get_python_version_number()
	get_temp_directory()
	get_test_directory()
	is_executed_from_console()
	set_error_color()
	set_ok_color()
	set_text_color()

# -----------------------------------------------------------------------------

# make the module executable
# run tests if executed as stand-alone
if __name__ == "__main__":
	set_text_color()
	print(get_python_version())
	test_all_functions()
	system_exit()
