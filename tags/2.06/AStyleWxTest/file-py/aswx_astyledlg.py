#! /usr/bin/python

"""Check AStyleDlgBase.h to AstyleDlg.h to verify that all virtual fuctions are overridden.
   Check AStyleDlgBase.h to AstyleDlgBase.cpp to verify that all identifiers have an exent
   and therefore a preview display.
   Check AStyleDlgBase.h to AstyleDlg.cpp to verify that all radio buttons hhave a
   bind event so a mouse click will be displayed in the preview widdow..
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastylewx      # local directory

# global variables ------------------------------------------------------------

# these can be changed to print the details
__print_detail = False          # print line numbers and total functions
__print_functions = False       # print the functions in the lists
__print_identifiers = False     # print the identifiers in the lists

# these should not be changed
__is_resizable = False          # the dialog is resizeable

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""

    # lists to compare virtual function overrides
    dlggui_functions = []           # functions in AStyleDlgBase.h
    dlg_functions = []              # functions in AStyleDlg.h
    # lists to compare events
    dlggui_identifiers = []         # identifiers in AStyleDlgBase.h
    dlggui_events = []              # event identifiers in AStyleDlgBase.cpp
    # lists to compare bind events
    dlggui_radio_buttons = []       # radio buttons in AStyleDlgBase.h
    dlg_bind_events = []     # bind events in AStyleDlg.cpp
    # file paths
    dlggui_path = libastylewx.get_astylewx_directory() + "/dialog/AStyleDlgBase.h"
    dlg_path = libastylewx.get_astylewx_directory() + "/src/AStyleDlg.h"
    dlgguisrc_path = libastylewx.get_astylewx_directory() + "/dialog/AStyleDlgBase.cpp"
    dlgsrc_path = libastylewx.get_astylewx_directory() + "/src/AStyleDlg.cpp"

    # extract data
    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
    print("AStyleDlg")
    # get lists to compare virtual function overrides
    get_dlggui_functions(dlggui_functions, dlggui_path)
    get_dlg_functions(dlg_functions, dlg_path)
    # lists to compare events
    get_dlggui_identifiers(dlggui_identifiers, dlggui_path)
    get_dlgguisrc_event_identifiers(dlggui_events, dlgguisrc_path)
    # lists to compare bind events
    get_dlggui_radio_buttons(dlggui_radio_buttons, dlggui_path)
    get_dlgsrc_conect_events(dlg_bind_events, dlgsrc_path)
    # find diffs
    find_function_diffs(dlggui_functions, dlg_functions)
    find_identifier_diffs(dlggui_identifiers, dlggui_events)
    find_radio_button_diffs(dlggui_radio_buttons, dlg_bind_events)
    if __is_resizable:
        print("AStyleDlgBase is resizeable.")

    if __print_functions:
        print(dlggui_functions)
        print(dlg_functions)
    if __print_identifiers:
        print(dlggui_identifiers)
        print(dlggui_events)

# -----------------------------------------------------------------------------

def extract_void_function_name(line):
    """Extract the function name of a function with a "void' return value.
       Extracts the text between 'void' and the first opening paren.
       Returns the function name.
    """

    name_start = line.find("void")
    if name_start == -1:
        return ''
    function_name = line[name_start + len("void"):].strip()
    name_end = function_name.find('(')
    if name_end == -1:
        return ''
    function_name = function_name[:name_end].strip()
    return function_name

# -----------------------------------------------------------------------------

def find_function_diffs(dlggui_functions, dlg_functions):
    """Find differences in dlggui and dlg functions lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_functions = set(dlggui_functions) - set(dlg_functions)

    if len(missing_functions) > 0:
        missing_functions = list(missing_functions)
        missing_functions.sort()
        print(missing_functions)

    diffs = len(missing_functions)
    if diffs == 0:
        print("There are NO missing function overrides!!!")
    else:
        print("There are {0} missing function overrides.".format(diffs))

# -----------------------------------------------------------------------------

