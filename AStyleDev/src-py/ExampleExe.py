#! /usr/bin/python

""" ExampleExe.py
    This program calls the Artistic Style executable to format the AStyle source files.
    The Artistic Style executable must be in the same directory as this script.
    It will work with either Python version 2 or 3 (unicode).
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import subprocess
import sys

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    files = ["ASBeautifier.cpp", "ASFormatter.cpp", "astyle.h"]
    options = "-A2tOP"

    #initialization
    print("ExampleExe",
          platform.python_implementation(),
          platform.python_version(),
          platform.architecture()[0])
    exe = initialize_exe()
    display_astyle_version(exe)
    # process the input files
    for file_path in files:
        file_path = get_project_directory(file_path)
        format_source_code(exe, file_path, options)

# -----------------------------------------------------------------------------

def display_astyle_version(exe):
    """Display the version number from the AStyle executable.
       This will not display when run from a Windows editor.
    """
    astyle = [exe, "--version"]
    retval = subprocess.call(astyle)
    if retval:
        print("Bad astyle return: " + str(retval))
        sys.exit(1)

# -----------------------------------------------------------------------------

def format_source_code(exe, file_path, options):
    """Format file_in by calling the AStyle executable.
       The unicode variables in Version 3 will be changed to
       byte variables by the operating system.
       The astyle messages will not display when run from a
       Windows editor.
    """
    astyle = [exe, options, file_path]
    retval = subprocess.call(astyle)
    if retval:
        print("Bad astyle return: " + str(retval))
        sys.exit(1)

# -----------------------------------------------------------------------------

def get_project_directory(file_name):
    """Find the directory path and prepend it to the file name.
       The source is expected to be in the "src-py" directory.
       This may need to be changed for your directory structure.
    """
    file_path = sys.path[0]
    end = file_path.find("src-py")
    if end == -1:
        print("Cannot find source directory", file_path)
        sys.exit(1)
    file_path = file_path[0:end]
    file_path = file_path + "test-data" + os.sep + file_name
    return file_path

# -----------------------------------------------------------------------------

def initialize_exe():
    """Set the file path and executable name.
       Verify the executable is available.
       Return the executable name.
    """
    # change directory to the path where this script is located
    pydir = sys.path[0]
    os.chdir(pydir)
    # return the executable name for the platform
    if os.name == "nt":
        exe = "AStyle.exe"
    else:
        exe = "astyle"
    # verify the astyle executable is available
    if not os.path.isfile(exe):
        print("Cannot find", exe)
        sys.exit(1)
    return exe

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    sys.exit(0)
