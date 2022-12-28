#! /usr/bin/python
# Copy or move Artistic Style backup files to a backup directory.
# NOTE: This script uses "shutil.copy2" which will keep the
#     last access time and last modification time of the original file.

import os
import shutil
import sys

# global variables ------------------------------------------------------------

# CHANGE THE FOLLOWING 4 VARIABLES
# g_indir is the input top level directory containing the .orig files
# g_outdir is the output top level directory containing the moved files
# g_fileext is the backup file extension
# g_copyfiles is COPY or MOVE the files

g_indir = "~/Projects/TestData/CodeBlocks/src"
g_outdir = "~/Projects/TestData/CodeBlocks/bak"
g_fileext = ".orig"
# USE ONE OF THE FOLLOWING TO COPY OR MOVE THE FILES
g_copyfiles = "COPY"
# g_copyfiles = "MOVE"

# -----------------------------------------------------------------------------

def process_directories():
	"""Main processing function"""
	"""Walk thru the top-level directory tree."""
	global g_indir, g_outdir
	# initialization
	g_indir = os.path.normpath(os.path.expanduser(g_indir))
	g_outdir = os.path.normpath(os.path.expanduser(g_outdir))
	display_global_variables()
	if not validate_global_variables(): return
	processed = 0		# number of files processed
	print g_indir
	# walk thru the directory tree
	for dirpath, dirnames, filenames in os.walk(g_indir):
		if dirpath != g_indir:
			print "directory: " + dirpath[len(g_indir)+1:]
		remove_hidden_directories(dirnames)
		processed += process_backup_files(dirpath, filenames)
	print "{0} \"{1}\" files processed".format(processed, g_fileext)

# -----------------------------------------------------------------------------

def display_global_variables():
	"""Display the global variables."""
	print
	print g_copyfiles + " Artistic Style backup files"
	print "FROM " + g_indir
	print "TO   " + g_outdir
	print

# -----------------------------------------------------------------------------

def move_or_copy_file(filepath, outpath, file):
	"""Move or copy a file to the backup directory."""
	outdir = outpath[:-len(file)-1]
	# create a directory
	if not os.path.isdir(outdir):
		os.makedirs(outdir)
	# copy to backup
	shutil.copy2(filepath, outpath)
	# remove from filepath
	if g_copyfiles == "MOVE":
		os.remove(filepath)
		
# -----------------------------------------------------------------------------

def process_backup_files(dirpath, filenames):
	"""Process the backup files in a directory."""
	"""Return the number of files processed."""
	processed = 0		# number of files processed
	for file in filenames:
		# bypass if not the correct file extension
		if not file.endswith(g_fileext): 
			continue
		# process the file
		filepath = os.path.join(dirpath, file)
		outpath = g_outdir + os.path.join(dirpath[len(g_indir):], file)
		move_or_copy_file(filepath, outpath, file)
		processed += 1
	return processed

# -----------------------------------------------------------------------------
		
def remove_hidden_directories(dirnames):
	"""Remove hidden directories in the dirnames list (don't process)."""
	for dir in dirnames:
		if dir[0] == '.': 
			dirnames.remove(dir)

# -----------------------------------------------------------------------------

def validate_global_variables():
	"""Validate the value of global variables."""
	if not os.path.isdir(g_indir):
		print "Input directory does not exist!"
		print
		return False
	if g_indir == g_outdir:
		print "Input and output directories are the same!"
		print
		return False
	if len(g_fileext) == 0:
		print "Invalid \"g_fileext\" value!"
		print
		return False
	if (g_copyfiles != "COPY"
	and g_copyfiles != "MOVE"):
		print "Invalid \"g_copyfiles\" value!"
		print
		return False
	return True

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	process_directories()
	# pause if script is not run from SciTE (argv[1] = 'scite')
	if (os.name == "nt"
	and len(sys.argv) == 1):
		print
		os.system("pause")
		# raw_input("\nPress Enter to continue . . .")

# -----------------------------------------------------------------------------
