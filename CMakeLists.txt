cmake_minimum_required(VERSION 3.8)
project(ijc_tests)

include(GoogleTest.cmake)

# Test targets
enable_testing()

add_executable(htab_test
        htab_tests.cpp

        # list your htab .c files here
        #htab-header.h
        htab.h
        htab_priv.h
        htab_bucket_count.c
        htab_find.c
        htab_for_each.c
        htab_hash_function.c
        htab_init.c
        htab_lookup_add.c
        htab_size.c
        htab_clear.c htab_erase.c htab_free.c htab_move.c)

add_executable(tekno_test
        htab_test.cpp

        # list your htab .c files here
        #htab-header.h
        htab_priv.h
        htab.h
        htab_bucket_count.c
        htab_find.c
        htab_for_each.c
        htab_hash_function.c
        htab_init.c
        htab_lookup_add.c
        htab_size.c
        htab_clear.c htab_erase.c htab_free.c htab_move.c)
add_executable(wordcount
        io.h
        htab.h
        wordcount.c
        io.c
        libhtab.a)

target_link_libraries(htab_test gtest_main)
target_link_libraries(tekno_test gtest_main)
GTEST_ADD_TESTS(htab_test "" htab_tests.cpp)
GTEST_ADD_TESTS(tekno_test "" htab_test.cpp)
