#! /usr/bin/python3
"""Generate the suppression file and run cppcheck.
   Input the AStyleWx source files and output the suppression file
   with the current line numbers.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import subprocess
# local libraries
import libastylewx

# global variables ------------------------------------------------------------

__expected_version = "1.74"
__src_dir = libastylewx.get_astylewx_directory() + "/src/"
__py_dir = libastylewx.get_astylewxtest_directory() + "/file-py/"
__suppression_path = __py_dir + "cppcheck-suppress"

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    generate_suppression_file()
    run_cppcheck()

# -----------------------------------------------------------------------------

def generate_suppression_file():
    """Generate the suppression file.
    """
    outfile = open(__suppression_path, 'w')

    # File Suppressions
    file_suppression_list = ["\n// File Suppressions\n"]
    process_file_suppressions(file_suppression_list)
    outfile.writelines(file_suppression_list)

    # AboutDlg header
    aboutdlg_header_list = ["\n// AboutDlg.h\n"]
    process_aboutdlg_header(aboutdlg_header_list)
    outfile.writelines(aboutdlg_header_list)

    # ASApp
    asapp_list = ["\n// ASApp.cpp\n"]
    process_asapp(asapp_list)
    outfile.writelines(asapp_list)

    # AStyleDisplay
    astyledisplay_list = ["\n// AStyleDisplay.cpp\n"]
    process_astyledisplay(astyledisplay_list)
    outfile.writelines(astyledisplay_list)

    # AStyleDisplay Header
    astyledisplay_header_list = ["\n// AStyleDisplay.h\n"]
    process_astyledisplay_header(astyledisplay_header_list)
    outfile.writelines(astyledisplay_header_list)

    # AStyleDlg
    astyledlg_list = ["\n// AStyleDlg.cpp\n"]
    process_astyledlg(astyledlg_list)
    outfile.writelines(astyledlg_list)

    # ASEditor
    aseditor_list = ["\n// ASEditor.cpp\n"]
    process_aseditor(aseditor_list)
    outfile.writelines(aseditor_list)

    # AStyleFormat
    astyleformat_list = ["\n// AStyleFormat.cpp\n"]
    process_astyleformat(astyleformat_list)
    outfile.writelines(astyleformat_list)

    # AStyleIFace
    astyleiface_list = ["\n// AStyleIFace.cpp\n"]
    process_astyleiface(astyleiface_list)
    outfile.writelines(astyleiface_list)

    # AStyleWx
    astylewx_list = ["\n// AStyleWx.cpp\n"]
    process_astylewx(astylewx_list)
    outfile.writelines(astylewx_list)

    # AStyleWx header
    astylewx_header_list = ["\n// AStyleWx.h\n"]
    process_astylewx_header(astylewx_header_list)
    outfile.writelines(astylewx_header_list)

    # Config
    config_list = ["\n// Config.cpp\n"]
    process_config(config_list)
    outfile.writelines(config_list)

    # EditorDlg
    editordlg_list = ["\n// EditorDlg.cpp\n"]
    process_editordlg(editordlg_list)
    outfile.writelines(editordlg_list)

    # Encoding
    encoding_list = ["\n// Encoding.cpp\n"]
    process_encoding(encoding_list)
    outfile.writelines(encoding_list)

    # FileManager
    filemanager_list = ["\n// FileManager.cpp\n"]
    process_filemanager(filemanager_list)
    outfile.writelines(filemanager_list)

    # Indent
    indent_list = ["\n// Indent.cpp\n"]
    process_indent(indent_list)
    outfile.writelines(indent_list)

    outfile.close()

# -----------------------------------------------------------------------------

def process_aboutdlg_header(aboutdlg_header_list):
    """Generate suppressions for AboutDlg header.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AboutDlg.h"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("AboutDlg(wxWindow*"):
            aboutdlg_header_list.append("noExplicitConstructor:" + src_path + ":" + str(lines)
                                        + "\t\t// AboutDlg\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_asapp(asapp_list):
    """Generate suppressions for ASApp.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "ASApp.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if "OnExit" in line:
            asapp_list.append("unusedFunction:" + src_path + ":" + str(lines)
                              + "\t\t\t\t// OnExit\n")
        if "OnInit" in line:
            asapp_list.append("unusedFunction:" + src_path + ":" + str(lines)
                              + "\t\t\t\t// OnInit\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_astyledisplay(astyledisplay_list):
    """Generate suppressions for AStyleDisplay.
    """
    lines = 0				# current input line number
    ints_processed = 0		# only want certain 'int start'
    src_path = __src_dir + "AStyleDisplay.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if line.startswith("int start"):
            ints_processed += 1
            if ints_processed == 2:
                astyledisplay_list.append("unreadVariable:" + src_path + ":" + str(lines)
                                          + "\t\t// int start\n")
                astyledisplay_list.append("variableScope:" + src_path + ":" + str(lines)
                                          + "\t\t// int start\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_astyledisplay_header(astyledisplay_header_list):
    """Generate suppressions for AStyleDisplay HEADER.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AStyleDisplay.h"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        # for some reason this doesn't work! - false positive?
        if "StcIndent_MaxInStatementDisplay" in line:
            astyledisplay_header_list.append("functionConst:" + src_path + ":" + str(lines)
                                             + "\t\t// StcIndent_MaxInStatementDisplay\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_astyledlg(astyledlg_list):
    """Generate suppressions for AStyleDlg.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AStyleDlg.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if "OnFormatClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnFormatClick\n")
        if "OnIndentClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnIndentClick\n")
        if "OInit" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OInit\n")
        if "OnModifierClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnModifierClick\n")
        if "OnNotebookPageChanged" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnNotebookPageChanged\n")
        if "OnOkClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnOkClick\n")
        if "OnOtherClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnOtherClick\n")
        if "OnPadClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnPadClick\n")
        if "OnResetAllClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnResetAllClick\n")
        if "OnSettingsClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnSettingsClick\n")
        if "OnStyleClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnStyleClick\n")
        if "OnTabClick" in line:
            astyledlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnTabClick\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_aseditor(aseditor_list):
    """Generate suppressions for Editor.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "ASEditor.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
    file_in.close()

# -----------------------------------------------------------------------------

def process_astyleformat(astyleformat_list):
    """Generate suppressions for AStyleForamt.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AStyleFormat.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        # useInitializationList error
        if line.startswith("m_firstLineMarker"):
            astyleformat_list.append("useInitializationList:" + src_path + ":" + str(lines)
                                     + "\t\t// m_firstLineMarker\n")
        if line.startswith("m_minSelectionMarker"):
            astyleformat_list.append("useInitializationList:" + src_path + ":" + str(lines)
                                     + "\t\t// m_minSelectionMarker\n")
        if line.startswith("m_maxSelectionMarker"):
            astyleformat_list.append("useInitializationList:" + src_path + ":" + str(lines)
                                     + "\t\t// m_maxSelectionMarker\n")
        if line.startswith("m_bookmark1Marker"):
            astyleformat_list.append("useInitializationList:" + src_path + ":" + str(lines)
                                     + "\t\t// m_bookmark1Marker\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_astyleiface(astyleiface_list):
    """Generate suppressions for AStyleIFace.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AStyleIFace.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
    file_in.close()

# -----------------------------------------------------------------------------

def process_astylewx(astylewx_list):
    """Generate suppressions for AStyleWx.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AStyleWx.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if line.startswith("ID_RECENT_FILE"):  # in EVT_MENU
            continue
    file_in.close()

# -----------------------------------------------------------------------------

def process_astylewx_header(astylews_header_list):
    """Generate suppressions for AStyleWx header.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "AStyleWx.h"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("ASEditor(wxWindow*"):
            astylews_header_list.append("noExplicitConstructor:" + src_path + ":" + str(lines)
                                        + "\t\t// ASEditor\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_config(config_list):
    """Generate suppressions for Config.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "Config.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
    file_in.close()

# -----------------------------------------------------------------------------

def process_editordlg(editordlg_list):
    """Generate suppressions for EditorDlg.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "EditorDlg.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if "OnBoldClick" in line:
            editordlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnBoldClick\n")
        if "OnItalicClick" in line:
            editordlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnItalicClick\n")
        if "OnResetClick" in line:
            editordlg_list.append("unusedFunction:" + src_path + ":" + str(lines)
                                  + "\t\t// OnResetClick\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_encoding(encoding_list):
    """Generate suppressions for Encoding.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "Encoding.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if line.startswith("size_t BOMSize"):
            encoding_list.append("unreadVariable:" + src_path + ":" + str(lines)
                                 + "\t\t// size_t BOMSize\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_file_suppressions(file_suppression_list):
    """ Generate suppressions for an entire file.
    """
    file_suppression_list.append("// Suppressed on the Command Line\n")
    file_suppression_list.append("// functionStatic is supressed for the entire project.\n")
    file_suppression_list.append("// noValidConfiguration is supressed for the entire project.\n")
    #~ file_suppression_list.append("// purgedConfiguration is supressed for the entire project.\n")
    file_suppression_list.append("//\n")

# -----------------------------------------------------------------------------

def process_filemanager(filemanager_list):
    """Generate suppressions for FileManager.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "FileManager.cpp"
    strings_processed = 0
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if line.startswith("wxString message"):
            strings_processed += 1
            if strings_processed == 1:
                filemanager_list.append("unreadVariable:" + src_path + ":" + str(lines)
                                        + "\t\t// wxString message\n")
    file_in.close()

# -----------------------------------------------------------------------------

def process_indent(indent_list):
    """Generate suppressions for Indent.
    """
    lines = 0				# current input line number
    src_path = __src_dir + "Indent.cpp"
    file_in = open(src_path, 'r')
    # get exceptions
    for line_in in file_in:
        lines += 1
        line = line_in.strip()
        if len(line) == 0:
            continue
        if line.startswith("//"):
            continue
        comment = line.find("//")
        if comment != -1:
            line = line[:comment].rstrip()
        if line.startswith("EVT_"):
            continue
        if line.startswith("size_t end"):
            indent_list.append("unreadVariable:" + src_path + ":" + str(lines)
                               + "\t\t\t// size_t end\n")
            indent_list.append("variableScope:" + src_path + ":" + str(lines)
                               + "\t\t\t// size_t end\n")
    file_in.close()

# -----------------------------------------------------------------------------

def run_cppcheck():
    """Run the cppcheck program.
       NOTE: The window stays open only if run from the console.
       --enable=all       Enable all checks
       -f, --force        Force checking if "too many" #ifdefs.
       -h, --help         Print the help information.
       --inconclusive     Error messages for inconclusive analysis.
       -j <jobs>          Start [jobs] threads.
       -q, --quiet        Only print error messages.
       --report-progress  Report progress while checking a file.
       --suppress=<spec>  Suppress a specific warning.
       --suppressions-list=<file> Suppress warnings listed in the file.
       -v, --verbose      More detailed error reports.
       --version          Print the version number.
       --xml              Write results in xml to error stream.
       --xml-version=2    Use new xml format.
    """
    if os.name == "nt":
        exepath = "C:/Program Files/Cppcheck/cppcheck.exe"
        if not os.path.exists(exepath):
            libastylewx.system_exit("Cannot find executable: " + exepath)
    else:
        exepath = "cppcheck"
    verify_cppcheck_version(exepath)
    cppcheck = [exepath]
    # -j<jobs> is threads to use for silmutaneous checking
    # runs faster but messages for the files are mixed
    cppcheck.append("-j2")
    # cppcheck.append("--dump")
    cppcheck.append("--enable=all")
    cppcheck.append("--xml-version=2")
    cppcheck.append("--force")
    cppcheck.append("--inconclusive")
    cppcheck.append("--verbose")
    cppcheck.append("--suppress=functionStatic")
    cppcheck.append("--suppress=noValidConfiguration")
    #~ cppcheck.append("--suppress=purgedConfiguration")
    cppcheck.append("--suppressions-list=" + __suppression_path)
    cppcheck.append(__src_dir)
    # shell=True keeps the console window open, but will not display if run from an editor
    # subprocess.check_output() doesn't work from an editor
    try:
        subprocess.check_call(cppcheck)
    except subprocess.CalledProcessError as err:
        libastylewx.system_exit("Bad cppcheck return: " + str(err.returncode))
    except OSError:
        libastylewx.system_exit("Cannot find executable: " + cppcheck[0])

# -----------------------------------------------------------------------------

def verify_cppcheck_version(exepath):
    """Verify the Cppcheck version number to the expected version.
       A lower version number may result in unexpected warnings.
       The expected version number is global.
    """
    # check_output always returns byte code
    version = subprocess.check_output([exepath, "--version"])
    if platform.python_version_tuple()[0] >= '3':
        version = version.decode()
    version = version[9:]   # remove "Cppcheck "
    version = version.rstrip("\r\n")
    if version < __expected_version:
        print("Cppcheck version", version,
              "is less than expected version", __expected_version, "\n")

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
