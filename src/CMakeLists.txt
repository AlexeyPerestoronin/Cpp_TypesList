cmake_minimum_required(VERSION 3.1.0)

project(TypeLists)

include_directories(./)

file(GLOB HPP_FILES "./*.hpp")
file(GLOB CPP_FILES "./*.cpp")

add_library(${PROJECT_NAME} STATIC ${HPP_FILES} ${CPP_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE ${PROJECT_CPP_STANDART})
