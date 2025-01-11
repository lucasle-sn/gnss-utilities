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

# Doxygen setup
if (gnss-utilities_DOXYGEN_BUILD_ENABLED)
  message(STATUS "gnss-utilities doxygen build enabled")
  add_subdirectory(doxygen)
else()
  message(STATUS "gnss-utilities doxygen build disabled")
endif()
