cmake_minimum_required(VERSION 3.0)

set(This IJCDU2)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#target_compile_options(${This} -Wall -Werror)

enable_testing()

add_subdirectory(googletest)

set(Headers
        to_be_tested.h
        )
set(Sources
        tail.c
        )

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)