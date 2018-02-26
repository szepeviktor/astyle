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

__expected_version = "5.0"
__src_dir = libastyle.get_astyle_directory() + "/src/"
__py_dir = libastyle.get_astyletest_directory() + "/file-py/"
__astyle_file_names = [os.path.basename(path)
                       for path in glob.glob(__src_dir + "*.cpp")]
# can also check selected files in a list
#__astyle_file_names = ["astyle_main.cpp"]

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    if os.name == "nt":
        tidy_exepath = "C:/Program Files/LLVM/bin/clang-tidy.exe"
        if not os.path.exists(tidy_exepath):
            libastyle.system_exit("Cannot find executable: " + tidy_exepath)
    else:
        tidy_exepath = "clang-tidy-5.0"

    clang_version = verify_clang_tidy_version(tidy_exepath)
    print("clang-tidy version " + clang_version)

    __astyle_file_names.sort()
    for file_name in __astyle_file_names:
        run_clang_tidy(tidy_exepath, file_name)

# -----------------------------------------------------------------------------

def run_clang_tidy(tidy_exepath, file_name):
    """Run the clang-tidy program for the specified file.
       NOTE: The window stays open only if run from the console.
    """
    # cert-err34-c warns of using atoi errors - astyle_main checks the input length to avoid
    # cert-err58-cpp warns of static storage exceptions for static variables in ASResource
    # cppcoreguidelines-pro-bounds-array-to-pointer-decay is a false positive on asserts
    # cppcoreguidelines-pro-bounds-pointer-arithmetic, don't use pointer arithmetic in astyle_main
    # cppcoreguidelines-pro-type-member-init gives constructor does not initialize warning
    # cppcoreguidelines-pro-type-vararg don't use printf in astyle_main
    # cppcoreguidelines-special-member-functions add copy and move assignments
    # google-build-using-namespace gives warning for "using namespace"
    # google-readability-braces-around-statements
    # google-readability-casting replaces c-style casts with c++ casts
    # google-readability-todo adds username to todo comments
    # google-runtime-references
    # hicpp-member-init adds braces to member variables for initialization
    # hicpp-special-member-functions same as cppcoreguidelines-special-member-functions
    # llvm-header-guard adds the filepath to the header guard name
    # misc-misplaced-widening-cast is casting size_t to int instead of int to size_t
    # misc-unused-parameters caused several false positives, is checked by compiler
    # readability-braces-around-statements expects braces around single statements
    # readability-implicit-bool-cast use 'if (x=0)' instead of 'if (!x)'
    # readability-simplify-boolean-expr returns a conditional statement
    #
    # modernize-use-auto recomments using auto for variable types
    # modernize-use-noexcept astyle uses no-exceptions compiler option
    #
    # to fix one option: (disable checks, add the option, include -fix)
    # clangtidy.append("-checks=-*,readability-implicit-bool-cast")
    # clangtidy.append("-fix")
    #
    tidy_checks = ("-checks=*,"
                   "-cert-err34-c,"
                   "-cert-err58-cpp,"
                   "-cppcoreguidelines-pro-bounds-array-to-pointer-decay,"
                   "-cppcoreguidelines-pro-bounds-pointer-arithmetic,"
                   "-cppcoreguidelines-pro-type-member-init,"
                   "-cppcoreguidelines-pro-type-vararg,"
                   "-cppcoreguidelines-special-member-functions,"
                   "-google-build-using-namespace,"
                   "-google-readability-braces-around-statements,"
                   "-google-readability-casting,"
                   "-google-readability-todo,"
                   "-google-runtime-references,"
                   "-hicpp-member-init,"
                   "-hicpp-special-member-functions,"
                   "-llvm-header-guard,"
                   "-misc-misplaced-widening-cast,"
                   "-misc-unused-parameters,"
                   "-readability-braces-around-statements,"
                   "-readability-implicit-bool-cast,"
                   "-readability-simplify-boolean-expr,"
                   "-modernize-use-auto,"
                   "-modernize-use-noexcept")
    clangtidy = [tidy_exepath]
    clangtidy.append(tidy_checks)
    clangtidy.append("-header-filter=.*")
    clangtidy.append(__src_dir + file_name)
    clangtidy.append("--")                  # compiler options follow
    clangtidy.append("-std=c++14")          # c++14 minimum is required for clang
    clangtidy.append("-fno-rtti")
    clangtidy.append("-fno-exceptions")
    # stdout file must have full path
    filename = __src_dir + "xclang-" + file_name + ".txt"
    outfile = open(filename, 'w')
    print()
    print(file_name)
    # shell=True keeps the console window open, but will not display if run from an editor
    # subprocess.check_output() doesn't work from an editor
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
    version = subprocess.check_output([tidy_exepath, "-version"])
    if platform.python_version_tuple()[0] >= '3':
        version = version.decode()
    version = version[40:43]
    if version < __expected_version:
        print("clang-tidy version", version,
              "is less than expected version", __expected_version, "\n")
    return version

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastyle.system_exit()

# -----------------------------------------------------------------------------
