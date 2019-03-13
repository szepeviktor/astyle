cmake_minimum_required(VERSION 3.0)
project(astylewx CXX)

# WINDOWS CMAKE COMMAND LINE VARIABLES
# WXWIN is optional. It is used when cmake cannot find a default configuration
#     or when the default configuration needs to be changed. It must point to the
#     top level wxWidgets directory to be used.
# WXSHARED is optional. The default is to link with static libraries in the
#     wxWidgets "lib/gcc_lib" directory. If set with -DWXSHARED=1, linking
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
        message("## wxWidgets_CONFIG_OPTIONS are ${wxWidgets_CONFIG_OPTIONS}")
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
message("## CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

# Set file name if different than 'astylewx'
if(WIN32)
    set_property(TARGET astylewx PROPERTY OUTPUT_NAME AStyleWx)
endif()

if(NOT WIN32)
    # COMPILE OPTIONS
    if(APPLE)
        target_compile_options(astylewx PRIVATE -Wall
                                                -fno-exceptions
                                                -std=c++11
                                                -stdlib=libc++)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options(astylewx PRIVATE -Wall
                                                -fno-rtti
                                                -fno-exceptions
                                                -std=c++11)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(astylewx PRIVATE -Wall
                                                -fno-exceptions
                                                -std=c++11)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        target_compile_options(astylewx PRIVATE -Wall
                                                -fno-exceptions
                                                -std=c++11)
    endif()
    # GET WXWIDGETS VARIABLES
    set(wxWidgets_USE_UNICODE)
    find_package(wxWidgets COMPONENTS adv aui core stc REQUIRED)
    #SET OPTIONS
    include(${wxWidgets_USE_FILE})
    target_compile_options(astylewx PRIVATE ${compile_options})
    target_include_directories(astylewx PRIVATE src
                                                dialog
                                                image)
    add_definitions(-DASTYLE_LIB)
    target_link_libraries(astylewx ${wxWidgets_LIBRARIES})
    # STRIP RELEASE BUILDS
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        add_custom_command(TARGET astylewx POST_BUILD
                           COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:astylewx>)
    endif()

elseif(MINGW)
    # COMPILE OPTIONS
    # -fno-rtti causes "duplicate section ... has different size" warnings
    # the exe will run OK but it is better to eliminate the warnings
    target_compile_options(astylewx PRIVATE -Wall
                                            -Wextra
                                            -std=gnu++11    # must be gnu
                                            -fno-exceptions
                                            -Wno-deprecated-declarations)
    # GET WXWIDGETS VARIABLES
    set(wxWidgets_CONFIGURATION mswu)
    # do not change the order of these or there will be linker errors
    find_package(wxWidgets COMPONENTS adv aui stc core base scintilla REQUIRED)
    # SET OPTIONS
    include(${wxWidgets_USE_FILE})
    target_compile_options(astylewx PRIVATE ${compile_options})
    target_include_directories(astylewx PRIVATE src
                                                dialog
                                                image)
    add_definitions(-DASTYLE_LIB)
    # LINK LIBRARIES
    if(NOT WXSHARED)
        # UxTheme is not included in the cmake link libraries, so it is added here
        target_link_libraries(astylewx ${wxWidgets_LIBRARIES} "UxTheme")
    else()
        # using DLLs requires a custom build
        set(msw_link_dir "${wxWidgets_ROOT_DIR}/lib/gcc_dll/")
        string(REPLACE "/" "\\" msw_copy_dir ${msw_link_dir})
        add_custom_command(TARGET astylewx POST_BUILD
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}wxmsw*u_adv_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}wxmsw*u_aui_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}wxmsw*u_stc_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}wxmsw*u_core_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}wxbase*u_gcc_*.dll >NUL)
        foreach(mingw_lib ${wxWidgets_LIBRARIES})
            string(REPLACE "/lib/gcc_lib/" "/lib/gcc_dll/" mingw_lib_new ${mingw_lib})
            list(APPEND mingw_libs "${mingw_lib_new}")
        endforeach(mingw_lib)
        ## message("## MINGW_LIBS: ${mingw_libs}")                  # for testing
        target_link_libraries(astylewx ${mingw_libs})
    endif()
    # STRIP RELEASE BUILDS
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        add_custom_command(TARGET astylewx POST_BUILD
                           COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:astylewx>)
    endif()
endif()
