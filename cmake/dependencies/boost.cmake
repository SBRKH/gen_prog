set( gen_prog_Boost_VERSION
    1.61.0
    )

set( gen_prog_Boost_COMPONENTS
    filesystem
    log
    system
    thread
    )

hunter_add_package(
    Boost
    COMPONENTS
        ${gen_prog_Boost_COMPONENTS}
    )

if(HUNTER_ENABLED)
    set(FIND_PACKAGE_MODE CONFIG)
endif()

find_package(
    Boost
        ${gen_prog_Boost_VERSION}
    REQUIRED
    COMPONENTS
        ${gen_prog_Boost_COMPONENTS}
    ${FIND_PACKAGE_MODE}
    )
