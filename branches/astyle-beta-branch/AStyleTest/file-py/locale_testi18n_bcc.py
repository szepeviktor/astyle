#! /usr/bin/python3
""" Run the Embarcadero AStyleTestI18n test using AppLocale to test non-ASCII files.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import subprocess
import time
# local libraries
import libastyle

# global variables ------------------------------------------------------------
# always uses the debug configuration
__builddir = libastyle.get_astyletest_directory() + "/build/cb-bcc"

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    # initialization
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    verify_os()
    exepath = "C:/Windows/AppPatch/AppLoc.exe"
    i18npath = __builddir + "/bin/AStyleTestI18nd.exe"
    # verify files
    if not os.path.exists(exepath):
        libastyle.system_exit("AppLoc not installed: " + exepath)
    build_testi18n_executable()

    # for some reason the subprocess call must be one long statement and quoted as follows???
    # the country LCID is added by the subprocess call
    command = exepath + ' ' + i18npath + ' ' + "\"--terse_output --no_close\"" + ' '
    # run tests
    print("\nWAIT for a test to finish before running the next.")
    print("NOTE A bad return may work anyway. Check the individual displays.")
    print("Press OK to continue with the displayed language.\n")
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
    """Build the Embarcadero AStyleTestI18n debug executable.
    """
    print("Building Embarcadero AStyleTestI18n Debug")
    # Compile the astyle executable for Windows.
    buildpath = "C:/Program Files (x86)/CodeBlocks/codeblocks.exe"
    if platform.architecture()[0] == "32bit":        # if running on a 32-bit system
        buildpath = buildpath.replace("Program Files (x86)", "Program Files")
    if not os.path.isfile(buildpath):
        message = "Cannot find CodeBlocks executable: " + buildpath
        libastyle.system_exit(message)
    print("Close the build window when finished ...")
    arg1 = "--build"
    arg2 = "--target=Debug"
    arg3 = "--no-batch-window-close"
    gmpath = __builddir + "/Bcc GTest Lib.cbp"
    gmbuild = ([buildpath, arg1, arg2, arg3, gmpath])
    cbpath = __builddir + "/Bcc AStyleTestI18n.cbp"
    cbbuild = ([buildpath, arg1, arg2, arg3, cbpath])
    buildfile = libastyle.get_temp_directory() + "/build.txt"
    outfile = open(buildfile, 'w')
    retvalgm = subprocess.call(gmbuild, stdout=outfile)
    if retvalgm:
        libastyle.system_exit("Bad gmbuild return: " + str(retvalgm))
    retvalcb = subprocess.call(cbbuild, stdout=outfile)
    if retvalcb:
        libastyle.system_exit("Bad cbbuild return: " + str(retvalcb))
    outfile.close()
    try:
        os.remove(buildfile)
    except PermissionError as err:
        libastyle.system_exit(str(err))

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
