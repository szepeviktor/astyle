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
    find_package(wxWidgets COMPONENTS adv aui core stc)
    if(NOT wxWidgets_FOUND)
        set(err_wx " Use 'wx-config --list' to check available configurations")
        message(FATAL_ERROR ${err_wx})
    endif()
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
endif()
