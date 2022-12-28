#! /usr/bin/python3
"""Generate the suppression file and run clang-tidy.
   Input the AStyleWx source files and output the suppression file
   with the current line numbers.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import os
import platform
import subprocess
# local libraries
import libastylewx

# global variables ------------------------------------------------------------

__minimum_version = "5.0"
__src_dir = libastylewx.get_astylewx_directory() + "/src/"
__py_dir = libastylewx.get_astylewxtest_directory() + "/file-py/"
__suppression_path = __py_dir + "clang-tidy-suppress"
__astylewx_file_names = [os.path.basename(path)
                         for path in glob.glob(__src_dir + "*.cpp")]
# can also check selected files in a list
#__astylewx_file_names = ["ASEditor.cpp"]

# wxWidgets directories
if os.name == "nt":
    __wxw = "C:/Programs/wxWidgets-3.0.3_vs2017"
else:
    __wxw = "/usr"

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    if os.name == "nt":
        tidy_exepath = "C:/Program Files/LLVM/bin/clang-tidy.exe"
    else:
        tidy_exepath = "clang-tidy-5.0"

    tidy_version = verify_clang_tidy_version(tidy_exepath)
    print("clang-tidy version " + tidy_version)

    __astylewx_file_names.sort()
    for file_name in __astylewx_file_names:
        run_clang_tidy(tidy_exepath, tidy_version, file_name)

# -----------------------------------------------------------------------------

def run_clang_tidy(tidy_exepath, tidy_version, file_name):
    """Run the clang-tidy program for the specified file.
       NOTE: The window stays open only if run from the console.
    """
    # cppcoreguidelines-owning-memory
    # cppcoreguidelines-pro-type-member-init gives constructor does not initialize warning
    # cppcoreguidelines-pro-type-vararg don't use printf in astyle_main
    # google-global-names-in-headers, don't like the restriction (std::vector)
    # google-build-using-namespace gives warning for "using namespace"
    # google-readability-braces-around-statements
    # google-readability-casting replaces c-style casts with c++ casts
    # google-readability-todo adds username to todo comments
    # google-runtime-int values are determined by wxWidgets
    # google-runtime-references 'const' is determined by wxWidgets, cannot fix
    # hicpp-braces-around-statements redirects to readability-braces-around-statements
    # hicpp-member-init adds braces to member variables for initialization
    # hicpp-use-auto redirects to modernize-use-auto
    # hicpp-use-noexcept redirects to modernize-use-noexcept
    # llvm-header-guard adds the filepath to the header guard name
    # misc-misplaced-widening-cast is casting size_t to int instead of int to size_t
    # misc-unused-parameters caused several false positives, is checked by compiler
    # readability-braces-around-statements expects braces around single statements
    # readability-implicit-bool-cast use 'if (x=0)' instead of 'if (!x)'
    # readability-implicit-bool-conversion replaces above ...bool-cast in version6
    # readability-simplify-boolean-expr returns a conditional statement
    #
    # modernize-use-auto recommends using auto for variable types
    #
    # to fix one option: (disable checks, add the option, include -fix)
    # clangtidy.append("-checks=-*,readability-implicit-bool-cast")
    # clangtidy.append("-fix")
    #
    # version 5 checks
    tidy_checks = ("-checks=*,"
                   "-cppcoreguidelines-pro-type-member-init,"
                   "-google-global-names-in-headers,"
                   "-google-readability-braces-around-statements,"
                   "-google-readability-todo,"
                   "-google-runtime-int,"
                   "-google-runtime-references,"
                   "-hicpp-member-init,"
                   "-llvm-header-guard,"
                   "-misc-unused-parameters,"
                   "-readability-braces-around-statements,"
                   "-readability-implicit-bool-cast,"
                   "-readability-simplify-boolean-expr,"
                   "-modernize-use-auto")
    # version 6 checks
    if tidy_version[:1] > "5":
        tidy_checks += (","
                        "-cppcoreguidelines-owning-memory,"
                        "-fuchsia-default-arguments,"
                        "-hicpp-braces-around-statements,"
                        "-hicpp-use-auto,"
                        "-hicpp-use-noexcept,"
                        "-readability-implicit-bool-conversion")
    clangtidy = [tidy_exepath]
    clangtidy.append(tidy_checks)
    clangtidy.append("-header-filter=-^wx,$Base.h") # exclude wx and dialog headers
    clangtidy.append(__src_dir + file_name)
    clangtidy.append("--")                  # compiler options follow
    clangtidy.append("-std=c++14")          # c++14 minimum is required for clang
    clangtidy.append("-fno-rtti")
    clangtidy.append("-fno-exceptions")
    clangtidy.append("-I" + libastylewx.get_astylewx_directory() + "/dialog")
    if os.name == "nt":
        clangtidy.append("-I" + __wxw + "/include")
        clangtidy.append("-I" + __wxw + "/lib/vc_lib/mswud")
    else:
        clangtidy.append("-I" + __wxw + "/include/wx-3.0")
        # too many errors with setup.h
        #clangtidy.append("-I" + __wxw + "/lib/x86_64-linux-gnu/wx/include/gtk2-unicode-3.0")
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
        libastylewx.system_exit("Bad clang-tidy return: " + str(err.returncode))
    except OSError:
        libastylewx.system_exit("Cannot find executable: " + clangtidy[0])

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
        libastylewx.system_exit("\nBad clang-tidy return: " + str(err.returncode))
    except OSError:
        libastylewx.system_exit("\nCannot find executable: " + tidy_exepath)

    if platform.python_version_tuple()[0] >= '3':
        version = version.decode()
    version = version[40:43]
    if version < __minimum_version:
        print("\nclang-tidy version ", version,
              "is less than minimum version", __minimum_version, "\n")
    return version

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    libastylewx.system_exit()

# -----------------------------------------------------------------------------
