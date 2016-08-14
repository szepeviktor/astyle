#! /usr/bin/python
""" Format a project using AStyle.
    Run from an option in the "Tools" menu of a development environment.
    For Visual Studio:
        Title:       Format Project (AStyle)
        Command:     %PROGRAMFILES%\Python 3.5\python.exe
        Arguments:   "format-project.py"  "$(ProjectFileName)"
        Init Dir:    %USERPROFILE%\Projects\AStyleTest\file-py
    For CodeBlocks (Windows):
        Name:        Format Project (AStyle)
        Executable:  %PROGRAMFILES%\Python 3.5\python.exe
        Parameters:  "format-project.py"  "$(ProjectFileName)"
        Work Dir:    %USERPROFILE%\Projects\AStyleTest\file-py
    For CodeBlocks (Linux):
        Name:        Format Project (AStyle)
        Executable:  python3
        Parameters:  "format-project.py"  "$(ProjectFileName)"
        Work Dir:    $(HOME)/Projects/AStyleTest/file-py
"""

# to disable the print statement and use the print() function (version 3 format_)
from __future__ import print_function

import os
import subprocess
import sys

# global variables ------------------------------------------------------------

# -----------------------------------------------------------------------------

def main():
    """ Main processing function.
    """
   # verify argv[1]
    if len(sys.argv) < 2 or sys.argv[1] == '':
        print("Missing project file name in arg1")
        print("Is script run from CodeBlocks or Visual Studio?")
        print()
        os._exit(1)

    print("Hello '" + sys.argv[1] + "'")

    # get the project name
    split = []
    proj_name = ""
    proj_name2 = None
    if sys.argv[1].endswith(".cbp"):
        project = sys.argv[1][:-4]
        split = project.split(' ')
        proj_name = split[1]
        if len(split) > 2:
            proj_name2 = split[2]
    elif sys.argv[1].endswith(".csproj"):
        project = sys.argv[1][:-7]
        split = project.split(' ')
        proj_name = split[0]
        if len(split) > 1:
            proj_name2 = split[1]
    elif sys.argv[1].endswith(".vcxproj"):
        project = sys.argv[1][:-8]
        split = project.split(' ')
        proj_name = split[0]
        if len(split) > 1:
            proj_name2 = split[1]
    else:
        print("Invalid file extension in '" + sys.argv[1] + "'")
        print()
        os._exit(1)

    process_project(proj_name, proj_name2)

# -----------------------------------------------------------------------------

def call_astyle_executable(subdir):
    """ Call the astyle executable to format the project.
        Uses the file astyle-options.cfg for formatting options.
    """
    if os.name == "nt":
        exepath = "C:/Program Files/AStyle/AStyle.exe"
        projdir = os.getenv("USERPROFILE") + "/Projects/"
        options = "--options=" + projdir + "/AStyleTest/file-py/astyle-options.cfg"
    else:
        exepath = os.getenv("HOME") + "/bin/astyle"
        projdir = os.getenv("HOME") + "/Projects/"
        options = "--options=" + projdir + "/AStyleTest/file-py/astyle-options.cfg"

    # build the astyle_call list
    # add --formatted (Q) to the options
    # override "AStyleDev" options with --style=horstmann (A9) --indent=spaces (s)
    if "AStyleDev" in subdir:
         astyle_call = [exepath, options, "-Q", "-A9s", projdir + subdir]
    else:
         astyle_call = [exepath, options, "-Q", projdir + subdir]

    try:
        retval = subprocess.call(astyle_call)
    except FileNotFoundError:
        print("Cannot find '" + exepath + "'")
        os._exit(1)
    if retval:
        print("Bad astyle return: " + str(retval))
        os._exit(1)

# -----------------------------------------------------------------------------

def format_AStyle():
    """ Format the AStyle source files.
    """
    print("Formatting AStyle")
    print()
    call_astyle_executable("AStyle/src/*.cpp")
    print()
    call_astyle_executable("AStyle/src/*.h")
    print()

# -----------------------------------------------------------------------------

def format_AStyleTest():
    """ Format the AStyleTest source files.
    """
    print("Formatting AStyleTest")
    print()
    call_astyle_executable("AStyleTest/src/*.cpp")
    print()
    call_astyle_executable("AStyleTest/src/*.h")
    print()

# -----------------------------------------------------------------------------

def format_AStyleTestCon():
    """ Format the AStyleTestCon source files.
    """
    print("Formatting AStyleTestCon")
    print()
    call_astyle_executable("AStyleTest/srccon/*.cpp")
    print()
    call_astyle_executable("AStyleTest/srccon/*.h")
    print()

# -----------------------------------------------------------------------------

