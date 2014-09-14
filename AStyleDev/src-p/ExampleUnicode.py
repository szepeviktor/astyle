#! /usr/bin/python

"""ExampleUnicode.py
   This program calls the Artistic Style DLL to format the AStyle source files.
   The Artistic Style DLL must be in the same directory as this script.
   The Artistic Style DLL must have the same bit size (32 or 64) as the Python executable.
   It will work with either Python version 2 or 3 (unicode).
   For Python 3 the files are converted to Unicode and encoded or decoded as needed.
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
    options = "-A2tOP"

    #initialization
    print("ExampleUnicode",
          platform.python_implementation(),
          platform.python_version(),
          platform.architecture()[0])
    initialize_platform()
    libc = initialize_library()
    version = get_astyle_version(libc)
    print("Artistic Style Version " + version)
    # process the input files
    for file_path in files:
        file_path = get_project_directory(file_path)
        text_in = get_source_code(file_path)
        options_in = options
        # unicode must be encoded to utf-8 bytes
        # encoding to utf-8 will not cause an exception
        # IronPython must be explicitely converted to bytes???
        if __is_iron_python__:
            text_in = bytes(text_in.encode('utf-8'))
            options_in = bytes(options_in.encode('utf-8'))
        elif __is_unicode__:
            text_in = text_in.encode('utf-8')
            options_in = options_in.encode('utf-8')
        formatted_text = format_source_code(libc, text_in, options_in)
        # if an error occurs, the return is a type(None) object
        if type(formatted_text) == type(None):
            print("Error in formatting", file_path)
            os._exit(1)
        # unicode must be decoded from utf-8 bytes
        # decoding from utf-8 will not cause an exception
        if __is_unicode__:
            formatted_text = formatted_text.decode('utf-8')
        save_source_code(formatted_text, file_path)
        # allocated memory is deleted here, not in the allocation function
        del formatted_text
        print("Formatted", file_path)

# -----------------------------------------------------------------------------

def format_source_code(libc, text_in, options):
    """Format the text_in by calling the AStyle shared object (DLL).
       The variable text_in is expected to be a byte string.
       The return value is a byte string.
       If an error occurs, the return value is a NoneType object.
    """
    astyle_main = libc.AStyleMain
    astyle_main.restype = c_char_p
    formatted_text = astyle_main(text_in,
                                 options,
                                 ERROR_HANDLER,
                                 MEMORY_ALLOCATION)
    return formatted_text

# -----------------------------------------------------------------------------

def get_astyle_version(libc):
    """Get the version number from the AStyle shared object (DLL).
       The AStyle return value is always byte type.
       It is converted to unicode for Python 3.
       Since the version is ascii the decoding will not cause an exception.
    """
    astyle_version = libc.AStyleGetVersion
    astyle_version.restype = c_char_p
    version = astyle_version()
    if __is_unicode__:
        version = version.decode('utf-8')
    return version

# -----------------------------------------------------------------------------

def get_project_directory(file_name):
    """Find the directory path and prepend it to the file name.
       The source is expected to be in the "src-p" directory.
       This may need to be changed for your directory structure.
    """
    file_path = sys.path[0]
    end = file_path.find("src-p")
    if end == -1:
        print("Cannot find source directory", file_path)
        os._exit(1)
    file_path = file_path[0:end]
    file_path = file_path + "test-data" + os.sep + file_name
    return file_path

# -----------------------------------------------------------------------------

def get_source_code(file_path):
    """Get the source code (unicode in Version 3).
       Opening the file as non-binary will read it as a unicode string.
       An exception is handled in case the file cannot be decoded using
       the system default codec.
       The return value is a unicode string.
    """
    # version 3 will read unicode since the file is not declared as binary
    # could also read the file as binary and use an explicit decode
    try:
        file_in = open(file_path, 'r')
        text_in = file_in.read()
    except IOError as err:
        # "No such file or directory: <file>"
        print(err)
        print("Cannot open", file_path)
        os._exit(1)
    except UnicodeError as err:
        # "'<codec>' codec can't decode byte 0x81 in position 40813: <message>"
        print(err)
        print("Cannot read", file_path)
        os._exit(1)
    file_in.close()
    return text_in

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
    shared = os.path.join(sys.path[0], "libastyle-2.05.so")
    # os.name does not always work for mac
    if sys.platform == "darwin":
        shared = shared.replace(".so", ".dylib")
    try:
        libc = cdll.LoadLibrary(shared)
    except OSError as err:
        # "cannot open shared object file: No such file or directory"
        print(err)
        print("Cannot find ", shared)
        os._exit(1)
    return libc

# -----------------------------------------------------------------------------

def load_windows_dll():
    """Load the dll for Windows platforms.
       The shared object must be in the same folder as this python script.
       An exception is handled if the dll bits do not match the Python
       executable bits (32 vs 64).
    """
    dll = "AStyle-2.05.dll"
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
        os._exit(1)
    # exception for IronPython
    except OSError as err:
        print("Cannot load library", dll)
        print("If the library is available you may be mixing 32 and 64 bit code")
        os._exit(1)
    # exception for IronPython
    # this sometimes occurs with IronPython during debug
    # rerunning will probably fix
    except TypeError as err:
        print("TypeError - rerunning will probably fix")
        os._exit(1)
    return libc

# -----------------------------------------------------------------------------

def save_source_code(text_out, file_path):
    """Save the source code as bytes.
       The variable text_out is Unicode in Python 3.
       The text_out will be encoded to a byte string using the default codec.
       An exception is handled in case the file cannot be encoded.
    """
    # remove old .orig, if any
    backup_path = file_path + ".orig"
    if os.path.isfile(backup_path):
        os.remove(backup_path)
    # rename original to backup
    os.rename(file_path, backup_path)
    # version 3 will encode the file from unicode using the default codec
    # could also use an explicit decode before wiiting the file
    file_out = open(file_path, 'w')
    try:
        file_out.write(text_out)
    except UnicodeError as err:
        # "'<codec>' codec can't encode characters in position 0-2: <message>"
        print(err)
        print("Cannot write", file_path)
        os._exit(1)
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
    os._exit(1)

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
    os._exit(0)
