#! /usr/bin/python
""" Check ASBeautifier constructor and copy constructor to class variables
    in the header file to verify all variables are initialized and copied.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle		#local directory

# global variables ------------------------------------------------------------

__print_detail = False				# print line numbers and total variables
__print_variables = False			# print the variables in the lists

# -----------------------------------------------------------------------------

def main():
	"""Main processing function."""

	header_variables = []		# variables in astyle.h
	class_variables = []		# variables in the class constructor
	copy_variables = []			# variables in the copy constructor
	header_path = libastyle.get_astyle_directory() + "/src/astyle.h"
	beautifier_path = libastyle.get_astyle_directory() + "/src/ASBeautifier.cpp"

	libastyle.set_text_color()
	print(libastyle.get_python_version())
	get_header_variables(header_variables, header_path)
	get_constructor_variables(class_variables, beautifier_path)
	get_initializer_variables(class_variables, beautifier_path)
	get_copy_variables(copy_variables, beautifier_path)
	header_variables.sort()

	print("Checking ASBeautifier header to class constructor and copy constructor.")
	total_variables = len(header_variables)
	print("There are {0} variables in the header list.".format(total_variables))
	print()

	find_class_diffs(header_variables, class_variables)
	find_copy_diffs(header_variables, copy_variables)

	if __print_variables:
		print(header_variables)
		print(class_variables)
		print(copy_variables)

# -----------------------------------------------------------------------------

def convert_class_functions(line):
	"""Convert class initializer functions to the corresponding variable."""
	first_paren = line.find('(')
	if first_paren == -1:
		return line
	if "initContainer" in line:
		line = line[first_paren + 1:]
		first_comma = line.find(',')
		if first_comma != -1:
			line = line[:first_comma]
		line = line.strip()
	elif "->" in line:
		line = ''
	elif "initVectors" in line:
		line = ''
	elif "ASBase::init" in line:
		line = ''
	elif "initStatic" in line:
		line = ''
	elif "setSpaceIndentation" in line:
		line = "indentLength"
	elif "setMinConditionalIndentOption" in line:
		line = "minConditionalOption"
	elif "setMaxInStatementIndentLength" in line:
		line = "maxInStatementIndent"
	elif "setClassIndent" in line:
		line = "classIndent"
	elif "setModifierIndent" in line:
		line = "modifierIndent"
	elif "setSwitchIndent" in line:
		line = "switchIndent"
	elif "setCaseIndent" in line:
		line = "caseIndent"
	elif "setBlockIndent" in line:
		line = "blockIndent"
	elif "setBracketIndent" in line:
		line = "bracketIndent"
	elif "setNamespaceIndent" in line:
		line = "namespaceIndent"
	elif "setLabelIndent" in line:
		line = "labelIndent"
	elif "setEmptyLineFill" in line:
		line = "emptyLineFill"
	elif "setCStyle" in line:
		line = "fileType"
	elif "setPreprocessorIndent" in line:	# depreciated version 2.04
		line = "preprocessorIndent"
	elif "setPreprocDefineIndent" in line:
		line = "shouldIndentPreprocDefine"
	elif "setPreprocConditionalIndent" in line:
		line = "shouldIndentPreprocConditional"
	elif "setAlignMethodColon" in line:
		line = "shouldAlignMethodColon"
	else:
		line = "unidentified function: " + line
	return line

# -----------------------------------------------------------------------------

def find_class_diffs(header_variables, class_variables):
	"""Find differences in header and class variables lists."""
	# A set is an unordered collection with no duplicate elements
	# converting to a 'set' will remove duplicates
	missing_header =  set(class_variables) - set(header_variables)
	missing_class = set(header_variables) - set(class_variables)

	if len(missing_header) > 0:
		missing_header = list(missing_header)
		missing_header.sort()
		print(str(len(missing_header)) + " missing header variables:")
		print(missing_header)

	if len(missing_class) > 0:
		missing_class = list(missing_class)
		missing_class.sort()
		print(str(len(missing_class)) + " missing class variables:")
		print(missing_class)

	diffs = len(missing_header) + len(missing_class)
	if diffs == 0:
		print("There are NO diffs in the class constructor variables!!!")
	else:
		print("There are {0} diffs in the class constructor variables.".format(diffs))

# -----------------------------------------------------------------------------

def find_copy_diffs(header_variables, copy_variables):
	"""Find differences in header and copy variables lists."""
	# A set is an unordered collection with no duplicate elements
	# converting to a 'set' will remove duplicates
	missing_header =  set(copy_variables) - set(header_variables)
	missing_copy = set(header_variables) - set(copy_variables)

	if len(missing_header) > 0:
		missing_header = list(missing_header)
		missing_header.sort()
		print(str(len(missing_header)) + " missing header variables:")
		print(missing_header)

	if len(missing_copy) > 0:
		missing_copy = list(missing_copy)
		missing_copy.sort()
		print(str(len(missing_copy)) + " missing copy constructor variables:")
		print(missing_copy)

	diffs = len(missing_header) + len(missing_copy)
	if diffs == 0:
		print("There are NO diffs in the copy constructor variables!!!")
	else:
		print("There are {0} diffs in the copy constructor variables.".format(diffs))

# -----------------------------------------------------------------------------

def get_constructor_variables(class_variables, beautifier_path):
	"""Read the ASBeautifier file and save the class constuctor variables."""

	class_lines = [0, 0]	# line numbers for class constructor
	class_total = 0			# total variables for class constructor
	lines = 0					# current input line number
	file_in = open(beautifier_path, 'r')

	# get class constructor lines
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		# start between the following lines
		if "ASBeautifier::ASBeautifier" in line:
			class_lines[0] = lines + 1
			continue
		if (class_lines[0]  == 0
		or class_lines[0]  >= lines):
			continue
		# find ending bracket
		if '}' in line:
			class_lines[1] = lines
			break
		# get the variable name
		variable_name = line
		if '(' in line:
			variable_name = convert_class_functions(line)
		else:
			first_space = line.find(' ')
			if first_space != -1:
				variable_name = line[0:first_space].strip()
		if len(variable_name) == 0:
			continue
		# omit global variable initialization to avoid a difference
		if "g_preprocessorCppExternCBracket" in line:
			continue
		class_variables.append(variable_name)
		class_total += 1
		# setSpaceIndentation() sets indentLength and ndentString
		# minConditionalIndent is set in ASFormatter by fixOptionVariableConflicts()
		# verbatimDelimiter is a string that is not initialized in the constructor
		if variable_name == "indentLength":
			class_variables.append("indentString")
			class_variables.append("minConditionalIndent")
			class_variables.append("verbatimDelimiter")
			class_total += 3
	file_in.close()
	if __print_detail:
		print("{0} {1} class constructor".format(class_lines, class_total))

# -----------------------------------------------------------------------------

def get_copy_variables(copy_variables, beautifier_path):
	"""Read the ASBeautifier file and save the copy constuctor variables."""

	copy_lines = [0, 0]		# line numbers for copy constructor
	copy_total = 0				# total variables for copy constructor
	copy_brackets  = 0		#  unmatched brackets in the copy constructor
	lines = 0						# current input line number
	file_in = open(beautifier_path, 'r')

	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue

		# start between the following lines
		if "ASBeautifier(const ASBeautifier" in line:
			copy_lines[0] = lines + 1
			copy_brackets += 1
			continue
		if (copy_lines[0]  == 0
		or copy_lines[0]  >= lines):
			continue
		# count brackets
		if '{' in line:
			copy_brackets += 1
		if '}' in line:
			copy_brackets -= 1
		if  copy_brackets == 0:
			copy_lines[1] = lines
			break
		# get the variable name
		first_space = line.find(' ')
		if first_space == -1:
			continue
		variable_name = line[:first_space].strip()
		# value-of variables are duplicates
		if variable_name[0] == '*':
			continue
		copy_variables.append(variable_name)
		copy_total += 1

	file_in.close()
	if __print_detail:
		print("{0} {1} copy constructor".format(copy_lines, copy_total))

# -----------------------------------------------------------------------------

def get_header_variables(header_variables, header_path):
	"""Read the header file and save the ASBeautifier variables."""

	header_lines = [0, 0]	# line numbers for header
	header_total = 0			# total variables for header
	lines = 0					# current input line number
	file_in = open(header_path, 'r')

	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue

		# start between the following lines
		if "class ASBeautifier" in line:
			header_lines[0] = lines + 1
			continue
		if (header_lines[0]  == 0
		or header_lines[0]  >= lines):
			continue
		# find ending bracket
		if '}' in line:
			header_lines[1] = lines
			break
		if (line.startswith("public:")
		or line.startswith("private:")
		or line.startswith("protected:")):
			continue
		# bypass functions
		if ('(' in line
		or ')' in line):
			continue
		# get the variable name
		semi_colon = line.find(';')
		if semi_colon == -1:
			continue
		last_space = line[:semi_colon].rfind(' ')
		if last_space == -1:
			continue
		variable_name = line[last_space:semi_colon].strip()
		if variable_name[0] == '*':
			variable_name = variable_name[1:]
		header_variables.append(variable_name)
		header_total += 1

	file_in.close()
	if __print_detail:
		print("{0} {1} header".format(header_lines, header_total))

# -----------------------------------------------------------------------------

def get_initializer_variables(class_variables, beautifier_path):
	"""Read the ASBeautifier file and save the class initializer variables."""

	class_lines_init = [0, 0]		# line numbers for class init() function
	class_total_init = 0			# total variables for class init() function
	lines_init = 0					# current input line number
	file_in_init = open(beautifier_path, 'r')

	# get class initializer lines
	for line_in in file_in_init:
		lines_init += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line.startswith("//"):
			continue
		# start between the following lines
		if "void ASBeautifier::init(ASSourceIterator* iter)" in line:
			class_lines_init[0] = lines_init + 1
			continue
		if (class_lines_init[0]  == 0
		or class_lines_init[0]  >= lines_init):
			continue
		# find ending bracket
		if '}' in line:
			class_lines_init[1] = lines_init
			break
		# get the variable name
		variable_name = line
		if '(' in line:
			variable_name = convert_class_functions(line)
		else:
			first_space = line.find(' ')
			if first_space != -1:
				variable_name = line[:first_space].strip()
		if len(variable_name) == 0:
			continue
		class_variables.append(variable_name)
		class_total_init += 1

	file_in_init.close()
	if __print_detail:
		print("{0} {1} class initializer".format(class_lines_init, class_total_init))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	main()
	libastyle.system_exit()

# -----------------------------------------------------------------------------
