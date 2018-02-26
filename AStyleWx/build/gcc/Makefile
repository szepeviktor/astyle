# Make file for GCC compiler on Linux or compatible OS

# list of astylewx source files without the directory
# included are files from astyle/src, astylewx/src, and astylewx/dialog
SRC = astyle_main.cpp ASBeautifier.cpp ASFormatter.cpp ASEnhancer.cpp ASResource.cpp \
$(shell find ../../src -name "*.cpp" | sed -e 's@../../src/@@') \
AboutDlgBase.cpp  AStyleDlgBase.cpp  EditorDlgBase.cpp  SettingsDlgBase.cpp

# list of astylewxso source files without the directory
# included are files from astylewx/src, and astylewx/dialog
# not included are files from astyle/src,
SRCs = $(shell find ../../src -name "*.cpp" | sed -e 's@../../src/@@') \
AboutDlgBase.cpp  AStyleDlgBase.cpp  EditorDlgBase.cpp  SettingsDlgBase.cpp

# source directories
vpath %.cpp ../../src ../../dialog ../../../AStyle/src ../../../astyle/src
vpath %.h   ../../src ../../dialog ../../../AStyle/src ../../../astyle/src

# set prefix if not defined on the command line
ifndef prefix
    prefix=/usr
endif
SYSCONF_PATH=$(prefix)/share/doc/astylewx

#install prefix for desktop
ifdef GTK3
GTKVERSION=gtk+-3.0
else
GTKVERSION=gtk+-2.0
endif
gnomeprefix:=$(shell pkg-config --variable=prefix $(GTKVERSION) 2>/dev/null)
ifndef prefix
ifdef gnomeprefix
  prefix=$(gnomeprefix)
else
  prefix=/usr
endif
endif

# set wxWidgets release if not defined on the command line
ifndef wx
	wx=$(shell wx-config --release)
endif

# define macros
bindir = bin$(wx)
objdir = obj$(wx)
idatadir=$(prefix)/share
ipixmapdir=$(idatadir)/pixmaps
ibindir=$(prefix)/bin
rpaths = -Wl,-rpath,./ -Wl,-rpath,../ -Wl,-rpath,./lib -Wl,-rpath,../lib \
-Wl,-rpath,../../../../AStyle/build/gcc/bin  -Wl,-rpath,../../../../astyle/build/gcc/bin
SOLIBVER = 3.2.0
# -Wno-unused-local-typedefs is for wxWidgets 2.8 and gcc 4.9 compiler
# wxWidgets 3.0 does not need it, gcc < 4.9 does not need it
CBASEFLAGS = -Wall -Wextra -std=c++11 -Wno-unused-local-typedefs -fno-rtti -fno-exceptions \
-I../../src -I../../dialog -I../../image
LDBASEFLAGS = -L../../../AStyle/build/gcc/bin  -L../../../astyle/build/gcc/bin
CXX = g++
INSTALL=install -o $(USER) -g $(USER)

##################################################

# define compile options for each build
ifdef CFLAGS
    CFLAGSr  =    -DNDEBUG $(CBASEFLAGS) $(CFLAGS) $(shell wx-config --version=$(wx) --cflags)
    CFLAGSd  = -g -D_DEBUG $(CBASEFLAGS) $(CFLAGS) $(shell wx-config --version=$(wx) --cflags --debug)
else
    CFLAGSr  = -O2 -DNDEBUG $(CBASEFLAGS) $(shell wx-config --version=$(wx) --cflags)
    CFLAGSd  = -g  -D_DEBUG $(CBASEFLAGS) $(shell wx-config --version=$(wx) --cflags --debug)
endif

# define link options
ifdef LDFLAGS
    LDFLAGSr = $(LDBASEFLAGS) $(LDFLAGS)  $(shell wx-config --version=$(wx) --libs)
    LDFLAGSd = $(LDBASEFLAGS) $(LDFLAGS) $(shell wx-config --version=$(wx) --libs --debug)
else
    LDFLAGSr = -s $(LDBASEFLAGS) $(shell wx-config --version=$(wx) --libs)
    LDFLAGSd =    $(LDBASEFLAGS) $(shell wx-config --version=$(wx) --libs --debug)
