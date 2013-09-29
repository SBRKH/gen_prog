#------------------------------------------------------------------------------
# define minimum cmake version
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)


#------------------------------------------------------------------------------
# define project name
#------------------------------------------------------------------------------
project(gen_prog)
set(GEN_PROG__MAJOR_VERSION 0)
set(GEN_PROG__MINOR_VERSION 1)
set(GEN_PROG__PATCH_VERSION 0)
set(GEN_PROG__SOVERSION 1)


#------------------------------------------------------------------------------
# define policies
#------------------------------------------------------------------------------
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


#------------------------------------------------------------------------------
# define CMake Module path
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_HOME_DIRECTORY}/CMakeModules )
find_package(CMakeModules)

include( install_functions )
include( determine_lib_postfix )
include( output_directory_functions )
include( win32_use_mp_option )
include( CXX11 )


#------------------------------------------------------------------------------
# find dependancies
#------------------------------------------------------------------------------
find_package(Boost COMPONENTS prg_exec_monitor unit_test_framework system)


#------------------------------------------------------------------------------
# define build policies
#------------------------------------------------------------------------------
set(CMAKE_DEBUG_POSTFIX "d")

# define CMAKE_*_OUTPUT_DIRECTORY
define_output_directory()

win32_use_mp_option()


check_for_cxx11_compiler(GEN_PROG__CPP11__SUPPORTED)



if(GEN_PROG__CPP11__SUPPORTED)
    option(GEN_PROG__USE_CXX11 "Enable C++11" 0)
    
    if(GEN_PROG__USE_CXX11)
        enable_cxx11()
    endif()
    
endif()
 
 

if(WIN32)
    if(MSVC)
        add_definitions(-D_USE_MATH_DEFINES)
        add_definitions(-D_SCL_SECURE_NO_WARNINGS)
        add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    endif(MSVC)
endif(WIN32)

IF(UNIX AND NOT WIN32 AND NOT APPLE)
  IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
ENDIF(UNIX AND NOT WIN32 AND NOT APPLE)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
endif()


include_directories(${gen_prog_SOURCE_DIR}/include)
#------------------------------------------------------------------------------
# define subdirectories
#------------------------------------------------------------------------------
#add_subdirectory(src)

if(Boost_FOUND)
	add_subdirectory(test)
endif()


#------------------------------------------------------------------------------
# define uninstall policies
#------------------------------------------------------------------------------
define_uninstall_target()
