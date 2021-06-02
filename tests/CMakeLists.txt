cmake_minimum_required(VERSION 3.1.0)

set(UNIT_TESTS_EXE_NAME ${LIB_NAME}-unit-tests)

project(${UNIT_TESTS_EXE_NAME} NONE)

include_directories(../)


# brief: add Google tests to current test-project
# note1: the google tests project downloads from its git-repository and builds before building the test-protect
# note2: if google tests has been download and build early it not be do again
function(AddGoogleTests)
    if(TARGET GTest::gtest_main AND TARGET GTest::gmock_main)
        message(INFO "GTest and GMock is already downloaded, build and loaded")
        return()
    endif()

    # this technique from: https://crascit.com/2015/07/25/cmake-gtest/
    configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/tests/googletest-download/CMakeLists.txt)

    execute_process(
        COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download"
    )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download"
    )

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds the following targets:
    # gtest, gtest_main, gmock and gmock_main
    add_subdirectory(
        ${CMAKE_BINARY_DIR}/tests/googletest-src
        ${CMAKE_BINARY_DIR}/tests/googletest-build
    )

    # The gtest/gmock targets carry header search path dependencies
    # automatically when using CMake 2.8.11 or later. Otherwise we
    # have to add them here ourselves.
    if(CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include"
                            "${gmock_SOURCE_DIR}/include"
        )
    endif()
endfunction(AddGoogleTests)


# brief: creates unit tests as one test project
function(AddUnitTests)
    file(GLOB TESTS_FILES_HPP "./test-*.hpp")

    # unit-test file template
    file(GLOB UNIT_TESTS_FILES_CPP "./test-unit-*.cpp")

    add_executable(${UNIT_TESTS_EXE_NAME} ${UNIT_TESTS_FILES_CPP} ${TESTS_FILES_HPP})
    target_compile_features(${UNIT_TESTS_EXE_NAME} PRIVATE ${PROJECT_CPP_STANDART})
    # target_link_libraries(${UNIT_TESTS_EXE_NAME} ${LIB_NAME})
    target_link_libraries(${UNIT_TESTS_EXE_NAME} GTest::gtest_main)
    target_link_libraries(${UNIT_TESTS_EXE_NAME} GTest::gmock_main)
endfunction(AddUnitTests)


# brief: creates suit tests
# note1: one suit test is creates from one code file and presents as unique project
function(AddSuitTests)
    file(GLOB TESTS_FILES_HPP "./test-*.hpp")

    # suit-test file template
    file(GLOB SUIT_TESTS_FILES_CPP "./test-suit-*.cpp")

    foreach(SUIT_TEST ${SUIT_TESTS_FILES_CPP})
        get_filename_component(SUIT_TEST_FILE_NAME ${SUIT_TEST} NAME_WE)
        set(SUIT_TEST_EXE_NAME ${LIB_NAME}-${SUIT_TEST_FILE_NAME})
        add_executable(${SUIT_TEST_EXE_NAME} ${SUIT_TEST} ${TESTS_FILES_HPP})
        target_compile_features(${SUIT_TEST_EXE_NAME} PRIVATE ${PROJECT_CPP_STANDART})
        # target_link_libraries(${SUIT_TEST_EXE_NAME} ${LIB_NAME})
        target_link_libraries(${SUIT_TEST_EXE_NAME} GTest::gtest_main)
        target_link_libraries(${SUIT_TEST_EXE_NAME} GTest::gmock_main)
    endforeach()
endfunction(AddSuitTests)


AddGoogleTests()
AddUnitTests()
AddSuitTests()
