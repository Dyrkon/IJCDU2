#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../to_be_tested_Cplus.h"
#include <cstdio>
#include <cstdlib>

// #define FILENAME "wordFile.txt"
#define FILENAME "test.txt"

using namespace std;

class NonEmptyMap : public ::testing::Test {
protected:
    virtual void SetUp()
    {
        correct_name = "/home/dyrkon/code/C/IJC/IJCDU2/tests/wordFile.txt";
        incorrect_name = "";
    }
    string correct_name;
    string incorrect_name;
};

class EmptyMap : public ::testing::Test {
protected:
    virtual void SetUp()
    {

    }
    std::vector<char*> words;
};

TEST_F(NonEmptyMap, Asing)
{
    //EXPECT_EQ(1,1);
    IJCDU2model(correct_name);
}