def format_AStyleTestI18n():
    """ Format the AStyleTestI18n source files.
    """
    print("Formatting AStyleTestI18n")
    print()
    call_astyle_executable("AStyleTest/srci18n/*.cpp")
    print()
    # uses a header from the srccon directory
    call_astyle_executable("AStyleTest/srccon/*.h")
    print()

# -----------------------------------------------------------------------------

def format_AStyleTestLib():
    """ Format the AStyleTestLib source files.
    """
    print("Formatting AStyleTestLib")
    print()
    call_astyle_executable("AStyleTest/srclib/*.cpp")
    print()
    call_astyle_executable("AStyleTest/srclib/*.h")
    print()

# -----------------------------------------------------------------------------

def format_AStyleTestLoc():
    """ Format the AStyleTestLoc source files.
    """
    print("Formatting AStyleTestLoc")
    print()
    call_astyle_executable("AStyleTest/srcloc/*.cpp")
    print()

# -----------------------------------------------------------------------------

def format_AStyleWx():
    """ Format the AStyleWx source files.
    """
    print("Formatting AStyleWx")
    print()
    call_astyle_executable("AStyleWx/src/*.cpp")
    print()
    call_astyle_executable("AStyleWx/src/*.h")
    print()

# -----------------------------------------------------------------------------

def format_AStyleWxTest():
    """ Format the AStyleWxTest source files.
       Also format the AStyleWx files since they
       are included in the project.
    """
    print("Formatting AStyleWxTest")
    print()
    call_astyle_executable("AStyleWxTest/src/*.cpp")
    print()
    call_astyle_executable("AStyleWxTest/src/*.h")
    print()
    # uses source files from AStyleWx
    call_astyle_executable("AStyleWx/src/*.cpp")
    print()
    call_astyle_executable("AStyleWx/src/*.h")
    print()

# -----------------------------------------------------------------------------

def format_ExampleCpp():
    """ Format the Cpp Example source files.
    """
    # the options override is done in call_astyle_executable
    print("Formatting Example Cpp")
    print("override standard options with --style=horstmann --indent=spaces")
    print()
    call_astyle_executable("AStyleDev/src-c/*.cpp")
    print()

# -----------------------------------------------------------------------------

def format_ExampleObjC():
    """ Format the Objective-C Example source files.
    """
    # the options override is done in call_astyle_executable
    print("Formatting Example Objective-C")
    print("override standard options with --style=horstmann --indent=spaces")
    print()
    call_astyle_executable("AStyleDev/src-o/*.m")
    print()

# -----------------------------------------------------------------------------

def format_ExampleSharp():
    """ Format the C# Example source files.
    """
    # the options override is done in call_astyle_executable
    print("Formatting Examples C#")
    print("override standard options with --style=horstmann --indent=spaces")
    print()
    call_astyle_executable("AStyleDev/src-s/*.cs")
    print()
    call_astyle_executable("AStyleDev/src-s2/*.cs")
    print()

# -----------------------------------------------------------------------------

def process_project(proj_name, proj_name2):
    """ Use the project name to determine the source files
       to be processed, and call the required format procedure.
    """
    # AStyle
    if proj_name == "AStyle":
        format_AStyle()
        return

    # AStyleDev Examples
    if (proj_name == "ExampleDll" or proj_name == "ExampleSo"
    or proj_name == "ExampleLib" or proj_name == "ExampleA"
    or proj_name == "ExampleObj" or proj_name == "ExampleO"):
        if proj_name2 == "ObjC":
            format_ExampleObjC()
        else:
            format_ExampleCpp()
        return
    if (proj_name == "ExampleCs"
    or proj_name == "Example2Cs"):
        format_ExampleSharp()
        return

    # AStyleTest
    if proj_name == "AStyleTest":
        format_AStyleTest()
        return
    if proj_name == "AStyleTestCon":
        format_AStyleTestCon()
        return
    if proj_name == "AStyleTestI18n":
        format_AStyleTestI18n()
        return
    if proj_name == "AStyleTestLib":
        format_AStyleTestLib()
        return
    if proj_name == "AStyleTestLoc":
        format_AStyleTestLoc()
        return

    # AStyleWx
    if (proj_name == "AStyleWx"
    or proj_name == "AStyleWxDll" or proj_name == "AStyleWxSo"):
        format_AStyleWx()
        return

    # AStyleWxTest
    if proj_name == "AStyleWxTest":
        format_AStyleWxTest()
        return

    # project was not found
    print("Cannot format project '" + proj_name + "'")
    os._exit(1)

# -----------------------------------------------------------------------------

# make the module executable
# NOTE: the calling program should pause before exiting
if __name__ == "__main__":
    main()
    os._exit(0)
