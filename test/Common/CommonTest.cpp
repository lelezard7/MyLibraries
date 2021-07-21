#include "IdManager.h"

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
