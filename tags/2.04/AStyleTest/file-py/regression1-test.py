#! /usr/bin/python
""" Run the AStyle regression test.
    Tests the output of a new program against an older one.
    Change the global variables to the desired values.
    Variables astyleexe1 & 2 should be an old and new version of the program.
    Changes will cause files in the second run to be formatted.
    The differences can be checked with a diff program.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle		# local directory
import libextract		# local directory
import libtest			# local directory
import locale
import os
import shutil
import subprocess
import time

# global variables ------------------------------------------------------------

# select one of the following from libastyle
# CODEBLOCKS
# DRJAVA            # Java - Cannot compile
# GWORKSPACE        # Objective-C
# JEDIT             # Java
# SCITE
# SHARPDEVELOP      # C# - Compile on Windows only
# SHARPMAIN         # C# - 1000 files from SharpDevelop
# TESTPROJECT
__project = libastyle.CODEBLOCKS

# select OPT0 thru OPT3, or use customized options
__options = libastyle.OPT0

# options_x are for BOTH executables
__options_x  = ""
# options_x2 are for ONLY exe2 to test new options
__options_x2 = ""

# executables for test - astyleexe1 is old version, astyleexe2 is new version
__astyleexe1 = "astyle24n"
__astyleexe2 = "astyle"

# select one of the following to unarchive files
#__extract_files = True
__extract_files = False

# extract all files options, use False for speed
#__all_files_option = True
__all_files_option = False

# -----------------------------------------------------------------------------

def main():
	"""Main processing function.
	"""
	# initialization
	starttime = time.time()
	libastyle.set_text_color()
	print(libastyle.get_python_version())
	locale.setlocale(locale.LC_ALL, "")
	verify_options_x_variable()
	print_run_header()
	os.chdir(libastyle.get_file_py_directory())
	libastyle.build_astyle_executable(get_astyle_config())
	verify_astyle_executables(__astyleexe1, __astyleexe2)
	filepaths = libastyle.get_project_filepaths(__project)
	excludes = libastyle.get_project_excludes(__project)
	testfile = "test.txt"
	if __extract_files:
		print("\nExtracting")
		libextract.extract_project(__project, __all_files_option)

	# run test 1
	print_test_header(1, __astyleexe1)
	astyle = set_astyle_args(filepaths, excludes, __astyleexe1)
	print_formatting_message(astyle, __project)
	call_artistic_style(astyle, testfile)
	print_astyle_totals(testfile)

	# run test 2
	print_test_header(2, __astyleexe2)
	astyle = set_astyle_args(filepaths, excludes, __astyleexe2)
	print_formatting_message(astyle, __project)
	call_artistic_style(astyle, testfile)
	totformat, unused = print_astyle_totals(testfile)
	files = libtest.get_formatted_files(testfile)
	verify_formatted_files(len(files), totformat)

	# process formatted files
	print_run_total(starttime)
	libtest.diff_formatted_files(files)

# -----------------------------------------------------------------------------

def call_artistic_style(astyle, testfile):
	"""Call artistic style.
	"""
	outfile = open(testfile, 'w')
	try:
		subprocess.check_call(astyle, stdout=outfile)
	except subprocess.CalledProcessError as err:
		libastyle.system_exit("Bad astyle return: " + str(err.returncode))
	except OSError:
		libastyle.system_exit("Cannot find executable: " + astyle[0])
	outfile.close()

# -----------------------------------------------------------------------------

def get_astyle_config():
	"""Get the build configuration from the executalbe name.
	"""
	config = libastyle.DEBUG
	if (__astyleexe1.lower() == "astyle"
	or __astyleexe2.lower() == "astyle"):
		config = libastyle.RELEASE
	return config

# -----------------------------------------------------------------------------

def get_astyle_path(astyleexe):
	"""Get the astyle executable path.
	"""
	config = get_astyle_config()
	astylepath = libastyle.get_astyleexe_directory(config, True) + astyleexe
	return astylepath

# -----------------------------------------------------------------------------

def print_astyle_totals(filename):
	"""Print total information from the astyle total line.
	   Returns files formatted and total files from the report total line.
	"""
	# the native locale should be set to get the numeric formatting
	formatted, totfiles, minute, sec = libtest.get_astyle_totals(filename)
	if minute == 0:
		printline = "{0:n} formatted; {1:n} files; {2} seconds"
		print(printline.format(formatted, totfiles, sec))
	else:
		printline = "{0:n} formatted; {1:n} files; {2} min {3} seconds"
		print(printline.format(formatted, totfiles, minute, sec))
	return (formatted, totfiles)

# -----------------------------------------------------------------------------

def print_formatting_message(args, project):
	"""Print the formatting message at the start of a test.
	   Input is the command list used to call astyle.
	"""
	print("Formatting " +  project, end=" ")
	# print args starting with a '-' except for excludes
	for arg in args:
		if not arg[0] == '-': continue
		if arg[:9] == "--exclude": continue
		print(arg, end=" ")
	print()

# -----------------------------------------------------------------------------

def print_run_header():
	"""Print run header information.
	"""
	print("Regression-1 Test for {0}".format(__project))
	if os.name == "nt":
		print("Using ({0}) {1} {2}".format(libastyle.VS_RELEASE,
				__astyleexe1, __astyleexe2), end=" ")
	else:
		print("Using {0} {1}".format(__astyleexe1, __astyleexe2), end=" ")
	if __options == libastyle.OPT0:
		print("OPT0", end=" ")
	elif __options == libastyle.OPT1:
		print("OPT1", end=" ")
	elif __options == libastyle.OPT2:
		print("OPT2", end=" ")
	elif __options == libastyle.OPT3:
		print("OPT3", end=" ")
	else:
		print(__options, end=" ")
	if len(__options_x.strip()) > 0:
		print(__options_x, end=" ")
	if len(__options_x2) > 0:
		print("({0})".format(__options_x2), end=" ")
	print()

# -----------------------------------------------------------------------------

def print_run_total(starttime):
	"""Print total information for the entire run.
	"""
	print()
	stoptime = time.time()
	runtime = int(stoptime - starttime + 0.5)
	minute =  int(runtime / 60)
	sec =  int(runtime % 60)
	if min == 0:
		print("{0} seconds total run time".format(sec))
	else:
		print("{0} min {1} seconds total run time".format(minute, sec))
	print()

# -----------------------------------------------------------------------------

def print_test_header(testnum, astyleexe):
	"""Print header information for a test.
	"""
	spaces = 16 - len(astyleexe)
	print()
	print("TEST {0} with {1}".format(testnum, astyleexe), end='')
	print(' ' * spaces, end='')
	print(libastyle.get_formatted_time())

# -----------------------------------------------------------------------------

def set_astyle_args(filepath, excludes, astyleexe):
	"""Set args for calling artistic style.
	"""
	astylepath = get_astyle_path(astyleexe)
	args = [astylepath]
	# set filepaths
	for file_in in filepath:
		args.append(file_in)
	# set options - must have ".orig" backup for comparison in astyleexe2
	if astyleexe == __astyleexe1:
		args.append("-vRQn")
	else:
		args.append("-vRQ")
	if len(__options.strip()) > 0:
		args.append(__options)
	if len(__options_x.strip()) > 0:
		args.append(__options_x)
	if (astyleexe == __astyleexe2
	and len(__options_x2.strip()) > 0):
		args.append(__options_x2)
	# set excludes
	for exclude in excludes:
		args.append(exclude)
	return args

# -----------------------------------------------------------------------------

def verify_astyle_executables(exe1, exe2):
	"""Verify that the astyle test executables are available.
	"""
	# get paths
	exe1path = get_astyle_path(exe1)
	exe2path = get_astyle_path(exe2)
	regress1path = libastyle.get_astyle_directory() + "/regress/" + exe1
	# add "exe" extension
	if os.name == "nt":
		if not exe1path.endswith(".exe"):
			exe1path += ".exe"
		if not exe2path.endswith(".exe"):
			exe2path += ".exe"
		if not regress1path.endswith(".exe"):
			regress1path += ".exe"
	# verify exe1
	if not os.path.exists(exe1path):
		# try to copy exe1 from the "regress" directory
		if os.path.exists(regress1path):
			print("Copying " + exe1)
			shutil.copy(regress1path, exe1path)
		else:
			libastyle.system_exit("Cannot find executable 1: " + exe1path)
	# check exe1 for most current by bumping the ending letter by 1
	if not verify_current_exe1(regress1path):
		libastyle.system_exit("Executable 1 is not current: " + regress1path)
	# verify exe2
	if not os.path.exists(exe2path):
		libastyle.system_exit("Cannot find executable 2: " + exe2path)

# -----------------------------------------------------------------------------

def verify_current_exe1(regress1path):
	"""Check that the requested exe1 is the most current version.
	"""
	# check exe1 for most current by bumping the ending letter by 1
	alphas = "abcdefghijklmnopqrstuvwxyz"
	if os.name == "nt":
		if regress1path[-5].isdigit():	# for first file from last release (AStyle1.exe)
			return True
		index = alphas.find(regress1path[-5])
		if index == -1:
			libastyle.system_exit("Bad index for alpha: " + index)
		test1path = regress1path[:-5] + alphas[index+1] + regress1path[-5+1:]
	else:
		if regress1path[-1].isdigit():	# for first file from last release (astyle1)
			return True
		index = alphas.find(regress1path[-1])
		if index == -1:
			libastyle.system_exit("Bad index for alpha: " + index)
		test1path = regress1path[:-1] + alphas[index+1]
	# is NOT most current if the next version exista
	if os.path.exists(test1path):
		return False
	return True

# -----------------------------------------------------------------------------

def verify_formatted_files(numformat, totformat):
	"""Check that the formatted files list equals the astyle report total.
	"""
	if totformat != numformat:
		message = "files != report ({0},{1})".format(numformat, totformat)
		libastyle.system_exit(message)

# -----------------------------------------------------------------------------

def verify_options_x_variable():
	"""Check that the options_x and options_x2 variables begin with a '-'
	"""
	global __options_x, __options_x2
	# options_x
	if len(__options_x) > 0:
		__options_x = __options_x.strip()
	if len(__options_x) > 0 and __options_x[0] != '-':
		__options_x = '-' + __options_x
	# options_x2
	if len(__options_x2) > 0:
		__options_x2 = __options_x2.strip()
	if len(__options_x2) > 0 and __options_x2[0] != '-':
		__options_x2 = '-' + __options_x2

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	main()
	libastyle.system_exit()

# -----------------------------------------------------------------------------
