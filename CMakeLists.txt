cmake_minimum_required(VERSION 3.0)
project(buildwatch VERSION 0.0.1 LANGUAGES C
        DESCRIPTION "Build System Debugger")

set(CMAKE_C_STANDARD 11)

include(CheckIncludeFiles)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

enable_testing()

add_executable(buildwatch src/main.c)

include(${CMAKE_SOURCE_DIR}/cmake/tools.cmake)

check_include_files("getopt.h" HAVE_GETOPT_H)
check_include_files("linux/ptrace.h" HAVE_LINUX_PTRACE_H)

if(NOT HAVE_GETOPT_H)
    message(FATAL_ERROR "dependency getopt not found")
endif()
if(NOT HAVE_LINUX_PTRACE_H)
    message(FATAL_ERROR "dependency ptrace not found")
endif()

