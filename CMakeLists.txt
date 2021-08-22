cmake_minimum_required(VERSION 3.0)
project(buildwatch VERSION 0.0.1 LANGUAGES C
        DESCRIPTION "Build System Debugger")

set(CMAKE_C_STANDARD 11)

include(CheckIncludeFiles)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

enable_testing()

add_executable(buildwatch_exec src/main.c)

check_include_files("linux/ptrace.h" HAVE_LINUX_PTRACE_H)
include(${CMAKE_SOURCE_DIR}/cmake/tools.cmake)