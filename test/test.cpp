#include "../math_functions_2.cpp"
#include <gtest/gtest.h>
 
TEST(MaxBetweenTwoNumbersTest, num) 
    { 
    ASSERT_EQ(6.0, max_between_two_numbers(3.0, 6.0));
    ASSERT_EQ(18.0, max_between_two_numbers(18.0, 7.0));
    ASSERT_EQ(25.4, max_between_two_numbers(25.4, 15.4));
    ASSERT_EQ(2.0, max_between_two_numbers(1.0, 2.0));
    }

TEST(MinBetweenThreeNumbersTest, num) 
    { 
    ASSERT_EQ(3.0, min_between_three_numbers(3.0, 6.0, 4.0));
    ASSERT_EQ(7.0, min_between_three_numbers(18.0, 7.0, 45.0));
    ASSERT_EQ(25.4, min_between_three_numbers(25.4, 35.4, 80.0));
    ASSERT_EQ(2.0, min_between_three_numbers(4.0, 2.0, 7.9));
    }

TEST(MinIndexBetweenThreeNumbersTest, num) 
    { 
    ASSERT_EQ(0, min_index_between_three_numbers(3.0, 6.0, 4.0));
    ASSERT_EQ(1, min_index_between_three_numbers(18.0, 7.0, 45.0));
    ASSERT_EQ(0, min_index_between_three_numbers(25.4, 35.4, 80.0));
    ASSERT_EQ(1, min_index_between_three_numbers(4.0, 2.0, 7.9));
    }

TEST(EuclideanDistTest, num) 
    { 
    ASSERT_EQ(3, euclidean_dist(3.0, 6.0));
    ASSERT_EQ(11, euclidean_dist(18.0, 7.0));
    ASSERT_EQ(10, euclidean_dist(25.4, 35.4));
    ASSERT_EQ(2, euclidean_dist(4.0, 2.0));
    }
 
int main(int argc, char **argv) 
    {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }

