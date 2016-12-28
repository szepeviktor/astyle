#! /usr/bin/python
"""Check AStyleIFace constructor to class variables
   in the header file to verify all variables are initialized.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastylewx		# local directory

# global variables ------------------------------------------------------------

__print_detail = False				# print line numbers and total variables
__print_variables = False			# print the variables in the lists

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""

    header_variables = []		# variables in astyle.h
    class_variables = []			# variables in the class constructor
    header_path = libastylewx.get_astylewx_directory() + "/src/AStyleIFace.h"
    astyleiface_path = libastylewx.get_astylewx_directory() + "/src/AStyleIFace.cpp"

    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
    get_header_variables(header_variables, header_path)
    get_constructor_variables(class_variables, astyleiface_path)

    print("Checking AStyleIFace header to class constructor.")
    total_variables = len(header_variables)
    print("There are {0} variables in the header list.".format(total_variables))
    print()

    find_class_diffs(header_variables, class_variables)

    if __print_variables:
        print(header_variables)
        print(class_variables)

# -----------------------------------------------------------------------------

def find_class_diffs(header_variables, class_variables):
    """Find differences in header and class variables lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_header = set(class_variables) - set(header_variables)
    missing_class = set(header_variables) - set(class_variables)

    if len(missing_header) > 0:
        missing_header = list(missing_header)
        missing_header.sort()
        print(str(len(missing_header)) + " missing header variables:")
        print(missing_header)

    if len(missing_class) > 0:
        missing_class = list(missing_class)
        missing_class.sort()
        print(str(len(missing_class)) + " missing class variables:")
        print(missing_class)

    diffs = len(missing_header) + len(missing_class)
    if diffs == 0:
        print("There are NO diffs in the class constructor variables!!!")
    else:
        print("There are {0} diffs in the class constructor variables.".format(diffs))

# -----------------------------------------------------------------------------

def get_constructor_variables(class_variables, astyleiface_path):
    """Read the AStyleIFace file and save the class constuctor variables."""

    class_lines = [0, 0]	# line numbers for class constructor
    class_total = 0			# total variables for class constructor
    lines = 0					# current input line number
    file_in = open(astyleiface_path, 'r')

    # get class constructor lines
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        # start between the following lines
        if line.find("AStyleIFace::AStyleIFace()") != -1:
            class_lines[0] = lines + 1
            continue
        if (class_lines[0] == 0
                or class_lines[0] >= lines):
            continue
        # find ending bracket
        if line.find('}') != -1:
            class_lines[1] = lines
            break
        # get the variable name
        first_space = line.find(' ')
        if first_space == -1:
            continue
        variable_name = line[0:first_space].strip()
        if len(variable_name) == 0:
            continue
        class_variables.append(variable_name)
        class_total += 1

    file_in.close()
    if __print_detail:
        print("{0} {1} class constructor".format(class_lines, class_total))

# -----------------------------------------------------------------------------

def get_header_variables(header_variables, header_path):
    """Read the header file and save the AStyleIFace variables."""

    header_lines = [0, 0]		# line numbers for header
    header_total = 0			# total variables for header
    header_brackets = 0			# unmatched brackets in the header
    lines = 0					# current input line number
    file_in = open(header_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue

        # start between the following lines
        if line.find("class AStyleIFace") != -1:
            header_lines[0] = lines + 1
            header_brackets += 1
            continue
        if (header_lines[0] == 0
                or header_lines[0] >= lines):
            continue
        # count brackets
        if line.find('{') != -1:
            header_brackets += 1
        if line.find('}') != -1:
            header_brackets -= 1
        # bypass class modifiers
        if (line.find("public:") != -1
                or line.find("private:") != -1
                or line.find("protected:") != -1):
            continue
        # bypass functions
        if (line.find('(') != -1
                or line.find(')') != -1):
            continue
        # get the variable name
        semi_colon = line.find(';')
        if semi_colon == -1:
            continue
        last_space = line[:semi_colon].rfind(' ')
        if last_space == -1:
            continue
        variable_name = line[last_space:semi_colon].strip()
        if variable_name[0] == '*':
            variable_name = variable_name[1:]
        header_variables.append(variable_name)
        header_total += 1

    file_in.close()
    if __print_detail:
        print("{0} {1} header".format(header_lines, header_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
