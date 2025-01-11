add_executable(ntrip-logging
    src/ntrip_logging.cc
)
target_link_libraries(ntrip-logging
    PRIVATE gnss-utilities utilities
)
