cmake_minimum_required(VERSION 3.11)

project(hello_library)

# library

add_library(
    hello_library
    STATIC
    src/Hello.cpp
)

target_include_directories(
    hello_library
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

include(FetchContent)

FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git)

FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# exe

add_executable(hello_binary 
src/main.cpp
)

target_link_libraries(
    hello_binary
    PRIVATE
    hello_library
)

target_link_libraries(hello_library PRIVATE yaml-cpp)
target_link_libraries(hello_binary PRIVATE yaml-cpp)

