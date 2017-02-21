#! /usr/bin/python
""" Format a python file using autopep8.
    Run from an option in the "Tools" menu of a development environment.
    For Visual Studio:
        Title:       Format Python
        Command:     C:/Program Files/Python35/python.exe
        Arguments:   "format_python.py"  "$(ItemFileName)$(ItemExt)"
        Init Dir:    %USERPROFILE%/Projects/AStyleTest/file-pyr)
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
    print("Formatting " + file_name)
    print()
    call_autopep8_executable(file_name)
    print()

# -----------------------------------------------------------------------------

def call_autopep8_executable(file_name):
    """ Call the autopep8 executable to format the project.
        Uses the file pyprp8rc for formatting options.
    """
    if os.name == "nt":
        exepath = "C:/Program Files/Python35/Scripts/autopep8.exe"
    else:
        exepath = "autopep8"

    # couldn't get options file to work "--global-config=pypep8rc"
    # so get them from the file
    options = []
    get_options(options)
    print("options =", options)
    print()

    # build the autopep8 call list
    autopep8_call = options
    autopep8_call.insert(0, exepath)
    autopep8_call.append("--in-place")
    autopep8_call.append("--verbose")
    autopep8_call.append(file_name)

    try:
        retval = subprocess.call(autopep8_call)
    except FileNotFoundError:
        print("Cannot find '" + exepath + "'")
        os._exit(1)
    # a fatal return contains a bit-ORed 1
    # a usage error contains a bit-ORed 32
    # other bit values indicate messages that were issued
    # https://docs.pylint.org/en/latest/user_guide/run.html
    if retval and (retval & 1 or retval & 32):
        print("\nBad autopep8 return: " + str(retval))
        os._exit(1)

# -----------------------------------------------------------------------------

def get_options(options):
    """ Get options in the options file.
        Couldn't get the file options to work, so do this.
    """
    opt_path = "pypep8rc"
    options_in = open(opt_path, 'r')
    # get exceptions
    for line_in in options_in:
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("#"):
            continue
        if line.startswith("[") and "pep8" in line:
            continue
        option = line
        if not line.startswith("-"):
            line = "--" + line
        options.append(line)

    options_in.close()

# -----------------------------------------------------------------------------

# make the module executable
# NOTE: the calling program should pause before exiting
if __name__ == "__main__":
    main()
    os._exit(0)
