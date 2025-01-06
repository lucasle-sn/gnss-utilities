cmake_minimum_required(VERSION 3.10)
project(gnss-utilities)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(gnss-utilities_TESTING_ENABLED "Enable gnss-utilities testing" OFF)
option(gnss-utilities_DOXYGEN_BUILD_ENABLED "Enable gnss-utilities doxygen build" OFF)

if(gnss-utilities_TESTING_ENABLED)
  message(STATUS "gnss-utilities testing enabled")
  enable_testing()
endif()

message(STATUS "Enable testing")
enable_testing()

add_subdirectory(third_party/gtest)
add_subdirectory(third_party/libcore)
add_subdirectory(gnss_utilities)
add_subdirectory(tools)

# Doxygen setup
if (gnss-utilities_DOXYGEN_BUILD_ENABLED)
  message(STATUS "gnss-utilities doxygen build enabled")
  add_subdirectory(doxygen)
else()
  message(STATUS "gnss-utilities doxygen build disabled")
endif()
