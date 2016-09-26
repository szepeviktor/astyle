#! /usr/bin/python
"""Check astyle_main.cpp "settext" translation strings to the test variables
   in AStyleTestLoc.cpp.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
# local libraries
import libastyle

# global variables ------------------------------------------------------------

__print_detail = False          # print line numbers and total variables
__print_variables = False       # print the variables in the lists

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""

    astyle_strings = []         # _() translation strings in astyle_main.cpp
    test_strings = []           # test strings in AStyleTestLoc.cpp
    astyle_path = libastyle.get_astyle_directory() + "/src/astyle_main.cpp"
    if not os.path.exists(astyle_path):
        libastyle.system_exit("\nCannot locate file " + astyle_path)
    test_path = libastyle.get_astyletest_directory() + "/srcloc/AStyleTestLoc.cpp"
    if not os.path.exists(test_path):
        libastyle.system_exit("\nCannot locate file " + test_path)
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    get_astyle_strings(astyle_strings, astyle_path)
    get_test_strings(test_strings, test_path)

    # remove duplicate entries in astyle_strings from Linux and Windows functions
    astyle_strings = set(astyle_strings)
    astyle_strings = list(astyle_strings)
    print("Checking astyle_main strings to TranslationF.")
    total_astyle_strings = len(astyle_strings)
    print("There are {0} unique translated strings in astyle_main.".format(total_astyle_strings))
    print()

    find_string_diffs(astyle_strings, test_strings)

    if __print_variables:
        astyle_strings.sort()
        test_strings.sort()
        print()
        print(astyle_strings)
        print()
        print(test_strings)

# -----------------------------------------------------------------------------

def find_string_diffs(astyle_strings, test_strings):
    """Find differences in header and class variables lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_test = set(astyle_strings) - set(test_strings)
    missing_astyle = set(test_strings) - set(astyle_strings)

    if len(missing_test) > 0:
        missing_test = list(missing_test)
        missing_test.sort()
        print(str(len(missing_test)) + " missing test strings", end=" ")
        print(missing_test)

    if len(missing_astyle) > 0:
        missing_astyle = list(missing_astyle)
        missing_astyle.sort()
        print(str(len(missing_astyle)) + " test not in astyle  ", end=" ")
        print(missing_astyle)

    diffs = len(missing_test) + len(missing_astyle)
    if diffs == 0:
        print("There are NO diffs in the test strings!!!")
    else:
        print("There are {0} diffs in the test strings.".format(diffs))

# -----------------------------------------------------------------------------

def get_astyle_strings(astyle_strings, astyle_path):
    """Read the astyle_main.cpp file and save the settext strings."""

    astyle_total = 0            # total strings extracted
    lines = 0                   # current input line number
    file_in = open(astyle_path, 'r')

    # get astyle settext strings
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line[:2] == "//":
            continue
        # get the _() settext strings
        start = line.find('_("')
        if start == -1:
            continue
        start += 3
        end = line.find('")', start)
        if end == -1:
            continue
        settext_string = line[start:end]
        astyle_strings.append(settext_string)
        astyle_total += 1

    file_in.close()
    if __print_detail:
        print("{0} astyle strings".format(astyle_total))

# -----------------------------------------------------------------------------

def get_test_strings(test_strings, test_path):
    """Read the AStyleTestLoc.cpp file and save the test strings."""

    test_lines = [0, 0]     # line numbers for TranslationF constructor
    test_total = 0          # total variables for header
    test_brackets = 0       # unmatched brackets in the header
    lines = 0               # current input line number
    file_in = open(test_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line[:2] == "//":
            continue

        # start between the following lines
        if line.startswith("TranslationF()"):
            test_lines[0] = lines + 1
            continue
        if test_lines[0] == 0:
            continue
        # count brackets
        if '{' in line:
            test_brackets += 1
        if '}' in line:
            test_brackets -= 1
        if  test_brackets == 0:
            test_lines[1] = lines
            break
        # extract the string
        if not 'm_ascii.push_back("' in line:
            continue
        start = line.find('("')
        if start == -1:
            continue
        start += 2
        end = line.find('")', start)
        if end == -1:
            continue
        test_string = line[start:end]
        test_strings.append(test_string)
        test_total += 1

    file_in.close()
    if __print_detail:
        print("{0} {1} test strings".format(test_lines, test_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
