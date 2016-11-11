#include "deque.h"

#include <gtest/gtest.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <deque>

class TestDequeFixture : public ::testing::Test {
protected:

    Deque<int> dq;
    std::deque<int> std_dq;

    const int CONTAINER_SIZE = (int)1e4;

    void SetUp() {
        srand(time(NULL));
    }

    void PushBackRandomElement() {
        int val = rand();
        dq.push_back(val);
        std_dq.push_back(val);
    }

    void PushFrontRandomElement() {
        int val = rand();
        dq.push_front(val);
        std_dq.push_front(val);
    }

    void PopFrontElement() {
        dq.pop_front();
        std_dq.pop_front();
    }

    void PopBackElement() {
        dq.pop_back();
        std_dq.pop_back();
    }

    bool AreEqual() {
        for (int i = 0; i < std_dq.size(); ++i) {
            if (std_dq[i] != dq[i])
                return false;
        }
        return true;
    }

    void FillWithRandomElements() {
        for (int i = 0; i < CONTAINER_SIZE; ++i) {
            PushBackRandomElement();
        }
    }

    void TearDown() {
        dq.clear();
    }

};

// Container tests

TEST_F(TestDequeFixture, test_brackets) {
    FillWithRandomElements();
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        ASSERT_EQ(std_dq[i], dq[i]);
    }
}

TEST_F(TestDequeFixture, test_push_back_push_front) {
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() :  PushFrontRandomElement();
        ASSERT_TRUE(AreEqual());
    }
}

TEST_F(TestDequeFixture, test_pop_back_pop_front) {
    FillWithRandomElements();
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PopBackElement() : PopFrontElement();
        ASSERT_TRUE(AreEqual());
    }
}

TEST_F(TestDequeFixture, test_back_front) {
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() :  PushFrontRandomElement();
        ASSERT_EQ(std_dq.back(), dq.back());
        ASSERT_EQ(std_dq.front(), dq.front());
    }
}

TEST_F(TestDequeFixture, test_capacity) {
    ASSERT_EQ(std_dq.size(), dq.size());
    ASSERT_EQ(std_dq.empty(), dq.empty());
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() : PushFrontRandomElement();
        ASSERT_EQ(std_dq.size(), dq.size());
        ASSERT_EQ(std_dq.empty(), dq.empty());
    }
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PopBackElement() : PopFrontElement();
        ASSERT_EQ(std_dq.size(), dq.size());
        ASSERT_EQ(std_dq.empty(), dq.empty());
    }
    ASSERT_EQ(std_dq.size(), dq.size());
    ASSERT_EQ(std_dq.empty(), dq.empty());
}

TEST_F(TestDequeFixture, test_shink_to_fit) {
    ASSERT_EQ(std_dq.size(), dq.size());
    ASSERT_EQ(std_dq.empty(), dq.empty());
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PushBackRandomElement() : PushFrontRandomElement();
        dq.shink_to_fit();
        ASSERT_TRUE(AreEqual());
        ASSERT_EQ(std_dq.size(), dq.size());
        ASSERT_EQ(std_dq.empty(), dq.empty());
    }
    for (int i = 0; i < CONTAINER_SIZE; ++i) {
        rand() % 2 ? PopBackElement() : PopFrontElement();
        dq.shink_to_fit();
        ASSERT_TRUE(AreEqual());
        ASSERT_EQ(std_dq.size(), dq.size());
        ASSERT_EQ(std_dq.empty(), dq.empty());
    }
    ASSERT_EQ(std_dq.size(), dq.size());
    ASSERT_EQ(std_dq.empty(), dq.empty());
}