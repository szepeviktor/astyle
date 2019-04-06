# WINDOWS CMAKE COMMAND LINE VARIABLES
# WXWIN is optional. It is used when cmake cannot find a default configuration
#     or when the default configuration needs to be changed. It must point to the
#     top level wxWidgets directory to be used.
# WXSHARED is optional. The default is to link with static libraries in the
#     wxWidgets "lib/gcc_lib" directory. If set with -DWXSHARED=ON, linking
#     will be with the shared libraries in the "lib/gcc_dll" directory.
if(WIN32)
    if(DEFINED WXWIN)
        set(wxWidgets_ROOT_DIR ${WXWIN} CACHE PATH "wxWidgets top directory")
    endif()
    option(WXSHARED "Link with wxWidgets shared libraries" OFF)
endif()

# LINUX CMAKE COMMAND LINE VARIABLES
# -DWX=x.y to use a wxWidgets version other than the default. x is the major
#          version number, y is the minor version number.
# -DTK=(gtk2,gtk3) to use the gtk2 or gtk3 toolkit instead of the default.
# There must be a wxWidgets with these specifications installed in wx-config.
if(NOT WIN32)
    if(DEFINED WX OR DEFINED TK)
        set(wxWidgets_CONFIG_OPTIONS --version=${WX} --toolkit=${TK})
    endif()
endif()

# Release Build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# AStyleWx Source
file(GLOB SRCS src/*.cpp
               dialog/*.cpp
               image/*.rc
               ../AStyle/src/*.cpp)

# WIN32 will prevent opening a console window on execution
add_executable(astylewx WIN32 ${SRCS})
