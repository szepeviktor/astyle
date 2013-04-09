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
__is_iron_python = False
__is_unicode = False

# -----------------------------------------------------------------------------

def process_files():
	"""Main processing function."""
	# options are byte code for AStyle input
	option_bytes = b"-A2tOP"
	files = [ "../test-c/ASBeautifier.cpp",
	          "../test-c/ASFormatter.cpp" ,
	          "../test-c/astyle.h" ]

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
		bytes_in = get_source_code_bytes(file_path)
		formatted_bytes = format_source_bytes(libc, bytes_in, option_bytes)
		if type(formatted_bytes) is type(None):
			print("Error in formatting", file_path)
			continue
		print("Formatted", file_path)
		save_source_code_bytes(formatted_bytes, file_path)

# -----------------------------------------------------------------------------

def format_source_bytes(libc, bytes_in, option_bytes):
	"""Format the bytes_in by calling the AStyle shared object (DLL).
	   The variable bytes_in is expected to be a byte string.
	   The return value is a byte string.
	   If an error occurs, the return value is a NoneType object.
	"""
	astyle_main = libc.AStyleMain
	astyle_main.restype = c_char_p
	formatted_bytes = (
		astyle_main(bytes_in, option_bytes, ERROR_HANDLER, MEMORY_ALLOCATION))
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
		os._exit(1)
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
	"""Check the python_implementation and the python_version
	   and change the global variables is_iron_python and is_unicode
	   if necessary.
	   PyPy does not currently support Unicode.
	   Jython will get errors and not run.
	"""
	global __is_iron_python, __is_unicode
	if platform.python_implementation() == "CPython":
		if platform.python_version_tuple()[0] >= '3':
			__is_unicode = True
	elif platform.python_implementation() == "IronPython":
		__is_iron_python = True
		__is_unicode = True
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
		print("Cannot find", shared)
		os._exit(1)
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
		print(err)
		print("Cannot load library", dll)
		if err.args[0] == 126:      #  "The specified module could not be found"
			print("Cannot find", dll)
		if err.args[0] == 193:      #  "%1 is not a valid Win32 application"
			print("You may be mixing 32 and 64 bit code")
		os._exit(1)
	# exception for IronPython - cannot determine the cause
	except OSError as err:
		print("Cannot load library", dll)
		print("You may be mixing 32 and 64 bit code")
		os._exit(1)
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
# typedef void (STDCALL *fpError)(int, char*);		 // pointer to callback error handler
# typedef char* (STDCALL *fpAlloc)(unsigned long);	 // pointer to callback memory allocation
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
	if sys.version_info[0] >= 3:
		err = err.decode('utf-8')
	print(err)
	os._exit(1)

# create the error handler callback function
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

# create the memory allocation callback function
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
