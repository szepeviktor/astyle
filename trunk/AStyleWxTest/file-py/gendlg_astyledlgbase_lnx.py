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
__styles = 0            # number of style lines changed
__tabs = 0              # number of tab lines changed
__indents = 0           # number of indent lines changed
__pads = 0              # number of pad lines changed
__formats = 0           # number of format lines changed
__others = 0            # number of other lines changed

# constants - the number to change
# does not include labels or spacers
__style_total = 15      # number of style lines to change
__tab_total = 9         # number of tab lines to change
__indent_total = 10     # number of indent lines to change
__pad_total = 11        # number of pad lines to change
__format_total = 11     # number of format lines to change
__other_total = 5       # number of other lines to change

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    libastylewx.set_text_color("yellow")
    print(libastylewx.get_python_version())
    print("Generating AStyleDlgBaseLnx")
    filedir = libastylewx.get_astylewx_directory(True) + "dialog"
    os.chdir(filedir)
    infile = filedir + os.sep + "AStyleDlgBase.cpp"
    outfile = filedir + os.sep + "AStyleDlgBaseLnx.cpp"
    create_astyledlggui_lnx(infile, outfile)
    print_totals()

# -----------------------------------------------------------------------------

def create_astyledlggui_lnx(infile, outfile):
    """Read the input file and find the lines similar to
       m_styleSizer->Add( m_bracketsNone, 0, wxALL, 5 );
       and call a function to correct the line.
    """
    global __lines
    file_in = open(infile, 'r')
    file_out = open(outfile, 'w')
    for line in file_in:
        __lines += 1
        # find the sizer lines with a border
        # but not notebook or button sizers
        if (line.find("Sizer->Add") != -1
                and line.find("notebookSizer") == -1
                and line.find("buttonSizer") == -1
                and line.find("sdbSizer") == -1):
            # make sure it has a name (bypass spacers)
            if line.find("( m_") != -1:
                # don't include the preview STC
                if line.find("PreviewSTC") == -1:
                    # this sizer needs special handling
                    if line.find("m_forceTabSizer") != -1:
                        line = process_force_tab(line)
                    elif line.find("m_breakAfterLogicalSizer") != -1:
                        line = process_break_after_logical(line)
                    else:
                        line = process_line(line)
        file_out.write(line)
    file_in.close()
    file_out.close()

# -----------------------------------------------------------------------------

def process_line(line):
    """Replace 'wxALL' with 'wxTOP' or '0' in the line.
    """
    if line.find(" wxALL,") == -1:
        print("Cannot find replacement in line " + str(__lines))
    # the first line gets a top border
    if (line.find("m_styleNone") != -1
            or line.find("m_spaceIndent") != -1
            or line.find("m_attachNamespace") != -1
            or line.find("m_indentClassBlocks") != -1
            or line.find("m_breakHeaderBlocks") != -1
            or line.find("m_breakClosingBraces") != -1
            or line.find("m_padMethodPrefix") != -1):
        line = line.replace("wxALL", "wxTOP|wxLEFT")
    # the last line gets a bottom border
    elif (line.find("styleLisp") != -1
            or line.find("attachExternC") != -1):
        line = line.replace("wxALL", "wxBOTTOM|wxLEFT")
    else:
        if (line.find("indentLength") == -1
                and line.find("maxCodeLength") == -1):
            line = line.replace("wxALL", "wxLEFT")
    accum_totals(line)
    return line

# -----------------------------------------------------------------------------

def process_force_tab(line):
    """Special handling for forceTabSizer.
        wxALL is replaced only for the m_useTabLength check box.
    """
    if line.find("m_useTabLength") != -1:
        if line.find(" wxALL,") == -1:
            print("Cannot find replacement in line " + str(__lines))
        line = line.replace("wxALL", "wxLEFT")
        accum_totals(line)
    return line


# -----------------------------------------------------------------------------

def process_break_after_logical(line):
    """Special handling for breakAfterLogicalSizer.
        wxALL is replaced only for the m_breakAfterLogical check box.
    """
    if line.find("m_breakAfterLogical,") != -1:
        if line.find(" wxALL,") == -1:
            print("Cannot find replacement in line " + str(__lines))
        line = line.replace("wxALL", "wxLEFT")
        accum_totals(line)
    return line


# -----------------------------------------------------------------------------

def accum_totals(line):
    """Accumulate total changes for each tab page
    """
    global __styles, __tabs, __indents, __pads, __formats, __others
    if line.find("m_styleSizer") != -1:
        __styles += 1
    elif (line.find("m_tabSizer") != -1
            or line.find("m_forceTabSizer") != -1
            or line.find("m_modifySizer") != -1):
        __tabs += 1
    elif line.find("m_indentSizer") != -1:
        __indents += 1
    elif line.find("m_padSizer") != -1:
        __pads += 1
    elif (line.find("m_formatSizer") != -1
            or line.find("m_breakAfterLogicalSizer") != -1):
        __formats += 1
    elif line.find("m_otherSizer") != -1:
        __others += 1
    else:
        print("Cannot find total category in line " + str(__lines))

# -----------------------------------------------------------------------------

def print_totals():
    """print to run totals and check for differences.
    """
    errors = False
    if __styles != __style_total:
        styles_text = "There are {0} style diffs."
        print(styles_text.format(__styles - __style_total))
        errors = True
    if __tabs != __tab_total:
        tabs_text = "There are {0} tab diffs."
        print(tabs_text.format(__tabs - __tab_total))
        errors = True
    if __indents != __indent_total:
        indents_text = "There are {0} indent diffs."
        print(indents_text .format(__indents - __indent_total))
        errors = True
    if __pads != __pad_total:
        pads_text = "There are {0} pad diffs."
        print(pads_text.format(__pads - __pad_total))
        errors = True
    if __formats != __format_total:
        formats_text = "There are {0} format diffs."
        print(formats_text.format(__formats - __format_total))
        errors = True
    if __others != __other_total:
        others_text = "There are {0} other diffs."
        print(others_text.format(__others - __other_total))
        errors = True
    if not errors:
        print("There are NO diffs in the number of lines to be changed!!!")


# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
