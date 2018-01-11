#! /usr/bin/python3
"""Change AStyleWxGui files to wxNotebook, wxChoicebook, wxListbook, or wxTreebook.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import libastylewx      # local directory

# this is the CtrlBook type ---------------------------------------------------
# set this to the new object
# NOTE: additions here require changes to AStyleDlg.h and Editor.Dlg.h

#__new_book = "wxChoicebook"
#__new_book = "wxListbook"      # does not work with 2.8
#__new_book = "wxNotebook"
__new_book = "wxTreebook"

# global variables ------------------------------------------------------------

# short and long page names
# the "modify" page is added by AStyleDlg
__short_name = ['"Style"', '"Tabs"', '"Indent"', '"Pad"', '"Format"', '"Other"']
__long_name  = ['"Brace Style"', '"Tabs/Spaces"', '"Indentation"',
                '"Padding"', '"Formatting"', '"Objective-C"']
# accums
__num_cb = 0        # changes to wxChoicebook
__num_lb = 0        # changes to wxListbook
__num_nb = 0        # changes to wxNotebook
__num_tb = 0        # changes to wxTreebook

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """

    file_paths = ["AStyleDlgBase.h",
                  "AStyleDlgBase.cpp",
                  "EditorDlgBase.h",
                  "EditorDlgBase.cpp",
                  ]

    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
#   print("Changing to {0}".format(__new_book))
    filedir = libastylewx.get_astylewx_directory(True) + "dialog"
    os.chdir(filedir)
    for file_path in file_paths:
        change_variables(file_path)
        print_totals(file_path)

# -----------------------------------------------------------------------------

def change_variables(file_path):
    """Process a file.
    """
    global __num_cb, __num_lb, __num_nb, __num_tb

    if not os.path.exists(file_path):
        libastylewx.system_exit("No file to process: " + file_path)
    # extra lines for wxTreebook
    tba = '\tm_notebook->AddPage( NULL, wxT("Artistic Style Options"), false );\n'
    tbe = '\tm_notebook->AddPage( NULL, wxT("Editor Options"), false );\n'

    # get variables
    new_header = get_new_header()
    new_macro = get_new_macro()
    file_in = open(file_path, 'r')
    updated_lines = []

    for line in file_in:
        if len(line) == 0 or line.startswith("//"):
            updated_lines.append(line)
            continue
        # replace objects (wxNotebook) and events (wxNotebookEvent)
        if "wxChoicebook" in line and __new_book != "wxChoicebook":
            line = line.replace("wxChoicebook", __new_book)
            __num_cb += 1
        elif "wxListbook" in line and __new_book != "wxListbook":
            line = line.replace("wxListbook", __new_book)
            __num_lb += 1
        elif "wxNotebook" in line and __new_book != "wxNotebook":
            line = line.replace("wxNotebook", __new_book)
            __num_nb += 1
        elif "wxTreebook" in line and __new_book != "wxTreebook":
            line = line.replace("wxTreebook", __new_book)
            __num_tb += 1

        # replace include
        if "choicebk.h" in line and __new_book != "wxChoicebook":
            line = line.replace("choicebk.h", new_header)
            __num_cb += 1
        elif "listbook.h" in line and __new_book != "wxListbook":
            line = line.replace("listbook.h", new_header)
            __num_lb += 1
        elif "notebook.h" in line and __new_book != "wxNotebook":
            line = line.replace("notebook.h", new_header)
            __num_nb += 1
        elif "treebook.h" in line and __new_book != "wxTreebook":
            line = line.replace("treebook.h", new_header)
            __num_tb += 1

        # replace page change event (EVT_NOTEBOOK_PAGE_CHANGED)
        if "_CHOICEBOOK_" in line and __new_book != "wxChoicebook":
            line = line.replace("_CHOICEBOOK_", new_macro)
            __num_cb += 1
        elif "_LISTBOOK_" in line and __new_book != "wxListbook":
            line = line.replace("_LISTBOOK_", new_macro)
            __num_lb += 1
        elif "_NOTEBOOK_" in line and __new_book != "wxNotebook":
            line = line.replace("_NOTEBOOK_", new_macro)
            __num_nb += 1
        elif "_TREEBOOK_" in line and __new_book != "wxTreebook":
            line = line.replace("_TREEBOOK_", new_macro)
            __num_tb += 1

        # replace AddPage strings
        # remove tba and tbe from all files
        # tba and tbe will be restated to wxTreebook
        if "AddPage" in line or "AddSubPage" in line:
            if "AddPage" in line and "NULL" in line:
                continue
            if __new_book == "wxChoicebook":
                line = process_choicebook_pages(line)
            elif __new_book == "wxListbook":
                line = process_listbook_pages(line)
            elif __new_book == "wxNotebook":
                line = process_notebook_pages(line)
            elif __new_book == "wxTreebook":
                if "m_stylePage" in line:
                    updated_lines.append(tba)
                if "m_optionsPage" in line:
                    updated_lines.append(tbe)
                line = process_treebook_pages(line)

        updated_lines.append(line)

    file_in.close()

    if __num_cb or __num_lb or __num_nb or __num_tb:
        write_output_file(updated_lines, file_path)

