#! /usr/bin/python
""" Enumerate selected locales and sort by codepage to determine
    which  languages the locales support.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import libastyle		#local directory
import locale
import os
import platform
import sys

# -----------------------------------------------------------------------------

def main():
	"""Main processing function.
	"""
	if os.name != "nt":
		libastyle.system_exit("This script is for Windows only!")

	if platform.python_implementation() == "IronPython":
		libastyle.system_exit("IronPython is not currently supported")

	libastyle.set_text_color()
	print(libastyle.get_python_version())

	languages = (
			# "chinese",					# returns chinese-simplified
			"chinese-simplified",
			"chinese-traditional",
			"czech",
			"danish",
			"dutch",
			"belgian",
			"english",
			"finnish",
			"french",
			"german",
			"greek",
			"hungarian",
			"icelandic",
			"italian",
			"japanese",
			"korean",
			"norwegian",
			"polish",
			"portuguese",
			"russian",
			"slovak",
			"spanish",
			"swedish",
			"turkish",
			)

	# build list of locale names
	locale_names = []
	for language in languages:
		# print language
		try:
			locale.setlocale(locale.LC_ALL, language)
		except locale.Error:
			print("unsupported locale: " + language)
		# print(locale.getlocale(locale.LC_CTYPE))
		locale_name = locale.setlocale(locale.LC_ALL, None)

		locale_names.append(locale_name)
	# sort the list of locale names
	# the call changed with version 3
	if sys.version_info[0] < 3:
		locale_names.sort(sort_compare)
	else:
		locale_names.sort(key=get_codepage)
	# print the list of locale names
	prevoius_codepage = 0
	total1252 = 0
	for locale_name in locale_names:
		codepage = get_codepage(locale_name)
		if codepage == "1252":
			total1252 += 1
		if codepage != prevoius_codepage:
			if prevoius_codepage == "1252":
				print("1252 TOTAL " + str(total1252))
			print()
			prevoius_codepage = codepage
		print(codepage + ' ' + locale_name)

# -----------------------------------------------------------------------------

def sort_compare(locale_name1, locale_name2):
	"""Sort comparison function.
	   Not used by version 3.
	"""
	# get codepage from the locale
	codepage1 = get_codepage(locale_name1)
	codepage2 = get_codepage(locale_name2)
	# then sort by codepage
	if codepage1 < codepage2:
		return -1
	if codepage1 > codepage2:
		return 1
	# codepage is equal, sort by name
	if locale_name1 < locale_name2:
		return -1
	return 1

# -----------------------------------------------------------------------------

def get_codepage(locale_name):
	"""Extract codepage from the locale name.
	"""
	# extract codepage
	codepage_sep = locale_name.rfind('.')
	if codepage_sep == -1:
		codepage = "0"
	else:
		codepage = locale_name[codepage_sep+1:]
	# if less than 4 bytes prefix with a zero
	if len(codepage) == 3:
		codepage = '0' + codepage
	return codepage

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	main()
	libastyle.system_exit()

# -----------------------------------------------------------------------------
