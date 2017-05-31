#! /usr/bin/python3

"""Check AStyleIFace.h to Main_Test.h to verify that all virtual fuctions are overridden.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastylewx      # local directory

# global variables ------------------------------------------------------------

__print_detail    = False       # print line numbers and total functions
__print_functions = False       # print the functions in the lists

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""

    # lists to compare virtual function overrides
    iface_functions = []    # functions in AStyleDlgBase.h
    mtest_functions = []    # functions in AStyleDlg.h
    # file paths
    iface_path = libastylewx.get_astylewx_directory() + "/src/AStyleIFace.h"
    mtest_path = libastylewx.get_astylewxtest_directory() + "/src/Main_Test.h"

    # extract data
    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
    print("Virtual Functions")
    get_iface_functions(iface_functions, iface_path)
    get_mtest_functions(mtest_functions, mtest_path)
    # find diffs
    find_function_diffs(iface_functions, mtest_functions)

    if __print_functions:
        # iface_functions.sort()
        print(iface_functions)
        # mtest_functions.sort()
        print(mtest_functions)

# -----------------------------------------------------------------------------

def extract_function_name(line):
    """Extract the function name of a function with a "void' return value.
       Extracts the text between 'void' and the first opening paren.
       Returns the function name.
    """
    function_name = line.strip()
    end_return_type = line.find(' ')
    if end_return_type == -1:
        return ''
    function_name = function_name[end_return_type:].strip()
    name_end = function_name.find('(')
    if name_end == -1:
        return ''
    function_name = function_name[:name_end].strip()
    return function_name

# -----------------------------------------------------------------------------

def find_function_diffs(iface_functions, mtest_functions):
    """Find differences in iface and mtest functions lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_functions = set(iface_functions) - set(mtest_functions)

    if len(missing_functions) > 0:
        missing_functions = sorted(missing_functions)
        print(missing_functions)

    diffs = len(missing_functions)
    if diffs == 0:
        print("There are NO missing function overrides!!!")
    else:
        print("There are {0} missing function overrides.".format(diffs))

    # print extra functions in Main_Test not in AStyleIFace
    extra_functions = set(mtest_functions) - set(iface_functions)
    diffs = len(extra_functions)
    if diffs != 0:
        print(extra_functions)
        print("There are {0} unmatched functions in Main_Test.".format(diffs))

# -----------------------------------------------------------------------------

def get_iface_functions(iface_functions, iface_path):
    """Read the header file and save the AStyleIFace 'virtual' functions."""

    function_total = 0      # total virtual functions for header
    lines = 0                   # current input line number
    file_in = open(iface_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # find the virtual functions
        if not line.startswith("virtual"):
            continue
        virtual_word = line.find("virtual")
        line = line[virtual_word + len("virtual"):].strip()
        # get the function name
        function_name = extract_function_name(line)
        if function_name == '':
            continue
        if (function_name == "SetAStyleOptionFromConfig"
                or function_name == "ShowMessageBox"):
            continue
        iface_functions.append(function_name)
        function_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleIFace functions".format(function_total))

# -----------------------------------------------------------------------------

def get_mtest_functions(mtest_functions, mtest_path):
    """Read the header file and save the Main_Test virtual function overrides."""
    virtual_start = False       # start looking for virtual functions
    header_total = 0            # total virtual functions for header
    lines = 0                   # current input line number
    file_in = open(mtest_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # start with the following line
        if line.startswith("class AStyleIFace_Test"):
            virtual_start = True
            continue
        if not virtual_start:
            continue
        # end with the following line
        if line.startswith("};"):
            virtual_start = False
            continue

        # find the virtual override functions
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.find(" return ") == -1 and line.find(" = ") == -1:
            continue
        # get the function name
        function_name = extract_function_name(line)
        if function_name == '':
            continue
        if function_name == "ShowMessageBox":
            continue
        mtest_functions.append(function_name)
        header_total += 1

    file_in.close()
    if __print_detail:
        print("{0} Main_Test functions".format(header_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
