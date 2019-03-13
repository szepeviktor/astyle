#/usr/bin/python3
""" cppcheck addon for naming conventions
    Example usage (variable name must start with lowercase, function name must start with uppercase):
    $ cppcheck --dump path-to-src/
    $ python addons/naming.py --var='[a-z].*' --function='[A-Z].*' path-to-src/*.dump
"""

import os
import re
import sys
# add cppcheck addon directory to the module search path
# cppcheckdata must be after the append
if os.name == "nt":
    sys.path.append("C:/Program Files/Cppcheck/addons")
import cppcheckdata

# global variables ------------------------------------------------------------

RE_VARNAME = None
RE_FUNCTIONNAME = None
RE_CLASSNAME = None

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """
    process_command_line()
    verify_command_line_input()

    for arg in sys.argv[1:]:
        if not arg[-5:] == '.dump':
            continue
        # the file will be processed
        print()
        if not os.path.isfile(arg):
            print('* * * * NOT A VALID FILE PATH \"' + arg + '\"')
            continue
        process_cppcheck_dump_file(arg)

# -----------------------------------------------------------------------------

def create_class_list(scopes):
    """ Create a list of class names to eliminate constructor and destructor
        function name checks.
    """
    classes = []
    for scope in scopes:
        if scope.type == 'Class' or scope.type == 'Struct':
            classes.append(scope.className)
    return classes

# -----------------------------------------------------------------------------

def process_command_line():
    """ Process the command line arguments.
    """
    global RE_VARNAME, RE_FUNCTIONNAME, RE_CLASSNAME
    count = 0
    dump_file = None
    for arg in sys.argv[1:]:
        count += 1
        if arg[:6] == '--var=':
            RE_VARNAME = arg[6:]
        elif arg[:11] == '--function=':
            RE_FUNCTIONNAME = arg[11:]
        elif arg[:8] == '--class=':
            RE_CLASSNAME = arg[8:]
        elif arg[-5:] == '.dump':
            dump_file = arg
    if count == 0:
        print('\n* * * * NO INPUT TO PROCESS')
        print('* * * * This script is usually called from a batch file')
        os._exit(1)
    if not dump_file:
        print('\n* * * * MISSING .DUMP FILE IN ARGUMENTS')
        os._exit(1)
    if not RE_VARNAME and not RE_FUNCTIONNAME and not RE_CLASSNAME:
        print('\n* * * * MISSING REGEX ENTRIES IN ARGUMENTS')
        os._exit(1)

# -----------------------------------------------------------------------------

def process_cppcheck_dump_file(file):
    """ Process the dump file data.
        This processes variables and scopes configurations from cppcheckdata.parsedump.
        The variables configuration contains only variables.
        The scopes configuration contain the following types:
            type="Namespace", type="Function", type="Class", type="Struct", type="Enum"
        All scopes configuration types are checked except type="Namespace"

    """
    print('Checking ' + file + '...')
    data = cppcheckdata.parsedump(file)
    for cfg in data.configurations:
        if len(data.configurations) > 1:
            print('Checking ' + file + ', config "' + cfg.name + '"...')
        # process variables configuration
        if RE_VARNAME:
            for var in cfg.variables:
                res = re.match(RE_VARNAME, var.nameToken.str)
                if not res:
                    report_error(var.typeStartToken,
                                 'style',
                                 'Variable '
                                 + var.nameToken.str
                                 + ' violates naming convention')
        # processes scope configuration type="Function"
        if RE_FUNCTIONNAME:
            classes = create_class_list(cfg.scopes)
            for scope in cfg.scopes:
                if scope.type == 'Function':
                    # delete constructors and destructors from function check
                    if scope.className in classes:
                        continue
                    res = re.match(RE_FUNCTIONNAME, scope.className)
                    if not res:
                        report_error(scope.classStart, 'style',
                                     'Function '
                                     + scope.className
                                     + ' violates naming convention')
        # process scope configuration type="Class", type="Struct", and type="Enum"
        if RE_CLASSNAME:
            for scope in cfg.scopes:
                if (scope.type == 'Class' or scope.type == 'Struct'
                        or scope.type == 'Enum'):
                    res = re.match(RE_CLASSNAME, scope.className)
                    if not res:
                        report_error(scope.classStart, 'style',
                                     scope.type + ' '
                                     + scope.className
                                     + ' violates naming convention')

# -----------------------------------------------------------------------------

def report_error(token, severity, msg):
    """ Write an error message.
    """
    sys.stderr.write(
        '[' + token.file + ':' + str(token.linenr) + '] (' + severity + ') naming.py: ' + msg + '\n')

# -----------------------------------------------------------------------------

def verify_command_line_input():
    """ Verify regex command line input.
        DO NOT check in the function that sets the global variables.
    """
    if not RE_VARNAME:
        print('* * * * VARIABLES NOT CHECKED')
    if not RE_FUNCTIONNAME:
        print('"* * * * FUNCTIONS NOT CHECKED')
    if not RE_CLASSNAME:
        print('* * * * CLASSES NOT CHECKED')

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    # this does NOT raise a SystemExit exception like sys.exit()
    os._exit(0)
