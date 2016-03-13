#! /usr/bin/python
"""Check ASLocalizer.h "Translation" classes to the test functions in AStyleTestLoc.cpp.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle        # local directory
import os

# global variables ------------------------------------------------------------

__print_detail = False          # print line numbers and total variables
__print_variables = False       # print the variables in the lists

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """

    language_strings = []       # translation classes in ASLocalizer.h
    name_functions = []         # name test functions in AStyleTestLoc.cpp
    lcid_functions = []         # lcid test functions in AStyleTestLoc.cpp
    translate_functions = []    # lcid test functions in AStyleTestLoc.cpp
    localizer_path = libastyle.get_astyle_directory() + "/src/ASLocalizer.h"
    if not os.path.exists(localizer_path):
        libastyle.system_exit("\nCannot locate file " + localizer_path)
    test_path = libastyle.get_astyletest_directory() + "/srcloc/AStyleTestLoc.cpp"
    if not os.path.exists(test_path):
        libastyle.system_exit("\nCannot locate file " + test_path)
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    get_language_strings(language_strings, localizer_path)
    get_name_functions(name_functions, test_path)
    get_lcid_functions(lcid_functions, test_path)
    get_translate_functions(translate_functions, test_path)

    print("Checking ASLocalizer.h classes to AStyleTestLoc.cpp test functions.")
    total_language_strings = len(language_strings)
    print("There are {0} language strings in ASLocalizer.h.".format(total_language_strings))
    print()

    find_string_diffs(language_strings, name_functions, "name functions")
    find_string_diffs(language_strings, lcid_functions, "lcid functions")
    find_string_diffs(language_strings, translate_functions, "translate functions")

    if __print_variables:
        language_strings.sort()
        name_functions.sort()
        lcid_functions.sort()
        translate_functions.sort()
        print()
        print(language_strings)
        print()
        print(name_functions)
        print()
        print(lcid_functions)
        print()
        print(translate_functions)

# -----------------------------------------------------------------------------

def find_string_diffs(language_strings, test_functions, test_function_type=""):
    """ Find differences in header and class variables lists.
    """
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_functions = set(language_strings) - set(test_functions)
    missing_classes = set(test_functions) - set(language_strings)

    if len(missing_functions) > 0:
        missing_functions = list(missing_functions)
        missing_functions.sort()
        print("{0} missing test functions in {1}".format(
            str(len(missing_functions), test_function_type)))
        print(missing_functions)

    if len(missing_classes) > 0:
        missing_classes = list(missing_classes)
        missing_classes.sort()
        print("{0} missing classes in ASLocalizer.h for test {1}:".format(
            str(len(missing_classes)), test_function_type))
        print(missing_classes)

    diffs = len(missing_functions) + len(missing_classes)
    if diffs == 0:
        print("There are NO diffs in the test {0}!!!".format(test_function_type))
    else:
        print("There are {0} diffs in the test {1}.".format(diffs, test_function_type))

# -----------------------------------------------------------------------------

def get_language_strings(language_strings, localizer_path):
    """ Read ASLocalizer.h and save the language names of the derived Translation classes.
    """
    language_total = 0          # total language classess extracted
    lines = 0                   # current input line number
    file_in = open(localizer_path, 'r')

    # extract the ASLocalizer language class strings
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line[:2] == "//":
            continue

        # extract the derived class names
        if (line.startswith("class")
        and "public Translation" in line):
            start = line.find("class")
            if start == -1:
                continue
            start += 5
            end = line.find(':', start)
            if end == -1:
                continue
            lang_string = line[start:end].strip()
            language_strings.append(lang_string)
            language_total += 1

    file_in.close()
    if __print_detail:
        print("{0} language strings from ASLocalizer.h".format(language_total))

# -----------------------------------------------------------------------------

def get_lcid_functions(lcid_functions, test_path):
    """ Read the AStyleTestLoc.cpp file and save the LCID test functions.
    """

    lcid_total = 0          # number of name test functions
    lines = 0               # current input line number
    file_in = open(test_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line[:2] == "//":
            continue

       # extract the translation names
        if (line.startswith("TEST")
        and "ASLocalizerLCID" in line
        and not "Unrecognized" in line):
            start = line.find(',')
            if start == -1:
                continue
            start += 1
            end = line.find("Translation", start)
            if end == -1:
                continue

            # extract the test function language
            lcid_string = line[start:end].strip()
            lcid_functions.append(lcid_string)
            lcid_total += 1

    file_in.close()
    if __print_detail:
        print("{0} lcid test functions".format(lcid_total))

# -----------------------------------------------------------------------------

def get_name_functions(name_functions, test_path):
    """ Read the AStyleTestLoc.cpp file and save the name test functions.
    """

    name_total = 0          # number of name test functions
    lines = 0               # current input line number
    file_in = open(test_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line[:2] == "//":
            continue

       # extract the translation names
        if (line.startswith("TEST")
        and "ASLocalizerName" in line
        and not "Unrecognized" in line):
            start = line.find(',')
            if start == -1:
                continue
            start += 1
            end = line.find("Translation", start)
            if end == -1:
                continue

            # extract the test function language
            name_string = line[start:end].strip()
            name_functions.append(name_string)
            name_total += 1

    file_in.close()
    if __print_detail:
        print("{0} name test functions".format(name_total))

# -----------------------------------------------------------------------------

def get_translate_functions(translate_functions, test_path):

    """ Read the AStyleTestLoc.cpp file and save the translate test functions.
    """
    translate_total = 0     # number of name test functions
    lines = 0               # current input line number
    file_in = open(test_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line[:2] == "//":
            continue

       # extract the translation names
        if (line.startswith("TEST_F")
        and "TranslationF" in line):
            start = line.find(',')
            if start == -1:
                continue
            start += 1
            end = line.find(')', start)
            if end == -1:
                continue

            # extract the test function language
            translate_string = line[start:end].strip()
            translate_functions.append(translate_string)
            translate_total += 1

    file_in.close()
    if __print_detail:
        print("{0} name test functions".format(translate_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
