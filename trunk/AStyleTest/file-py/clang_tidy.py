#! /usr/bin/python3
""" Generate the suppression file and run clang-tidy.
    Input the AStyle source files and output the suppression file
    with the current line numbers.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import os
import platform
import subprocess
# local libraries
import libastyle

# global variables ------------------------------------------------------------

__minimum_version = "6.0"
__src_dir = libastyle.get_astyle_directory() + "/src/"
__py_dir = libastyle.get_astyletest_directory() + "/file-py/"
#__astyle_file_names = [os.path.basename(path)
 #                      for path in glob.glob(__src_dir + "*.cpp")]
# can also check selected files in a list
__astyle_file_names = ["astyle_main.cpp"]

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    if os.name == "nt":
        tidy_exepath = "C:/Program Files/LLVM/bin/clang-tidy.exe"
    else:
        tidy_exepath = "clang-tidy"

    tidy_version = verify_clang_tidy_version(tidy_exepath)
    print("clang-tidy version " + tidy_version)

    __astyle_file_names.sort()
    for file_name in __astyle_file_names:
        run_clang_tidy(tidy_exepath, tidy_version, file_name)

# -----------------------------------------------------------------------------

def run_clang_tidy(tidy_exepath, tidy_version, file_name):
    """Run the clang-tidy program for the specified file.
       List of clang-tidy checks:
       https://clang.llvm.org/extra/clang-tidy/checks/list.html
       NOTE: The window stays open only if run from the console.
    """
    # cert-err34-c warns of using atoi errors - astyle_main checks the input length to avoid
    # cert-err58-cpp warns of static storage exceptions for static variables in ASResource
    #
    # to fix one option: (disable checks, add the option, include -fix)
    # clangtidy.append("-checks=-*,readability-implicit-bool-cast")
    # clangtidy.append("-fix")
    #
    tidy_checks = ("-checks=*,"
                   "-cert-err34-c,"
                   "-cert-err58-cpp,"
                   "-cppcoreguidelines-owning-memory,"
                   "-cppcoreguidelines-pro-bounds-array-to-pointer-decay,"
                   "-cppcoreguidelines-pro-bounds-pointer-arithmetic,"
                   "-cppcoreguidelines-pro-type-member-init,"
                   "-cppcoreguidelines-pro-type-vararg,"
                   "-cppcoreguidelines-special-member-functions,"
                   "-fuchsia-default-arguments,"
                   "-google-build-using-namespace,"
                   "-google-readability-braces-around-statements,"
                   "-google-readability-casting,"
                   "-google-readability-todo,"
                   "-google-runtime-references,"
                   "-hicpp-braces-around-statements,"
                   "-hicpp-member-init,"
                   "-hicpp-no-array-decay,"
                   "-hicpp-signed-bitwise,"
                   "-hicpp-special-member-functions,"
                   "-hicpp-use-auto,"
                   "-hicpp-use-noexcept,"
                   "-hicpp-vararg,"
                   "-llvm-header-guard,"
                   "-misc-misplaced-widening-cast,"
                   "-misc-unused-parameters,"
                   "-readability-braces-around-statements,"
                   "-readability-implicit-bool-cast,"
                   "-readability-implicit-bool-conversion,"
                   "-readability-simplify-boolean-expr,"
                   "-modernize-use-auto,"
                   "-modernize-use-noexcept")
    # version 7 checks
    # if tidy_version[:1] > "6":
    #     tidy_checks += (",")

    clangtidy = [tidy_exepath]
    clangtidy.append(tidy_checks)
    clangtidy.append("-header-filter=.*")
    clangtidy.append(__src_dir + file_name)
    clangtidy.append("--")                  # compiler options follow
    clangtidy.append("-std=c++14")          # c++14 minimum is required for clang
    clangtidy.append("-fno-rtti")
    clangtidy.append("-fno-exceptions")
#    clangtidy.append("-DASTYLE_LIB")

    # stdout file must have full path
    filename = __src_dir + "xclang-" + file_name + ".txt"
    outfile = open(filename, 'w')
    print()
    print(file_name)
    # shell=True keeps the console window open, but will not display if run from an editor
    # subprocess.check_call() doesn't work from an editor
    try:
        subprocess.check_call(clangtidy, stdout=outfile)
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("Bad clang-tidy return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("Cannot find executable: " + clangtidy[0])

# -----------------------------------------------------------------------------

def verify_clang_tidy_version(tidy_exepath):
    """Verify the clang-tidy version number to the expected version.
       A lower version number may result in unexpected warnings.
       The expected version number is global.
       Return the two digit version number.
    """
    # check_output always returns byte code
    try:
        version = subprocess.check_output([tidy_exepath, "-version"])
    except subprocess.CalledProcessError as err:
        libastyle.system_exit("\nBad clang-tidy return: " + str(err.returncode))
    except OSError:
        libastyle.system_exit("\nCannot find executable: " + tidy_exepath)

    if platform.python_version_tuple()[0] >= '3':
        version = version.decode()
    version = version[40:43]
    if version < __minimum_version:
        print("clang-tidy version", version,
              "is less than minimum version", __minimum_version, "\n")
    return version

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
