set( libunocxx_Boost_VERSION
    1.61.0
    )

set( libunocxx_Boost_COMPONENTS
    filesystem
    log
    system
    thread
    )

hunter_add_package(
    Boost
    COMPONENTS
        ${libunocxx_Boost_COMPONENTS}
    )


find_package(
    Boost
        ${libunocxx_Boost_VERSION}
    REQUIRED COMPONENTS
        ${libunocxx_Boost_COMPONENTS}
    CONFIG
    )