# -----------------------------------------------------------------------------

def get_new_header():
    """Get a header for the requested global __new_book.
    """
    if "wxChoicebook" in __new_book:
        return "choicebk.h"
    if "wxListbook" in __new_book:
        return "listbook.h"
    if "wxNotebook" in __new_book:
        return "notebook.h"
    if "wxTreebook" in __new_book:
        return "treebook.h"

# -----------------------------------------------------------------------------

def get_new_macro():
    """Get a macro for the requested global __new_book.
    """
    if "wxChoicebook" in __new_book:
        return "_CHOICEBOOK_"
    if "wxListbook" in __new_book:
        return "_LISTBOOK_"
    if "wxNotebook" in __new_book:
        return "_NOTEBOOK_"
    if "wxTreebook" in __new_book:
        return "_TREEBOOK_"

# -----------------------------------------------------------------------------

def print_totals(file_path):
    """Print file totals.
    """
    global __num_cb, __num_lb, __num_nb, __num_tb
    # strip file path from the file name
    file_name = file_path
    dialog_dir = file_path.find("dialog")
    if dialog_dir != -1:
        file_name = file_path[dialog_dir + 7:]
    if __num_cb != 0:
        print("wxChoicebook to {0}: {1} in {2}".format(__new_book, __num_cb, file_name))
    if __num_lb != 0:
        print("wxListbook to {0}: {1} in {2}".format(__new_book, __num_lb, file_name))
    if __num_nb != 0:
        print("wxNotebook to {0}: {1} in {2}".format(__new_book, __num_nb, file_name))
    if __num_tb != 0:
        print("wxTreebook to {0}: {1} in {2}".format(__new_book, __num_tb, file_name))
    if __num_cb == __num_lb == __num_nb == __num_tb == 0:
        print("no changes to {0} in {1}".format(__new_book, file_name))
    __num_cb = __num_lb = __num_nb = __num_tb = 0

# -----------------------------------------------------------------------------

def process_choicebook_pages(line):
    """Process the Choicebook AddPage lines.
       Choicebook uses long names.
    """
    if "AddSubPage" in line:
        line = line.replace("AddSubPage", "AddPage")
    # replace short name with long name if any
    for i in range(0, len(__short_name)):
        if __short_name[i] in line:
            line = line.replace(__short_name[i], __long_name[i])
    return line

# -----------------------------------------------------------------------------

def process_listbook_pages(line):
    """Process the Listbook AddPage lines.
       Listbook uses long names.
    """
    if "AddSubPage" in line:
        line = line.replace("AddSubPage", "AddPage")
    # replace short name with long name if any
    for i in range(0, len(__short_name)):
        if __short_name[i] in line:
            line = line.replace(__short_name[i], __long_name[i])
    return line

# -----------------------------------------------------------------------------

def process_notebook_pages(line):
    """Process the Notebook AddPage lines.
       Notebook uses short names.
    """
    if "AddSubPage" in line:
        line = line.replace("AddSubPage", "AddPage")
    # replace long name with short name if any
    for i in range(0, len(__short_name)):
        if __long_name[i] in line:
            line = line.replace(__long_name[i], __short_name[i])
    return line

# -----------------------------------------------------------------------------

def process_treebook_pages(line):
    """Process the Treebook AddPage lines.
       Treebook uses long names.
    """
    if "AddPage" in line:
        line = line.replace("AddPage", "AddSubPage")
    # replace short name with long name if any
    for i in range(0, len(__short_name)):
        if __short_name[i] in line:
            line = line.replace(__short_name[i], __long_name[i])
    return line

# -----------------------------------------------------------------------------

def write_output_file(updated_lines, file_path):
    """Rename the current file by appending a ".orig" extension.
       Write a new file to replace the .orig file.
    """
    orig_file = file_path + ".orig"
    # remove an existion .orig file
    if os.path.isfile(orig_file):
        os.remove(orig_file)
    # rename the current file
    os.rename(file_path, orig_file)
    # write the new file
    file_out = open(file_path, "w")
    for line in updated_lines:
        file_out.write(line)
    file_out.close()

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
