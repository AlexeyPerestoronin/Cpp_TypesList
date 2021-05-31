cmake_minimum_required(VERSION 3.1.0)

project(tests)

# GoogleTest: START: https://github.com/google/googletest/tree/master/googletest
# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(./googletest)

# The gtest/gtest_main targets carry header search path dependencies automatically when using CMake 2.8.11 or later. Otherwise we have to add them here ourselves.
include_directories("${gtest_SOURCE_DIR}/include")
# GoogleTest: END.

include_directories(../)

file(GLOB TESTS "./test-unit-*.cpp")

foreach(test ${TESTS})
    get_filename_component(file_basename ${test} NAME_WE)
    add_executable(${file_basename} ${test})
    target_compile_features(${file_basename} PRIVATE ${PROJECT_CPP_STANDART})
    target_link_libraries(${file_basename} gtest_main)
endforeach()
