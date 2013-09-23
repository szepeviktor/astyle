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
__is_iron_python = False
__is_unciode = False

# -----------------------------------------------------------------------------

def process_files():
    """Main processing function.
    """
    files = [ "AStyleDev/test-data/ASBeautifier.cpp",
              "AStyleDev/test-data/ASFormatter.cpp",
              "AStyleDev/test-data/astyle.h" ]
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
        formatted_text = format_source_code(libc, text_in, options)
        if type(formatted_text) == type(None):
            print("Error in formatting", file_path)
            continue
        print("Formatted", file_path)
        save_source_code(formatted_text, file_path)

# -----------------------------------------------------------------------------

def format_source_code(libc, text_in, options):
    """Format the text_in by calling the AStyle shared object (DLL).
       The return value is a byte or Unicode string.
       If an error occurs, the return value is a NoneType object.
       For Python 3:
           The text is encoded to utf-8 before calling AStyle.
           The text is decoded from utf-8 after being returned.
           Using utf-8 will not cause an exception.
    """
    # version 3 must be encoded to utf-8 bytes
    # encoding to utf-8 will not cause an exception
    # IronPython must also be converted to bytes
    if __is_iron_python:
        text_in = bytes(text_in.encode('utf-8'))
        options = bytes(options.encode('utf-8'))
    elif __is_unciode:
        text_in = text_in.encode('utf-8')
        options = options.encode('utf-8')
    astyle_main = libc.AStyleMain
    astyle_main.restype = c_char_p
    formatted_text = astyle_main(text_in,
                                 options,
                                 ERROR_HANDLER,
                                 MEMORY_ALLOCATION)
    # if an error occurs, the return is a type(None) object
    # Python3 must be decoded to Unicode
    # decoding from utf-8 will not cause an exception
    if (__is_unciode
    and type(formatted_text) != type(None)):
        formatted_text = formatted_text.decode('utf-8')
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
    if __is_unciode:
        version = version.decode('utf-8')
    return version

# -----------------------------------------------------------------------------

def get_project_directory(file_path):
    """Prepend the project directory to the subpath.
       This may need to be changed for your directory structure.
    """
    if os.name == "nt":
        homedir =  os.getenv("USERPROFILE")
    else:
        homedir = os.getenv("HOME")
    if homedir == None:
        print(err)
        print("Cannot find HOME directory")
        os._exit(1)
    project_path = homedir + "/Projects/" + file_path
    return project_path

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
        libc = load_windows_dll(pydir)
    else:
        libc = load_linux_so(pydir)
    return libc

# -----------------------------------------------------------------------------

def initialize_platform():
    """Check the python_implementation and the python_version
       and change the global variables __is_iron_python and __is_unciode
       if necessary.
       PyPy does not currently support Unicode.
       Jython will get errors and not run.
    """
    global __is_iron_python, __is_unciode
    if platform.python_implementation() == "CPython":
        if platform.python_version_tuple()[0] >= '3':
            __is_unciode = True
    elif platform.python_implementation() == "IronPython":
        __is_iron_python = True
        __is_unciode = True
        # NOTE: IronPython is NOT currently supported.
        # A bug in IronPython ctypes memory allocation needs to be fixed.
        print("IronPython is not currently supported")
        os._exit(1)

# -----------------------------------------------------------------------------

def load_linux_so():
    """Load the shared object for Linux platforms.
       The shared object must be in the same folder as this python script.
    """
    shared = os.path.join(sys.path[0], "libastyle.so")
    try:
        libc = cdll.LoadLibrary(shared)
    except OSError as err:
        # "cannot open shared object file: No such file or directory"
        print(err)
        print("Cannot find ", shared)
        os._exit(1)
    return libc

# -----------------------------------------------------------------------------

def load_windows_dll(pydir):
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
            print("Cannot find {0} in {1}".format(dll, pydir))
        elif err.winerror == 193:   #  "%1 is not a valid Win32 application"
            print("You may be mixing 32 and 64 bit code")
        else:
            print(err.strerror)
        os._exit(1)
    # exception for IronPython - cannot determine the cause
    except OSError as err:
        print("Cannot load library", dll)
        print("If the library is available you may be mixing 32 and 64 bit code")
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
def ErrorHandler(num, err):
    """AStyle callback error handler.
       The return error string (err) is always byte type.
       It is converted to unicode for Python 3.
    """
    print("Error in input {0}".format(num))
    if __is_unciode:
        err = err.decode()
    print(err)
    os._exit(1)

# global to create the error handler callback function
if os.name == "nt":
    ErrorHandlerCallback = WINFUNCTYPE(None, c_int, c_char_p)
else:
    ErrorHandlerCallback = CFUNCTYPE(None, c_int, c_char_p)
ERROR_HANDLER = ErrorHandlerCallback(ErrorHandler)

# -----------------------------------------------------------------------------

# AStyle Memory Allocation Callback
# allocated memory must be global
__allocated = []
def MemoryAllocation(size):
    """AStyle callback memory allocation.
       The size to allocate is always byte type.
       The allocated memory must be global.
       The previous allocated memory will be freed.
    """
    arr_type = c_char * size      # create a c_char array
    arr_obj = arr_type()          # create an array object
    __allocated.append(arr_obj)   # so the object will not be destroyed
    if len(__allocated) > 1:      # free memory for the previous object
        del __allocated[0]
    return addressof(arr_obj)     # return a pointer

# global to create the memory allocation callback function
if os.name == "nt":
    MemoryAllocationCallback = WINFUNCTYPE(c_char_p, c_ulong)
else:
    MemoryAllocationCallback = CFUNCTYPE(c_char_p, c_ulong)
MEMORY_ALLOCATION = MemoryAllocationCallback(MemoryAllocation)

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
    process_files()
    os._exit(0)
