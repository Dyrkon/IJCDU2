//
// Created by Miroslav Šafář on 08.04.2021.
//

// including C library from C++ file
extern "C" {
    #include "/home/dyrkon/code/C/IJC/IJCDU2/htab.h"
}

#include "gtest/gtest.h"
#include "htab.h"

// FIXTURES -- Author: Tekno --
#define HTAB_BUCKET_COUNT 20

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
        htab_free(htab);
    }

    htab_t *htab;
};

// for each function, being used in for_each tests
void for_each(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
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
// FIXTURES -- Author: Tekno --

// TESTS -- Author: Miroslav Šafář --

TEST(Htab, Initialization) {
    htab_t *htab;
    ASSERT_NO_THROW(htab = htab_init(HTAB_BUCKET_COUNT));
    ASSERT_TRUE(htab != nullptr);
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
    EXPECT_EQ(htab_size(htab), 0);
    EXPECT_EQ(count_items(htab), 0);
}

TEST_F(HtabEmpty, LookupAdd_SingleKey) {
    htab_pair_t *pair = htab_lookup_add(htab, "key1");
    ASSERT_TRUE(pair != nullptr);
    EXPECT_STREQ(pair->key, "key1");
    EXPECT_EQ(pair->value, 0);
    pair->value++;
    EXPECT_EQ(htab_size(htab), 1);
    EXPECT_EQ(count_items(htab), 1);

    htab_pair_t *pair1 = htab_lookup_add(htab, "key1");
    ASSERT_TRUE(pair1 != nullptr);
    EXPECT_STREQ(pair1->key, "key1");
    EXPECT_EQ(pair1->value, 1);
    EXPECT_EQ(htab_size(htab), 1);
    EXPECT_EQ(count_items(htab), 1);
}

TEST_F(HtabEmpty, LookupAdd_MultipleKeys) {
    htab_pair_t *pair1 = htab_lookup_add(htab, "key1");
    htab_pair_t *pair2 = htab_lookup_add(htab, "key2");
    htab_pair_t *pair3 = htab_lookup_add(htab, "key3");
    htab_pair_t *pair4 = htab_lookup_add(htab, "key1");
    ASSERT_TRUE(pair1 != nullptr);
    ASSERT_TRUE(pair2 != nullptr);
    ASSERT_TRUE(pair3 != nullptr);
    ASSERT_TRUE(pair4 != nullptr);

    EXPECT_NE(pair1, pair2);
    EXPECT_NE(pair1, pair3);
    EXPECT_NE(pair2, pair3);

    EXPECT_EQ(pair1, pair4);

    EXPECT_STREQ(pair1->key, "key1");
    EXPECT_STREQ(pair2->key, "key2");
    EXPECT_STREQ(pair3->key, "key3");

    EXPECT_EQ(htab_size(htab), 3);
    EXPECT_EQ(count_items(htab), 3);

}

TEST_F(HtabEmpty, Find) {
    EXPECT_TRUE(htab_find(htab, "key") == nullptr);
}

TEST_F(HtabEmpty, BucketCount) {
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
}

TEST_F(HtabEmpty, Size) {
    htab_t *new_htab = htab_move(100, htab);
    ASSERT_TRUE(new_htab != nullptr);
    EXPECT_EQ(htab_bucket_count(new_htab), 100);
    EXPECT_EQ(htab_size(new_htab), 0);
    EXPECT_EQ(count_items(new_htab), 0);

    EXPECT_EQ(htab_size(htab), 0);
    EXPECT_EQ(count_items(htab), 0);
}

TEST_F(HtabEmpty, Clear) {
    EXPECT_NO_THROW(htab_clear(htab));
    EXPECT_EQ(htab_size(htab), 0);
    EXPECT_EQ(count_items(htab), 0);
}

TEST_F(HtabEmpty, Move) {
    EXPECT_NO_THROW(htab_clear(htab));
    EXPECT_EQ(htab_size(htab), 0);
    EXPECT_EQ(count_items(htab), 0);
}

TEST_F(HtabFilled, Find) {
    EXPECT_TRUE(htab_find(htab, "key") == nullptr);
    htab_pair_t *pair1 = htab_find(htab, "key1");
    htab_pair_t *pair2 = htab_find(htab, "key2");
    htab_pair_t *pair3 = htab_find(htab, "key3");
    htab_pair_t *pair4 = htab_find(htab, "key1");
    ASSERT_TRUE(pair1 != nullptr);
    ASSERT_TRUE(pair2 != nullptr);
    ASSERT_TRUE(pair3 != nullptr);
    ASSERT_TRUE(pair4 != nullptr);

    EXPECT_NE(pair1, pair2);
    EXPECT_NE(pair2, pair3);
    EXPECT_NE(pair1, pair3);
    EXPECT_EQ(pair1, pair4);
}

TEST_F(HtabFilled, BucketCount) {
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
}

TEST_F(HtabFilled, Size) {
    EXPECT_EQ(htab_size(htab), 3);
}

TEST_F(HtabFilled, Clear) {
    EXPECT_NO_THROW(htab_clear(htab));
    EXPECT_EQ(htab_size(htab), 0);
    EXPECT_EQ(count_items(htab), 0);
}

TEST_F(HtabFilled, Move) {
    int old_size = htab_size(htab);
    htab_t *new_htab = htab_move(100, htab);
    ASSERT_TRUE(new_htab != nullptr);
    EXPECT_EQ(htab_bucket_count(new_htab), 100);
    EXPECT_EQ(htab_size(new_htab), old_size);
    EXPECT_EQ(count_items(new_htab), old_size);

    EXPECT_EQ(htab_size(htab), 0);
    EXPECT_EQ(count_items(htab), 0);
}

