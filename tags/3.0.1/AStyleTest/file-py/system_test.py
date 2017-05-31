#! /usr/bin/python3
""" Run the AStyle system test.
    Tests brace changes and that changes are completed in one pass.
    The application should be compiled after the test.
    Change the global variables to the desired values.
    -------------------------------------------------------
    Runs each brace type twice to verify there are no changes.
    Runs braces=none after each new brace type to verify
        there are no changes and to check for consistency.
    Files with undesired changes will be copied to a Test directory
        where they can be checked with a diff program.
    At end the application directory is renamed by appending the
        options number. This allows the application to be compiled
        while another test is run with a different set of options.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import locale
import os
import shutil
import subprocess
import time
# local libraries
import libastyle
import libextract
import libtest

# global variables ------------------------------------------------------------

# select one of the following from libastyle
# CODEBLOCKS
# GWORKSPACE        # Objective-C
# JEDIT             # Java
# SCITE
# SHARPDEVELOP      # C# - Compile on Windows only
# SHARPMAIN
# TESTPROJECT
__project = libastyle.JEDIT

# enumerate thru all the __options
# otherwise use only the option below
__enumerate = True
# total errors for the enumeration
__total_errors = 0

# select OPT0 thru OPT3, or use customized options
# options_x can be a brace style or any other option
#__options = "-tapO"
__options = libastyle.OPT3
__options_x = ""

# executable for test
__astyleexe = "astyled"

# extract all files option, use False for speed, use True to compile
__all_files_option = True
#__all_files_option = False

# test number to start with (usually 1)
__start = 1

# brace options and the order they are tested (start with number 1)
#__bracesOLD = "__aa_bb_ll_gg_aa_ll_bb_gg_bb_aa_gg_ll_aa_"

# brace options and the order they are tested (start with number 1)
# a = attached (A2), b = broken (A1), r = run-in (A9), p = pico (A11),
__braces = "__aa_bb_rr_arbp"

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    global __total_errors
    # total files formatted in error
    errors = 0
    errtests = []

    # initialization
    starttime = time.time()
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    locale.setlocale(locale.LC_ALL, "")
    print_run_header()
    os.chdir(libastyle.get_file_py_directory())
    libastyle.set_test_directory("TestDataSys")
    libastyle.build_astyle_executable(get_astyle_config())
    filepaths = libastyle.get_project_filepaths(__project)
    excludes = libastyle.get_project_excludes(__project)
    index = set_test_start()
    remove_test_files(index)
    remove_test_directories(index)
    print("\nExtracting files")
    libextract.extract_project(__project, __all_files_option)

    # process the brace options
    while index < len(__braces):
        print_test_header(index)
        testfile = get_test_file_name(index)
        astyle = set_astyle_args(filepaths, excludes, index)
        print_formatting_message(astyle, __project)
        call_artistic_style(astyle, testfile)
        totformat, unused = print_astyle_totals(testfile)
        files = check_formatted_files(testfile, index)
        if len(files) > 0:
            errors += totformat
            errtests.append(get_test_directory_name(index))
            copy_formatted_files(files, testfile, index)
            verify_formatted_files(len(files), totformat)
        os.remove(testfile)
        index += 1

    rename_output_file(filepaths)
    print_run_total(errors, errtests, starttime)
    __total_errors += errors

# -----------------------------------------------------------------------------

def call_artistic_style(astyle, testfile):
    """Call artistic style.
    """
    outfile = open(testfile, 'w')
    try:
        subprocess.check_call(astyle, stdout=outfile)
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("Bad astyle return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("Cannot find executable: " + astyle[0])
    outfile.close()

# -----------------------------------------------------------------------------

def check_formatted_files(testfile, index):
    """Check the output for files that were formatted.
       Return is the number of files formatted.
    """
    # check for conditions that are not errors
    if index == 0:
        return []
    if (__braces[index] != __braces[index - 1]
            and __braces[index] != '_'):
        return []
    # get formatted files from the astyle report
    files = libtest.get_formatted_files(testfile)
    return files

# -----------------------------------------------------------------------------

def copy_formatted_files(files, testfile, index):
    """Copy formatted files to a test directory.
    """
    testdir = get_test_directory_name(index)
    if os.path.exists(testdir):
        shutil.rmtree(testdir)
    os.makedirs(testdir)
    shutil.copy(testfile, testdir)
    for file_in in files:
        print("copying " + strip_directory_prefix(file_in))
        try:
            shutil.copy(file_in, testdir)
            shutil.copy(file_in + ".orig", testdir)
        except IOError as err:
            print()
            print(err)
            message = ("This must be corrected to continue")
            libastyle.system_exit(message)

# -----------------------------------------------------------------------------

def get_astyle_config():
    """Get the build configuration from the executable name.
       Static configuration is used to avoid conflict with regression tests.
    """
    config = libastyle.DEBUG
    if __astyleexe.lower() == "astyle":
        if os.name == "nt":
            config = libastyle.STATIC
        else:
            config = libastyle.RELEASE
    return config

# -----------------------------------------------------------------------------

def get_brace_option(index):
    """Get the brace option from the "__braces" symbol.
       a = attached (A2), b = broken (A1), r = run-in (A9), p = pico (A11),
    """
    if __braces[index] == 'a':
        return "A2"
    elif __braces[index] == 'b':
        return "A1"
    elif __braces[index] == 'r':
        return "A9"
    elif __braces[index] == 'p':
        return "A11"
    elif __braces[index] == '_':
        return ""
    else:
        libastyle.system_exit("Bad brace option: " + str(__braces[index]))

# -----------------------------------------------------------------------------

def get_modified_options(index):
    """Modify the options for the system tests.
       This is done so that the comparisons will be correct
       or so the program will compile.
    """
    modified_options = __options
    # run-in braces must have indented switches
    # run-in braces do not atach to inlines
    if (index > 0
            and __braces[index] == '_'
            and __braces[index - 1] == 'r'):
        # add indent-switchws to options
        if modified_options.find('S') == -1:
            modified_options = modified_options + "S"
        # remove attach-inlines from options
        if modified_options.find('xl') != -1:
            modified_options = modified_options.replace("xl", "")
    # GWorkspace uses multi-line macros and cannot remove braces (xj)
    if __project == libastyle.GWORKSPACE:
        modified_options = modified_options.replace("xj", "")
    # GENERATE ERRORS FOR TESTING by changing the indent-cases option
#	if index == 1 or index == 3 or index == 6 or index == 9:
#		if modified_options.find('K') == -1:
#			modified_options = modified_options + "K"
#		else:
#			modified_options = modified_options.replace("K", "")
    # check for leading '-'
    if len(modified_options.strip()) > 0 and modified_options[0] != '-':
        modified_options = '-' + modified_options
    return modified_options

# -----------------------------------------------------------------------------

def get_options_variable_name():
    """Get the name of the options variable from the global __options.
    """
    if __options == libastyle.OPT0:
        return "OPT0"
    elif __options == libastyle.OPT1:
        return "OPT1"
    elif __options == libastyle.OPT2:
        return "OPT2"
    elif __options == libastyle.OPT3:
        return "OPT3"
    else:
        libastyle.system_exit("\nCannot find options variable name: " + __options)

# -----------------------------------------------------------------------------

def get_test_directory_name(index):
    """Get name of the test directory for the requested options.
    """
    options_suffix = get_options_variable_name()[-1]
    dir_name = '_' + __project + options_suffix
    dir_name += os.sep + "test{0}".format(index + 1)
    return dir_name

# -----------------------------------------------------------------------------

def get_test_file_name(index):
    """Get name of the test file for the given index.
    """
    return "test{0}.txt".format(index + 1)

# -----------------------------------------------------------------------------

def print_astyle_totals(filename):
    """Print total information from the astyle total line.
       Returns files formatted and total files from the report total line.
    """
    formatted, totfiles, minute, sec = libtest.get_astyle_totals(filename)
    if min == 0:
        printline = "{0:n} formatted; {1:n} files; {2} seconds"
        print(printline.format(formatted, totfiles, sec))
    else:
        printline = "{0:n} formatted; {1:n} files; {2} min {3} seconds"
        print(printline.format(formatted, totfiles, minute, sec))
    return (formatted, totfiles)

# -----------------------------------------------------------------------------

def print_formatting_message(args, project):
    """Print the formatting message at the start of a test.
       Input is the command list used to call astyle.
    """
    print("Formatting " + project, end=" ")
    # print args starting with a '-' except for excludes
    for arg in args:
        if not arg[0] == '-':
            continue
        if arg[:9] == "--exclude":
            continue
        print(arg, end=" ")
    print()

# -----------------------------------------------------------------------------

def print_run_header():
    """Print run header information.
    """
    print("System Test for {0}".format(__project))
    if os.name == "nt":
        print("Using ({0}) {1}".format(libastyle.VS_RELEASE, __astyleexe), end=" ")
    else:
        print("Using {0}".format(__astyleexe), end=" ")
    print(get_options_variable_name(), end=" ")
    if len(__options_x.strip()) > 0:
        print(__options_x, end=" ")
    print()

# -----------------------------------------------------------------------------

def print_run_total(errors, errtests, starttime):
    """Print total information for the entire run.
    """
    print()
    stoptime = time.time()
    runtime = int(stoptime - starttime + 0.5)
    minute = int(runtime / 60)
    sec = int(runtime % 60)
    if min == 0:
        print("{0} seconds total run time".format(sec))
    else:
        print("{0} min {1} seconds total run time".format(minute, sec))
    if errors == 0:
        print(str(errors) + " errors")
    else:
        print(str(errors) + " errors in", end=" ")
        for test in errtests:
            # print only the test directory name
            start = test.find("test")
            print(test[start:], end=" ")
        print()

# -----------------------------------------------------------------------------

def print_test_header(index):
    """Print header information for a test.
    """
    test_no = index + 1
    print('\n' + ('-' * 60) + '\n')
    print("TEST {0} OF {1}".format(test_no, len(__braces)), end='')
    print(' ' * 12, end='')
    print(libastyle.get_formatted_time())
    print(__braces[:test_no])
    print(__braces)

# -----------------------------------------------------------------------------

def remove_test_directories(index):
    """Remove top test directory for this run.
       If there is an active process using the directory it cannot be removed.
       The active process will have to be killed to remove the directory.
    """
    testdir = get_test_directory_name(index)
    # remove subdirectory
    end = testdir.find(os.sep)
    testdir = testdir[:end]
    # remove top directory - this is a problem with Windows only
    if os.path.exists(testdir):
        imax = 5
        for i in range(0, imax):
            shutil.rmtree(testdir, True)
            if not os.path.isdir(testdir):
                break
            if i == imax - 1:
                print()
                libastyle.system_exit("Directory not removed: " + testdir)
            time.sleep(2)

# -----------------------------------------------------------------------------

def remove_test_files(index):
    """Remove test files for this run.
       If there is an active process using the file it cannot be removed.
       The active process will have to be killed to remove the file.
    """
    for i in range(index, len(__braces)):
        testfile = get_test_file_name(i)
        if os.path.exists(testfile):
            libextract.remove_test_directory(testfile)

# -----------------------------------------------------------------------------

def rename_output_file(filepaths):
    """Rename the output file by appending the options variable number (0-3).
    """
    print('\n' + ('-' * 60))
    # extract filename
    filepath = filepaths[0]
    filepath = filepath.replace('\\', '/')
    testdir = libastyle.get_test_directory()
    start = len(testdir) + 1
    end = filepath.find('/', start)
    if end == -1:
        libastyle.system_exit("Cannot find filename for rename: " + filepath)
    dirname = filepath[start:end]
    dirpath = testdir + '/' + dirname
    options_suffix = get_options_variable_name()[-1]
    newname = dirname + options_suffix
    newpath = dirpath + options_suffix
    # rename by adding the option number to the end
    if os.path.isdir(newpath):
        libextract.remove_test_directory(newname)
    print("rename {0} {1}".format(dirname, newname))
    try:
        shutil.move(dirpath, newpath)
    except WindowsError as err:
        time.sleep(2)
        try:
            shutil.move(dirpath, newpath)
        except WindowsError as err:
            print()
            print(err)
            libastyle.system_exit("Error in renaming output file: " + dirpath)

# -----------------------------------------------------------------------------

def set_astyle_args(filepath, excludes, index):
    """Set args for calling artistic style.
    """
    global __options_x
    # set astyle executable
    args = [libastyle.get_astyleexe_path(get_astyle_config())]
    # set filepaths
    for file_in in filepath:
        args.append(file_in)
    # set options - must create a backup file
    args.append("-vRQ")
    modified_options = get_modified_options(index)
    if len(modified_options) > 0:
        args.append(modified_options)
    # options_x
    if len(__options_x) > 0:
        __options_x = __options_x.strip()
    if len(__options_x) > 0 and __options_x[0] != '-':
        __options_x = '-' + __options_x
        args.append(__options_x)
    brace_option = get_brace_option(index)
    if brace_option != '':
        args.append('-' + brace_option)
    # set excludes
    for exclude in excludes:
        args.append(exclude)
    return args

# -----------------------------------------------------------------------------

def set_test_start():
    """Set the test number for start.
       Returns the starting index.
    """
    if __start <= 1:
        index = 0
    else:
        index = __start - 1
    if index > 0:
        print("Start with test {0}".format(index + 1))
        # if needed decrease by one test
        if __braces[index] == __braces[index - 1]:
            index -= 1
            print("Starting with test {0} to avoid diffs".format(index + 1))
        elif __braces[index] == '_':
            if index >= 2:
                index -= 2
            else:
                index -= 1
            print("Starting with test {0} to apply format".format(index + 1))
    return index

# -----------------------------------------------------------------------------

def strip_directory_prefix(directory):
    """Strip the prefix from a directory or file for printing.
    """
    prefix = libastyle.get_test_directory(True)
    start = len(prefix)
    if start > len(directory):
        start = 0
    return directory[start:]

# -----------------------------------------------------------------------------

def verify_formatted_files(numformat, totformat):
    """Check that the formatted files list equals the astyle report total.
    """
    if totformat != numformat:
        message = "files != report ({0},{1})".format(numformat, totformat)
        libastyle.system_exit(message)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    if __enumerate:
        opts = [ libastyle.OPT0, libastyle.OPT1, libastyle.OPT2, libastyle.OPT3]
        for unused, opt in enumerate(opts):
            __options = opt
            main()
            print('\n' + ('#' * 60)  + '\n')
        print(str(__total_errors) + " total errors")
    else:
        main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
