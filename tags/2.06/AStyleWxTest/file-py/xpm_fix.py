#! /usr/bin/python
"""Convert xpm files from "static char *" to "static const char *".
   to eliminate gcc compiler warnings.

   Convert .bmp to .xpm with XnView
   1. Open .bmp in XnView.
   2. Image > count colours used > get the count of colors.
   3. Image > Convert to Colours > 8 or 16 depending on #2.
   4. Image > Edit Palette > Enable transparency
       Choose transparent color, usually C0C0C0 or FF00FF.
   5. File > Save As  > Choose XPM.
   When all are changed run this script to emiminate comiler wanings.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
# local libraries
import libastylewx

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
    print("Converting xpm files")
    xpm_files = get_xpm_files()
    change_files(xpm_files)

# -----------------------------------------------------------------------------

def change_files(xpm_files):
    """Change the files from "static char *" to "static const char *"
       to eliminate gcc compiler warnings.
       Input is a xpm_files list.
    """
    # process list of files
    num_files_changes = 0
    warnings = 0
    for file_path in xpm_files:
        file_in = open(file_path, "r")
        updated_lines = []
        line_num = 0
        file_changed = False
        # find the line to change
        for line in file_in:
            line_num += 1
            unused, tail = os.path.split(file_path)
            # check for "static char *"
            if line.startswith("static char *"):
                line = line.replace("static char *",
                                    "static const char *")
                file_changed = False
                num_files_changes += 1
                print(tail)
            # check the number of colors
            # line 4 contains width, height, num colors, chars per pixel
            if line_num == 4:
                line4 = line.split()
                if int(line4[3]) > 8:
                    print(tail + "  number of colors: " + line4[3])
                    warnings += 1
            # check for a transparent color
            if line_num == 6:
                if line.find("c None") == -1:
                    print(tail + "  no transparent color")
                    warnings += 1
            updated_lines.append(line)
        file_in.close()
        if file_changed:
            write_output_file(updated_lines, file_path)
    message = "\n{0} of {1} files changed, {2} warnings\n"
    print(message.format(num_files_changes, len(xpm_files), warnings))

# -----------------------------------------------------------------------------

def get_xpm_files():
    """Find files with a ".xpm" extension.
       Return a list of xpm_files.
    """
    xpm_files = []
    filedir = get_image_directory()
    all_files = os.listdir(filedir)
    for filename in all_files:
        filepath = filedir + filename
        unused, ext = os.path.splitext(filepath)
        if ext == ".xpm":
            xpm_files.append(filepath)
    xpm_files.sort()
    return xpm_files

# -----------------------------------------------------------------------------

def get_image_directory():
    """Get the image directory path for the os environment.
       Extract the directory from path[0]
    """
    imagedir = libastylewx.get_astylewx_directory() + "/image/"
    imagedir = imagedir.replace('\\', '/')
    # verify the path
    if not os.path.isdir(imagedir):
        message = "Cannot find image directory: " + imagedir
        libastylewx.system_exit(message)
    return  imagedir

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
