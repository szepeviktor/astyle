# Display build information
message( STATUS "---------- General Configuration ----------" )
message( STATUS )
message( STATUS "CMake Generator:         ${CMAKE_GENERATOR}" )
message( STATUS "CMake Compiler:          ${CMAKE_CXX_COMPILER_ID}" )
# NOTE: dll or not
message( STATUS "AStyleWx Build:          AStyleWx" )
message( STATUS "AStyleWx Configuration:  ${CMAKE_BUILD_TYPE}" )

if(WIN32)
    message( STATUS "wxWidgets Directory:     ${wxWidgets_ROOT_DIR}" )
    message( STATUS "wxWidgets Shared Libs:   ${WXSHARED}" )
else()
    if(DEFINED WX OR DEFINED TK)
        message( STATUS "wx-config Options:       ${wxWidgets_CONFIG_OPTIONS}" )
    else()
        message( STATUS "wx-config Options:       Default" )
    endif()
endif()

message( STATUS )
message( STATUS "-------------------------------------------" )
