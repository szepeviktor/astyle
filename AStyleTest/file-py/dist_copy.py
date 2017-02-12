#! /usr/bin/python
""" Create the distribution files for Artistic Style.
    Windows distribution is created on Windows.
    Linux distribution is created on Linux.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import os
import shutil
import stat
import subprocess
import time
# local libraries
import libastyle

# global variables ------------------------------------------------------------

# release number for distribution file
AS_RELEASE = "2.7"

# extract all platforms for testing (Windows, Linux, Mac)
#EXTRACT_ALL = False
EXTRACT_ALL = True

# inut from AStyle directory
__astyle_dir = libastyle.get_astyle_directory()
# output to Project directory
__base_dir = libastyle.get_project_directory()

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    libastyle.set_text_color("yellow")
    print(libastyle.get_python_version())
    os.chdir(libastyle.get_file_py_directory())
    remove_dist_directories()
    verify_localizer_signature()
    if EXTRACT_ALL:
        build_windows_distribution()
        build_linux_distribution()
        build_mac_distribution()
    elif os.name == "nt":
        build_windows_distribution()
    else:
        build_linux_distribution()
        build_mac_distribution()
#		build_vms_distribution()

# -----------------------------------------------------------------------------

def build_linux_distribution():
    """Copy astyle files to the linux directory.
    """
    print()
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    print("*           Copying AStyle Linux Distribution           *")
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    dist_base = __base_dir + "/DistLinux"
    dist_astyle = dist_base + "/astyle"
    os.makedirs(dist_astyle)

    # top directory
    dist_top = dist_astyle + "/"
    copy_astyle_top(dist_top)

    # build directory
    dist_build = dist_astyle + "/build"
    os.mkdir(dist_build)
    copy_linux_build_directories(dist_build)

    # doc directory
    dist_doc = dist_astyle + "/doc/"
    os.mkdir(dist_doc)
    copy_astyle_doc(dist_doc)

    # src directory
    dist_src = dist_astyle + "/src/"
    os.mkdir(dist_src)
    copy_astyle_src(dist_src)

    # create tar.bz2
    tarname = "astyle_{0}_linux.tar".format(AS_RELEASE)
    call_7zip(dist_base, tarname)
    bz2name = tarname + ".gz"
    call_7zip(dist_base, bz2name)

# -----------------------------------------------------------------------------

def build_mac_distribution():
    """Copy astyle files to the mac directory.
    """
    print()
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    print("*            Copying AStyle Mac Distribution            *")
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    print("Building release", AS_RELEASE)
    dist_base = __base_dir + "/DistMac"
    dist_astyle = dist_base + "/astyle"
    os.makedirs(dist_astyle)

    # top directory
    dist_top = dist_astyle + "/"
    copy_astyle_top(dist_top)

    # build directory
    dist_build = dist_astyle + "/build"
    os.mkdir(dist_build)
    copy_mac_build_directories(dist_build)

    # doc directory
    dist_doc = dist_astyle + "/doc/"
    os.mkdir(dist_doc)
    copy_astyle_doc(dist_doc)

    # src directory
    dist_src = dist_astyle + "/src/"
    os.mkdir(dist_src)
    copy_astyle_src(dist_src)

    # create tar.gz
    tarname = "astyle_{0}_macos.tar".format(AS_RELEASE)
    call_7zip(dist_base, tarname)
    gzname = tarname + ".gz"
    call_7zip(dist_base, gzname)

# -----------------------------------------------------------------------------

def build_vms_distribution():
    """Copy astyle files to the open vms directory.
    """
    print()
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    print("*          Copying AStyle OpenVMS Distribution          *")
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    print("Building release", AS_RELEASE)
    dist_base = __base_dir + "/DistVMS"
    dist_astyle = dist_base + "/astyle"
    os.makedirs(dist_astyle)

    # top directory
    dist_top = dist_astyle + "/"
    copy_astyle_top(dist_top)

    # doc directory
    dist_doc = dist_astyle + "/doc/"
    os.mkdir(dist_doc)
    copy_astyle_doc(dist_doc)

    # src directory
    dist_src = dist_astyle + "/src/"
    os.mkdir(dist_src)
    copy_astyle_src(dist_src)

    # build/mac directory
    astyle_build_vms = __astyle_dir + "/build/vms/"
    dist_build_vms = dist_astyle + "/build/vms/"
    os.makedirs(dist_build_vms)
    for file_in in ("descrip.mms",
                    "java.opt",
                    "lib.opt",
                    "vmsbuild.com"):
        shutil.copy(astyle_build_vms + file_in, dist_build_vms)

    # create zip
    zipfile = "astyle_{0}_openvms.zip".format(AS_RELEASE)
    call_7zip(dist_base, zipfile)

# -----------------------------------------------------------------------------

def build_windows_distribution():
    """Copy astyle files to the windows directory.
    """
    print()
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    print("*          Copying AStyle Windows Distribution          *")
    print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
    # the following variables may be modified
    # do NOT use STATIC_XP, there is another script for that
    vsdir = libastyle.VS_RELEASE
    vscfg = libastyle.STATIC

    print("Compiling with", vsdir)
    print("Building AStyle release", AS_RELEASE)
    if not vsdir >= "vs2013":
        libastyle.system_exit("Must compile with vs2013 or greater in libastyle: " + vsdir)
    dist_base = __base_dir + "/DistWindows"
    dist_astyle = dist_base + "/AStyle"
    os.makedirs(dist_astyle)
    libastyle.build_astyle_executable(vscfg)

    # Windows includes an executable in the bin directory
    print("copying exe")
    dist_astyle_bin = dist_astyle + "/bin/"
    os.mkdir(dist_astyle_bin)
    astyle_build_directory = libastyle.get_astyle_build_directory(vscfg)
    if vscfg == libastyle.DEBUG:
        shutil.copy(astyle_build_directory + "/debug/AStyled.exe", dist_astyle_bin)
    elif vscfg == libastyle.RELEASE:
        shutil.copy(astyle_build_directory + "/bin/AStyle.exe", dist_astyle_bin)
    elif vscfg == libastyle.STATIC:
        shutil.copy(astyle_build_directory + "/binstatic/AStyle.exe", dist_astyle_bin)
    else:
        libastyle.system_exit("Invalid compile configuration: " + vscfg)

    # top directory
    dist_top = dist_astyle + "/"
    copy_astyle_top(dist_top, True)

    # build directory
    dist_build = dist_astyle + "/build"
    os.mkdir(dist_build)
    copy_windows_build_directories(dist_build)

    # doc directory
    dist_doc = dist_astyle + "/doc/"
    os.mkdir(dist_doc)
    copy_astyle_doc(dist_doc, True)

    # file directory
    dist_file = dist_astyle + "/file/"
    os.mkdir(dist_file)
    copy_astyle_file(dist_file, True)

    # src directory
    dist_src = dist_astyle + "/src/"
    os.mkdir(dist_src)
    copy_astyle_src(dist_src, True)

    # create zip
    zipfile = "AStyle_{0}_windows.zip".format(AS_RELEASE)
    call_7zip(dist_base, zipfile)

# -----------------------------------------------------------------------------

def call_7zip(dist_base, compressed_file):
    """Call 7zip to create an archive.
       arg 1- the directory to compress.
       arg 2- name of the compressed file.
    """
    exepath = libastyle.get_7zip_path()
    compress = [exepath, "a", compressed_file]
    # check file ending to see if it is a tarball
    if compressed_file.endswith((".gz", ".bz2")):
        compress.append("*.tar")
    # stdout file must have full path since 'cwd' is used in call
    filename = libastyle.get_file_py_directory(True) + "compress.txt"
    outfile = open(filename, 'w')
    try:
        subprocess.check_call(compress, cwd=dist_base, stdout=outfile)
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("Bad 7zip return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("Cannot find executable: " + compress[0])
    outfile.close()
    os.remove(filename)
    print(compressed_file + " created")

# -----------------------------------------------------------------------------

def convert_line_ends(dist_dir, to_dos):
    """Convert line ends to dos (CRLF) or linux (LF).
       Needs tofrodos package.
       All files in a directory are converted.
    """
    files = glob.glob(dist_dir + "*.*")
    if os.name == "nt":
        exedir = "C:/Programs/tofrodos/"
        if to_dos:
            call_list = [exedir + "todos"] + files
        else:
            call_list = [exedir + "fromdos"] + files
    else:
        if to_dos:
            call_list = ["todos"] + files
        else:
            call_list = ["fromdos"] + files

    # call the conversion program
    try:
        subprocess.check_call(call_list)
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("Bad tofro return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("Cannot find executable: " + call_list[0])

# -----------------------------------------------------------------------------

def copy_astyle_doc(dist_doc, to_dos=False):
    """Copy astyle doc directory to a distribution directory.
    """
    print("copying doc")
    deleted = 0
    docfiles = sorted(glob.glob(__astyle_dir + "/doc/*"))
    for filepath in docfiles:
        sep = filepath.rfind(os.sep)
        filename = filepath[sep + 1:]
        if (filename == "astyle.html"
                or filename == "install.html"
                or filename == "news.html"
                or filename == "notes.html"
                or filename == "styles.css"):
            shutil.copy(filepath, dist_doc)
            print("    " + filename)
        else:
            deleted += 1
    convert_line_ends(dist_doc, to_dos)
    # verify copy - had a problem with bad filenames
    distfiles = (glob.glob(dist_doc + "/*.html")
                 + glob.glob(dist_doc + "/*.css"))
    if len(distfiles) != len(docfiles) - deleted:
        libastyle.system_exit("Error copying doc: " + str(len(distfiles)))
    # change file permissions
    for srcfile in distfiles:
        # read/write by the owner and read only by everyone else (-rw-r--r--)
        mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
        os.chmod(srcfile, mode)

# -----------------------------------------------------------------------------

def copy_astyle_file(dist_file, to_dos=False):
    """Copy astyle src directory to a distribution directory.
    """
    print("copying file")
    deleted = 0
    filefiles = sorted(glob.glob(__astyle_dir + "/file/*"))
    for filepath in filefiles:
        sep = filepath.rfind(os.sep)
        filename = filepath[sep + 1:]
        unused, ext = os.path.splitext(filename)
        if ext != ".yaml":
            shutil.copy(filepath, dist_file)
            print("    " + filename)
        else:
            deleted += 1
    convert_line_ends(dist_file, to_dos)
    # verify copy - had a problem with bad filenames
    distfiles = glob.glob(dist_file + "/*")
    if len(distfiles) != len(filefiles) - deleted:
        libastyle.system_exit("Error copying file: " + str(len(distfiles)))
    # change file permissions
    for filefile in distfiles:
        # read/write by the owner and read only by everyone else (-rw-r--r--)
        mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
        os.chmod(filefile, mode)

# -----------------------------------------------------------------------------

def copy_astyle_src(dist_src, to_dos=False):
    """Copy astyle src directory to a distribution directory.
    """
    print("copying src")
    srcfiles = sorted(glob.glob(__astyle_dir + "/src/*"))
    for srcpath in srcfiles:
        shutil.copy(srcpath, dist_src)
    convert_line_ends(dist_src, to_dos)
    # verify copy - had a problem with bad filenames
    distfiles = (glob.glob(dist_src + "/*.cpp")
                 + glob.glob(dist_src + "/*.h"))
    if len(distfiles) != len(srcfiles):
        libastyle.system_exit("Error copying src: " + str(len(distfiles)))
    # change file permissions
    for srcfile in distfiles:
        # read/write by the owner and read only by everyone else (-rw-r--r--)
        mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
        os.chmod(srcfile, mode)

# -----------------------------------------------------------------------------

def copy_astyle_top(dist_top, to_dos=False):
    """Copy files in the top directory to a distribution directory.
    """
    print("copying top")
    deleted = 0
    docfiles = sorted(glob.glob(__astyle_dir + "/*"))
    for filepath in docfiles:
        sep = filepath.rfind(os.sep)
        filename = filepath[sep + 1:]
        if (filename == "LICENSE.txt"
                or filename == "README.txt"):
            shutil.copy(filepath, dist_top)
            print("    " + filename)
        else:
            deleted += 1
    convert_line_ends(dist_top, to_dos)
    # verify copy - had a problem with bad filenames
    distfiles = (glob.glob(dist_top + "/*.txt"))
    if len(distfiles) != len(docfiles) - deleted:
        libastyle.system_exit("Error copying top: " + str(len(distfiles)))
    # change file permissions
    for srcfile in distfiles:
        # read/write by the owner and read only by everyone else (-rw-r--r--)
        mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
        os.chmod(srcfile, mode)

# -----------------------------------------------------------------------------

def copy_build_directories_cb(dist_build, build_dir):
    """Copy the build/codeblocks directories to the distribution directory.
    """
    buildfiles = __astyle_dir + "/build/"
    dist_astyle_cb = dist_build + '/' + build_dir + '/'
    os.mkdir(dist_astyle_cb)
    files_copied = 0
    workfiles = glob.glob(buildfiles + build_dir + "/*.workspace")
    for workfile in workfiles:
        shutil.copy(workfile, dist_astyle_cb)
        files_copied += 1
    cbpfiles = glob.glob(buildfiles + build_dir + "/*.cbp")
    for cbpfile in cbpfiles:
        shutil.copy(cbpfile, dist_astyle_cb)
        files_copied += 1
    if files_copied != 5:
        libastyle.system_exit("Error in number of build files copied: " + str(files_copied))

# -----------------------------------------------------------------------------

def copy_build_directories_make(dist_build, build_dir):
    """Copy the build/makefile directories to the distribution directory.
    """
    # permissions = read/write by the owner and read only by everyone else
    mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
    buildfiles = __astyle_dir + "/build/"

    makedir = '/' + build_dir + '/'
    dist_astyle_make = dist_build + makedir
    os.mkdir(dist_astyle_make)
    files_copied = 0
    makefiles = glob.glob(buildfiles + makedir + "[Mm]ake*")
    for makefile in makefiles:
        shutil.copy(makefile, dist_astyle_make)
        os.chmod(dist_astyle_make, mode)
        files_copied += 1
    if files_copied != 1:
        libastyle.system_exit("Error in number of build files copied: " + str(files_copied))

# -----------------------------------------------------------------------------

def copy_build_directories_vs(dist_build, build_dir):
    """Copy the build/visual-studio directories to the distribution directory.
    """
    buildfiles = __astyle_dir + "/build/"
    # copy solution files
    vsdir = '/' + build_dir + '/'
    dist_astyle_vs20xx = dist_build + vsdir
    os.mkdir(dist_astyle_vs20xx)
    slnfiles = glob.glob(buildfiles + vsdir + "*.sln")
    for sln in slnfiles:
        shutil.copy(sln, dist_astyle_vs20xx)

    # build project directories
    for projdir in ("/AStyle/",
                    "/AStyle Dll/",
                    "/AStyle Java/",
                    "/AStyle Lib/"):
        dist_astyle_proj = dist_astyle_vs20xx[:-1] + projdir
        os.mkdir(dist_astyle_proj)

        # copy project files
        projfiles = glob.glob(buildfiles + vsdir[:-1] + projdir + "*.*proj")
        files_copied = 0
        for proj in projfiles:
            files_copied += 1
            shutil.copy(proj, dist_astyle_proj)
        if vsdir[1:-1] >= "vs2010":
            filtfiles = glob.glob(buildfiles + vsdir[:-1] + projdir + "*.*.filters")
            for filter_in in filtfiles:
                files_copied += 1
                shutil.copy(filter_in, dist_astyle_proj)
        # verify number of files copied
        if files_copied != 2 and files_copied != 1:
            libastyle.system_exit("Error in number of build files copied: " + str(files_copied))

# -----------------------------------------------------------------------------

def copy_linux_build_directories(dist_build):
    """Copy the Linux build directories to the distribution directory.
    """
    print("copying build")
    buildfiles = __astyle_dir + "/build/"
    # get a list of build directories
    build_dir_list = sorted(os.listdir(buildfiles))
    for unused, build_dir in enumerate(build_dir_list):
        # build/codeblocks directories
        if (build_dir.startswith("cb-clang")
                or build_dir.startswith("cb-gcc")
                or build_dir.startswith("cb-intel")):
            print("    " + build_dir)
            copy_build_directories_cb(dist_build, build_dir)
        # build makefile directories
        if (build_dir.startswith("clang")
                or build_dir.startswith("gcc")
                or build_dir.startswith("intel")):
            print("    " + build_dir)
            copy_build_directories_make(dist_build, build_dir)

# -----------------------------------------------------------------------------

def copy_mac_build_directories(dist_build):
    """Copy the Mac build directories to the distribution directory.
    """
    print("copying build")
    buildfiles = __astyle_dir + "/build/"
    # get a list of build directories
    build_dir_list = sorted(os.listdir(buildfiles))
    for unused, build_dir in enumerate(build_dir_list):
        # build/codeblocks directories
        if build_dir.startswith("cb-mac"):
            print("    " + build_dir)
            copy_build_directories_cb(dist_build, build_dir)
        # build makefile directories
        if build_dir.startswith("mac"):
            print("    " + build_dir)
            copy_build_directories_make(dist_build, build_dir)

    # build/xcode directory
    print("    xcode")
    astyle_build_xcode = __astyle_dir + "/build/xcode/"
    dist_build_xcode = dist_build + "/xcode/"
    shutil.copytree(astyle_build_xcode, dist_build_xcode)
    # permissions = read/write by the owner and read only by everyone else
    mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
    for file_in in ("/AStyle.xcodeproj/project.pbxproj",
                    "/AStyleA.xcodeproj/project.pbxproj",
                    "/AStyleDylib.xcodeproj/project.pbxproj",
                    "/AStyleJava.xcodeproj/project.pbxproj"):
        os.chmod(dist_build_xcode + file_in, mode)
    for file_in in ("/install.sh",
                    "/uninstall.sh"):
        os.chmod(dist_build_xcode + file_in, mode)

# -----------------------------------------------------------------------------

def copy_windows_build_directories(dist_build):
    """Copy the build/vs20xx directories to the distribution directory.
    """
    print("copying build")
    buildfiles = __astyle_dir + "/build"
    # get a list of build/vs20xx directories
    build_dir_list = sorted(os.listdir(buildfiles))
    for unused, build_dir in enumerate(build_dir_list):
        # build/codeblocks directories
        if (build_dir.startswith("cb-bcc32c")
                or build_dir.startswith("cb-mingw")):
            print("    " + build_dir)
            copy_build_directories_cb(dist_build, build_dir)

        # build/vs directories
        if (build_dir.startswith("vs20")
                and not build_dir.endswith("-clang")):
            print("    " + build_dir)
            copy_build_directories_vs(dist_build, build_dir)

# -----------------------------------------------------------------------------

def remove_dist_directories():
    """Remove directories from a previous run.
    """
    dirs = sorted(glob.glob(__base_dir + "/[Dd]ist*/"))
    for directory in dirs:
        if "wx" in directory.lower():
            continue
        directory = directory.replace('\\', '/')
        print("remove " + directory)
        # remove the directory - this is a problem with Windows only
        imax = 5
        for i in range(0, imax):
            shutil.rmtree(directory, True)
            if not os.path.isdir(directory):
                break
            if i == imax - 1:
                libastyle.system_exit("Directory not removed: " + directory)
            time.sleep(2)

# -----------------------------------------------------------------------------

def verify_localizer_signature():
    """Verify that ASLocalizer.cpp does NOT have a signature (BOM).
    """
    localizerpath = libastyle.get_astyle_directory() + "/src/ASLocalizer.cpp"
    file_fd = os.open(localizerpath, os.O_RDONLY)
    file_bytes = os.read(file_fd, 8)
    if file_bytes[:3] == b"\xEF\xBB\xBF":
        libastyle.system_exit("\nASLocalizer.cpp must NOT have a signature")
    os.close(file_fd)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
