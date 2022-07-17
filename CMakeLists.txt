cmake_minimum_required(VERSION 3.22)
project(inamorata)

set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

# 3rd-party libs
add_subdirectory(libs)

# Sources
set(SOURCES
    include/${PROJECT_NAME}/validator.h
    src/validator.cpp
)

# Tests
set(TARGETS ${PROJECT_NAME})

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPERCASED)
option(${PROJECT_NAME_UPPERCASED}_BUILD_TESTS "${PROJECT_NAME}: Build tests" ${MAIN_PROJECT})
set(BUILD_TESTS ${${PROJECT_NAME_UPPERCASED}_BUILD_TESTS})

if(BUILD_TESTS)
    set(TEST_TARGET ${PROJECT_NAME}_test)
    list(APPEND TARGETS ${TEST_TARGET})

    enable_testing()
    add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

    add_executable(${TEST_TARGET} ${SOURCES})

    target_link_libraries(${TEST_TARGET}
        PRIVATE doctest_with_main
        PRIVATE yaml-cpp
    )
endif()

# Library
add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE doctest
    PRIVATE yaml-cpp
)

# Compile options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")

    set(TARGET_COMPILE_OPTIONS
        -Wall
        -Wextra
        -Werror
        -Wpedantic
        -pedantic-errors
        -pedantic
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(TARGET_COMPILE_OPTIONS /W4 /WX /utf-8)
endif()

# Target properties
set(TARGET_PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

foreach(TARGET ${TARGETS})
    target_include_directories(${TARGET} PUBLIC include)

    target_compile_options(${TARGET} PRIVATE ${TARGET_COMPILE_OPTIONS})
    set_target_properties(${TARGET} PROPERTIES ${TARGET_PROPERTIES})
endforeach()
