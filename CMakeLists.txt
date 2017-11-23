cmake_minimum_required(VERSION 3.8)
project(booky)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/sqlite3.c src/Storage.cpp src/Storage.h)

add_executable(booky ${SOURCE_FILES})

target_link_libraries(booky m pthread dl)

target_compile_options(booky PRIVATE -Wall -pedantic -O3)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    target_compile_options(booky PRIVATE -g)
endif()
