#! /usr/bin/python
""" Create the distribution files for Artistic Style.
    Windows distribution is created on Windows.
    Linux distribution is created on Linux.
"""

# to disable the print statement and use the print() function (version 3 format)
from __future__ import print_function

import glob
import libastyle		#local directory
import os
import shutil
import stat
import subprocess
import time

# global variables ------------------------------------------------------------

# release number for distribution file
__release = "2.04"
# inut from AStyle directory
__astyle_dir = libastyle.get_astyle_directory()
# output to Project directory
__base_dir =  libastyle.get_project_directory()

# -----------------------------------------------------------------------------

def create_distributions():
	"""Main processing function.
	"""
	libastyle.set_text_color()
	print(libastyle.get_python_version())
	os.chdir(libastyle.get_file_py_directory())
	remove_dist_directories()
	if os.name == "nt":
		build_windows_distribution()
	else:
		build_linux_distribution()
		build_mac_distribution()
		# build_vms_distribution()

# -----------------------------------------------------------------------------

def build_linux_distribution():
	"""Copy astyle files to the linux directory.
	"""
	print()
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	print("*              Copying Linux Distribution               *")
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	dist_base = __base_dir + "/DistLinux"
	dist_astyle = dist_base + "/astyle"
	os.makedirs(dist_astyle)

	# doc directory
	dist_doc = dist_astyle + "/doc/"
	os.mkdir(dist_doc)
	copy_astyle_doc(dist_doc)

	# src directory
	dist_src = dist_astyle +  "/src/"
	os.mkdir(dist_src)
	copy_astyle_src(dist_src)

	# build/clang directory
	astyle_build_clang = __astyle_dir + "/build/clang/"
	dist_build_clang = dist_astyle +  "/build/clang/"
	os.makedirs(dist_build_clang)
	make_path_clang = astyle_build_clang + "/Makefile"
	shutil.copy(make_path_clang, dist_build_clang)
	# permissions = read/write by the owner and read only by everyone else
	mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
	os.chmod(make_path_clang, mode)
	print("build/clang copied")

	# build/gcc directory
	astyle_build_gcc = __astyle_dir + "/build/gcc/"
	dist_build_gcc = dist_astyle +  "/build/gcc/"
	os.makedirs(dist_build_gcc)
	make_path_gcc = astyle_build_gcc + "/Makefile"
	shutil.copy(make_path_gcc, dist_build_gcc)
	# permissions = read/write by the owner and read only by everyone else
	mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
	os.chmod(make_path_gcc, mode)
	print("build/gcc copied")

	# build/intel directory
	astyle_build_intel = __astyle_dir + "/build/intel/"
	dist_build_intel = dist_astyle +  "/build/intel/"
	os.makedirs(dist_build_intel)
	make_path_intel = astyle_build_intel + "/Makefile"
	shutil.copy(make_path_intel, dist_build_intel)
	# permissions = read/write by the owner and read only by everyone else
	mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
	os.chmod(make_path_intel, mode)
	print("build/intel copied")

	# create tar.bz2
	tarname = "astyle_{0}_linux.tar".format(__release)
	call_7zip(dist_base, tarname)
	bz2name = tarname + ".gz"
	call_7zip(dist_base, bz2name)

# -----------------------------------------------------------------------------

def build_mac_distribution():
	"""Copy astyle files to the mac directory.
	"""
	print()
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	print("*               Copying Mac Distribution                *")
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	dist_base = __base_dir + "/DistMac"
	dist_astyle = dist_base + "/astyle"
	os.makedirs(dist_astyle)

	# doc directory
	dist_doc = dist_astyle + "/doc/"
	os.mkdir(dist_doc)
	copy_astyle_doc(dist_doc)

	# src directory
	dist_src = dist_astyle +  "/src/"
	os.mkdir(dist_src)
	copy_astyle_src(dist_src)

	# build/mac directory
	astyle_build_mac = __astyle_dir + "/build/mac/"
	dist_build_mac = dist_astyle +  "/build/mac/"
	make_path_mac = astyle_build_mac + "/Makefile"
	os.makedirs(dist_build_mac)
	shutil.copy(make_path_mac, dist_build_mac)
	# permissions = read/write by the owner and read only by everyone else
	mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
	os.chmod(make_path_mac, mode)
	print("build/mac copied")

	# create tar.gz
	tarname = "astyle_{0}_macosx.tar".format(__release)
	call_7zip(dist_base, tarname)
	gzname = tarname + ".gz"
	call_7zip(dist_base, gzname)

# -----------------------------------------------------------------------------

