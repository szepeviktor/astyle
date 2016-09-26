#! /usr/bin/python
""" Calls libextract to extract files in the TestArchives directory.
    Change the global variables to the desired values.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import time
#local libraries
import libastyle
import libextract

# global variables ------------------------------------------------------------

# select one of the following from libastyle
#  CODEBLOCKS
#  CODELITE
#  JEDIT
#  KDEVELOP
#  SCITE
#  SHARPDEVELOP
#  TESTPROJECT
__project = libastyle.TESTPROJECT

# extract all files options, use False for speed
#__all_files_option = True
__all_files_option = False

# -----------------------------------------------------------------------------

def main():
    """Call the library procedure to extract the requested project.
    """
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    starttime = time.time()
    libextract.extract_project(__project, __all_files_option)
    stoptime = time.time()
    print_run_time(starttime, stoptime)

# -----------------------------------------------------------------------------

def print_run_time(starttime, stoptime):
    """Print run time for the test.
    """
    runtime = int(stoptime - starttime + 0.5)
    minute = int(runtime / 60)
    sec = int(runtime % 60)
    if minute == 0:
        print("{0} seconds".format(sec))
    else:
        print("{0} min {1} seconds".format(minute, sec))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
