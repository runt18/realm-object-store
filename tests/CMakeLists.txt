include_directories(../external/catch/single_include .)

set(HEADERS
    util/event_loop.hpp
    util/index_helpers.hpp
    util/test_file.hpp
)

set(SOURCES
    collection_change_indices.cpp
    handover.cpp
    index_set.cpp
    list.cpp
    main.cpp
    migrations.cpp
    object_store.cpp
    parser.cpp
    realm.cpp
    results.cpp
    schema.cpp
    transaction_log_parsing.cpp
    util/event_loop.cpp
    util/test_file.cpp
)

if(REALM_ENABLE_SYNC)
    list(APPEND HEADERS
        sync/sync_test_utils.hpp
    )
    list(APPEND SOURCES 
        sync/file.cpp
        sync/metadata.cpp
        sync/session.cpp
        sync/sync_manager.cpp
        sync/sync_test_utils.cpp
        sync/user.cpp
    )
endif()

add_executable(tests ${SOURCES} ${HEADERS})
target_compile_definitions(tests PRIVATE ${PLATFORM_DEFINES})

if(REALM_ENABLE_SYNC)
    # It's necessary to explicitly link to realm-sync here to control the order in which libraries are
    # linked to avoid link errors when using GNU ld.
    target_link_libraries(tests realm-sync realm-sync-server)
endif()

target_link_libraries(tests realm-object-store ${PLATFORM_LIBRARIES})

create_coverage_target(generate-coverage tests)

add_custom_target(run-tests USES_TERMINAL DEPENDS tests COMMAND ./tests)

add_subdirectory(notifications-fuzzer)
