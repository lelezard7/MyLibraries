#include "ONF.h"

#include <gtest/gtest.h>

using namespace ONF;


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(CommonTest, onf_abs)
{
    EXPECT_EQ(onf_abs(100000), 100000);
    EXPECT_EQ(onf_abs(50000), 50000);
    EXPECT_EQ(onf_abs(1000), 1000);
    EXPECT_EQ(onf_abs(10), 10);
    EXPECT_EQ(onf_abs(1), 1);
    EXPECT_EQ(onf_abs(0), 0);
    EXPECT_EQ(onf_abs(-1), 1);
    EXPECT_EQ(onf_abs(-10), 10);
    EXPECT_EQ(onf_abs(-1000), 1000);
    EXPECT_EQ(onf_abs(-50000), 50000);
    EXPECT_EQ(onf_abs(-100000), 100000);

    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(100000)), 100000.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(50000)), 50000.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(1000)), 1000.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(10)), 10.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(1)), 1.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(0)), 0.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(-1)), 1.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(-10)), 10.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(-1000)), 1000.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(-50000)), 50000.0);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<float>(-100000)), 100000.0);

    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(100000.065)), 100000.065);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(50000.0001)), 50000.0001);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(1000.44)), 1000.44);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(10.9)), 10.9);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(1.1)), 1.1);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(0.3)), 0.3);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(-1.1)), 1.1);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(-10.9)), 10.9);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(-1000.44)), 1000.44);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(-50000.0001)), 50000.0001);
    EXPECT_FLOAT_EQ(onf_abs(static_cast<double>(-100000.065)), 100000.065);
}

TEST(IdManagerTest, isStandardId)
{
    EXPECT_TRUE(isStandardId( 10, 0, 1));
    EXPECT_TRUE(isStandardId( 1,  0, 1));
    EXPECT_TRUE(isStandardId( 0,  0, 1));
    EXPECT_TRUE(isStandardId(-1,  0, 1));
    EXPECT_TRUE(isStandardId(-5,  0, 1));


    EXPECT_FALSE(isStandardId( 10.0, 0.0, 1.5));
    EXPECT_TRUE (isStandardId( 1.5,  0.0, 1.5));
    EXPECT_TRUE (isStandardId( 0.0,  0.0, 1.5));
    EXPECT_FALSE(isStandardId( 1.1,  0.0, 1.5));
    EXPECT_TRUE (isStandardId(-3.0,  0.0, 1.5));
    EXPECT_TRUE (isStandardId(-10.5, 0.0, 1.5));
    EXPECT_FALSE(isStandardId( 8.3,  0.0, 1.5));

    EXPECT_FALSE(isStandardId( 10.0, 0.0, -1.5));
    EXPECT_TRUE (isStandardId( 1.5,  0.0, -1.5));
    EXPECT_TRUE (isStandardId( 0.0,  0.0, -1.5));
    EXPECT_FALSE(isStandardId( 1.1,  0.0, -1.5));
    EXPECT_TRUE (isStandardId(-3.0,  0.0, -1.5));
    EXPECT_TRUE (isStandardId(-10.5, 0.0, -1.5));
    EXPECT_FALSE(isStandardId( 8.3,  0.0, -1.5));


    EXPECT_FALSE(isStandardId( 10.0, 2.0, 1.5));
    EXPECT_TRUE (isStandardId( 11.0, 2.0, 1.5));
    EXPECT_TRUE (isStandardId( 3.5,  2.0, 1.5));
    EXPECT_TRUE (isStandardId( 2.0,  2.0, 1.5));
    EXPECT_FALSE(isStandardId( 0.0,  2.0, 1.5));
    EXPECT_TRUE (isStandardId(-1.0,  2.0, 1.5));
    EXPECT_TRUE (isStandardId(-10.0, 2.0, 1.5));
    EXPECT_TRUE (isStandardId(-2.5,  2.0, 1.5));
    EXPECT_FALSE(isStandardId(-11.0, 2.0, 1.5));

    EXPECT_FALSE(isStandardId( 10.0, 2.0, -1.5));
    EXPECT_TRUE (isStandardId( 11.0, 2.0, -1.5));
    EXPECT_TRUE (isStandardId( 3.5,  2.0, -1.5));
    EXPECT_TRUE (isStandardId( 2.0,  2.0, -1.5));
    EXPECT_FALSE(isStandardId( 0.0,  2.0, -1.5));
    EXPECT_TRUE (isStandardId(-1.0,  2.0, -1.5));
    EXPECT_TRUE (isStandardId(-10.0, 2.0, -1.5));
    EXPECT_TRUE (isStandardId(-2.5,  2.0, -1.5));
    EXPECT_FALSE(isStandardId(-11.0, 2.0, -1.5));


    EXPECT_FALSE(isStandardId( 10.0, -1.5, 1.5));
    EXPECT_TRUE (isStandardId( 10.5, -1.5, 1.5));
    EXPECT_TRUE (isStandardId( 0.0,  -1.5, 1.5));
    EXPECT_TRUE (isStandardId(-1.5,  -1.5, 1.5));
    EXPECT_FALSE(isStandardId( 1.0,  -1.5, 1.5));
    EXPECT_TRUE (isStandardId(-3.0,  -1.5, 1.5));
    EXPECT_TRUE (isStandardId(-12.0, -1.5, 1.5));
    EXPECT_TRUE (isStandardId(-7.5,  -1.5, 1.5));
    EXPECT_FALSE(isStandardId(-13.1, -1.5, 1.5));

    EXPECT_FALSE(isStandardId( 10.0, -1.5, -1.5));
    EXPECT_TRUE (isStandardId( 10.5, -1.5, -1.5));
    EXPECT_TRUE (isStandardId( 0.0,  -1.5, -1.5));
    EXPECT_TRUE (isStandardId(-1.5,  -1.5, -1.5));
    EXPECT_FALSE(isStandardId( 1.0,  -1.5, -1.5));
    EXPECT_TRUE (isStandardId(-3.0,  -1.5, -1.5));
    EXPECT_TRUE (isStandardId(-12.0, -1.5, -1.5));
    EXPECT_TRUE (isStandardId(-7.5,  -1.5, -1.5));
    EXPECT_FALSE(isStandardId(-13.1, -1.5, -1.5));
}