def find_identifier_diffs(dlggui_identifiers, dlggui_events):
    """Find differences in dlggui and dlg functions lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_identifiers = set(dlggui_identifiers) - set(dlggui_events)

    if len(missing_identifiers) > 0:
        missing_identifiers = list(missing_identifiers)
        missing_identifiers.sort()
        print(missing_identifiers)

    diffs = len(missing_identifiers)
    if diffs == 0:
        print("There are NO missing events!!!")
    else:
        print("There are {0} missing events.".format(diffs))

# -----------------------------------------------------------------------------

def find_radio_button_diffs(dlggui_radio_buttons, dlg_bind_events):
    """Find differences in radio buttons and bind event lists."""
    # A set is an unordered collection with no duplicate elements
    # converting to a 'set' will remove duplicates
    missing_identifiers = set(dlggui_radio_buttons) - set(dlg_bind_events)

    if len(missing_identifiers) > 0:
        missing_identifiers = list(missing_identifiers)
        missing_identifiers.sort()
        print(missing_identifiers)

    diffs = len(missing_identifiers)
    if diffs == 0:
        print("There are NO missing bind events!!!")
    else:
        print("There are {0} missing bind events.".format(diffs))

# -----------------------------------------------------------------------------

def get_dlg_functions(dlg_functions, dlg_path):
    """Read the header file and save the AStyleDlg 'void' functions."""

    function_total = 0      # total virtual functions for header
    lines = 0                   # current input line number
    file_in = open(dlg_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # find the void functions
        if not line.startswith("void"):
            continue
        # get the function name
        virtual_function_name = extract_void_function_name(line)
        if virtual_function_name == '':
            continue
        dlg_functions.append(virtual_function_name)
        function_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleDlg functions".format(function_total))

# -----------------------------------------------------------------------------

def get_dlggui_functions(dlggui_functions, dlggui_path):
    """Read the header file and save the AStyleDlgBase 'virtual void' functions."""
    virtual_start = False       # start looking for virtual functions
    header_total = 0            # total virtual functions for header
    lines = 0                   # current input line number
    file_in = open(dlggui_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        # extra check for resizeable dialog
        if (line.find("AStyleDlgBase(") != -1
                and line.find("wxRESIZE_BORDER") != -1):
            global __is_resizable
            __is_resizable = True

        # start with the following line
        if line.startswith("// Virtual event handlers"):
            virtual_start = True
            continue
        if virtual_start != True:
            continue
        # find the virtual functions
        if not line.startswith("virtual void"):
            continue
        # get the function name
        virtual_function_name = extract_void_function_name(line)
        if virtual_function_name == '':
            continue
        dlggui_functions.append(virtual_function_name)
        header_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleDlgBase functions".format(header_total))

# -----------------------------------------------------------------------------

def get_dlggui_identifiers(dlggui_identifiers, dlggui_path):
    """Read the header file and save the AStyleDlgBase identifiers."""
    identifiers_start = False   # start looking for identifiers
    identifier_total = 0            # total identifiers for header
    lines = 0                       # current input line number
    file_in = open(dlggui_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # start with the following line
        if line.startswith("enum"):
            identifiers_start = True
            continue
        if identifiers_start != True:
            continue
        # end with the following line
        if line.startswith("};"):
            identifiers_start = False
            continue

        # find the identifiers
        if not line.startswith("ID_"):
            continue
        # get the identifier
        id_start = line.find("ID_")
        line = line[id_start:]
        id_end = line.find(',')
        id_space = line.find(' ')
        if id_space != -1 and id_space < id_end:
            id_end = id_space
        if id_end == -1:
            id_end = len(line)
        identifier = line[:id_end]
        # radio button idebtifiers that use a bind event (checked separately)
        if (identifier.startswith("ID_INDENT_LENGTH")
                or  identifier.startswith("ID_TAB_LENGTH")):
            continue
        # identifiers without events
        if (identifier.endswith("_PAGE")
                or  identifier.endswith("_STC")
                or  identifier == "ID_MIN_CONDITIONAL"
                or  identifier == "ID_MAX_INSTATEMENT"
                or  identifier == "ID_ALIGN_POINTER"):
            continue
        dlggui_identifiers.append(identifier)
        identifier_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleDlgBase identifiers".format(identifier_total))

# -----------------------------------------------------------------------------

def get_dlggui_radio_buttons(dlggui_radio_buttons, dlggui_path):
    """Read the header file and save the AStyleDlgBase radio buttons."""
    buttons_total = 0           # total radio buttons for header
    lines = 0                       # current input line number
    file_in = open(dlggui_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # find the identifiers
        if not line.startswith("wxRadioButton*"):
            continue
        # get the identifier
        name_start = line.find("m_")
        name_end = line.find(';')
        identifier = line[name_start:name_end]
        dlggui_radio_buttons.append(identifier)
        buttons_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleDlgBase radio buttons".format(buttons_total))

# -----------------------------------------------------------------------------

def get_dlgguisrc_event_identifiers(dlggui_events, dlgguisrc_path):
    """Read the source file and save the AStyleDlgBase event identifiers."""
    identifiers_start = False       # start looking for event identifiers
    identifier_total = 0            # total event identifiers for source
    lines = 0                       # current input line number
    file_in = open(dlgguisrc_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # start with the following line
        if line.startswith("BEGIN_EVENT_TABLE"):
            identifiers_start = True
            continue
        if identifiers_start != True:
            continue
        # end with the following line
        if line.startswith("END_EVENT_TABLE"):
            identifiers_start = False
            continue

        # find the identifiers
        if not line.startswith("EVT_"):
            continue
        # get the identifier
        if line.find("wxID_") != -1:
            continue
        id_start = line.find("ID_")
        if id_start == -1:
            continue
        id_end = line.find(',')
        if id_end == -1:
            continue
        identifier = line[id_start:id_end]
        dlggui_events.append(identifier)
        identifier_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleDlgBase event identifiers".format(identifier_total))

# -----------------------------------------------------------------------------

def get_dlgsrc_conect_events(dlg_bind_events, dlgsrc_path):
    """Read the source file and save the AStyleDlg bind events."""
    bind_start = False       # start looking for bind events
    bind_total = 0               # total bind events for source
    lines = 0                       # current input line number
    file_in = open(dlgsrc_path, 'r')

    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue

        # start with the following line (the constructor)
        if line.startswith("AStyleDlg::AStyleDlg"):
            bind_start = True
            continue
        if bind_start != True:
            continue
        # end with the following line (the destructor)
        if line.startswith("AStyleDlg::~AStyleDlg"):
            bind_start = False
            continue

        # find the identifiers
        if line.find("->Bind") == -1:
            continue
        # get the identifier
        id_start = line.find("m_")
        if id_start == -1:
            continue
        id_end = line.find('->')
        if id_end == -1:
            continue
        identifier = line[id_start:id_end]
        dlg_bind_events.append(identifier)
        bind_total += 1

    file_in.close()
    if __print_detail:
        print("{0} AStyleDlg bind events".format(bind_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
