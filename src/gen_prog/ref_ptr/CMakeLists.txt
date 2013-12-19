# gen_prog build definition
# Copyright David Callu 2013
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)


set(TARGET_NAME ref_ptr)

#------------------------------------------------------------------------------
# define header files
#------------------------------------------------------------------------------

set(REF_PTR_INCLUDE_DIR ${GEN_PROG_DIR}/include/gen_prog/ref_ptr)

set(REF_PTR_HEADER
        ${REF_PTR_INCLUDE_DIR}/config.cpp
        ${REF_PTR_INCLUDE_DIR}/observer.cpp
        ${REF_PTR_INCLUDE_DIR}/observer_ptr.cpp
        ${REF_PTR_INCLUDE_DIR}/ref_ptr.cpp
        ${REF_PTR_INCLUDE_DIR}/referenced.cpp
        ${REF_PTR_INCLUDE_DIR}/referenced_definition.cpp
        ${REF_PTR_INCLUDE_DIR}/referenced_fwd.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/delete_handler/no_delete_handler.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/delete_handler/local_delete_handler.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/delete_handler/static_delete_handler.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/thread/boost_atomic.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/thread/boost_mutex.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/thread/single_thread.cpp
        ${REF_PTR_INCLUDE_DIR}/policy/thread/std_atomic.cpp)

#------------------------------------------------------------------------------
# install command
#------------------------------------------------------------------------------
#install_library( ${TARGET_NAME} INCLUDE_DIRS ${REF_PTR_INCLUDE_DIR})
