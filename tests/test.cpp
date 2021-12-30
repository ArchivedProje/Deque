// Copyright byteihq 2021 <kotov038@gmail.com>

#include <Deque.h>
#include <gtest/gtest.h>
#include <string>

TEST(Deque, Constructor) {
    {
        Deque<int> d;
        EXPECT_EQ(d.size(), 0);
        EXPECT_TRUE(d.empty());
    }
    {
        Deque<size_t> d(3, 4);
        EXPECT_EQ(d.size(), 3);
        EXPECT_FALSE(d.empty());
    }
    {
        Deque<char> d(140, 'c');
        EXPECT_EQ(d.size(), 140);
        EXPECT_FALSE(d.empty());
    }
}

TEST(Deque, FrontBack) {
    {
        Deque<float> d(1, 1.75);
        EXPECT_FLOAT_EQ(d.front(), 1.75);
        EXPECT_FLOAT_EQ(d.front(), d.back());
        d.front() = -1.2;
        EXPECT_FLOAT_EQ(d.front(), -1.2);
        EXPECT_FLOAT_EQ(d.front(), d.back());
        d.back() = 0.12;
        EXPECT_FLOAT_EQ(d.front(), 0.12);
        EXPECT_FLOAT_EQ(d.front(), d.back());

        EXPECT_EQ(d.size(), 1);
        EXPECT_FALSE(d.empty());
    }
    {
        Deque<double> d(4, 1.75);
        EXPECT_DOUBLE_EQ(d.front(), 1.75);
        EXPECT_DOUBLE_EQ(d.front(), d.back());
        d.front() = -1.2;
        EXPECT_DOUBLE_EQ(d.front(), -1.2);
        EXPECT_NE(d.front(), d.back());
        d.back() = 0.12;
        EXPECT_DOUBLE_EQ(d.back(), 0.12);
        EXPECT_NE(d.front(), d.back());

        EXPECT_EQ(d.size(), 4);
        EXPECT_FALSE(d.empty());
    }
}

TEST(Deque, Indexing) {
    {
        Deque<unsigned> d(12, 3);
        EXPECT_EQ(d.front(), 3);
        EXPECT_EQ(d.front(), d[0]);
        EXPECT_EQ(d[0], d.at(0));

        EXPECT_EQ(d.back(), 3);
        EXPECT_EQ(d.back(), d[11]);
        EXPECT_EQ(d.back(), d[d.size() - 1]);
        EXPECT_EQ(d[11], d.at(11));

        EXPECT_THROW(d.at(12), std::out_of_range);
        EXPECT_THROW(d.at(100), std::out_of_range);
    }
    {
        Deque<std::string> d(3, "hello world");
        EXPECT_EQ(d.front(), "hello world");
        EXPECT_EQ(d.front(), d[0]);
        EXPECT_EQ(d[0], d.at(0));

        EXPECT_EQ(d.back(), "hello world");
        EXPECT_EQ(d.back(), d[2]);
        EXPECT_EQ(d.back(), d[d.size() - 1]);
        EXPECT_EQ(d.at(2), d[2]);

        d[0] = "not hello";
        EXPECT_EQ(d.front(), "not hello");
        EXPECT_EQ(d.front(), d[0]);
        EXPECT_EQ(d[0], d.at(0));

        d.at(1) = "other phrase";
        EXPECT_EQ(d.front(), "not hello");
        EXPECT_EQ(d[1], "other phrase");
        EXPECT_EQ(d[1], d.at(1));

        EXPECT_EQ(d.back(), "hello world");
        EXPECT_EQ(d.back(), d[2]);
        EXPECT_EQ(d.back(), d[d.size() - 1]);
        EXPECT_EQ(d.at(2), d[2]);

        EXPECT_EQ(d.size(), 3);
        EXPECT_FALSE(d.empty());
    }
}

TEST(Deque, PopBack) {
    {
        Deque<std::string_view> d(1);
        EXPECT_EQ(d.size(), 1);
        EXPECT_FALSE(d.empty());
        d.pop_back();
        EXPECT_EQ(d.size(), 0);
        EXPECT_TRUE(d.empty());
    }
    {
        Deque<long long> d(1000, 20);
        EXPECT_EQ(d.size(), 1000);
        EXPECT_FALSE(d.empty());

        EXPECT_NO_THROW(d.pop_back());
        EXPECT_NO_THROW(d.pop_back());
        EXPECT_EQ(d.front(), 20);
        EXPECT_EQ(d.front(), d.back());
        EXPECT_EQ(d.size(), 998);
        EXPECT_FALSE(d.empty());

        for (size_t i = 0; i < 998; i += 2) {
            d.pop_back();
        }

        EXPECT_EQ(d.size(), 499);
    }
}

TEST(Deque, PushBack) {
    {
        Deque<unsigned int> d;
        EXPECT_EQ(d.size(), 0);
        EXPECT_TRUE(d.empty());

        d.push_back(4);
        EXPECT_EQ(d.size(), 1);
        EXPECT_FALSE(d.empty());
        EXPECT_EQ(d.front(), 4);
        EXPECT_EQ(d.front(), d.back());

        d.push_back(8);
        EXPECT_EQ(d.size(), 2);
        EXPECT_EQ(d.front(), 4);
        EXPECT_EQ(d.back(), 8);
    }
    {
        Deque<char32_t> d(12, 'q');

        d.push_back('w');
        EXPECT_EQ(d.size(), 13);
        EXPECT_EQ(d.front(), 'q');
        EXPECT_EQ(d.back(), 'w');

        d.pop_back();
        EXPECT_EQ(d.size(), 12);
        EXPECT_EQ(d.front(), 'q');
        EXPECT_EQ(d.back(), 'q');
    }
    {
        Deque<uint16_t> d(123, 321);
        for (size_t i = 0; i < 1000; ++i) {
            d.push_back(333);
            d.pop_back();
        }
        EXPECT_EQ(d.size(), 123);
    }
    {
        Deque<uint8_t> d;
        uint8_t value = 3;
        d.push_back(value);
        EXPECT_EQ(d.size(), 1);
        EXPECT_FALSE(d.empty());
        EXPECT_EQ(value, 3);
        EXPECT_EQ(d.front(), value);
        EXPECT_EQ(d.front(), d.back());

        d.push_back(4);
        EXPECT_EQ(value, 3);
        EXPECT_EQ(d.front(), value);
        EXPECT_EQ(d.back(), 4);
    }
}

TEST(Deque, PushFront) {
    {
        Deque<int> d;
        d.push_front(3);
        EXPECT_EQ(d.size(), 1);
        EXPECT_EQ(d.front(), 3);
        EXPECT_EQ(d.front(), d.back());

        d.push_front(2);
        EXPECT_EQ(d.size(), 2);
        EXPECT_EQ(d.front(), 2);
        EXPECT_EQ(d.back(), 3);
    }
    {
        Deque<std::string> d;

        std::string word = "One more test";
        d.push_front(word);
        EXPECT_EQ(word, "One more test");
        EXPECT_EQ(d.front(), word);
        EXPECT_EQ(d.front(), d.back());

        d.push_front("another test");
        EXPECT_EQ(word, "One more test");
        EXPECT_EQ(d.front(), "another test");
        EXPECT_EQ(d.back(), word);
    }
    {
        Deque<long double> d;
        for (size_t i = 0; i < 100; ++i) {
            d.push_front(1);
            d.pop_back();
        }
        EXPECT_EQ(d.size(), 0);
        EXPECT_TRUE(d.empty());
    }
}
