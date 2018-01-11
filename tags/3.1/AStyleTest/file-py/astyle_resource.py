#! /usr/bin/python3
""" Check ASResource vectors for various criteria.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle        # local directory

# global variables ------------------------------------------------------------

__print_detail = False              # print line numbers and total variables
__print_variables = False           # print the variables in the lists

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""

    header_variables = []               # header vector variables
    np_header_variables = []            # non-paren header variables
    pre_block_variables = []            # pre-block statement variables
    pre_command_variables = []      # pre-command header variables
    resource_path = libastyle.get_astyle_directory() + "/src/ASResource.cpp"

    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    get_header_variables(header_variables, resource_path)
    get_np_header_variables(np_header_variables, resource_path)
    get_pre_block_variables(pre_block_variables, resource_path)
    get_pre_command_variables(pre_command_variables, resource_path)

    print("Checking header variables to non-paren, pre-block, and pre-command.")
    total_variables = len(header_variables)
    print("There are {0} variables in the header list.".format(total_variables))
    print()

    find_header_diffs(header_variables, np_header_variables)
    find_pre_block_diffs(header_variables, pre_block_variables)
    find_pre_command_diffs(header_variables, pre_command_variables)

    if __print_variables:
        print(header_variables)
        print(np_header_variables)
        print(pre_block_variables)
        print(pre_command_variables)

# -----------------------------------------------------------------------------

def convert_class_functions(line):
    """Convert class initializer functions to the corresponding variable."""
    first_paren = line.find('(')
    if first_paren == -1:
        return line
    if "initContainer" in line:
        line = line[first_paren + 1:]
        first_comma = line.find(',')
        if first_comma != -1:
            line = line[:first_comma]
        line = line.strip()
    elif "->" in line:
        line = ''
    elif "ASBase::init" in line:
        line = ''
    elif "initStatic" in line:
        line = ''
    elif "setSpaceIndentation" in line:
        line = "indentLength"
    elif "setMaxInStatementIndentLength" in line:
        line = "maxInStatementIndent"
    elif "setClassIndent" in line:
        line = "classIndent"
    elif "setSwitchIndent" in line:
        line = "switchIndent"
    elif "setCaseIndent" in line:
        line = "caseIndent"
    elif "setBlockIndent" in line:
        line = "blockIndent"
    elif "setBraceIndent" in line:
        line = "braceIndent"
    elif "setNamespaceIndent" in line:
        line = "namespaceIndent"
    elif "setLabelIndent" in line:
        line = "labelIndent"
    elif "setEmptyLineFill" in line:
        line = "emptyLineFill"
    elif "setCStyle" in line:
        line = "fileType"
    elif "setPreprocessorIndent" in line:
        line = "preprocessorIndent"
    elif "setMinConditionalIndentOption" in line:
        line = "minConditionalOption"
    else:
        line = "unidentified function: " + line
    return line

# -----------------------------------------------------------------------------

def find_header_diffs(header_variables, np_header_variables):
    """Find differences in header and non-paren header variables lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_header = set(np_header_variables) - set(header_variables)

    if len(missing_header) > 0:
        missing_header = sorted(missing_header)
        print(str(len(missing_header)) + " missing header variables:")
        print(missing_header)

    diffs = len(missing_header)
    if diffs == 0:
        print("There are NO missing non-paren header variables!!!")
    else:
        print("There are {0} missing non-paren header variables.".format(diffs))

# -----------------------------------------------------------------------------

def find_pre_block_diffs(header_variables, pre_block_variables):
    """Find common elements in header and pre-block variables lists."""
    # A set is an unordered collection with no duplicate elements.
    # Converting to a 'set' will remove duplicates.
    # The & operator computes the intersection of the sets.
    # The intersection will be the elements in BOTH sets.
    duplicate_header = set(pre_block_variables) & set(header_variables)

    if len(duplicate_header) != 0:
        duplicate_header = sorted(duplicate_header)
        print()
        print(str(len(duplicate_header)) + " duplicate pre-block variables:")
        print(duplicate_header)

    diffs = len(duplicate_header)
    if diffs == 0:
        print("There are NO duplicates in the pre-block variables!!!")
    else:
        print("There are {0} duplicates in the pre-block variables.".format(diffs))