def build_vms_distribution():
	"""Copy astyle files to the open vms directory.
	"""
	print()
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	print("*             Copying OpenVMS Distribution              *")
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	dist_base = __base_dir + "/DistVMS"
	dist_astyle = dist_base + "/astyle"
	os.makedirs(dist_astyle)

	# doc directory
	dist_doc = dist_astyle + "/doc/"
	os.mkdir(dist_doc)
	copy_astyle_doc(dist_doc)

	# src directory
	dist_src = dist_astyle +  "/src/"
	os.mkdir(dist_src)
	copy_astyle_src(dist_src)

	# build/mac directory
	astyle_build_vms = __astyle_dir + "/build/vms/"
	dist_build_vms = dist_astyle + "/build/vms/"
	os.makedirs(dist_build_vms)
	for file_in in ("descrip.mms",
			     "java.opt",
			     "lib.opt",
			     "vmsbuild.com"):
		shutil.copy(astyle_build_vms + file_in, dist_build_vms)
	print("build/vms copied")

	# create zip
	zipfile = "astyle_{0}_openvms.zip".format(__release)
	call_7zip(dist_base, zipfile)

# -----------------------------------------------------------------------------

def build_windows_distribution():
	"""Copy astyle files to the windows directory.
	"""
	print()
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	print("*             Copying Windows Distribution              *")
	print("* * * * * * * * * * * * * * * * * * * * * * * * * * * * *")
	dist_base = __base_dir + "/DistWindows"
	dist_astyle = dist_base + "/AStyle"
	vsdir = libastyle.VS_RELEASE
	if vsdir != "vs2010":
		libastyle.system_exit("Must compile with vs2010 in libastyle: "  + vsdir)
	os.makedirs(dist_astyle)

	# Windows includes an executable in the bin directory
	libastyle.build_astyle_executable(libastyle.STATIC)
	dist_astyle_bin = dist_astyle +  "/bin/"
	os.mkdir(dist_astyle_bin)
	astyle_build_directory = libastyle.get_astyle_build_directory(libastyle.STATIC)
	shutil.copy(astyle_build_directory + "/binstatic/AStyle.exe", dist_astyle_bin)
	print("exe copied ({0})".format(vsdir))

	# doc directory
	dist_doc = dist_astyle + "/doc/"
	os.mkdir(dist_doc)
	copy_astyle_doc(dist_doc, True)

	# src directory
	dist_src = dist_astyle +  "/src/"
	os.mkdir(dist_src)
	copy_astyle_src(dist_src, True)

	# build directory
	astyle_build_dir = __astyle_dir + "/build"
	dist_astyle_build = dist_astyle +  "/build"
	os.mkdir(dist_astyle_build)
	# copy_vs2003_directory(astyle_build_dir, dist_astyle_build)
	copy_vs20xx_directories(astyle_build_dir, dist_astyle_build)

	# create zip
	zipfile = "AStyle_{0}_windows.zip".format(__release)
	call_7zip(dist_base, zipfile)

# -----------------------------------------------------------------------------

def call_7zip(dist_base, compressed_file):
	"""Call 7zip to create an archive.
	   arg 1- the directory to compress.
	   arg 2- name of the compressed file.
	"""
	exepath = libastyle.get_7zip_path()
	compress = [exepath, "a", compressed_file]
	# check file ending to see if it is a tarball
	if compressed_file.endswith((".gz", ".bz2")):
		compress.append("*.tar")
	# stdout file must have full path since 'cwd' is used in call
	filename = libastyle.get_file_py_directory(True) + "compress.txt"
	outfile = open(filename, 'w')
	try:
		subprocess.check_call(compress, cwd=dist_base, stdout=outfile)
	except subprocess.CalledProcessError as err:
		libastyle.system_exit("Bad 7zip return: " + str(err.returncode))		
	except OSError:
		libastyle.system_exit("Cannot find executable: " + compress[0])		
	outfile.close()
	os.remove(filename)
	print(compressed_file + " created")

# -----------------------------------------------------------------------------

def convert_line_ends(dist_dir, to_dos):
	"""Convert line ends to dos (CRLF) or linux (LF).
	   Needs tofrodos package.
	   All files in a directory are converted.
	"""
	files = glob.glob(dist_dir + "*")
	if os.name == "nt":
		exedir = "C:/Programs/tofrodos/"
		if to_dos: call_list = [exedir + "todos"] + files
		else:     call_list = [exedir + "fromdos"] + files
	else:
		if to_dos: call_list = ["todos"] + files
		else:     call_list = ["fromdos"] + files

	# call the conversion program
	try:
		retval = subprocess.check_call(call_list)
	except subprocess.CalledProcessError as err:
		libastyle.system_exit("Bad tofro return: " + str(err.returncode))
	except OSError:
		libastyle.system_exit("Cannot find executable: " + call_list[0])
		
# -----------------------------------------------------------------------------

