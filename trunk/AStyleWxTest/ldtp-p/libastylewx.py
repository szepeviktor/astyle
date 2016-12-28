# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import ldtp     # ldtp script
import os
import subprocess
import sys


# -----------------------------------------------------------------------------

# Visual Studio release
#VS_RELEASE = "vs2010"
#VS_RELEASE = "vs2012"
VS_RELEASE = "vs2013"

# wxWidgets release
WX_RELEASE = "3.0"

# -----------------------------------------------------------------------------

def activate_linux_menus():
    """Linux must open a menu to call OnMenuOpen() in
       astylewx to activate or deactivate the submenus.
    """
    if not os.name == "nt":
        ldtp.selectmenuitem('frmAStyleWx', 'mnuFile')
        ldtp.keypress('<esc>')
        ldtp.keyrelease('<esc>')
        ldtp.wait(1)

# -----------------------------------------------------------------------------

def close_astylewx_ldtp():
    """Close the test project astylewx program.
    """
    #print("Closing astylewx ldtp")
    ldtp.closewindow('frmAStyleWx')
    if not ldtp.waittillguinotexist('*AStyleWx'):
        terminate_program("Error in waittillguinotexist")

# -----------------------------------------------------------------------------

def compile_windows_astylewx_exe(config):
    """Compile the astylewx executable for Windows using MSBuild.
    """
    slnpath = (get_astylewx_path()
               + "/build/"
               + VS_RELEASE  + "_" + WX_RELEASE
               + "/AStyleWx_" + WX_RELEASE
               + ".sln")
    slnpath = slnpath.replace('/', os.sep)
    # remove the cache file as a precaution
    cachepath = slnpath + "/AStyle.sln.cache"
    if os.path.isfile(cachepath):
        os.remove(cachepath)
    # call MSBuild
    compver = "12.0"
    if VS_RELEASE >= "vs2015":
        compver = "14.0"
    buildpath = ("C:/Program Files (x86)/MSBuild/"
                  + compver
                  + "/Bin/MSBuild.exe")
    buildpath = buildpath.replace('/', os.sep)
    if not os.path.isfile(buildpath):
        message = "\nCannot find build path: " + buildpath
        terminate_program(message)
    config_prop = "/property:Configuration=" + config
    platform_prop = "/property:Platform=Win32"
    msbuild = ([buildpath, config_prop, platform_prop, slnpath])
    buildfile = get_temp_directory() + "/build." + config + ".tmp"
    if os.path.exists(buildfile):
        remove_build_file(buildfile)
    outfile = open(buildfile, 'w')
    retval = subprocess.call(msbuild, stdout=outfile)
    if retval:
        terminate_program("\nBad msbuild return: " + str(retval))
    outfile.close()
    remove_build_file(buildfile)

# -----------------------------------------------------------------------------

def get_astylewx_path():
    """Get the astylewx filepath from the argv filepath.
    """
    #print(sys.path[0])
    end = sys.path[0].find("AStyleWxTest")
    aswxpath = sys.path[0][:end] + "AStyleWx"
    aswxpath = aswxpath.replace(os.sep, '/')
    return aswxpath

# -----------------------------------------------------------------------------

def get_temp_directory():
    """Get the temporary directory for the os environment.
    """
    if os.name == "nt":
        tempdir = os.getenv("TEMP")
        tempdir = tempdir.replace(os.sep, '/')
    else:
        tempdir = "./"
    return  tempdir

# -----------------------------------------------------------------------------

def launch_astylewx_ldtp():
    """Run the test project astylewx program.
    """
    #print("Launching astylewx ldtp")
    if os.name == "nt":
        exepath = (get_astylewx_path()
                   + "/build/"
                   + VS_RELEASE  + "_" + WX_RELEASE
                   + "/debug/AStyleWxd_dll.exe")
        exepath = exepath.replace('/', os.sep)
    else:
        exepath = (get_astylewx_path()
                   + "/build/cb-gcc"
                   + "/wx" + WX_RELEASE
                   + "/bin/astylewxd")
    exeargs = ['--ldtp_test']

    try:
        ldtp.launchapp(exepath, exeargs)
    except ldtp.client_exception.LdtpExecutionError as err:
        print("\nError in launchapp: " + exepath)
        terminate_program(err)

    if not ldtp.waittillguiexist('*AStyleWx'):
        terminate_program("\nError in waittillguiexist")
    ldtp.wait(1)        # needed for linux

# -----------------------------------------------------------------------------

def print_separator():
    """Print an additional test separator.
    """
    print('')
    print('=' * 70)

# -----------------------------------------------------------------------------

def remove_build_file(buildfile):
    """Remove the build.CONFIG.tmp file from the astyle compile.
       If the file cannot be removed it is probably in use by another script.
       Wait until the other script finishes the compile to fix the problem.
    """
    try:
        os.remove(buildfile)
    except WindowsError as err:
        message = ("\nThe file '{0}' must be removed "
                    "before continuing").format(buildfile)
        print(message)
        terminate_program(err)

# -----------------------------------------------------------------------------

def terminate_program(errmsg):
    """Print an error message and terminate.
    """
    print(errmsg)
    print("The script has terminated!")
    sys.exit(1)