endif

# object files are built from the source list $(SRC)
# a suffix is added for each build
OBJ   = $(patsubst %.cpp,$(objdir)/%.o,$(SRC))
OBJd  = $(patsubst %.cpp,$(objdir)/%_d.o,$(SRC))
OBJs  = $(patsubst %.cpp,$(objdir)/%_s.o,$(SRCs))
OBJsd = $(patsubst %.cpp,$(objdir)/%_sd.o,$(SRCs))

# define object file rule (with the suffix) for each build

# OBJ
$(objdir)/%.o:  %.cpp  deps.mak
	@ mkdir -p $(objdir)
	$(CXX) $(CFLAGSr) -DASTYLE_LIB -c $< -o $@

# OBJd
$(objdir)/%_d.o:  %.cpp  deps.mak
	@ mkdir -p $(objdir)
	$(CXX) $(CFLAGSd) -DASTYLE_LIB -c $< -o $@

# OBJs
$(objdir)/%_s.o:  %.cpp  deps.mak
	@ mkdir -p $(objdir)
	$(CXX) $(CFLAGSr) -DASTYLE_DYLIB -c $< -o $@

# OBJsd
$(objdir)/%_sd.o:  %.cpp  deps.mak
	@ mkdir -p $(objdir)
	$(CXX) $(CFLAGSd) -DASTYLE_DYLIB -c $< -o $@

##################################################
# define build dependencies for each command

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
release:  astylewx
astylewx:  $(OBJ)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSr) -lwx_gtk2u_aui-$(wx) -lwx_gtk2u_stc-$(wx)
	@ echo

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
debug:  astylewxd
astylewxd:  $(OBJd)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSd) -lwx_gtk2u_aui-$(wx) -lwx_gtk2u_stc-$(wx)
	@ echo

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
shared:  astylewxso
astylewxso:  $(OBJs)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSr) -lwx_gtk2u_aui-$(wx) -lwx_gtk2u_stc-$(wx) $(rpaths)
	@ echo

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
shareddebug:  astylewxsod
astylewxsod:  $(OBJsd)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSd) -lwx_gtk2u_aui-$(wx) -lwx_gtk2u_stc-$(wx) $(rpaths)
	@ echo

# used to display variables for debugging
show:
	@echo $(SRC)
	@echo $(OBJ)

all:  release  debug  shared  shareddebug

clean:
	rm -f $(objdir)/*.o $(bindir)/*astylewx*

cleanobj:
	rm -f $(objdir)/*.o

deps:
	$(CXX) -MM $(CFLAGSr) ../../dialog/*.cpp ../../src/*.cpp | sed -e 's@/usr.* @@' | grep [a-zA-Z] >deps.mak

# The two last install commands will fail if Gnome is not installed or is not at $(prefix).
# This is OK - just means no AStyleWx in the Gnome Applications menu
install:
	$(INSTALL) -m 755 -d $(ibindir)
	$(INSTALL) -m 755 $(bindir)/astylewx  $(ibindir)

	$(INSTALL) -m 755 -d $(SYSCONF_PATH)
	@mkdir -p $(SYSCONF_PATH)/html;
	@for files in ../../doc/*.html  ../../doc/*.css; \
	do \
		$(INSTALL)  -m 644  "$$files"  $(SYSCONF_PATH)/html; \
	done

ifdef gnomeprefix
	$(INSTALL) -m 755 -d $(idatadir)/applications $(ipixmapdir)
	$(INSTALL) -m 755 ../../image/AStyleWx.desktop $(idatadir)/applications/astylewx.desktop
	$(INSTALL) -m 644 ../../image/AStyle_32.xpm $(ipixmapdir)/astyle-32.xpm
endif

uninstall:
	rm -f $(ibindir)/astylewx
	rm -rf $(SYSCONF_PATH)
ifdef gnomeprefix
	rm -f $(idatadir)/applications/astylewx.desktop
	rm -f $(ipixmapdir)/astyle-32.xpm
endif
