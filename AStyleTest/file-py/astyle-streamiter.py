#! /usr/bin/python
""" Check ASStreamIterator constructor to class variables
    in the header file to verify all variables are initialized.
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
	class_variables = []			# variables in the class constructor
	header_path = libastyle.get_astyle_directory() + "/src/astyle_main.h"
	iterator_path = libastyle.get_astyle_directory() + "/src/astyle_main.cpp"

	libastyle.set_text_color()
	print(libastyle.get_python_version())
	get_header_variables(header_variables, header_path)
	get_constructor_variables(class_variables, iterator_path)

	print("Checking ASStreamIterator header to class constructor.")
	total_variables = len(header_variables)
	print("There are {0} variables in the header list.".format(total_variables))
	print()

	find_class_diffs(header_variables, class_variables)

	if __print_variables:
		print(header_variables)
		print(class_variables)

# -----------------------------------------------------------------------------

def convert_class_functions(line):
	"""Convert class initializer functions to the corresponding variable."""
	first_paren = line.find('(')
	if first_paren == -1:
		return line
	if "buffer.reserve" in line:
		line = ''
	elif "setOutputEOL" in line:
		line = "outputEOL[4]"
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
		print(str(len(missing_class)) + " missing class constructor variables:")
		print(missing_class)

	diffs = len(missing_header) + len(missing_class)
	if diffs == 0:
		print("There are NO diffs in the class constructor variables!!!")
	else:
		print("There are {0} diffs in the class constructor variables.".format(diffs))

# -----------------------------------------------------------------------------

def get_constructor_variables(class_variables, iterator_path):
	"""Read the astyle_main file and save the class constuctor variables."""

	class_lines = [0, 0]		# line numbers for class constructor
	class_total = 0			# total variables for class constructor
	lines = 0					# current input line number
	file_in = open(iterator_path, 'r')

	# get class constructor lines
	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line[:2] == "//":
			continue
		# start between the following lines
		if "ASStreamIterator<T>::ASStreamIterator" in line:
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
				variable_name = line[:first_space].strip()
			first_sqbr = variable_name.find('[')
			if first_sqbr != -1:
				variable_name = variable_name[:first_sqbr].strip()
		if len(variable_name) == 0:
			continue
		class_variables.append(variable_name)
		class_total += 1

	file_in.close()
	if __print_detail:
		print("{0} {1} class constructor".format(class_lines, class_total))

# -----------------------------------------------------------------------------

def get_header_variables(header_variables, header_path):
	"""Read the header file and save the ASStreamIterator variables."""

	header_lines = [0, 0]		# line numbers for header
	header_total = 0				# total variables for header
	lines = 0						# current input line number
	file_in = open(header_path, 'r')

	for line_in in file_in:
		lines += 1
		line = line_in.strip()
		if len(line) == 0:
			continue
		if line[:2] == "//":
			continue

		# start between the following lines
		if "class ASStreamIterator" in line:
			header_lines[0] = lines + 1
			continue
		if (header_lines[0]  == 0
		or header_lines[0]  >= lines):
			continue
		# find ending bracket - should find following comment instead
		if '}' in line:
			header_lines[1] = lines
			break
		# find ending comment
		if "// inline functions" in line:
			header_lines[1] = lines
			break
		if ("public:" in line
		or "private:" in line
		or "protected:" in line):
			continue
		# bypass functions
		if ('(' in line
		or ')' in line):
			continue
		# bypass static variables
		if line[:6] == "static":
			continue
		# bypass vectors and strings
		if "buffer" in line:
			continue
		if "prevBuffer" in line:
			continue
		# get the variable name
		semi_colon = line.find(';')
		if semi_colon == -1:
			continue
		first_space = line[:semi_colon].rfind(' ')
		if first_space == -1:
			continue
		variable_name = line[first_space:semi_colon].strip()
		first_sqbr = variable_name.find('[')
		if first_sqbr != -1:
			variable_name = variable_name[:first_sqbr].strip()
		if variable_name[0] == '*':
			variable_name = variable_name[1:]
		header_variables.append(variable_name)
		header_total += 1

	file_in.close()
	if __print_detail:
		print("{0} {1} header".format(header_lines, header_total))

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	main()
	libastyle.system_exit()

# -----------------------------------------------------------------------------
