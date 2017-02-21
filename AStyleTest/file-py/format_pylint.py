#! /usr/bin/python
""" Check a python file using pylint.
    Run from an option in the "Tools" menu of a development environment.
    For Visual Studio:
        Title:       Format Python
        Command:     C:/Program Files/Python35/python.exe
        Arguments:   "format_python.py"  "$(ItemFileName)$(ItemExt)"
        Init Dir:    %USERPROFILE%/Projects/AStyleTest/file-py
"""

# to disable the print statement and use the print() function (version 3 format_)
from __future__ import print_function

import os
import subprocess
import sys

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """
    if len(sys.argv) < 2 or sys.argv[1] == '':
        print("Missing python file name in arg1")
        print("Is script run from CodeBlocks or Visual Studio?")
        print()
        os._exit(1)
    file_name = sys.argv[1]
    print("Hello '" + file_name + "'")
    if not file_name.endswith(".py"):
        print("Invalid file extension in '" + file_name + "'")
        print()
        os._exit(1)
    print("Checking " + file_name)
    print()
    call_pylint_executable(file_name)
    print()

# -----------------------------------------------------------------------------

def call_pylint_executable(file_name):
    """ Call the pylint executable to format the project.
        Uses the file pylintrc for formatting options.
    """
    if os.name == "nt":
        exepath = "C:/Program Files/Python35/Scripts/pylint.exe"
    else:
        exepath = os.getenv("HOME") + "/bin/astyle"

    # build the pylint call list
    pylint_call = [exepath, "--rcfile=pylintrc", file_name]

    try:
        retval = subprocess.call(pylint_call)
    except FileNotFoundError:
        print("Cannot find '" + exepath + "'")
        os._exit(1)
    # a fatal return contains a bit-ORed 1
    # a usage error contains a bit-ORed 32
    # other bit values indicate messages that were issued
    # https://docs.pylint.org/en/latest/user_guide/run.html
    if retval and (retval & 1 or retval & 32):
        print("\nBad pylint return: " + str(retval))
        os._exit(1)

# -----------------------------------------------------------------------------

# make the module executable
# NOTE: the calling program should pause before exiting
if __name__ == "__main__":
    main()
    os._exit(0)
