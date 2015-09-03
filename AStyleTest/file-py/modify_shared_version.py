#! /usr/bin/python3
"""Modify the Artistic Style version number in the shared library compiles.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle        # local directory
import os
import platform
import re
import sys

# global variables ------------------------------------------------------------

__old_release = "2.05.1"
__new_release = "2.06"

__file_update = False           # should the files be updated?

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""
    libastyle.set_text_color()
    print (libastyle.get_python_version())
    print("Modify Shared Version from", __old_release, "to", __new_release)
    if not __file_update:
        print("\nFILES NOT UPDATED")
    # must use this version for newline option on the file open
    if platform.python_implementation() == "CPython" and sys.version_info[0] >= 3:
        pass
    else:
        libastyle.system_exit("Must use CPython version 3 or greater")
    print()

    # project file directories
    project_extension_list = ["Makefile", ".cbp", ".vcproj", ".vcxproj", ".pbxproj"]
    project_directory_list = [libastyle.get_project_directory(True) + "AStyle/build",
                              libastyle.get_project_directory(True) + "AStyleDev/build",
                              libastyle.get_project_directory(True) + "AStyleTest/build",
                              libastyle.get_project_directory(True) + "AStyleWin/build",
                              libastyle.get_project_directory(True) + "AStyleWx/build"]
    update_project_files(project_directory_list, project_extension_list)

    # source file directories
    source_extension_list = [".properties", ".cpp", ".m", ".java", ".py", ".cs"]
    source_directory_list = [libastyle.get_project_directory(True) + "AStyle/src",
                             libastyle.get_project_directory(True) + "AStyleDev/src-c",
                             libastyle.get_project_directory(True) + "AStyleDev/src-o",
                             libastyle.get_project_directory(True) + "AStyleDev/src-j",
                             libastyle.get_project_directory(True) + "AStyleDev/src-p",
                             libastyle.get_project_directory(True) + "AStyleDev/src-s",
                             libastyle.get_project_directory(True) + "AStyleTest/src",
                             libastyle.get_project_directory(True) + "AStyleWin/src",
                             libastyle.get_project_directory(True) + "AStyleWx/src"]
    # exclude files with utf-8 encoding (...Other.cpp seems to be an error in linux)
    source_excludes = [libastyle.get_project_directory(True) + "AStyle/src/ASLocalizer.cpp",
                       libastyle.get_project_directory(True) + "AStyleTest/src/AStyleTest_Other.cpp"]
    update_source_files(source_directory_list, source_extension_list, source_excludes)
    if not __file_update:
        print("FILES NOT UPDATED")

# -----------------------------------------------------------------------------

def get_requested_files(directory_path, file_extension_list, changeable_files_list):
    """Get all files in a directory, including sub directories.
       Check the file extensions to determine if it is a changable file.
       Write qualified files to the changeable files list.
       The version number is checked by a different procedure.
    """
    for dirpath, unused, filenames in os.walk(directory_path):
        # process each file in the directory
        for filename in filenames:
            unused, ext = os.path.splitext(filename)
            # check for the requested files
            for i in range(len(file_extension_list)):
                if (ext == file_extension_list[i]
                or (ext == '' and filename == file_extension_list[i])):
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
    """Find and replace the version number in input file_path.
       Used by both the project files and the source files.
       The new file is output to the updated_file_list in the calling function.
       "True" is returned if the file was updated, otherwise "False"
    """
    lines = 0               # current input line number
    file_changed = False    # the file has changed

    # find and change matching lines
    pattern = re.compile("[Aa][Ss]tyle-" + __old_release)
    with open(filepath, mode='r', newline='') as file_in:
        for line in file_in:
            lines += 1
            if pattern.search(line) or ('"' + __old_release + '"' in line):
                line = line.replace(__old_release, __new_release)
                file_changed = True
            updated_file_list.append(line)
    return file_changed

# -----------------------------------------------------------------------------

def update_project_files(project_directory_list, project_extension_list):
    """Update version number in the project files.
       The directory list and file extensions are in main().
    """
    # get project files in the directory list
    project_total = 0
    project_directory = "AStyle"
    for i in range(len(project_directory_list)):
        project_files_list = []
        get_requested_files(project_directory_list[i], project_extension_list, project_files_list)
        # update the files with shared object references
        for j in range(len(project_files_list)):
            updated_file = []
            file_changed = modify_input_file(project_files_list[j], updated_file)
            if file_changed:
                filepath = get_printble_filepath(project_files_list[j])
                end = filepath.find('/')
                main_directory = filepath[:end]
                if main_directory != project_directory:
                    print(project_directory, "Project Files", project_total)
                    print()
                    project_directory = main_directory
                    project_total = 0
                print(filepath)
                project_total += 1
                if __file_update:
                    write_output_file(updated_file, project_files_list[j])
    print(project_directory, "Project Files", project_total)
    print()

# -----------------------------------------------------------------------------

def update_source_files(source_directory_list, source_extension_list, source_excludes):
    """Update version number in the dource files.
       The directory list and file extensions are in main().
    """
    # get source files in the directory list
    source_total = 0
    for i in range(len(source_directory_list)):
        source_files_list = []
        get_requested_files(source_directory_list[i], source_extension_list, source_files_list)
        # remove excludes
        for j in range(len(source_excludes)):
            source_excludes[j] = source_excludes[j].replace('\\', '/')
            if source_excludes[j] in source_files_list:
                source_files_list.remove(source_excludes[j])
        # update the files with shared object references
        for k in range(len(source_files_list)):
            updated_file = []
            file_changed = modify_input_file(source_files_list[k], updated_file)
            if file_changed:
                filepath = get_printble_filepath(source_files_list[k])
                print(filepath)
                source_total += 1
                if __file_update:
                    write_output_file(updated_file, source_files_list[k])
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
    with open(file_path, mode='w', newline='') as file_out:
        for line in updated_file:
            file_out.write(line)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