def copy_astyle_doc(dist_doc, to_dos=False):
	"""Copy astyle doc directory to a distribution directory.
	"""
	deleted = 0
	docfiles = glob.glob(__astyle_dir + "/doc/*")
	for filepath in docfiles:
		# don't copy these files
		if "Archive" in filepath: 
			deleted += 1
			sep = filepath.rfind(os.sep)
			print("    " + filepath[sep+1:] + " - not copied")
		else:
			shutil.copy(filepath, dist_doc)
	convert_line_ends(dist_doc, to_dos)
	# verify copy - had a problem with bad filenames
	distfiles = (glob.glob(dist_doc + "/*.html")
					+ glob.glob(dist_doc + "/*.css"))
	if len(distfiles) != len(docfiles) - deleted:
		libastyle.system_exit("Error copying doc: " + str(len(distfiles)))
	# change file permissions
	for srcfile in distfiles:
		# read/write by the owner and read only by everyone else (-rw-r--r--)
		mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
		os.chmod(srcfile, mode)
	print("doc copied")

# -----------------------------------------------------------------------------

def copy_astyle_src(dist_src, to_dos=False):
	"""Copy astyle src directory to a distribution directory.
	"""
	srcfiles = glob.glob(__astyle_dir + "/src/*")
	for srcpath in srcfiles:
		shutil.copy(srcpath, dist_src)
	convert_line_ends(dist_src, to_dos)
	# verify copy - had a problem with bad filenames
	distfiles = (glob.glob(dist_src + "/*.cpp")
					+ glob.glob(dist_src + "/*.h"))
	if len(distfiles) != len(srcfiles):
		libastyle.system_exit("Error copying src: " + str(len(distfiles)))
	# change file permissions
	for srcfile in distfiles:
		# read/write by the owner and read only by everyone else (-rw-r--r--)
		mode = (stat.S_IRUSR | stat.S_IWUSR | stat.S_IRGRP | stat.S_IROTH)
		os.chmod(srcfile, mode)
	print("src copied")

# -----------------------------------------------------------------------------

#~ def copy_vs2003_directory(astyle_build_dir, dist_astyle_build):
	#~ """Copy the build/vs2003 directory to the distribution directory.
	#~ """
	#~ distAStyleVS2003 = dist_astyle_build +  "/vs2003/"
	#~ os.mkdir(distAStyleVS2003)
	#~ shutil.copy(astyle_build_dir + "/vs2003/AStyle.sln", distAStyleVS2003)
	#~ shutil.copy(astyle_build_dir + "/vs2003/AStyle.vcproj", distAStyleVS2003)
	#~ print "build/vs2003 copied"

# -----------------------------------------------------------------------------

def copy_vs20xx_directories(astyle_build_dir, dist_astyle_build):
	"""Copy the build/vs20xx directories to the distribution directory.
	"""
	for vsdir in ("/vs2005/",
				  "/vs2008/",
				  "/vs2010/",
				  "/vs2012/"):

		# copy solution files
		dist_astyle_vs20xx = dist_astyle_build + vsdir
		os.mkdir(dist_astyle_vs20xx)
		slnfiles = glob.glob(astyle_build_dir + vsdir + "*.sln")
		for sln in slnfiles:
			shutil.copy(sln, dist_astyle_vs20xx)

		# build project directories
		for projdir in ("/AStyle/",
					    "/AStyleDll/",
					    "/AStyleJava/",
					    "/AStyleLib/"):
			dist_astyle_proj = dist_astyle_vs20xx[:-1] + projdir
			os.mkdir(dist_astyle_proj)

			# copy project files
			projfiles = glob.glob(astyle_build_dir + vsdir[:-1] + projdir + "*.*proj")
			for proj in projfiles:
				shutil.copy(proj, dist_astyle_proj)
			if vsdir[1:-1] >= "vs2010":
				filtfiles = glob.glob(astyle_build_dir + vsdir[:-1] + projdir + "*.*.filters")
				for filter_in in filtfiles:
					shutil.copy(filter_in, dist_astyle_proj)

		print("build/" + vsdir[1:-1] + " copied")
	
# -----------------------------------------------------------------------------

def remove_dist_directories():
	"""Remove directories from a previous run.
	"""
	dirs = glob.glob(__base_dir + "/[Dd]ist*/")
	for directory in dirs:
		directory = directory.replace('\\', '/')
		print("remove " + directory)
		# remove the directory - this is a problem with Windows only
		imax = 5
		for i in range(0, imax):
			shutil.rmtree(directory, True)
			if not os.path.isdir(directory): break
			if i == imax - 1:
				libastyle.system_exit("Directory not removed: " + directory)
			time.sleep(2)		

# -----------------------------------------------------------------------------

# make the module executable
if __name__ == "__main__":
	create_distributions()
	libastyle.system_exit()

# -----------------------------------------------------------------------------
