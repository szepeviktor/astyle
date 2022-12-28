#! /usr/bin/python3
"""Modify the Artistic Style version number in the shared library compiles.
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

# windows
__old_release = "31"
__new_release = "32"

# linux
__old_solibver = "3.1.0"
__new_solibver = "3.2.0"

__file_update = False           # should the files be updated?

# -----------------------------------------------------------------------------

def main():
    """Main processing function."""
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    print("Modify AStyle Version from", __old_release, "to", __new_release)
    print("Modify Solib  Version from", __old_solibver, "to", __new_solibver)
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
                              libastyle.get_project_directory(True) + "AStyleWx/build",
                              libastyle.get_project_directory(True) + "AStyleWxTest/build"]
    update_project_files(project_directory_list, project_extension_list)

    # source file directories
    source_extension_list = [".properties", ".cpp", ".m", ".java", ".cs"]
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

    # change the internal version number in cmake
    cmakelists_file_path = libastyle.get_project_directory(True) + "AStyle/CMakeLists.txt"
    update_cmakelists(cmakelists_file_path)

    # change the internal version number in astyle_main source
    astyle_main_file_path = libastyle.get_project_directory(True) + "AStyle/src/astyle_main.cpp"
    update_astyle_main(astyle_main_file_path)

    if not __file_update:
        print("\nFILES NOT UPDATED")

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
    """Find and replace the version number in input file_path.
       Used by both the project files and the source files.
       The new file is output to the updated_file_list in the calling function.
       "True" is returned if the file was updated, otherwise "False"
    """
    lines = 0               # current input line number
    file_changed = False    # the file has changed

    # find and change matching lines
    astyle = re.compile("[Aa][Ss]tyle" + __old_release)
    with open(filepath, mode='r', encoding='utf-8', newline='') as file_in:
        for line in file_in:
            lines += 1
            if astyle.search(line):
                line = line.replace(__old_release, __new_release)
                file_changed = True
            elif "MAJORVER" in line:
                line = line.replace(__old_solibver[:1], __new_solibver[:1])
                file_changed = True
            elif "MINORVER" in line:
                line = line.replace(__old_solibver[2:3], __new_solibver[2:3])
                file_changed = True
            elif "PATCHVER" in line:
                line = line.replace(__old_solibver[4:5], __new_solibver[4:5])
                file_changed = True
            elif "SOLIBVER" in line:
                line = line.replace(__old_solibver, __new_solibver)
                file_changed = True
            updated_file_list.append(line)
    return file_changed

# -----------------------------------------------------------------------------

def update_astyle_main(filepath):
    """Update version number in the astyle_main source file.
       The file path is in main().
    """
    lines = 0               # current input line number
    file_changed = False    # the file has changed
    updated_file = []
    source_total = 0
    new_release_string = ''

    # get release number string
    old_astyle_release = __old_release[0] + '.' + __old_release[1]
    if len(__old_release) > 2:
        old_astyle_release = old_astyle_release + '.' + __old_release[2]
    new_astyle_release = __new_release[0] + '.' + __new_release[1]
    if len(__new_release) > 2:
        new_astyle_release = new_astyle_release + '.' + __new_release[2]

    # find and change matching lines
    with open(filepath, mode='r', encoding='utf-8', newline='') as source_file:
        for line in source_file:
            lines += 1
            if "g_version =" in line:
                printable_path = get_printble_filepath(filepath)
                print(printable_path, '(', "line", lines, ')')
                # first check for multiple updating runs
                if old_astyle_release not in line:
                    libastyle.system_exit("ERROR: cannot find old release in line")
                if new_astyle_release in line:
                    libastyle.system_exit("ERROR: release is already changed to "
                                          + str(new_astyle_release))
                line = line.replace(old_astyle_release, new_astyle_release + " beta")
                release_start = line.find(new_astyle_release)
                if release_start == -1:
                    libastyle.system_exit("ERROR: cannot find release start in line")
                release_end = line.rfind('"')
                if release_end == -1 or release_end <= release_start:
                    libastyle.system_exit("ERROR: cannot find release end in line")
                new_release_string = line[release_start:release_end]
                file_changed = True
            updated_file.append(line)
    if file_changed:
        print("Changed from release", old_astyle_release, "to", new_release_string)
        # second check for multiple updating runs
        if not verify_release_number(new_release_string):
            libastyle.system_exit("ERROR: bad astyle_main release number")
        source_total += 1
        if __file_update:
            write_output_file(updated_file, filepath)
    else:
        libastyle.system_exit("ERROR: astyle_main was not changed")
    print("astyle_main Source File", source_total)

# -----------------------------------------------------------------------------

def update_cmakelists(cmakelists_file_path):
    """Update version number in the CMakeLists.txt file.
       The directory list and file extensions are in main().
    """
    updated_file = []
    # find and change matching lines
    with open(cmakelists_file_path, mode='r', encoding='utf-8', newline='') as cmakelists_file:
        file_changed = modify_input_file(cmakelists_file_path, updated_file)
        if file_changed:
            cmakelists_file = get_printble_filepath(cmakelists_file_path)
            print(cmakelists_file)
    if __file_update:
        write_output_file(updated_file, cmakelists_file_path)

# -----------------------------------------------------------------------------

def update_project_files(project_directory_list, project_extension_list):
    """Update version number in the project files.
       The directory list and file extensions are in main().
    """
    # get project files in the directory list
    project_total = 0
    project_directory_name = "AStyle"
    for unused, project_directory in enumerate(project_directory_list):
        project_files_list = []
        get_requested_files(project_directory, project_extension_list, project_files_list)
        # update the files with shared object references
        for unused, project_file in enumerate(project_files_list):
            updated_file = []
            file_changed = modify_input_file(project_file, updated_file)
            if file_changed:
                filepath = get_printble_filepath(project_file)
                end = filepath.find('/')
                main_directory = filepath[:end]
                if main_directory != project_directory_name:
                    print(project_directory_name, "Project Files", project_total)
                    print()
                    project_directory_name = main_directory
                    project_total = 0
                print(filepath)
                project_total += 1
                if __file_update:
                    write_output_file(updated_file, project_file)
    print(project_directory_name, "Project Files", project_total)
    print()

# -----------------------------------------------------------------------------

def update_source_files(source_directory_list, source_extension_list):
    """Update version number in the source files.
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

def verify_release_number(new_release_string):
    """Verify the new release number string is a valid length.
    """
    # check for multiple updating runs
    new_release_number = new_release_string
    release_stop = new_release_string.find(' ')
    if release_stop != -1:
        new_release_number = new_release_string[:release_stop]
    if ((len(__new_release) == 2 and len(new_release_number) > 3)
            or (len(__new_release) == 3 and len(new_release_number) > 5)):
        return False
    return True

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
