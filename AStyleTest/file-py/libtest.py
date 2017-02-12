#! /usr/bin/python
""" Test functions to print and parse the astyle report file.
    Test functions to extract the formatted files and call a diff viewer.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import re				# regular expressions
import subprocess
# local libraries
import libastyle

# -----------------------------------------------------------------------------

def call_diff_program(filepath1, filepath2):
    """Call diff program.
    """
    diff = [libastyle.get_diff_path(), filepath1, filepath2]
    try:
        subprocess.check_call(diff)
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("Bad diff return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("Cannot find executable: " + diff[0])

# -----------------------------------------------------------------------------

def diff_formatted_files(filepaths, diff_old=False):
    """Call the diff program for formatted files.
       diff_old=True will diff files from the "OLD" directory.
       Otherwise diff ".orig" files from the current directory.
       This function requires keyboard input.
       It cannot be run from an editor.
    """
    if not libastyle.is_executed_from_console():
        if diff_old:
            diffprog = "diff2-print.py"
        else:
            diffprog = "diff1-print.py"
        msg = "Run {0} from the console to view the diffs"
        print(msg.format(diffprog))
        return
    print("Press m or n to skip, q to quit")
    numin = 0
    processed = 0
    for filepath in filepaths:
        numin += 1
        filepath = filepath.replace('\\', '/')
        stripfile = strip_test_directory_prefix(filepath)
        print("{0} of {1} {2}".format(numin, len(filepaths), stripfile))
        ch_in = libastyle.get_ch()
        if ch_in == 'n' or ch_in == 'N' or ch_in == 'm' or ch_in == 'M':
            continue
        if ch_in == 'q' or ch_in == 'Q':
            break
        processed += 1
        if diff_old:
            oldpath = get_old_filepath(filepath)
            call_diff_program(filepath, oldpath)
        else:
            call_diff_program(filepath, filepath + ".orig")
    print("{0} of {1} diffs processed".format(processed, len(filepaths)))

# -----------------------------------------------------------------------------

def extract_directory_from_line(line):
    """Get the directory from the 'directory line' in the astyle report.
    """
    # get the directory path
    linesplit = line.split()
    path = linesplit[1]
    # remove the wildcard
    pathsplit = os.path.split(path)
    directory = pathsplit[0]
    # verify result
    if directory == "":
        libastyle.system_exit("Cannot extract directory from line: " + line)
    return directory

# -----------------------------------------------------------------------------

def get_astyle_totals(filename):
    """Print total information from the astyle total line.
       The filename must be in the current directory.
       Return 1 - Number of files formatted
       Return 2 - Number of files processed
       Return 3 - Runtime minutes
       Return 4 - Runtime seconds
    """
#	infile = open_filein(filename, 'rb')		# changed for version 3.2
    infile = open_filein(filename, 'r')
#	infile.seek(-100, os.SEEK_END)			# changed for version 3.2
    try:
        os.lseek(infile.fileno(), -200, os.SEEK_END)
    except OSError:
        os.lseek(infile.fileno(), 0, os.SEEK_SET)

    for line in infile:
        # use regular expressions to search the lines
        # find total line (with following commas)
        if (re.search("formatted", line) is not None
                and re.search("unchanged", line) is not None):
            totline = line.split()
            # get the thousands separator from the total number of lines
            sep = get_thousands_sep(totline[-2])
            # cannot extract if the separator is a space (French)
            if sep is None:
                print("Cannot extract totals from file")
                return (0, 0, 0, 0)
            # extract the totals
#			totline[0] = totline[0].translate(None, sep)		# changed for version 3.2
            totline[0] = totline[0].replace(sep, '')
            formatted = int(totline[0])
#			totline[2] = totline[2].translate(None, sep)		# changed for version 3.2
            totline[2] = totline[2].replace(sep, '')
            unchanged = int(totline[2])
            totfiles = formatted + unchanged
            if totline[5] == "min":
                minutes = int(totline[4])
                seconds = int(totline[6])
            else:
                minutes = 0
                if totline[4].find('.') == -1:
                    seconds = int(totline[4])
                else:
                    seconds = float(totline[4])
            return (formatted, totfiles, minutes, seconds)

    libastyle.system_exit("Cannot find total line in libtest.py")

# -----------------------------------------------------------------------------

def get_formatted_files(filename):
    """Get a list of formatted files from the astyle output.
       Returns a list of the formatted files.
    """
#	infile = open_filein(filename, 'rb')		# changed for version 3.2
    infile = open_filein(filename, 'r')
    formatted = []

    for line in infile:
        # use regular expressions to search the lines
        # main directory line (start of line with a following space)
        if re.match("Directory ", line) is not None:
            directory = extract_directory_from_line(line)
            continue
        # total line (with a following comma)
        if (re.search("Formatted", line) is not None
                and re.search("Unchanged", line) is not None):
            continue
        # formatted file line (start of line with a following space)
        if re.match("Formatted ", line) is not None:
            subline = line[:-1].split(None, 1)
            formatted.append(directory + os.sep + subline[1])

    infile.close()
    return formatted

# -----------------------------------------------------------------------------

def get_old_filepath(filepath):
    """Build a filepath for the "OLD" directory.
    """
    testdir = libastyle.get_test_directory(True)
    subdir = filepath[len(testdir):]
    sep = subdir.find('/')
    dirname = subdir[:sep]
    oldpath = testdir + dirname + "OLD" + subdir[len(dirname):]
    return oldpath

# -----------------------------------------------------------------------------

def get_thousands_sep(num):
    """Get the thousands separator from a number string.
       Return the separator.
    """
    sep = ','
    if not len(num) > 3:
        return None
    if not num[-4].isdigit():
        sep = num[-4]
    return sep

# -----------------------------------------------------------------------------

def open_filein(filename, mode):
    """Open an input file and handle the error.
       Arguments are the same as for the python 'open' statement.
    """
    try:
        infile = open(filename, mode)
    except IOError:
        libastyle.system_exit("Cannot open input file: " + filename)
    return infile

# -----------------------------------------------------------------------------

def strip_test_directory_prefix(file_in):
    """Strip the test directory prefix from a directory or file for printing.
    """
    prefix = libastyle.get_test_directory(True)
    start = len(prefix)
    if start > len(file_in):
        start = 0
    return file_in[start:]

# -----------------------------------------------------------------------------

def test_all_functions():
    """Test all functions for syntax.
       This must be run from a console to test the 'diff' functions.
    """
    # write test file
    os.chdir(libastyle.get_file_py_directory())
    testfile = libastyle.get_temp_directory() + "libtest.txt"
    test_file_write(testfile)
    # begin tests -----------------------------------------
    files = get_formatted_files(testfile)
    # calls extract_directory_from_line()
    print("No files will be displayed in the comparison program.")
    diff_formatted_files(files)
    # calls call_diff_program()
    # calls strip_test_directory_prefix()
    get_astyle_totals(testfile)
    # end tests -------------------------------------------
    os.remove(testfile)

# -----------------------------------------------------------------------------

def test_file_write(filename):
    """Write a file for testing this module.
    """
    outfile = open(filename, 'w')
    text = (
        "Artistic Style 1.xx\n"
        "--------------------------------------------------\n"
        "directory $HOME/Projects/TestData/Project/*.cpp\n"
        "--------------------------------------------------\n"
        "formatted  plugins/astyle/astyle/ASFormatter.cpp\n"
        "unchanged* plugins/astyle/astyle/Unchanged.cpp\n"
        "formatted  plugins/codecompletion/parser.cpp\n"
        "unchanged* plugins/codecompletion/unchanged.cpp\n"
        "--------------------------------------------------\n"
        "2 formatted, 2 unchanged, 10 seconds, 1000 lines\n"
    )
    text = text.replace("$HOME", libastyle.get_home_directory())
    outfile.write(text)
    outfile.close()

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    print(libastyle.get_python_version())
    print("Testing Library Functions")
    test_all_functions()
    libastyle.system_exit()
