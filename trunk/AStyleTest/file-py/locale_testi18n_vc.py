#! /usr/bin/python
""" Run the Visual Studio AStyleTestI18n test using AppLocale to test non-ASCII files.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle        # local directory
import os
import subprocess
import time

# global variables ------------------------------------------------------------
# change the following for the correct VS version
# always uses the debug configuration
__builddir = libastyle.get_astyletest_directory() + "/build/" + libastyle.VS_RELEASE

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    # initialization
    libastyle.set_text_color()
    print(libastyle.get_python_version())
    verify_os()
    exepath = "C:/Windows/AppPatch/AppLoc.exe"
    i18npath = __builddir + "/debug/AStyleTestI18nd.exe"
    # verify files
    if not os.path.exists(exepath):
        libastyle.system_exit("AppLoc not installed: " + exepath)
    build_testi18n_executable()

    # for some reason the subprocess call must be one long statement and quoted as follows???
    # the country LCID is added by the subprocess call
    command = exepath + ' ' + i18npath + ' ' + "\"--terse_output --no_close\"" + ' '
    # run tests
    print("\nWAIT for a test to finish before running the next")
    print("Select OK to continue ...")
    print("\nNOTE: A bad return may work anyway. Check the individual displays.")
    print("Running Greek Test")
    retval = subprocess.call(command + "/L0408")
    if retval:
        print("    Bad AppLoc return: " + str(retval))
    time.sleep(2)       # must finish before running the next test
    print("Running Japanese Test")
    retval = subprocess.call(command + "/L0411")
    if retval:
        print("    Bad AppLoc return: " + str(retval))
    time.sleep(2)       # must finish before running the next test
    print("Running Russian Test")
    retval = subprocess.call(command + "/L0419")
    if retval:
        print("    Bad AppLoc return: " + str(retval))
    time.sleep(2)       # must finish before running the next test

# -----------------------------------------------------------------------------

def build_testi18n_executable():
    """Build the Visual Studio AStyleTestI18n debug executable.
    """
    print("Building " + libastyle.VS_RELEASE + " AStyleTestI18n Debug")
    # Compile the astyle executable for Windows.
    slnpath = (__builddir + "/AStyleTestI18n.sln")
    libastyle.compile_windows_executable(slnpath, libastyle.DEBUG)

# -----------------------------------------------------------------------------

def verify_os():
    """Verify the operating system
    """
    if os.name != "nt":
        print("This script is for Windows only")

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
