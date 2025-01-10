add_library(gnss-utilities
  src/ntrip_client.cc
  src/base64.cc
)
target_include_directories(gnss-utilities
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)
target_link_libraries(gnss-utilities
  PRIVATE utilities
)

if(gnss-utilities_TESTING_ENABLED)
  add_executable(unit-test-gnss-utilities
    test/test_ntrip_client.cc
  )
  target_link_libraries(unit-test-gnss-utilities
    PUBLIC gnss-utilities gtest gtest_main
  )
  add_test(NAME unit-test-gnss-utilities COMMAND unit-test-gnss-utilities)
endif()
