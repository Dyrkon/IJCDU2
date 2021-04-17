// Tekno's htab tests! wohoo

#include <iostream>

// including C library from C++ file
extern "C" {
#include "htab.h"
}

#include "gtest/gtest.h"

#define HTAB_BUCKET_COUNT 20

// empty htabs
class HtabEmpty : public ::testing::Test {
protected:
    HtabEmpty() {
        htab = htab_init(HTAB_BUCKET_COUNT);
    }

    virtual void TearDown() {
        //   htab_free(htab);
    }

    htab_t *htab;
};

// filled htabs
class HtabFilled : public ::testing::Test {
protected:
    HtabFilled() {
        htab = htab_init(HTAB_BUCKET_COUNT);
        htab_lookup_add(htab, "key1");
        htab_lookup_add(htab, "key2");
        htab_lookup_add(htab, "key2");
        htab_lookup_add(htab, "key3");
        htab_lookup_add(htab, "key3");
        htab_lookup_add(htab, "key3");
    }

    virtual void TearDown() {
        //  htab_free(htab);
    }

    htab_t *htab;
};

// for each function, being used in for_each tests
void for_each(htab_pair_t *data) {
    printf("%s\t%s\n", data->value, data->key);
}

static size_t item_count = 0;

void count_items_for_each(htab_pair_t *data) {
    item_count++;
}

size_t count_items(htab_t *htab) {
    item_count = 0;
    htab_for_each(htab, count_items_for_each);
    return item_count;
}

// test htab_init and htab_free
TEST(Htab, Test_lifecycle) {
    htab_t *htab;
    EXPECT_NO_THROW({
                        htab = htab_init(HTAB_BUCKET_COUNT);
                    });
    ASSERT_TRUE(htab != NULL);
    ASSERT_TRUE(htab_bucket_count(htab) == HTAB_BUCKET_COUNT);
    ASSERT_TRUE(htab_size(htab) == 0);

    /*
    EXPECT_NO_THROW({
                        htab_free(htab);
                    });
                    */
}

/**************************************************************************/
/*                            EMPTY HTAB TESTS                            */
/**************************************************************************/

TEST_F(HtabEmpty, Test_lookup_add) {
    EXPECT_TRUE(htab_lookup_add(htab, "key1") != NULL);
}

TEST_F(HtabEmpty, Test_lookup_add_multiple) {
    htab_pair_t *pair1 = htab_lookup_add(htab, "key1");
    EXPECT_EQ(pair1->value, 0);
    htab_pair_t *pair2 = htab_lookup_add(htab, "key1");
    htab_pair_t *pair3 = htab_lookup_add(htab, "key2");
    EXPECT_TRUE(pair1 != NULL);
    EXPECT_TRUE(pair3 != NULL);
    EXPECT_EQ(pair1, pair2);
    EXPECT_NE(pair1, pair3);
    EXPECT_EQ(pair2->value, 0);
    EXPECT_EQ(pair3->value, 0);
}

TEST_F(HtabEmpty, Test_find) {
    EXPECT_TRUE(htab_find(htab, "key1") == NULL);
}

TEST_F(HtabEmpty, Test_size) {
    EXPECT_EQ(htab_size(htab), 0);
}

TEST_F(HtabEmpty, Test_bucket_count) {
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
}


TEST_F(HtabEmpty, Test_erase) {
    EXPECT_FALSE(htab_erase(htab, "key"));
}


TEST_F(HtabEmpty, Test_for_each) {
    EXPECT_NO_THROW({
                        htab_for_each(htab, for_each);
                    });
}

TEST_F(HtabEmpty, Test_move) {
    htab_t *tmp;

    EXPECT_NO_THROW({
                        tmp = htab_move(100, htab);
                        htab_free(htab);

                        htab = htab_move(5, tmp);
                        htab_free(tmp);
                    });
}

TEST_F(HtabEmpty, Test_clear) {
    EXPECT_NO_THROW({
                        htab_clear(htab);
                    });
}


/**************************************************************************/
/*                            FILLED HTAB TESTS                           */
/**************************************************************************/

TEST_F(HtabFilled, Test_find) {
    EXPECT_TRUE(htab_find(htab, "key1") != NULL);
    EXPECT_TRUE(htab_find(htab, "key2") != NULL);
    EXPECT_TRUE(htab_find(htab, "key3") != NULL);
    EXPECT_TRUE(htab_find(htab, "key4") == NULL);
    EXPECT_TRUE(htab_find(htab, "") == NULL);
}

TEST_F(HtabFilled, Test_size) {
    EXPECT_EQ(htab_size(htab), 3);
}

TEST_F(HtabFilled, Test_bucket_count) {
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
}


TEST_F(HtabFilled, Test_erase) {
    EXPECT_EQ(htab_size(htab), 3);
    EXPECT_TRUE(htab_erase(htab, "key1"));

    EXPECT_EQ(htab_size(htab), 2);
    EXPECT_FALSE(htab_erase(htab, "key1"));
    EXPECT_EQ(htab_size(htab), 2);
    EXPECT_TRUE(htab_erase(htab, "key2"));

    EXPECT_EQ(htab_size(htab), 1);
    EXPECT_FALSE(htab_erase(htab, "key4"));
    EXPECT_EQ(htab_size(htab), 1);
    EXPECT_FALSE(htab_erase(htab, ""));
    EXPECT_EQ(htab_size(htab), 1);
}


TEST_F(HtabFilled, Test_for_each) {
    EXPECT_NO_THROW({
                        htab_for_each(htab, for_each);
                    });
}


TEST_F(HtabFilled, Test_move) {
    htab_t *tmp1;
    htab_t *tmp2;

    size_t initial_count = count_items(htab);

    EXPECT_NO_THROW({
                        tmp1 = htab_move(HTAB_BUCKET_COUNT, htab);
                        ASSERT_TRUE(tmp1 != NULL);
                        ASSERT_EQ(initial_count, count_items(tmp1));
                        htab_free(htab);

                        tmp2 = htab_move(HTAB_BUCKET_COUNT * 5, tmp1);
                        ASSERT_TRUE(tmp2 != NULL);
                        ASSERT_EQ(initial_count, count_items(tmp2));
                        htab_free(tmp1);

                        htab = htab_move(HTAB_BUCKET_COUNT / 5, tmp2);
                        ASSERT_TRUE(htab != NULL);
                        ASSERT_EQ(initial_count, count_items(htab));
                        htab_free(tmp2);
                    });
}


TEST_F(HtabFilled, Test_clear) {
    EXPECT_EQ(htab_size(htab), 3);
    EXPECT_NO_THROW({
                        htab_clear(htab);
                    });
    EXPECT_EQ(htab_size(htab), 0);
}

