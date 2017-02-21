#! /usr/bin/python3
"""Modify the Artistic Style copyright date in the astyle source.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import re
import sys
# local libraries
import libastyle

# global variables ------------------------------------------------------------

__old_date = "2016"
__new_date = "2017"

__file_update = False           # should the files be updated?

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    print("Modify Copyright Date from", __old_date, "to", __new_date)
    if not __file_update:
        print("\nFILES NOT UPDATED")
    # must use this version for newline option on the file open
    if platform.python_implementation() == "CPython" and sys.version_info[0] >= 3:
        pass
    else:
        libastyle.system_exit("Must use CPython version 3 or greater")
    print()

    # source file directories
    source_extension_list = [".h", ".cpp", ".m", ".java", ".py", ".cs"]
    source_directory_list = [libastyle.get_project_directory(True) + "AStyle/src",
                             libastyle.get_project_directory(True) + "AStyleDev/src-c",
                             libastyle.get_project_directory(True) + "AStyleDev/src-j",
                             libastyle.get_project_directory(True) + "AStyleDev/src-o",
                             libastyle.get_project_directory(True) + "AStyleDev/src-p",
                             libastyle.get_project_directory(True) + "AStyleDev/src-s",
                             libastyle.get_project_directory(True) + "AStyleTest/src",
                             libastyle.get_project_directory(True) + "AStyleTest/srccon",
                             libastyle.get_project_directory(True) + "AStyleTest/srci18n",
                             libastyle.get_project_directory(True) + "AStyleTest/srclib",
                             libastyle.get_project_directory(True) + "AStyleTest/srcloc",
                             libastyle.get_project_directory(True) + "AStyleTest/srcx",
                             libastyle.get_project_directory(True) + "AStyleWin/src",
                             libastyle.get_project_directory(True) + "AStyleWx/src",
                             libastyle.get_project_directory(True) + "AStyleWxTest/src",
                             libastyle.get_project_directory(True) + "AStyleWxTest/srcx"]
    update_source_files(source_directory_list, source_extension_list)
    if not __file_update:
        print("FILES NOT UPDATED")

# -----------------------------------------------------------------------------

def get_requested_files(directory_path, file_extension_list, changeable_files_list):
    """Get all files in a directory, including sub directories.
       Check the file extensions to determine if it is a changable file.
       Write qualified files to the changeable files list.
       The copyright date is checked by a different procedure.
    """
    for dirpath, unused, filenames in os.walk(directory_path):
        # process each file in the directory
        for filename in filenames:
            unused, ext = os.path.splitext(filename)
            # check for the requested files
            for unused, file_extension in enumerate(file_extension_list):
                if (ext == file_extension
                        or (ext == '' and filename == file_extension)):
                    filepath = os.path.join(dirpath, filename)
                    filepath = filepath.replace('\\', '/')
                    changeable_files_list.append(filepath)
                    break
    changeable_files_list.sort()

# -----------------------------------------------------------------------------

def get_printble_filepath(absolute_filepath):
    """Get the filepath without the Project directory path.
    """
    prefix = len(libastyle.get_project_directory(True))
    filepath = absolute_filepath[prefix:]
    return filepath

# -----------------------------------------------------------------------------

def modify_input_file(filepath, updated_file_list):
    """Find and replace the copyright date in input file_path.
       The new file is output to the updated_file_list in the calling function.
       "True" is returned if the file was updated, otherwise "False"
    """
    lines = 0               # current input line number
    file_changed = False    # the file has changed

    # find and change matching lines
    pattern = re.compile("[Cc]opyright")
    with open(filepath, mode='r', encoding='utf-8', newline='') as file_in:
        for line in file_in:
            lines += 1
            if pattern.search(line) and __old_date in line:
                line = line.replace(__old_date, __new_date)
                file_changed = True
            updated_file_list.append(line)
    return file_changed

# -----------------------------------------------------------------------------

def update_source_files(source_directory_list, source_extension_list):
    """Update version number in the dource files.
       The directory list and file extensions are in main().
    """
    # get source files in the directory list
    source_total = 0
    for unused, source_directory in enumerate(source_directory_list):
        source_files_list = []
        get_requested_files(source_directory, source_extension_list, source_files_list)
        # update the files with shared object references
        for unused, source_file in enumerate(source_files_list):
            updated_file = []
            file_changed = modify_input_file(source_file, updated_file)
            if file_changed:
                filepath = get_printble_filepath(source_file)
                print(filepath)
                source_total += 1
                if __file_update:
                    write_output_file(updated_file, source_file)
    print("Source Files", source_total)
    print()

# -----------------------------------------------------------------------------

def write_output_file(updated_file, file_path):
    """Write the updated file to disk.
       Used by both the project files and the source files.
       Rename the current file by appending a ".orig" extension.
       Write a new file to replace the .orig file.
    """
    orig_file = file_path + ".orig"
    # remove an existion .orig file
    if os.path.isfile(orig_file):
        os.remove(orig_file)
    # rename the current file
    os.rename(file_path, orig_file)
    # write the new file
    with open(file_path, mode='w', encoding='utf-8', newline='') as file_out:
        for line in updated_file:
            file_out.write(line)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
