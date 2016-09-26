#! /usr/bin/python
""" Generate test data for the C# Example.cs program.
    Creates a list of files to be used in the program.
    Input is a list of formatted files from regression2-test.py.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
# local libraries
import libastyle
import libtest

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    files = []
    totfiles = 0
    testfile = "test.txt"
    sharpfile = "test-csharp.txt"

    # initialization
    libastyle.set_text_color("yellow")
    os.chdir(libastyle.get_file_py_directory())
    if not os.path.exists(testfile):
        libastyle.system_exit(
            "Run regression2-test.py to create " + testfile)
    print(libastyle.get_python_version())
    print("extracting C# test data")

    # process formatted files
    files = libtest.get_formatted_files(testfile)
    outfile = open(sharpfile, 'w')
    for filepath in files:
        filepath = filepath.replace('\\', '/')  # replace file separators
        filepath = '\"' + filepath + '\",'      # add quotes to filepath
        outfile.write(filepath + '\n')
        totfiles += 1
    outfile.close()
    print("saved " + sharpfile)
    print("files extracted " + str(totfiles))
    formatted, unused, unused, unused = libtest.get_astyle_totals(testfile)
    if totfiles != formatted:
        libastyle.system_exit(
            "totals not equal {0} {1}".format(totfiles, formatted))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
