#! /usr/bin/python

""" ExampleByte.py
    This program calls the Artistic Style DLL to format the AStyle source files.
    The Artistic Style DLL must be in the same directory as this script.
    The Artistic Style DLL must have the same bit size (32 or 64) as the Python executable.
    It will work with either Python version 2 or 3 (unicode).
    For Python 3 the files are retained in byte format and not converted to Unicode.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import os
import platform
import sys
from ctypes import *

# global variables ------------------------------------------------------------

# will be updated from the platform properties by initialize_platform()
__is_iron_python__ = False
__is_unicode__ = False

# -----------------------------------------------------------------------------

def main():
    """Main processing function.
    """
    files = ["ASBeautifier.cpp", "ASFormatter.cpp", "astyle.h"]
    # options are byte code for AStyle input
    option_bytes = b"-A2tOP"

    #initialization
    print("ExampleByte",
          platform.python_implementation(),
          platform.python_version(),
          platform.architecture()[0])
    initialize_platform()
    libc = initialize_library()
    version_bytes = get_astyle_version_bytes(libc)
    print("Artistic Style Version " + version_bytes.decode('utf-8'))
    # process the input files
    for file_path in files:
        file_path = get_project_directory(file_path)
        bytes_in = get_source_code_bytes(file_path)
        formatted_bytes = format_source_bytes(libc, bytes_in, option_bytes)
        # if an error occurs, the return is a type(None) object
        if type(formatted_bytes) is type(None):
            print("Error in formatting", file_path)
            sys.exit(1)
        save_source_code_bytes(formatted_bytes, file_path)
        print("Formatted", file_path)

# -----------------------------------------------------------------------------

def format_source_bytes(libc, bytes_in, option_bytes):
    """Format the bytes_in by calling the AStyle shared object (DLL).
       The variable bytes_in is expected to be a byte string.
       The return value is a byte string.
       If an error occurs, the return value is a NoneType object.
    """
    astyle_main = libc.AStyleMain
    astyle_main.restype = c_char_p
    formatted_bytes = astyle_main(bytes_in,
                                  option_bytes,
                                  ERROR_HANDLER,
                                  MEMORY_ALLOCATION)
    return formatted_bytes

# -----------------------------------------------------------------------------

def get_astyle_version_bytes(libc):
    """Get the version number from the AStyle shared object (DLL).
       The function return value is a byte string.
    """
    astyle_version = libc.AStyleGetVersion
    astyle_version.restype = c_char_p
    version_bytes = astyle_version()
    return version_bytes

# -----------------------------------------------------------------------------

def get_project_directory(file_name):
    """Find the directory path and prepend it to the file name.
       The source is expected to be in the "src-py" directory.
       This may need to be changed for your directory structure.
    """
    file_path = sys.path[0]
    end = file_path.find("src-py")
    if end == -1:
        print("Cannot find source directory", file_path)
        sys.exit(1)
    file_path = file_path[0:end]
    file_path = file_path + "test-data" + os.sep + file_name
    return file_path

# -----------------------------------------------------------------------------

def get_source_code_bytes(file_path):
    """Get the source code as bytes.
       Opening the file as binary will read it as a byte string.
       The return value is a byte string.
    """
    # read the file as a byte string by declaring it as binary
    # version 3 will read unicode if not declared as binary
    try:
        file_in = open(file_path, 'rb')
        bytes_in = file_in.read()
    except IOError as err:
        # "No such file or directory: <file>"
        print(err)
        print("Cannot open", file_path)
        sys.exit(1)
    file_in.close()
    return bytes_in

# -----------------------------------------------------------------------------

def initialize_library():
    """Set the file path and load the shared object (DLL).
       Return the handle to the shared object (DLL).
    """
    # change directory to the path where this script is located
    pydir = sys.path[0]
    os.chdir(pydir)
    # return the handle to the shared object
    if os.name == "nt":
        libc = load_windows_dll()
    else:
        libc = load_linux_so()
    return libc

# -----------------------------------------------------------------------------

def initialize_platform():
    """Check the python_implementation and the python_version.
       Update the global variables __is_iron_python__ and __is_unicode__.
    """
    global __is_iron_python__, __is_unicode__
    if platform.python_implementation() == "CPython":
        if platform.python_version_tuple()[0] >= '3':
            __is_unicode__ = True
    elif platform.python_implementation() == "IronPython":
        __is_iron_python__ = True
        __is_unicode__ = True

# -----------------------------------------------------------------------------

def load_linux_so():
    """Load the shared object for Linux platforms.
       The shared object must be in the same folder as this python script.
    """
    shared = os.path.join(sys.path[0], "libastyle.so")
    # os.name does not always work for mac
    if sys.platform == "darwin":
        shared = shared.replace("libastyle.so", "libastyle.dylib")
    try:
        libc = cdll.LoadLibrary(shared)
    except OSError as err:
        # "cannot open shared object file: No such file or directory"
        print(err)
        print("Cannot find", shared)
        sys.exit(1)
    return libc

# -----------------------------------------------------------------------------

def load_windows_dll():
    """Load the dll for Windows platforms.
       The shared object must be in the same folder as this python script.
       An exception is handled if the dll bits do not match the Python
       executable bits (32 vs 64).
    """
    dll = "AStyle.dll"
    try:
        libc = windll.LoadLibrary(dll)
    # exception for CPython
    except WindowsError as err:
        # print(err)
        print("Cannot load library", dll)
        if err.winerror == 126:     #  "The specified module could not be found"
            print("Cannot find", dll)
        elif err.winerror == 193:   #  "%1 is not a valid Win32 application"
            print("You may be mixing 32 and 64 bit code")
        else:
            print(err.strerror)
        sys.exit(1)
    # exception for IronPython
    except OSError as err:
        print("Cannot load library", dll)
        print("If the library is available you may be mixing 32 and 64 bit code")
        sys.exit(1)
    # exception for IronPython
    # this sometimes occurs with IronPython during debug
    # rerunning will probably fix
    except TypeError as err:
        print("TypeError - rerunning will probably fix")
        sys.exit(1)
    return libc

# -----------------------------------------------------------------------------

def save_source_code_bytes(bytes_out, file_path):
    """Save the source code as bytes.
       The variable bytes_in is expected to be a byte string.
       Opening the file as binary will save it as a byte string.
    """
    # remove old .orig, if any
    backup_path = file_path + ".orig"
    if os.path.isfile(backup_path):
        os.remove(backup_path)
    # rename original to backup
    os.rename(file_path, backup_path)
    # save the file as a byte string by opening it as binary
    # version 3 will attempt to write unicode if not declared as binary
    file_out = open(file_path, 'wb')
    file_out.write(bytes_out)
    file_out.close()

# -----------------------------------------------------------------------------

# // astyle ASTYLE_LIB declarations
# typedef void (STDCALL *fpError)(int, char*);       // pointer to callback error handler
# typedef char* (STDCALL *fpAlloc)(unsigned long);   // pointer to callback memory allocation
# extern "C" EXPORT char* STDCALL AStyleMain(const char*, const char*, fpError, fpAlloc);
# extern "C" EXPORT const char* STDCALL AStyleGetVersion (void);

# -----------------------------------------------------------------------------

# AStyle Error Handler Callback
def error_handler(num, err):
    """AStyle callback error handler.
       The return error string (err) is always byte type.
       It is converted to unicode for Python 3.
    """
    print("Error in input {0}".format(num))
    if __is_unicode__:
        err = err.decode()
    print(err)
    sys.exit(1)

# -----------------------------------------------------------------------------

# global to create the error handler callback function
if os.name == "nt":
    ERROR_HANDLER_CALLBACK = WINFUNCTYPE(None, c_int, c_char_p)
else:
    ERROR_HANDLER_CALLBACK = CFUNCTYPE(None, c_int, c_char_p)
ERROR_HANDLER = ERROR_HANDLER_CALLBACK(error_handler)

# global allocation variable --------------------------------------------------

# global memory allocation returned to artistic style
# must be global for CPython
# IronPython doesn't need global, but it doesn't hurt
__allocated__ = c_char_p

# -----------------------------------------------------------------------------

# AStyle Memory Allocation Callback
def memory_allocation(size):
    """AStyle callback memory allocation.
       The size to allocate is always byte type.
       The allocated memory MUST BE FREED by the calling function.
    """
    # ctypes are different for CPython and IronPython
    global __allocated__
    # ctypes for IronPython do NOT seem to be mutable
    # using ctype variables in IronPython results in a
    # "System.AccessViolationException: Attempted to read or write protected memory"
    # IronPython must use create_string_buffer()
    if __is_iron_python__:
        __allocated__ = create_string_buffer(size)
        return __allocated__
    # ctypes for CPython ARE mutable and can be used for input
    # using create_string_buffer() in CPython results in a
    # "TypeError: string or integer address expected instead of c_char_Array"
    # CPython must use c_char_Array object
    else:
        arr_type = c_char * size      # create a c_char array
        __allocated__ = arr_type()      # create an array object
        return addressof(__allocated__)

# -----------------------------------------------------------------------------

# global to create the memory allocation callback function
if os.name == "nt":
    MEMORY_ALLOCATION_CALLBACK = WINFUNCTYPE(c_char_p, c_ulong)
else:
    MEMORY_ALLOCATION_CALLBACK = CFUNCTYPE(c_char_p, c_ulong)
MEMORY_ALLOCATION = MEMORY_ALLOCATION_CALLBACK(memory_allocation)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    main()
    sys.exit(0)
