if(WIN32)
    # Set Windows file name from 'astylewx'
    set_property(TARGET astylewx PROPERTY OUTPUT_NAME AStyleWx)
    if(MINGW)
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
        find_package(wxWidgets COMPONENTS adv aui stc core base scintilla)
        if(NOT wxWidgets_FOUND)
            set(err_wx "Use '-DWXWIN=<wxWidgets Directory>' to define the wxWidgets path")
            message(FATAL_ERROR ${err_wx})
        endif()
        # SET OPTIONS
        include(${wxWidgets_USE_FILE})
        target_compile_options(astylewx PRIVATE ${compile_options})
        target_include_directories(astylewx PRIVATE src
                                                    dialog
                                                    image)
        add_definitions(-DASTYLE_LIB)
        # LINK LIBRARIES
        if(WXSHARED)
            # using DLLs requires a custom build replaccing gcc_lib with gcc_dll
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
            ## message(( STATUS "MINGW_LIBS: ${mingw_libs}")        # for testing
            target_link_libraries(astylewx ${mingw_libs})
        else()
            # use static linking
            # UxTheme is not included in the cmake link libraries, so it is added here
            target_link_libraries(astylewx ${wxWidgets_LIBRARIES} "UxTheme")
        endif()
        # STRIP RELEASE BUILDS
        if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
            add_custom_command(TARGET astylewx POST_BUILD
                            COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:astylewx>)
        endif()
    endif()
endif()
