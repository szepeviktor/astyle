#/usr/bin/python3
""" cppcheck addon for naming conventions
    Example usage (variable name must start with lowercase, function name must start with uppercase):
    $ cppcheck --dump path-to-src/
    $ python addons/naming.py --var='[a-z].*' --function='[A-Z].*' path-to-src/*.dump
"""

import glob
import os
import platform
import re
import subprocess
import sys
import libastyle		# local directory
# add cppcheck addon directory to the module search path
# 'import cppcheckdata' must be after the append
if os.name == "nt":
    sys.path.append("C:/Program Files/Cppcheck/addons")
else:
    sys.path.append("/usr/local/share/Cppcheck")
import cppcheckdata

# global variables ------------------------------------------------------------

__astyle_src_dir = libastyle.get_astyle_directory() + "/src/"
if os.name == "nt":
    __cppcheck_exe = "C:/Program Files/Cppcheck/cppcheck.exe"
else:
    __cppcheck_exe = "cppcheck"

__astyle_file_names = []
# can also check selected files in a list
#__astyle_file_names = ["ASEnhancer.cpp", "ASResource.cpp"]

# Variables start with lower case OR underscore plus lower case OR AS_ or _AS_
# followed by all caps with underline allowed.
# _CRT_glob is a required name to turn off MinGW automatic file globbing
RE_VARNAME = "[a-z].*|_[a-z].*|[AS_|_AS_].[A-Z_]*$|_CRT_glob"
# Functions names start with lower case.
# The others are allowed DLL entry-point exceptions.
RE_FUNCTIONNAME = "[a-z].*|AStyleMain|AStyleGetVersion|Java_AStyleInterface"
# Class, struct, and enum names start with upper case.
# eState is an allowed enum exception
RE_CLASSNAME = "[A-Z].*|eState"

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """
    global __astyle_file_names
    libastyle.set_text_color("yellow")
    if not (platform.python_implementation() == "CPython" and sys.version_info[0] >= 3):
        libastyle.system_exit("\nMust use Python version 3 or greater")
    print(get_cppcheck_version(), "\n")
    if len(__astyle_file_names) == 0:
        __astyle_file_names = get_astyle_file_names()
    __astyle_file_names.sort(key=str.lower)
    for file_name in __astyle_file_names:
        print('Dumping', file_name + '...')
        create_dump_file(file_name)
    for file_name in __astyle_file_names:
        print()
        dump_file = file_name + '.dump'
        print('Checking', dump_file + '...')
        process_dump_file(dump_file)
    print()

# -----------------------------------------------------------------------------

def create_class_list(scopes):
    """ Create a list of class names to eliminate constructor and destructor
        function name checks.
    """
    classes = []
    for scope in scopes:
        if scope.type in ('Class', 'Struct'):
            classes.append(scope.className)
    return classes

# -----------------------------------------------------------------------------

def create_dump_file(filename):
    """ Use cppcheck to create a dump file.
    """
    filepath = __astyle_src_dir + filename
    outpath  = __astyle_src_dir + "dump.txt"
    outfile = open(outpath, 'w')
    try:
        subprocess.check_call([__cppcheck_exe, "--dump", "--force", filepath], stdout=outfile)
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("Bad cppcheck return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("Cannot find cppcheck executable")
    outfile.close()
    os.remove(outpath)

# -----------------------------------------------------------------------------

def get_astyle_file_names():
    """ Get all *.cpp filenames in the astyle src directory.
        The filepaths are removed so only the names are captured.
    """
    file_names = []
    filepaths = glob.glob(__astyle_src_dir + "*.cpp")
    # remove the path
    for file_name in filepaths:
        file_name = os.path.basename(file_name)
        file_names.append(file_name)
    return file_names


# -----------------------------------------------------------------------------

def get_cppcheck_version():
    """Return the cppcheck version number as a string."""
    # NOTE: minimum version should be 1.88, which contains a fix
    # Version 1.87 was patched to work.
    minimum_version = "1.87"
    version = subprocess.check_output([__cppcheck_exe, "--version"])
    # check_output always returns byte code
    version = version.decode()
    version = version.rstrip("\r\n")
    version_num = version[9:]
    if version_num < minimum_version:
        print("Cppcheck version", version_num,
              "is less than minimum version", minimum_version)
    return version

# -----------------------------------------------------------------------------

def process_dump_file(file):
    """ Process the dump file data.
        This processes variables and scopes configurations from cppcheckdata.parsedump.
        The variables configuration contains only variables.
        The scopes configuration contain the following types:
            type="Namespace", type="Function", type="Class", type="Struct", type="Enum"
        All scopes configuration types are checked except type="Namespace"
        This function is adapted from the cppcheck naming.py file.
    """
    variable_names = 0
    function_names = 0
    class_names    = 0
    filepath = __astyle_src_dir + file
    data = cppcheckdata.parsedump(filepath)
    for cfg in data.configurations:
        if len(data.configurations) > 1:
            print('Checking ' + file + ', config "' + cfg.name + '"...')
        # process variables configuration
        if RE_VARNAME:
            for var in cfg.variables:
                # the following 'if' from version 1.88 corrects a bug
                # python aborted when there is no variable name in a function argument
                if var.nameToken:
                    variable_names += 1
                    res = re.match(RE_VARNAME, var.nameToken.str)
                    if not res:
                        report_error(var.typeStartToken,
                                     'style',
                                     'Variable '
                                     + var.nameToken.str
                                     + ' violates naming convention')
        # processes scope configuration type="Function"
        if RE_FUNCTIONNAME:
            # get class names to eliminate constructors and destructors
            class_list = create_class_list(cfg.scopes)
            for scope in cfg.scopes:
                if scope.type == 'Function':
                    # delete constructors and destructors from function check
                    # they have class names not function names
                    if scope.className in class_list:
                        continue
                    function_names += 1
                    res = re.match(RE_FUNCTIONNAME, scope.className)
                    if not res:
                        report_error(scope.bodyStart,
                                     'style',
                                     'Function '
                                     + scope.className
                                     + ' violates naming convention')
        # process scope configuration type="Class", type="Struct", and type="Enum"
        if RE_CLASSNAME:
            for scope in cfg.scopes:
                if scope.type in ('Class', 'Struct', 'Enum'):
                    class_names += 1
                    res = re.match(RE_CLASSNAME, scope.className)
                    if not res:
                        report_error(scope.bodyStart,
                                     'style',
                                     scope.type + ' '
                                     + scope.className
                                     + ' violates naming convention')
                else:
                    # verify scope types
                    if scope.type in ('Global', 'Namespace', 'Function'):
                        continue
                    if scope.type in ('If', 'Else', 'While', 'For', 'Do', 'Switch'):
                        continue
                    print('Unrecognized scope.type: ' + scope.type)
    # end of top 'for' loop
    print('variables:', variable_names, ' functions:', function_names, ' classes:', class_names)

# -----------------------------------------------------------------------------

def report_error(token, severity, msg):
    """ Write an error message.
    """
    sys.stderr.write(
        '[' + token.file + ':' + str(token.linenr) + '] (' + severity + ') naming.py: ' + msg + '\n')

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    # this does NOT raise a SystemExit exception like sys.exit()
    os._exit(0)
