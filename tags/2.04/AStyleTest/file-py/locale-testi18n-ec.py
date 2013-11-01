#! /usr/bin/python
""" Run the Embarcadero AStyleTestI18n test using AppLocale to test non-ASCII files.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle		# local directory
import os
import subprocess
import time

# global variables ------------------------------------------------------------
# always uses the debug configuration
__builddir = libastyle.get_astyletest_directory() + "/build/cb-ec"

# -----------------------------------------------------------------------------

def main():
	"""Main processing function.
	"""
	# initialization
	libastyle.set_text_color()
	print(libastyle.get_python_version())
	verify_os()
	exepath = "C:/Windows/AppPatch/AppLoc.exe"
	i18npath = __builddir + "/bin/AStyleTestI18nd.exe"
	command = exepath + ' ' + i18npath + ' ' + "\"--terse_printer --no_close\"" + ' '
	# verify files
	if not os.path.exists(exepath):
		libastyle.system_exit("AppLoc not installed: " + exepath)
	build_testi18n_executable()

	# for some reason the subprocess call must be one long statement and quoted as follows???
	# the country LCID is added by the subprocess call
	command = exepath + ' ' + i18npath + ' ' + "\"--terse_printer --no_close\"" + ' '
	# run tests
	print("\nWAIT for a test to finish before running the next")
	print("Reply OK to continue ...")
	print("Running Greek Test")
	subprocess.call(command + "/L0408")
	time.sleep(2)		# must finish before running the next test
	print("Running Japanese Test")
	subprocess.call(command + "/L0411")
	time.sleep(2)		# must finish before running the next test
	print("Running Russian Test")
	subprocess.call(command + "/L0419")
	time.sleep(2)		# must finish before running the next test

# -----------------------------------------------------------------------------

def build_testi18n_executable():
	"""Build the Embarcadero AStyleTestI18n debug executable.
	"""
	print("Building Embarcadero AStyleTestI18n Debug")
	# Compile the astyle executable for Windows.
	buildpath =  "C:/Program Files/CodeBlocks/codeblocks.exe"
	if not os.path.isfile(buildpath):
		message = "Cannot find CodeBlocks executable: " + buildpath
		libastyle.system_exit(message)
	print("Close the build window when finished ...")
	arg1 = "--build"
	arg2 = "--target=Debug"
	arg3 = "--no-batch-window-close"
	cbpath = __builddir + "/EC AStyleTestI18n.workspace"
	cbbuild = ([buildpath, arg1, arg2, arg3, cbpath])
	buildfile = libastyle.get_temp_directory() + "/build.txt"
	outfile = open(buildfile, 'w')
	retval = subprocess.call(cbbuild, stdout=outfile)
	if retval:
		libastyle.system_exit("Bad cbbuild return: " + str(retval))
	outfile.close()
	os.remove(buildfile)

# -----------------------------------------------------------------------------

def verify_os():
	"""Verify the operating system
	"""
	if os.name != "nt":
		print("This script is for Windows only")
		return

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	main()
	libastyle.system_exit()

# -----------------------------------------------------------------------------