# -----------------------------------------------------------------------------

def find_pre_command_diffs(header_variables, pre_command_variables):
    """Find differences in header and pre-comand variables lists."""
    # A set is an unordered collection with no duplicate elements
    # Converting to a 'set' will remove duplicates.
    # The & operator computes the intersection of the sets.
    # The intersection will be the elements in BOTH sets.
    duplicate_header = set(pre_command_variables) & set(header_variables)

    if len(duplicate_header) != 0:
        duplicate_header = sorted(duplicate_header)
        print()
        print(str(len(duplicate_header)) + " duplicate pre-command variables:")
        print(duplicate_header)

    diffs = len(duplicate_header)
    if diffs == 0:
        print("There are NO duplicates in the pre-command variables!!!")
    else:
        print("There are {0} duplicates in the pre-command variables.".format(diffs))

# -----------------------------------------------------------------------------

def get_header_variables(header_variables, resource_path):
    """Read the ASResource file and save the header variables."""
    header_total = 0            # total variables for headers
    lines = 0                   # current input line number
    file_in = open(resource_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        # find the header write commands
        if "headers->push_back" not in line:
            continue
        # get the variable name
        start = line.find("AS_")
        if start == -1:
            continue
        end = line[start:].find(')')
        if end == -1:
            continue
        variable_name = line[start:start + end].strip()
        header_variables.append(variable_name)
        header_total += 1

    file_in.close()
    if __print_detail:
        print("{0} headers".format(header_total))

# -----------------------------------------------------------------------------

def get_np_header_variables(np_header_variables, resource_path):
    """Read the ASResource file and save the non-paren header variables."""
    np_header_total = 0     # total variables for non-paren headers
    lines = 0                   # current input line number
    file_in = open(resource_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        # find the non-paren header write commands
        if "nonParenHeaders->push_back" not in line:
            continue
        # get the variable name
        start = line.find("AS_")
        if start == -1:
            continue
        end = line[start:].find(')')
        if end == -1:
            continue
        variable_name = line[start:start + end].strip()
        np_header_variables.append(variable_name)
        np_header_total += 1

    file_in.close()
    if __print_detail:
        print("{0} non-paren headers".format(np_header_total))

# -----------------------------------------------------------------------------

def get_pre_block_variables(pre_block_variables, resource_path):
    """Read the ASResource file and save the pre-block statement variables."""
    pre_block_total = 0     # total variables for pre-block statements
    lines = 0                   # current input line number
    file_in = open(resource_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        # find the pre-block statement write commands
        if "preBlockStatements->push_back" not in line:
            continue
        # get the variable name
        start = line.find("AS_")
        if start == -1:
            continue
        end = line[start:].find(')')
        if end == -1:
            continue
        variable_name = line[start:start + end].strip()
        pre_block_variables.append(variable_name)
        pre_block_total += 1

    file_in.close()
    if __print_detail:
        print("{0} pre-block statements".format(pre_block_total))

    # -----------------------------------------------------------------------------

def get_pre_command_variables(pre_command_variables, resource_path):
    """Read the ASResource file and save the pre-command header variables."""
    pre_command_total = 0   # total variables for pre-command headers
    lines = 0                       # current input line number
    file_in = open(resource_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        # find the pre-command header write commands
        if "preCommandHeaders->push_back" not in line:
            continue
        # get the variable name
        start = line.find("AS_")
        if start == -1:
            continue
        end = line[start:].find(')')
        if end == -1:
            continue
        variable_name = line[start:start + end].strip()
        pre_command_variables.append(variable_name)
        pre_command_total += 1

    file_in.close()
    if __print_detail:
        print("{0} pre-command headers".format(pre_command_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
