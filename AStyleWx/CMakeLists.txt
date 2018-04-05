cmake_minimum_required(VERSION 3.0)
project(astylewx CXX)

# TODO: Separate macros for the huge "if" statement.

# LINUX CMAKE DEFINITIONS
# -DWX=x.y to use a wxWidgets version other than the default. x is the major
#          version number, y is the minor version number.
# -DTK=(gtk2,gtk3) to use the gtk2 or gtk3 toolkit instead of the default.
# There must be a wxWidgets with these specifications installed in wx-config.

# WINDOWS CMAKE CONSTANTS
# WXWIN is REQUIRED and must point to the top wxWidgets directory
# WXSHARED is optional. The default is to link with static libraries in the
#     wxWidgets "lib/gcc_lib" directory. If set with -DWXSHARED=1, linking
#     will be with the shared libraries in the "lib/gcc_dll" directory.
set(WXWIN "C:/Programs/wxWidgets-3.0.2_mingw" CACHE PATH "wxWidgets top directory")
option(WXSHARED "Link with wxWidgets shared libraries" OFF)

# Release Build - release by default
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

# Set file names if different than 'astylewx'
if(WIN32)
    set_property(TARGET astylewx PROPERTY OUTPUT_NAME AStyleWx)
endif()

# Set compile options for supported compilers
# COMPILE OPTIONS
set(compile_options "")
if(NOT WIN32)
    if(APPLE)
        set(compile_options -Wall
                            -fno-rtti
                            -fno-exceptions
                            -std=c++11
                            -stdlib=libc++)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(compile_options -Wall
                            -fno-rtti
                            -fno-exceptions
                            -std=c++11)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(compile_options -Wall
                            -fno-exceptions
                            -std=c++11
                            -Wno-potentially-evaluated-expression)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
        set(compile_options -Wall
                            -fno-exceptions
                            -std=c++11)
    endif()
    # verify wx-config
    execute_process(COMMAND wx-config --version
                    RESULT_VARIABLE res_var
                    OUTPUT_VARIABLE wx_ver)
    if(NOT ${res_var} EQUAL 0)
        message(FATAL_ERROR "\nCannot find 'wx-config' - is it installed?")
    endif()
    string(SUBSTRING ${wx_ver} 0 1 wx_ver_1)
    string(SUBSTRING ${wx_ver} 0 3 wx_ver_3)
    if(${wx_ver_1} LESS "3")
        message(FATAL_ERROR "\nCurrent version ${wx_ver_3} is not 3.0 or greater")
    endif()
    # build wx-config command
    # WX and TK are manually-specified variables defined on the command line
    set(config_command "wx-config")
    if(DEFINED WX)
        set(config_command ${config_command} --version=${WX})
    endif()
    if(DEFINED TK)
        set(config_command ${config_command} --toolkit=${TK})
    endif()
    message("## wx-config command: ${config_command}")
    # get options from wx-config
    execute_process(COMMAND ${config_command} --cflags
                    RESULT_VARIABLE res_var
                    OUTPUT_VARIABLE config_cflags)
    if(NOT ${res_var} EQUAL 0)
        message(FATAL_ERROR "\nNo cflags found for: ${config_command}")
    endif()
    separate_arguments(config_cflags)
    # set options from wx-config
    set(include_directories src dialog image)
    foreach(cflag ${config_cflags})
        string(LENGTH ${cflag} cflag_len)
        if(${cflag_len} LESS 2)
            continue()
        endif()
        string(SUBSTRING ${cflag} 0 2 cflag_opt)
        string(SUBSTRING ${cflag} 2 -1 cflag_txt)
        if(${cflag_opt} STREQUAL "-I")
            list(APPEND include_directories ${cflag_txt})
        elseif(${cflag_opt} STREQUAL "-D")
            add_definitions(${cflag})
        else()
            list(APPEND compile_options ${cflag})
        endif()
    endforeach(cflag)
    add_definitions(-DASTYLE_LIB)
    target_compile_options(astylewx PRIVATE ${compile_options})
    target_include_directories(astylewx PRIVATE ${include_directories})
    # LINK OPTIONS
    set(link_flags "")
    set(link_directory "")      # not used
    set(link_libraries "")
    # get options from wx-config
    execute_process(COMMAND ${config_command} --libs adv,aui,core,stc
                    RESULT_VARIABLE res_var
                    OUTPUT_VARIABLE config_libs)
    if(NOT ${res_var} EQUAL 0)
        message(FATAL_ERROR "\nNo libs found for: ${config_command}")
    endif()
    # string(REPLACE "\n" " " config_cflags ${config_cflags})    # debugging
    # string(REPLACE "\n" " " config_libs ${config_libs})        # debugging
    # message("## cflags: ${config_cflags}")                     # debugging
    # message("## libs:   ${config_libs}")                       # debugging
    separate_arguments(config_libs)
    # set options from wx-config
    foreach(lib ${config_libs})
        string(LENGTH ${lib} lib_len)
        if(${lib_len} LESS 2)
            continue()
        endif()
        string(SUBSTRING ${lib} 0 2 lib_opt)
        string(SUBSTRING ${lib} 2 -1 lib_txt)
        if(${lib_opt} STREQUAL "-l")
            list(APPEND link_libraries ${lib_txt})
        elseif(${lib_opt} STREQUAL "-L")
            list(APPEND link_directory ${lib_txt})
        else()
            list(APPEND link_flags ${lib})
        endif()
    endforeach(lib)
    set_target_properties(astylewx PROPERTIES LINK_FLAGS ${link_flags})
    target_link_libraries(astylewx ${link_libraries})
    # STRIP RELEASE BUILDS
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        add_custom_command(TARGET astylewx POST_BUILD
                           COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:astylewx>)
    endif()
