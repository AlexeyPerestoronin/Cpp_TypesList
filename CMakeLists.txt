cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_CPP_STANDART "cxx_std_11")
set(PROJECT_NAME "TypesListProject")
set(LIB_NAME "TypesList")

project(${PROJECT_NAME})

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

include_directories(./)

add_subdirectory(./tests)
