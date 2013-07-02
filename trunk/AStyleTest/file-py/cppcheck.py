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

# -----------------------------------------------------------------------------

def process_files():
	"""Main processing function.
	"""
	suppressionFileName = "cppcheck-suppress"
	generate_suppression_file(suppressionFileName)
	run_cppcheck(suppressionFileName)

# -----------------------------------------------------------------------------

def generate_suppression_file(suppressionFileName):
	""" Generate the suppression file.
	"""
	outfile = open(suppressionFileName, 'w')

	# uninitMemberVar
	uninitMemberVarList = ["\n// uninitMemberVar\n"]
	process_uninitMemberVar(uninitMemberVarList)
	outfile.writelines(uninitMemberVarList)

	# ASBeautifier
	beautifierList = ["\n// ASBeautifier.cpp\n"]
	process_beautifier(beautifierList)
	outfile.writelines(beautifierList)

	# ASEnhancer
	enhancerList = ["\n// ASEnhancer.cpp\n"]
	process_enhancer(enhancerList)
	outfile.writelines(enhancerList)

	# ASFormatter
	formatterList = ["\n// ASFormatter.cpp\n"]
	process_formatter(formatterList)
	outfile.writelines(formatterList)

	# ASLocalizer
	localizerList = ["\n// ASLocalizer.cpp\n"]
	process_localizer(localizerList)
	outfile.writelines(localizerList)

	# ASResource
	resourceList = ["\n// ASResource.cpp\n"]
	process_resource(resourceList)
	outfile.writelines(resourceList)

	# astyle_main
	astyleMainList = ["\n// astyle_main.cpp\n"]
	process_astyle_main(astyleMainList)
	outfile.writelines(astyleMainList)

	# astyle_main header
	astyleMainHeaderList = ["\n// astyle_main.h\n"]
	process_astyle_main_header(astyleMainHeaderList)
	outfile.writelines(astyleMainHeaderList)

	outfile.close()

# -----------------------------------------------------------------------------

def process_astyle_main(astyleMainList):
	""" Generate suppressions for astyle_main.
	"""
	lines = 0				# current input line number
	eStatesProcessed = 0		# only want the fifth'eState'
	src_path = "../../AStyle/src/astyle_main.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if line.startswith("eState = eStart"):
			eStatesProcessed += 1
			if eStatesProcessed == 5:
				astyleMainList.append("unreadVariable:" + src_path + ":" + str(lines) + "\t\t\t// eState\n")
		# unusedFunction warnings
		if line.find("ASConsole::getFilesFormatted") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getFilesFormatted\n")
		if line.find("ASConsole::getIgnoreExcludeErrors") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIgnoreExcludeErrors\n")
		if line.find("ASConsole::getIgnoreExcludeErrorsDisplay") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIgnoreExcludeErrorsDisplay\n")
		if line.find("ASConsole::getIsFormattedOnly") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsFormattedOnly\n")
		if line.find("ASConsole::getIsQuiet") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsQuiet\n")
		if line.find("ASConsole::getIsRecursive") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsRecursive\n")
		if line.find("ASConsole::getIsVerbose") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getIsVerbose\n")
		if line.find("ASConsole::getLineEndsMixed") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getLineEndsMixed\n")
		if line.find("ASConsole::getNoBackup") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getNoBackup\n")
		if line.find("ASConsole::getPreserveDate") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getPreserveDate\n")
		if line.find("Java_AStyleInterface_AStyleGetVersion") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// Java_AStyleInterface_AStyleGetVersion\n")
		if line.find("Java_AStyleInterface_AStyleMain") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// Java_AStyleInterface_AStyleMain\n")
		if line.find("AStyleMainUtf16") != -1:
			astyleMainList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// Java_AStyleInterface_AStyleMain\n")

# -----------------------------------------------------------------------------

def process_astyle_main_header(astyleMainHeaderList):
	""" Generate suppressions for astyle_main header.
	"""
	lines = 0				# current input line number
	src_path = "../../AStyle/src/astyle_main.h"
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
			astyleMainHeaderList.append("useInitializationList:" + src_path + ":" +  str(lines) + "\t\t// origSuffix\n")

# -----------------------------------------------------------------------------

