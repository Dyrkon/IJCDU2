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
        to_be_testedC.h
        to_be_tested_Cplus.h)
set(Sources1
        tail.c
        )

set(Sources2
        wordcountPlus.cc
        )

set(Sources3
        wordcount.c
        io.c)

add_library(${This}Tail STATIC ${Sources1} ${Headers})

add_library(${This}wcPlus STATIC ${Sources2} ${Headers})

add_library(${This}wcC STATIC ${Sources3} ${Headers})

add_subdirectory(tests)