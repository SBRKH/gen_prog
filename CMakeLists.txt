# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


#------------------------------------------------------------------------------
# define minimum cmake version
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)


#------------------------------------------------------------------------------
# define project name
#------------------------------------------------------------------------------
project(gen_prog VERSION 0.1.0)


#------------------------------------------------------------------------------
# define policies
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# define CMake Module path
#------------------------------------------------------------------------------
set(
    CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_HOME_DIRECTORY}/cmake
        $ENV{cmut_DIR} )

# cmake's module
include(CMakePrintHelpers)

# cmut's module
include( cmut_define_output_dirs )
include( cmut_define_install_dirs )
include( cmut_win32_use_mp_option )

#------------------------------------------------------------------------------
# find dependancies
#------------------------------------------------------------------------------
find_package(
    Boost
    COMPONENTS
        system)


#------------------------------------------------------------------------------
# define build policies
#------------------------------------------------------------------------------
set(CMAKE_DEBUG_POSTFIX "d")

# define CMAKE_*_OUTPUT_DIRECTORY
cmut_define_output_dirs()
# add option to enable build with all cpu's core when use Visual Studio or nmake
cmut_win32_use_mp_option()


# enable C++11
include( cmut_enable_cxx11 )

# enable warning
include( cmut_enable_warning )

# add include directory for all target
include_directories(${CMAKE_SOURCE_DIR}/include)

#------------------------------------------------------------------------------
# define subdirectories
#------------------------------------------------------------------------------
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()


#------------------------------------------------------------------------------
# define uninstall policies
#------------------------------------------------------------------------------
include(cmut_define_uninstall_target)

