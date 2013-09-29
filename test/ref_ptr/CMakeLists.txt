set(TARGET_NAME smart_ptr_test)

#------------------------------------------------------------------------------
# include dependancies
#------------------------------------------------------------------------------
include_directories(${Boost_INCLUDE_DIRS})



add_definitions(-DBOOST_TEST_DYN_LINK)


set(Min_Boost_Version_For_Thread "1.25.0")
set(Min_Boost_Version_For_Atomic "1.53.0")

if(Boost_VERSION VERSION_EQUAL Min_Boost_Version_For_Thread OR Boost_VERSION VERSION_GREATER Min_Boost_Version_For_Thread)
    add_definitions(-DGEN_PROG__BOOST_THREAD_AVAILABLE)
endif()


if(Boost_VERSION VERSION_EQUAL Min_Boost_Version_For_Atomic OR Boost_VERSION VERSION_GREATER Min_Boost_Version_For_Atomic)
    add_definitions(-DGEN_PROG__BOOST_ATOMIC_AVAILABLE)
endif()


if(GEN_PROG__USE_CXX11)
    add_definitions(-DGEN_PROG__CXX11_AVAILABLE)
endif()


#------------------------------------------------------------------------------
# define header and source files
#------------------------------------------------------------------------------

set(REF_PTR_TEST_SRC
        accessor.cpp
        constructor.cpp
        complex.cpp
        destructor.cpp
        manipulator.cpp)

#------------------------------------------------------------------------------
# build commands
#------------------------------------------------------------------------------
add_executable( ${TARGET_NAME} ${REF_PTR_TEST_SRC} )


target_link_libraries( ${TARGET_NAME} ${Boost_LIBRARIES} )


#------------------------------------------------------------------------------
# install command
#------------------------------------------------------------------------------
#install_library( ${TARGET_NAME} INCLUDE_DIRS ${OSGEXPLORER_INCLUDE_DIR} INSTALL_PDB TRUE )