def process_beautifier(beautifierList):
	""" Generate suppressions for ASBeautifier.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the first 'char ch'
	src_path = "../../AStyle/src/ASBeautifier.cpp"
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
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// headers\n")
		if line.startswith("nonParenHeaders = other.nonParenHeaders"):
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// nonParenHeaders\n")
		if line.startswith("assignmentOperators = other.assignmentOperators"):
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// assignmentOperators\n")
		if line.startswith("nonAssignmentOperators = other.nonAssignmentOperators"):
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// nonAssignmentOperators\n")
		if line.startswith("preBlockStatements = other.preBlockStatements"):
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// preBlockStatements\n")
		if line.startswith("preCommandHeaders = other.preCommandHeaders"):
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// preCommandHeaders\n")
		if line.startswith("indentableHeaders = other.indentableHeaders"):
			beautifierList.append("copyCtorPointerCopying:" + src_path + ":" +  str(lines) + "\t// indentableHeaders\n")
		if line.startswith("lineStartsInComment = isInComment"):
			beautifierList.append("redundantAssignment:" + src_path + ":" +  str(lines) + "\t\t// lineStartsInComment\n")
		if line.startswith("char ch"):
			charsProcessed += 1
			if charsProcessed == 1:
				beautifierList.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t// char ch\n")
		if line.startswith("char prevCh"):
			beautifierList.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t// char prevCh\n")
		if line.startswith("char tempCh"):
			beautifierList.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t// char tempCh\n")
		# unusedFunction warnings
		if line.find("ASBeautifier::getBeautifierFileType") != -1:
			beautifierList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getBeautifierFileType\n")
	file_in.close()

# -----------------------------------------------------------------------------

def process_enhancer(enhancerList):
	""" Generate suppressions for ASEnhancer.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the second'char ch'
	src_path = "../../AStyle/src/ASEnhancer.cpp"
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
				enhancerList.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t\t// char ch\n")

# -----------------------------------------------------------------------------

def process_formatter(formatterList):
	""" Generate suppressions for ASFormatter.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the second'char ch'
	src_path = "../../AStyle/src/ASFormatter.cpp"
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
				formatterList.append("variableScope:" + src_path + ":" +  str(lines) + "\t\t\t\t// char ch\n")
		# assertWithSideEffect
		if (line.startswith("assert") 
		and line.find("adjustChecksumIn")  != -1):			# 2 lines
			formatterList.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
		if (line.startswith("assert") 
		and line.find("computeChecksumOut")  != -1):	
			formatterList.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
		if (line.startswith("assert") 
		and line.find("computeChecksumIn")  != -1):		# 2 lines	
			formatterList.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
		# unusedFunction warnings
		if line.find("ASFormatter::getChecksumIn") != -1:
			formatterList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getChecksumIn\n")
		if line.find("ASFormatter::getChecksumOut") != -1:
			formatterList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getChecksumOut\n")
		if line.find("ASFormatter::getFormatterFileType") != -1:
			formatterList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t// getFormatterFileType\n")

# -----------------------------------------------------------------------------

def process_localizer(localizerList):
	""" Generate suppressions for ASLocalizer.
	"""
	lines = 0				# current input line number
	src_path = "../../AStyle/src/ASLocalizer.cpp"
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
			localizerList.append("useInitializationList:" + src_path + ":" +  str(lines) + "\t\t// m_localeName\n")
		if line.startswith('m_langID = "en"'):
			localizerList.append("useInitializationList:" + src_path + ":" +  str(lines) + "\t\t// m_langID\n")
		# unusedFunction warnings
		if line.find("ASLocalizer::getTranslationClass") != -1:
			localizerList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getTranslationClass\n")
		if line.find("Translation::getTranslationVectorSize") != -1:
			localizerList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getTranslationVectorSize\n")
		if line.find("Translation::getWideTranslation") != -1:
			localizerList.append("unusedFunction:" + src_path + ":" +  str(lines) + "\t\t\t\t// getWideTranslation\n")

# -----------------------------------------------------------------------------

def process_resource(resourceList):
	""" Generate suppressions for ASResource.
	"""
	lines = 0				# current input line number
	charsProcessed = 0		# only want the first 'char ch'
	src_path = "../../AStyle/src/ASResource.cpp"
	file_in = open(src_path, 'r')
	# get exceptions
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		if (line.startswith("assert") 
		and line.find("isCharPotentialHeader")  != -1):		# 2 lines
			resourceList.append("assertWithSideEffect:" + src_path + ":" +  str(lines) + "\t\t// assert\n")
			
# -----------------------------------------------------------------------------

def process_uninitMemberVar(uninitMemberVarList):
	""" Generate suppressions for uninitMemberVar.
	"""
	uninitMemberVarList.append("// These are actually initialized in the astyle 'init' functions.\n")
	uninitMemberVarList.append("// They are verified by other Python scripts.\n")
	uninitMemberVarList.append("uninitMemberVar:../../AStyle/src/ASBeautifier.cpp\n")
	uninitMemberVarList.append("uninitMemberVar:../../AStyle/src/ASEnhancer.cpp\n")
	uninitMemberVarList.append("uninitMemberVar:../../AStyle/src/ASFormatter.cpp\n")

# -----------------------------------------------------------------------------

def run_cppcheck(suppressionFileName):
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
		exepath = "C:/Program Files/Cppcheck/cppcheck.exe"
	else:
		exepath = "cppcheck"
	verify_cppcheck_version(exepath)
	cppcheck = [exepath]
	cppcheck.append("--enable=all")
	cppcheck.append("--force")
	cppcheck.append("--verbose")
	cppcheck.append("--xml")
	cppcheck.append("--suppressions-list=" + suppressionFileName)
	cppcheck.append("..\..\AStyle\src")
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
	process_files()
	libastyle.system_exit()

# -----------------------------------------------------------------------------

