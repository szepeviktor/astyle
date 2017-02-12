#! /usr/bin/python

""" One time script to remove wxT macro from AStyleWx source.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import os
import shutil
# local libraries
import libastylewx

# global variables ------------------------------------------------------------

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """
    #src_olddir = libastylewx.get_astylewx_directory() + "/srcOLD"
    #src_newdir = libastylewx.get_astylewx_directory() + "/src"
    # change line 61 or 62  when the following are used
    src_olddir = libastylewx.get_astylewxtest_directory() + "/srcOLD"
    src_newdir = libastylewx.get_astylewxtest_directory() + "/src"

    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())

    if not os.path.isdir(src_olddir):
        print("rename src to srcOLD")
        os.rename(src_newdir, src_olddir)
        os.mkdir(src_newdir)

    print("copy srcOLD to src")
    file_list_old = glob.glob(src_olddir + "/*")
    for file_path in file_list_old:
        shutil.copy(file_path, src_newdir)

    print("convert src")
    file_list_new = glob.glob(src_newdir + "/*")
    for file_path in file_list_new:
        process_file(file_path)

# -----------------------------------------------------------------------------

def process_file(file_path):
    """ Remove the wxT macros from the src file.
    """
    print(file_path)
    updated_lines = []

    # find the line to change
    file_in = open(file_path, "r")
    for line in file_in:
        count = line.count('wxT(')
        if count > 0:
            line = line.replace('wxT(', '')
            # if "AStyleDisplay" in file_path:
            if "AStyleFormat_Test" in file_path:
                line = line.replace('")', '"')
            else:
                line = line.replace(')"', '?"')
                line = line.replace(')!', '?!')
                line = line.replace(').', '?.')
                line = line.replace(')>', '?>')
                line = line.replace(')', '', count)
                line = line.replace('?"', ')"')
                line = line.replace('?!', ')!')
                line = line.replace('?.', ').')
                line = line.replace('?>', ')>')
        updated_lines.append(line)
    file_in.close()

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
