cmake_minimum_required(VERSION 3.22)
project(serialib)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_STATIC "Enable building static library" ON)
option(BUILD_SHARED "Enable building shared library" ON)
option(BUILD_EXAMPLES "Enable building examples" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include_directories(include)
file(GLOB LIB_SOURCES
    "lib/serialib.h"
    "lib/serialib.cpp"
)

IF(MSVC)
    set(CMAKE_CXX_FLAGS "/O2 /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/W4")
ELSE()
    set(CMAKE_CXX_FLAGS "-O3 -march=native -flto -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic")
ENDIF()

IF(BUILD_SHARED)
    add_library(serialib SHARED ${LIB_SOURCES})
ENDIF ()

IF(BUILD_STATIC)
    add_library(serialib_static STATIC ${LIB_SOURCES})
    set_target_properties(serialib_static PROPERTIES OUTPUT_NAME serialib)
ENDIF()

IF (BUILD_EXAMPLES)
    file(GLOB EXAMPLE1
        "lib/serialib.h"
        "example1/main.cpp"
    )
    add_executable(example1 ${EXAMPLE1})
    target_link_libraries(example1 serialib)

    file(GLOB EXAMPLE2
        "lib/serialib.h"
        "example2/main.cpp"
    )
    add_executable(example2 ${EXAMPLE2})
    target_link_libraries(example2 serialib)

    file(GLOB EXAMPLE3
        "lib/serialib.h"
        "example3/main.cpp"
    )
    add_executable(example3 ${EXAMPLE3})
    target_link_libraries(example3 serialib)

    file(GLOB EXAMPLE4
        "lib/serialib.h"
        "example4/main.cpp"
    )
    add_executable(example4 ${EXAMPLE4})
    target_link_libraries(example4 serialib)

    file(GLOB EXAMPLE5
        "lib/serialib.h"
        "example5/main.cpp"
    )
    add_executable(example5 ${EXAMPLE5})
    target_link_libraries(example5 serialib)
ENDIF()