elseif(MINGW)
    # COMPILE OPTIONS
    target_compile_options(astylewx PRIVATE -Wall
                                            -Wextra
                                            -fno-rtti
                                            -fno-exceptions
                                            -std=gnu++11    # must be gnu
                                            -Wno-deprecated-declarations)
    add_definitions(-DASTYLE_LIB)
    target_include_directories(astylewx PRIVATE src
                                                dialog
                                                ${WXWIN}/include
                                                ${WXWIN}/lib/gcc_lib/mswu)
    # LINK OPTIONS
    set(msw_link_dir "${WXWIN}/lib/gcc_lib")
    if(WXSHARED)
        set(msw_link_dir "${WXWIN}/lib/gcc_dll")
        string(REPLACE "/" "\\" msw_copy_dir ${msw_link_dir})
        add_custom_command(TARGET astylewx POST_BUILD
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}\\wxmsw30u_adv_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}\\wxmsw30u_aui_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}\\wxmsw30u_stc_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}\\wxmsw30u_core_gcc_*.dll >NUL
            COMMAND  cmd /c  copy /y  ${msw_copy_dir}\\wxbase30u_gcc_*.dll >NUL)
    endif()
    # do not change the order of these or there will be linker errors
    set(msw_libs libwxmsw30u_adv.a
                 libwxmsw30u_aui.a
                 libwxmsw30u_stc.a
                 libwxmsw30u_core.a
                 libwxbase30u.a
                 libwxscintilla.a
                 libwxpng.a
                 libwxzlib.a)
    foreach(msw_lib ${msw_libs})
        list(APPEND mingw_libs "${msw_link_dir}/${msw_lib}")
    endforeach(msw_lib)
    set(sys_libs comctl32
                 oleaut32
                 ole32
                 uuid
                 winspool)
    target_link_libraries(astylewx ${mingw_libs} ${sys_libs})
    # STRIP RELEASE BUILDS
    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        add_custom_command(TARGET astylewx POST_BUILD
                           COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:astylewx>)
    endif()
endif()
