#! /usr/bin/python
"""Library files for AStyleWx test modules.
   All directories and filepaths should be in this module.
   Executed as stand-alone it will run a series of tests.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import subprocess
import sys

if os.name == "nt":
    import msvcrt			# Windows only for get_ch()
else:
    import termios, tty		# Linux only for get_ch()

# global variables ------------------------------------------------------------

# compile configurations
DEBUG   = "debug"
RELEASE = "release"
STATIC  = "static"
STATIC_XP = "static-xp"

#WX_RELEASE = "3.0"
WX_RELEASE = "3.1"

# Visual Studio release
#VS_RELEASE = "vs2008"
#VS_RELEASE = "vs2010"
#VS_RELEASE = "vs2012"
#VS_RELEASE = "vs2013"
VS_RELEASE = "vs2015"
if (VS_RELEASE == "vs2015"
        and not os.path.exists("C:/Program Files (x86)/MSBuild/14.0/")):
    VS_RELEASE = "vs2013"

# -----------------------------------------------------------------------------

def build_astylewx_executable(config):
    """Build the astylewx executable.
    """
    if config == DEBUG:
        print("Building AStyleWx Debug")
    elif config == RELEASE:
        print("Building AStyleWx Release")
    elif config == STATIC and os.name == "nt":
        print("Building AStyleWx Static")
    elif config == STATIC_XP and os.name == "nt":
        print("Building AStyleWx Static XP")
    else:
        system_exit("Bad arg in build_astylewx_executable(): " + config)
    slnpath = get_astylewx_build_directory(config)
    if os.name == "nt":
        if config == STATIC_XP:
            slnpath = slnpath + "/AStyleWx " + WX_RELEASE + " XP.sln"
        else:
            slnpath = slnpath + "/AStyleWx " + WX_RELEASE + ".sln"
        compile_windows_executable(slnpath, config)
#    else:
#        compile_linux_executable(slnpath, config)

# -----------------------------------------------------------------------------

def compile_windows_executable(slnpath, config):
    """Compile the astylewx executable for Windows.
    """
    sdk = "v3.5"
    if VS_RELEASE >= "vs2010":
        sdk = "v4.0.30319"
    # remove the cache file as a precaution
    cachepath = slnpath + "/AStyleWx {0}.sln.cache".format(WX_RELEASE)
    if os.path.isfile(cachepath):
        os.remove(cachepath)
    # call MSBuild
    if VS_RELEASE == "vs2013":
        buildpath = "C:/Program Files (x86)/MSBuild/12.0/Bin/MSBuild.exe"
    elif VS_RELEASE >= "vs2015":
        buildpath = "C:/Program Files (x86)/MSBuild/14.0/Bin/MSBuild.exe"
    else:
        buildpath = (os.getenv("WINDIR")
                     + "/Microsoft.NET/Framework/"
                     + sdk
                     + "/MSBuild.exe")
    if not os.path.isfile(buildpath):
        message = "Cannot find build path: " + buildpath
        system_exit(message)
    if config == DEBUG:
        config_prop = "/property:Configuration=Debug"
    elif config == STATIC or config == STATIC_XP:
        config_prop = "/property:Configuration=Static"
    else:
        config_prop = "/property:Configuration=Release"
    platform_prop = "/property:Platform=Win32"
    if VS_RELEASE > "vs2013":
        platform_prop = "/property:Platform=x86"
    msbuild = ([buildpath, config_prop, platform_prop, slnpath])
    buildfile = get_temp_directory() + "/build." + config + ".tmp"
    if os.path.exists(buildfile):
        remove_build_file(buildfile)
    outfile = open(buildfile, 'w')
    retval = subprocess.call(msbuild, stdout=outfile)
    if retval:
        system_exit("Bad msbuild return: " + str(retval))
    outfile.close()
    remove_build_file(buildfile)

# -----------------------------------------------------------------------------

def get_7zip_path():
    """Get the 7zip executable path for the os environment.
    """
    if os.name == "nt":
        exepath = "C:/Program Files/7-Zip/7z.exe"
    else:
        exepath = "7z"
    return exepath

# -----------------------------------------------------------------------------

def get_astyle_directory(endsep=False):
    """Get the AStyle directory for the os environment.
       endsep = True will add an ending separator.
    """
    if endsep != True and endsep != False:
        system_exit("Bad arg in get_astyle_directory(): " + endsep)
    astyledir = get_project_directory() + "/AStyle"
    if not os.path.isdir(astyledir):
        message = "Cannot find astyle directory: " + astyledir
        system_exit(message)
    if endsep:
        astyledir += '/'
    return astyledir

# -----------------------------------------------------------------------------

def get_astylewx_build_directory(config):
    """Get the AStyleWx build path for the os environment.
    """
    if config != DEBUG and config != RELEASE and config != STATIC and config != STATIC_XP:
        system_exit("Bad arg in get_astylewx_build_directory(): " + config)
    astylewxdir = get_astylewx_directory()
    if os.name == "nt":
        if config == STATIC_XP:
            subpath = "/build/" + VS_RELEASE + "_" + WX_RELEASE + "-xp"
        else:
            subpath = "/build/" + VS_RELEASE + "_" + WX_RELEASE
    else:
        subpath = "/build/gcc"
    astylewxpath = astylewxdir + subpath
    if not os.path.isdir(astylewxpath):
        message = "Cannot find astylewx build directory: " + astylewxpath
        system_exit(message)
    return astylewxpath

# -----------------------------------------------------------------------------

def get_astylewx_directory(endsep=False):
    """Get the AStyleWx directory for the os environment.
       endsep = True will add an ending separator.
    """
    if endsep != True and endsep != False:
        system_exit("Bad arg in get_astylewx_directory(): " + endsep)
    astylewxdir = get_project_directory() + "/AStyleWx"
    if not os.path.isdir(astylewxdir):
        message = "Cannot find astylewx directory: " + astylewxdir
        system_exit(message)
    if endsep:
        astylewxdir += '/'
    return astylewxdir

# -----------------------------------------------------------------------------

def get_astylewxtest_directory(endsep=False):
    """Get the AStyleWx directory for the os environment.
       endsep = True will add an ending separator.
    """
    if endsep != True and endsep != False:
        system_exit("Bad arg in get_astylewx_directory(): " + endsep)
    astylewxdir = get_project_directory() + "/AStyleWxTest"
    if not os.path.isdir(astylewxdir):
        message = "Cannot find astylewx directory: " + astylewxdir
        system_exit(message)
    if endsep:
        astylewxdir += '/'
    return astylewxdir

# -----------------------------------------------------------------------------

def get_ch():
    """get_ch() for Windows and Linux.
       This won't work unless run from a terminal.
    """
    # this must be executed from a terminal
    if not is_executed_from_console():
        system_exit("libastylewx.get_ch() must be run from the console")
    # WINDOWS uses msvcrt
    if os.name == "nt":
        # clear buffer
        while msvcrt.kbhit():
            msvcrt.getch()
        # read char
        ch_in = msvcrt.getch()
    # LINUX uses termios and tty
    else:
        # clear buffer
        sys.stdin.flush()
        # read char
        fd_in = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd_in)
        try:
            tty.setraw(sys.stdin.fileno())
            ch_in = sys.stdin.read(1)
            if ch_in == '\x1b':			# alt key (27)
                ch_in = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd_in, termios.TCSADRAIN, old_settings)
    # convert to unicode for Python 3
    return ch_in.decode('utf-8')

# -----------------------------------------------------------------------------

def get_file_py_directory(endsep=False):
    """Get the file-py directory for the os environment.
       endsep = True will add an ending separator.
    """
    # get the path where this file is located
    pydir = sys.path[0]
    if endsep:
        pydir += '/'
    # verify it is executed from fixed disk and not a USB
    if os.name == "nt":
        if pydir[0:2] != "C:" and pydir[0:2] != "F:":
            system_exit("File executed from drive " + pydir[0:2])
    else:
        if pydir[0:6] != "/home/":
            sep = pydir[0:].find("/Projects/")
            if sep == -1:
                sep = len(pydir)
            else:
                sep += 1
            system_exit("File executed from drive " + pydir[0:sep])
    return  pydir

# -----------------------------------------------------------------------------

def get_project_directory(endsep=False):
    """Get the Project directory for the os environment.
       Extract the Project directory from path[0]
       endsep = True will add an ending separator.
    """
    # get project directory
    pydir = get_file_py_directory()
    projdir = pydir
    tail = pydir
    while len(tail) > 0:
        head, tail = os.path.split(projdir)
        if tail == 'Projects':
            break
        projdir = head
    if len(tail) == 0:
        system_exit("Cannot find project directory " + pydir[0:])
    if endsep:
        projdir += '/'
    return  projdir

# -----------------------------------------------------------------------------

def get_python_version():
    """Return the Python version number as a string."""
    version = ""
    if platform.python_implementation() == "CPython":
        version = "Python"
    else:
        version = platform.python_implementation()
    version += " {0}.{1}.{2}  ".format(sys.version_info[0],
                                       sys.version_info[1],
                                       sys.version_info[2])
    version += "({0})".format(platform.architecture()[0])
    return version

# -----------------------------------------------------------------------------

def get_temp_directory():
    """Get the temporary directory for the os environment.
       endsep = True will add an ending separator.
    """
    if os.name == "nt":
        tempdir = os.getenv("TEMP")
        tempdir = tempdir.replace('\\', '/')
    else:
        tempdir = "./"
    return  tempdir

# -----------------------------------------------------------------------------

def is_executed_from_console():
    """Check if this script is run is from the console or from an editor.
       If run from a console the sys.stdin will be a TTY.
    """
    return sys.stdin.isatty()

# -----------------------------------------------------------------------------

def remove_build_file(buildfile):
    """Remove the build.CONFIG.tmp file from the astylewx compile.
       If the file cannot be removed it is probably in use by another script.
       Wait until the other script finishes the compile to fix the problem.
    """
    try:
        os.remove(buildfile)
    except WindowsError as err:
        print()
        print(err)
        message = ("The file '{0}' must be removed "
                   "before continuing").format(buildfile)
        system_exit(message)

# -----------------------------------------------------------------------------

def set_text_color(color):
    """Change text color if script is run from the console.
    """
    if is_executed_from_console():
        if os.name == "nt":
            color_values = {"blue"    : "color 09",
                            "cyan"    : "color 0B",
                            "green"   : "color 0A",
                            "magenta" : "color 0D",
                            "red"     : "color 0C",
                            "white"   : "color 0F",
                            "yellow"  : "color 0E"}

            system_code = color_values.get(color, "invalid")
            if system_code == "invalid":
                system_exit("Invalid color param " + color)
            os.system(system_code)
        else:
            color_values = {"blue"    : "echo -n '[1;34m'",
                            "cyan"    : "echo -n '[1;36m'",
                            "green"   : "echo -n '[1;32m'",
                            "magenta" : "echo -n '[1;35m'",
                            "red"     : "echo -n '[1;31m'",
                            "white"   : "echo -n '[1;37m'",
                            "yellow"  : "echo -n '[1;33m'"}

            system_code = color_values.get(color, "invalid")
            if system_code == "invalid":
                system_exit("Invalid color param " + color)
            os.system(system_code)

# -----------------------------------------------------------------------------

def system_exit(message=''):
    """Accept keyboard input to assure a message is noticed.
    """
    if len(message.strip()) > 0:
        set_text_color("red")
        print(message)
    # pause if script is run from the console
    if is_executed_from_console():
        print("\nPress any key to end . . .")
        get_ch()
    else:
        print("\nEnd of script !")
    # this does NOT raise a SystemExit exception like sys.exit()
    os._exit(0)

# -----------------------------------------------------------------------------

def test_all_functions():
    """Test all functions for syntax.
    """
    if os.name == "nt":
        build_astylewx_executable(DEBUG)		# calls compile_astyle_windows()
    get_7zip_path()
    #get_archive_directory()
    get_astylewx_build_directory(DEBUG)
    get_astylewx_directory()
    #get_astyleexe_path(DEBUG)
    get_astylewxtest_directory()
    #get_diff_path()
    get_file_py_directory()
    #get_home_directory()
    get_project_directory()
    get_python_version()
    #get_python_version_number()
    get_temp_directory()
    #get_test_directory()
    is_executed_from_console()
    set_text_color("white")

# -----------------------------------------------------------------------------

# make the module executable
# run tests if executed as stand-alone
if __name__ == "__main__":
    print(get_python_version())
    print("Testing Library Functions")
    test_all_functions()
    system_exit()
