cmake_minimum_required(VERSION 3.0)

set(This IJCDU2Tests)

project(${This} C CXX)

set(Sources
        TailTests.cpp
        )

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
        gtest_main
        IJCDU2
        )

add_test(
        NAME ${This}
        COMMAND ${This}
)