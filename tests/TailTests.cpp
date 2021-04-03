#include "gtest/gtest.h"
#include <cstdio>

extern "C" {
    #include "../to_be_testedC.h"
}

// For stdin testing system("stdinSim.sh");

class TailTest : public ::testing::Test {
protected:
    virtual void SetUp()
    {

    }
    char const *filename_correct = "/home/dyrkon/code/C/IJC/IJCDU2/tests/test.txt";
    char const *filename_incorrect = "test1.txt";
    char const *stdinSim = "/home/dyrkon/code/C/IJC/IJCDU2/tests/stdinSim.sh";
    const char *argv_correct1[10] = {
            "tail",
            "-n",
            "3",
            filename_correct
    };
    const char *argv_correct2[10] = {
            "tail",
            "-n",
            "-3",
            filename_correct,
    };
    const char *argv_correct3[10] = {
            "tail",
            "-n",
            "6000",
            filename_correct
    };
    const char *argv_correct4[10] = {
            "tail",
            filename_correct
    };
    const char *argv_correct5[10] = {
            "tail",
            "-n",
            "5"
    };
    const char *argv_incorrect1[10] = {
            "tail"
    };
    const char *argv_incorrect2[10] = {
            "tail"
            "-n"
    };
};


TEST_F(TailTest, CorrectParamTest)
{
    EXPECT_NO_FATAL_FAILURE(start_tail(4, const_cast<char **>(argv_correct1)));
    EXPECT_NO_FATAL_FAILURE(start_tail(4, const_cast<char **>(argv_correct2)));
    EXPECT_NO_FATAL_FAILURE(start_tail(4, const_cast<char **>(argv_correct3)));
    EXPECT_NO_FATAL_FAILURE(start_tail(2, const_cast<char **>(argv_correct4)));
    //system(stdinSim);
    //EXPECT_NO_FATAL_FAILURE(start_tail(3, const_cast<char **>(argv_correct5)));
}

TEST_F(TailTest, IncorrectParamTest)
{
    EXPECT_EQ(start_tail(1, const_cast<char **>(argv_correct4)), 1);
    EXPECT_EQ(start_tail(5, const_cast<char **>(argv_correct4)), 1);
    EXPECT_EQ(start_tail(5, NULL), 1);
    EXPECT_EQ(start_tail(-5, const_cast<char **>(argv_correct4)), 1);
}
