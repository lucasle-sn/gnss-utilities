add_executable(ntrip
    src/ntrip.cc
)
target_link_libraries(ntrip
    PRIVATE gnss-utilities utilities
)
