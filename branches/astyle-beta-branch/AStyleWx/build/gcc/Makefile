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

# set wxWidgets release if not defined on the command line
ifdef WX
	wx = $(WX)
else
	wx = $(shell wx-config --release)
endif

# get GTK toolkit version and install prefix for desktop
tk = $(shell wx-config --query-toolkit)
ifeq ($(tk), gtk3)
	GTKVERSION = gtk+-3.0
else
	GTKVERSION = gtk+-2.0
endif

ifdef TK
ifeq ($(TK), gtk3)
	tk = gtk3
	GTKVERSION = gtk+-3.0
else ifeq ($(TK), gtk2)
	tk = gtk2
	GTKVERSION = gtk+-2.0
endif
endif

gnomeprefix:=$(shell pkg-config --variable=prefix $(GTKVERSION) 2>/dev/null)
ifndef prefix
ifdef gnomeprefix
	prefix=$(gnomeprefix)
else
	prefix=/usr
endif
endif

# define macros
# CXX defaults to g++
bindir = wx$(wx)$(tk)/bin
objdir = wx$(wx)$(tk)/obj
idatadir=$(prefix)/share
ipixmapdir=$(idatadir)/pixmaps
ibindir=$(prefix)/bin
rpaths = -Wl,-rpath,./ -Wl,-rpath,../ -Wl,-rpath,./lib -Wl,-rpath,../lib \
-Wl,-rpath,../../../../AStyle/build/gcc/bin  -Wl,-rpath,../../../../astyle/build/gcc/bin
SOLIBVER = 3.2.0
# -Wno-unused-local-typedefs is for wxWidgets 2.8 and gcc 4.9 compiler
# wxWidgets 3.0 does not need it, gcc < 4.9 does not need it
CBASEFLAGS = -Wall -std=c++11 -fno-rtti -fno-exceptions \
-I../../src -I../../dialog -I../../image
LDBASEFLAGS = -L../../../AStyle/build/gcc/bin  -L../../../astyle/build/gcc/bin
INSTALL=install -o $(USER) -g $(USER)

# get the compile and link options from wx-config
WXCONF := wx-config
ifdef WX
	WXCONF := $(WXCONF) --version=$(wx)
endif
ifdef TK
	WXCONF := $(WXCONF) --toolkit=$(tk)
endif
$(info ## WXCONF = $(WXCONF))

CCONFFLAGS  := $(shell $(WXCONF) --cxxflags)
LDCONFFLAGS := $(shell $(WXCONF) --libs adv,aui,core,stc)

##################################################

# define compile options for each build
ifdef CFLAGS
	CFLAGSr  =    -DNDEBUG $(CBASEFLAGS) $(CFLAGS) $(CCONFFLAGS)
	CFLAGSd  = -g -D_DEBUG $(CBASEFLAGS) $(CFLAGS) $(CCONFFLAGS)
else
	CFLAGSr  = -O2 -DNDEBUG $(CBASEFLAGS) $(CCONFFLAGS)
	CFLAGSd  = -g  -D_DEBUG $(CBASEFLAGS) $(CCONFFLAGS)
endif

# define link options
ifdef LDFLAGS
	LDFLAGSr = $(LDBASEFLAGS) $(LDFLAGS)  $(LDCONFFLAGS)
	LDFLAGSd = $(LDBASEFLAGS) $(LDFLAGS) $(LDCONFFLAGS)
else
	LDFLAGSr = -s $(LDBASEFLAGS) $(LDCONFFLAGS)
	LDFLAGSd =    $(LDBASEFLAGS) $(LDCONFFLAGS)
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
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSr)
	@ echo

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
debug:  astylewxd
astylewxd:  $(OBJd)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSd)
	@ echo

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
shared:  astylewxso
astylewxso:  $(OBJs)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSr) $(rpaths)
	@ echo

# the .o files must be before the LDFLAGS containing the wxWidgets libraries
# wxWidgets libraries missing from wx-config are added here
shareddebug:  astylewxsod
astylewxsod:  $(OBJsd)
	@ mkdir -p $(bindir)
	$(CXX) -o $(bindir)/$@ $^ $(LDFLAGSd) $(rpaths)
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
