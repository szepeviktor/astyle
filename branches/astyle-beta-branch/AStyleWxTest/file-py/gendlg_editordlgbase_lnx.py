#! /usr/bin/python3
"""Create the Linux AStyleDlgBaseLnx.cpp file from the Windows AStyleDlgBase.cpp.
   It removes the borders to compress the dialogs.
"""
# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
# local libraries
import libastylewx

# global variables ------------------------------------------------------------

# accumulators
__lines = 0             # current input line number
__options = 0           # number of options lines changed
__fonts = 0             # number of fonts lines changed
__styles = 0            # number of styles lines changed

# constants - the number to change
# does not include labels or spacers
__options_total = 5     # number of options lines to change
__fonts_total = 0       # number of fonts lines to change
__styles_total = 3      # number of styles lines to change

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
    print("Generating EditorDlgBaseLnx")
    filedir = libastylewx.get_astylewx_directory(True) + "dialog"
    os.chdir(filedir)
    infile = filedir + os.sep + "EditorDlgBase.cpp"
    outfile = filedir + os.sep + "EditorDlgBaseLnx.cpp"
    create_editordlggui_lnx(infile, outfile)
    print_totals()

# -----------------------------------------------------------------------------

def create_editordlggui_lnx(infile, outfile):
    """Read the input file and find the lines similar to
       m_styleSizer->Add( m_bracketsNone, 0, wxALL, 5 );
       Replace 'wxALL' with 'wxTOP' or '0' and write the new file.
    """
    global __lines
    file_in = open(infile, 'r')
    file_out = open(outfile, 'w')
    for line in file_in:
        __lines += 1
        # find the sizer lines with a border
        if (line.find("Sizer") != -1
                and line.find("->Add") != -1):
            # make sure it has a name (bypass spacers and fonts)
            if (line.find("( m_") != -1
                    and line.find("( m_default") == -1
                    and line.find("( m_comment") == -1
                    and line.find("( m_styles") == -1
                    and line.find("( m_notebook") == -1
                    and line.find("( m_reset") == -1
                    and line.find("( m_sdbSizer") == -1):
                # replace the spacing
                if line.find("|wxALL,") == -1:
                    print("Cannot find replacement in line " + str(__lines))
                line = line.replace("|wxALL", "")
                accum_totals(line)
        file_out.write(line)
    file_in.close()
    file_out.close()

# -----------------------------------------------------------------------------

def accum_totals(line):
    """Accumulate total changes for each tab page
    """
    global __options, __fonts, __styles
    if line.find("optionsSizer") != -1:
        __options += 1
    elif line.find("fonts") != -1 and line.find("Sizer") != -1:
        __fonts += 1
    elif line.find("stylesSizer") != -1:
        __styles += 1
    else:
        print("Cannot find total category in line " + str(line))

# -----------------------------------------------------------------------------

def print_totals():
    """print to run totals and check for differences.
    """
    errors = False
    if __options != __options_total:
        styles_text = "There are {0} options diffs."
        print(styles_text.format(__options - __options_total))
        errors = True
    if __fonts != __fonts_total:
        tabs_text = "There are {0} fonts diffs."
        print(tabs_text.format(__fonts - __fonts_total))
        errors = True
    if __styles != __styles_total:
        indents_text = "There are {0} styles diffs."
        print(indents_text .format(__styles - __styles_total))
        errors = True
    if not errors:
        print("There are NO diffs in the number of lines to be changed!!!")


# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
