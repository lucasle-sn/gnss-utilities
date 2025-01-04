cmake_minimum_required(VERSION 3.10)
project(gnss-utilities)

set(CMAKE_C_STANDARD 14)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(DOXYGEN_BUILD_ENABLED "Enable Doxygen Build" OFF)

# Doxygen setup
if (DOXYGEN_BUILD_ENABLED)
  message(STATUS "Doxygen build enabled")
  add_subdirectory(doxygen)
else()
  message(STATUS "Doxygen build disabled")
endif()
