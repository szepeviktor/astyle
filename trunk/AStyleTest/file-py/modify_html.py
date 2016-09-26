#! /usr/bin/python
"""Modify the Html files to change the markup format.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import os
import platform
import sys
# local libraries
import libastyle

# global variables ------------------------------------------------------------

# select only one at a time
__html_folder = libastyle.get_project_directory(True) + "AStyle/doc"
#__html_folder = libastyle.get_project_directory(True) + "AStyleDev/doc"
#__html_folder = libastyle.get_project_directory(True) + "AStyleWx/doc"


__file_update = False           # should the files be updated?

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    print("Modify Html files from", correct_path_separators(__html_folder))
    if not __file_update:
        print("Files NOT Updated")
    # must use this version for newline option on the file open
    if platform.python_implementation() == "CPython" and sys.version_info[0] >= 3:
        pass
    else:
        libastyle.system_exit("Must use CPython version 3 or greater")
    print()

    # update html files
    file_list = glob.glob(__html_folder + "/*.html")
    file_list.sort()
    for file_path in file_list:
        print(correct_path_separators(file_path))
        update_html_files(file_path)

# -----------------------------------------------------------------------------

def correct_path_separators(file_path):
    """Correct the separators in a file path.
    """
    if os.name == "nt":
        path = file_path.replace('/', '\\')
    else:
        path = file_path.replace('\\', '/')
    return path

# -----------------------------------------------------------------------------

def update_html_files(file_path):
    """Correct the Html.
       Input lines will end with '\n' in universal newlines mode.
       They will be changes at file output.
    """
    prev_line_index = 0
    prev_line = ''
    is_in_pre = False
    file_out_list = []
    file_in = open(file_path, 'r')

    for line_in in file_in:
        # process the line
        line = line_in.strip()
        if len(line) == 0:
            file_out_list.append(line_in)
            continue
        # process preformatted lines
        # this is probably not necessary, but just in case
        if "</pre" in line:
            is_in_pre = False
            file_out_list.append(line_in)
            continue
        if is_in_pre:
            file_out_list.append(line_in)
            continue
        if "<pre" in line:
            is_in_pre = True
            file_out_list.append(line_in)
            continue
        # get previous line
        if len(file_out_list) > 0:
            prev_line_index = len(file_out_list) - 1
            prev_line = file_out_list[prev_line_index].strip()
        # append </p> to the previous line
        if line.startswith("</p>"):
            file_out_list[prev_line_index] = file_out_list[prev_line_index].rstrip('\n')
            file_out_list[prev_line_index] += line + '\n'
            continue
        # combine <h? lines
        if line.startswith("</h") and line[3:4].isdigit():
            file_out_list[prev_line_index] = file_out_list[prev_line_index].rstrip('\n')
            file_out_list[prev_line_index] += line + '\n'
            continue
        if prev_line.startswith("<h") and prev_line[2:3].isdigit() and not "</h" in prev_line:
            file_out_list[prev_line_index] = file_out_list[prev_line_index].rstrip('\n')
            file_out_list[prev_line_index] += line + '\n'
            continue
        file_out_list.append(line_in)
    file_in.close()
    write_output_file(file_out_list, file_path)

# -----------------------------------------------------------------------------

def write_output_file(file_out_list, file_path):
    """Write the updated file to disk.
       Output lines will end with '\r\n'.
       if __file_update the old file will have a .orig extension.
       if not __file_update the new file will have a .new extension..
    """
    if __file_update:
        orig_file = file_path + ".orig"
        # remove an existing .orig file
        if os.path.isfile(orig_file):
            os.remove(orig_file)
        # rename the current file
        os.rename(file_path, orig_file)
        # write the file
        with open(file_path, mode='w', newline='\r\n') as file_out:
            for line in file_out_list:
                file_out.write(line)
    else:
        new_file = file_path + ".new"
         # remove an existing .new file
        if os.path.isfile(new_file):
            os.remove(new_file)
        # write the new file
        with open(new_file, mode='w', newline='\r\n') as file_out:
            for line in file_out_list:
                file_out.write(line)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()
