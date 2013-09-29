
#------------------------------------------------------------------------------
# define CMake Module path
#------------------------------------------------------------------------------

find_path( CMAKEMODULES_PATH CMakeModules_signature.cmake
           HINTS $ENV{CMAKEMODULES_DIR}
		   DOC "Path to CMakeModules directory project"
		   NO_DEFAULT_PATH )

if(NOT CMAKEMODULES_PATH)
    if(WIN32)
        set(CMAKEMODULES_PATH C:/SDK/CMakeModules)
    else()
        if(APPLE)
            set(CMAKEMODULES_PATH /opt/local/share/CMakeModules)
        else()
            set(CMAKEMODULES_PATH /usr/local/share/CMakeModules)
        endif()
    endif()
    message(STATUS "define default CMAKEMODULES_PATH, CMAKEMODULES_PATH=${CMAKEMODULES_PATH}")
endif()

if (CMAKEMODULES_PATH AND NOT EXISTS ${CMAKEMODULES_PATH})
	message( FATAL_ERROR "CMAKEMODULES_PATH need to be define to continue." )
endif()



set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKEMODULES_PATH})