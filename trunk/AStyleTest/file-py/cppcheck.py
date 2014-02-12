#! /usr/bin/python
""" Generate the suppression file and run cppcheck.
    Input the AStyle source files and output the suppression file
    with the current line numbers.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import codecs
import libastyle		# local directory
import os
import platform
import subprocess

# global variables ------------------------------------------------------------

__expected_version = "1.60"
__src_dir = libastyle.get_astyle_directory() + "/src/"
__py_dir = libastyle.get_astyletest_directory() + "/file-py/"
__suppression_path = __py_dir + "cppcheck-suppress"

# -----------------------------------------------------------------------------

def main():
	"""Main processing function.
	"""
	generate_suppression_file()
	run_cppcheck()

# -----------------------------------------------------------------------------

def generate_suppression_file():
	""" Generate the suppression file.
	"""
	outfile = open(__suppression_path, 'w')

	# File Suppressions
	file_suppression_list = ["\n// File Suppressions\n"]
	process_file_suppressions(file_suppression_list)
	outfile.writelines(file_suppression_list)

	# ASBeautifier
	beautifier_list = ["\n// ASBeautifier.cpp\n"]
	process_beautifier(beautifier_list)
	outfile.writelines(beautifier_list)

	# ASEnhancer
	enhancer_list = ["\n// ASEnhancer.cpp\n"]
	process_enhancer(enhancer_list)
	outfile.writelines(enhancer_list)

	# ASFormatter
	formatter_list = ["\n// ASFormatter.cpp\n"]
	process_formatter(formatter_list)
	outfile.writelines(formatter_list)

	# ASLocalizer
	localizer_list = ["\n// ASLocalizer.cpp\n"]
	process_localizer(localizer_list)
	outfile.writelines(localizer_list)

	# ASResource
	resource_list = ["\n// ASResource.cpp\n"]
	process_resource(resource_list)
	outfile.writelines(resource_list)

	# astyle_main
	astyle_main_list = ["\n// astyle_main.cpp\n"]
	process_astyle_main(astyle_main_list)
	outfile.writelines(astyle_main_list)

	# astyle_main header
	astyle_main_header_list = ["\n// astyle_main.h\n"]
	process_astyle_main_header(astyle_main_header_list)
	outfile.writelines(astyle_main_header_list)

	outfile.close()

# -----------------------------------------------------------------------------

def process_astyle_main(astyle_main_list):
	""" Generate suppressions for astyle_main.
	"""
	lines = 0				# current input line number
	src_path = __src_dir + "astyle_main.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		# unusedFunction warnings
		if "ASConsole::getFilesFormatted" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getFilesFormatted\n")
		if "ASConsole::getIgnoreExcludeErrors" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIgnoreExcludeErrors\n")
		if "ASConsole::getIgnoreExcludeErrorsDisplay" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIgnoreExcludeErrorsDisplay\n")
		if "ASConsole::getIsFormattedOnly" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsFormattedOnly\n")
		if "ASConsole::getIsQuiet" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsQuiet\n")
		if "ASConsole::getIsRecursive" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsRecursive\n")
		if "ASConsole::getIsVerbose" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsVerbose\n")
		if "ASConsole::getLineEndsMixed" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getLineEndsMixed\n")
		if "ASConsole::getNoBackup" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getNoBackup\n")
		if "ASConsole::getPreserveDate" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getPreserveDate\n")
		if "ASConsole::setBypassBrowserOpen" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// setBypassBrowserOpen\n")
		if "Java_AStyleInterface_AStyleGetVersion" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// Java_AStyleInterface_AStyleGetVersion\n")
		if "Java_AStyleInterface_AStyleMain" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// Java_AStyleInterface_AStyleMain\n")
		if "AStyleMainUtf16" in line and "STDCALL" in line:
			astyle_main_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// AStyleMainUtf16\n")

# -----------------------------------------------------------------------------

def process_astyle_main_header(astyle_main_header_list):
	""" Generate suppressions for astyle_main header.
	"""
	lines = 0				# current input line number
	src_path = __src_dir + "astyle_main.h"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if line.startswith('origSuffix = ".orig"'):
			astyle_main_header_list.append("useInitializationList:" + src_path + ":" +  str(lines) + "\t\t// origSuffix\n")

# -----------------------------------------------------------------------------

def process_beautifier(beautifier_list):
	""" Generate suppressions for ASBeautifier.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want certain 'char ch'
	src_path = __src_dir + "ASBeautifier.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if line.startswith("headers = other.headers"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// headers\n")
		if line.startswith("nonParenHeaders = other.nonParenHeaders"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// nonParenHeaders\n")
		if line.startswith("assignmentOperators = other.assignmentOperators"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// assignmentOperators\n")
		if line.startswith("nonAssignmentOperators = other.nonAssignmentOperators"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// nonAssignmentOperators\n")
		if line.startswith("preBlockStatements = other.preBlockStatements"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// preBlockStatements\n")
		if line.startswith("preCommandHeaders = other.preCommandHeaders"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// preCommandHeaders\n")
		if line.startswith("indentableHeaders = other.indentableHeaders"):
			beautifier_list.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// indentableHeaders\n")
		if line.startswith("char ch"):
			charsProcessed += 1
			if charsProcessed == 1 or charsProcessed == 3 :
				beautifier_list.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t// char ch\n")
		if line.startswith("char tempCh"):
			beautifier_list.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t// char tempCh\n")
		# unusedFunction warnings
		if "ASBeautifier::getBeautifierFileType" in line:
			beautifier_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getBeautifierFileType\n")
	file_in.close()

# -----------------------------------------------------------------------------

def process_enhancer(enhancer_list):
	""" Generate suppressions for ASEnhancer.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the second'char ch'
	src_path = __src_dir + "ASEnhancer.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if line.startswith("char ch"):
			charsProcessed += 1
			if charsProcessed == 1:
				enhancer_list.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t\t// char ch\n")

# -----------------------------------------------------------------------------

def process_file_suppressions(file_suppression_list):
	""" Generate suppressions for an entire file.
	"""
	file_suppression_list.append("// duplInheritedMember\n")
	file_suppression_list.append("// These are duplicate variable names in the header classes.\n")
	file_suppression_list.append("// The way the classes are used they are not a problem.\n")
	file_suppression_list.append("duplInheritedMember:" + __src_dir + "astyle.h\n")
	file_suppression_list.append("// uninitMemberVar\n")
	file_suppression_list.append("// These are actually initialized in the astyle 'init' functions.\n")
	file_suppression_list.append("// They are verified by other Python scripts.\n")
	file_suppression_list.append("uninitMemberVar:" + __src_dir + "ASBeautifier.cpp\n")
	file_suppression_list.append("uninitMemberVar:" + __src_dir + "ASEnhancer.cpp\n")
	file_suppression_list.append("uninitMemberVar:" + __src_dir + "ASFormatter.cpp\n")

# -----------------------------------------------------------------------------

def process_formatter(formatter_list):
	""" Generate suppressions for ASFormatter.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the second'char ch'
	src_path = __src_dir + "ASFormatter.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if line.startswith("char ch"):
			charsProcessed += 1
			if charsProcessed == 2:
				formatter_list.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t\t// char ch\n")
		if line.startswith("int spacesOutsideToDelete"):
			formatter_list.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t\t// spacesOutsideToDelete\n")
		# assertWithSideEffect
		if (line.startswith("assert") 
		and "adjustChecksumIn" in line):			# 2 lines
			formatter_list.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
		#~ if (line.startswith("assert") 
		#~ and "computeChecksumOut" in line:	
			#~ formatter_list.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
		#~ if (line.startswith("assert") 
		#~ and "computeChecksumIn" in line:		# 2 lines	
			#~ formatter_list.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
		# unusedFunction warnings
		if "ASFormatter::getChecksumIn" in line:
			formatter_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getChecksumIn\n")
		if "ASFormatter::getChecksumOut" in line:
			formatter_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getChecksumOut\n")
		if "ASFormatter::getFormatterFileType" in line:
			formatter_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getFormatterFileType\n")

# -----------------------------------------------------------------------------

def process_localizer(localizer_list):
	""" Generate suppressions for ASLocalizer.
	"""
	lines = 0				# current input line number
	langIDProcessed = 0		# only want certain 'm_langID'
	src_path = __src_dir + "ASLocalizer.cpp"
	file_in = codecs.open(src_path, "rb", "utf-8")
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if line.startswith('m_localeName = "UNKNOWN"'):
			localizer_list.append("useInitializationList:" + src_path + ":" +  str(lines) + "\t\t// m_localeName\n")
		if line.startswith('m_langID = "en"'):
			langIDProcessed += 1
			if langIDProcessed == 1 :
				localizer_list.append("useInitializationList:" + src_path + ":" +  str(lines) + "\t\t// m_langID\n")
		# unusedFunction warnings
		if "ASLocalizer::getTranslationClass" in line:
			localizer_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getTranslationClass\n")
		if "Translation::getTranslationVectorSize" in line:
			localizer_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getTranslationVectorSize\n")
		if "Translation::getWideTranslation" in line:
			localizer_list.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getWideTranslation\n")

# -----------------------------------------------------------------------------

def process_resource(resource_list):
	""" Generate suppressions for ASResource.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the first 'char ch'
	src_path = __src_dir + "ASResource.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		#~ if (line.startswith("assert") 
		#~ and "isCharPotentialHeader" in line:		# 2 lines
			#~ resource_list.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
			
# -----------------------------------------------------------------------------

def run_cppcheck():
	"""Run the cppcheck program.
	   NOTE: The window stays open only if run from the console.
	   --enable=all       Enable all checks
	   -f, --force        Force checking if "too many" #ifdefs.
	   -h, --help         Print the help information.
	   -j <jobs>          Start [jobs] threads.
	   -q, --quiet        Only print error messages.
	   --report-progress  Report progress while checking a file.
	   --suppress=<spec>  Suppress a specific warning.
	   --suppressions-list=<file> Suppress warnings listed in the file.
	   -v, --verbose      More detailed error reports.
	   --version          Print the version number.
	   --xml              Write results in xml to error stream.
	"""
	if os.name == "nt":
		exepath = "C:/Program Files (x86)/Cppcheck/cppcheck.exe"
	else:
		exepath = "cppcheck"
	if not os.path.exists(exepath):
		libastyle.system_exit("Cannot find executable: " + exepath)
	verify_cppcheck_version(exepath)
	cppcheck = [exepath]
	cppcheck.append("--enable=all")
	cppcheck.append("--force")
	cppcheck.append("--verbose")
	cppcheck.append("--xml")
	cppcheck.append("--suppressions-list=" +  __suppression_path)
	cppcheck.append(__src_dir)
	# shell=True keeps the console window open, but will not display if run from an editor
	# subprocess.check_output() doesn't work from an editor
	try:
		if libastyle.is_executed_from_console():
			subprocess.check_call(cppcheck, shell=True)
		else:
			subprocess.check_call(cppcheck)
	except subprocess.CalledProcessError as err:
		libastyle.system_exit("Bad cppcheck return: " + str(err.returncode))
	except OSError:
		libastyle.system_exit("Cannot find executable: " + cppcheck[0])

# -----------------------------------------------------------------------------

def verify_cppcheck_version(exepath):
	"""Verify the Cppcheck version number to the expected version.
	   A lower version number may result in unexpected warnings.
	   The expected version number is global.
	"""
	# check_output always returns byte code
	version = subprocess.check_output([exepath, "--version"])
	version = version.lstrip(b"Cppcheck ")
	version = version.rstrip(b"\r\n")
	if platform.python_version_tuple()[0] >= '3':
		version = version.decode()
	if version < __expected_version:
		print("Cppcheck version", version, 
		        "is less than expected version", __expected_version, "\n")
	
# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	main()
	libastyle.system_exit()

# -----------------------------------------------------------------------------

