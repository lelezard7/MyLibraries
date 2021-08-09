#include "IdManager.h"

#include <gtest/gtest.h>

using namespace ONF;


template<class T, class T_Step = T>
class OpenRangeIdManager : public RangeIdManager<T, T_Step>
{
public:
    OpenRangeIdManager(T start = 0, T_Step step = 1)
        : RangeIdManager<T, T_Step>(start, step) {};

    OpenRangeIdManager(const OpenRangeIdManager<T, T_Step>& other) = default;
    OpenRangeIdManager(OpenRangeIdManager<T, T_Step>&& other) = default;

    using RangeIdManager<T, T_Step>::getFreeIdsSize;
    using RangeIdManager<T, T_Step>::getReservedIdsSize;

    OpenRangeIdManager<T, T_Step>& operator=(const OpenRangeIdManager<T, T_Step>& other) = default;
    OpenRangeIdManager<T, T_Step>& operator=(OpenRangeIdManager<T, T_Step>&& other) = default;
};

struct OpenRangeIdManagerTests : public ::testing::Test
{
    OpenRangeIdManager<int> OpenRangeIdManager_int;
    OpenRangeIdManager<float> OpenRangeIdManager_float;
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned;

    OpenRangeIdManager<int> OpenRangeIdManager_int_Start_2_Step_2;
    OpenRangeIdManager<float> OpenRangeIdManager_float_Start_1p5_Step_1p5;
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_Start_2_Step_2;

    OpenRangeIdManager<int> OpenRangeIdManager_int_Start_n2_Step_n2;
    OpenRangeIdManager<float, int> OpenRangeIdManager_float_int_Start_n1p5_Step_n2;
    OpenRangeIdManager<unsigned, int> OpenRangeIdManager_unsigned_int_Start_10_Step_n2;

    OpenRangeIdManager<int> OpenRangeIdManager_int_Start_n2_Step_4;
    OpenRangeIdManager<float, int> OpenRangeIdManager_float_int_Start_n2p0_Step_2;

    OpenRangeIdManager<int> OpenRangeIdManager_int_Start_2_Step_n2;
    OpenRangeIdManager<float> OpenRangeIdManager_float_Start_2p0_Step_n2p0;

    OpenRangeIdManagerTests()
        : OpenRangeIdManager_int_Start_2_Step_2(2, 2),
          OpenRangeIdManager_float_Start_1p5_Step_1p5(1.5, 1.5),
          OpenRangeIdManager_unsigned_Start_2_Step_2(2, 2),

          OpenRangeIdManager_int_Start_n2_Step_n2(-2, -2),
          OpenRangeIdManager_float_int_Start_n1p5_Step_n2(-1.5, -2),
          OpenRangeIdManager_unsigned_int_Start_10_Step_n2(10, -2),

          OpenRangeIdManager_int_Start_n2_Step_4(-2, 4),
          OpenRangeIdManager_float_int_Start_n2p0_Step_2(-2.0, 2),

          OpenRangeIdManager_int_Start_2_Step_n2(2, -2),
          OpenRangeIdManager_float_Start_2p0_Step_n2p0(2.0, -2.0) {};

};


TEST_F(OpenRangeIdManagerTests, getStart)
{
    EXPECT_EQ(OpenRangeIdManager_int.getStart(), 0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getStart(), 0.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getStart(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getStart(), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getStart(), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getStart(), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getStart(), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getStart(), -1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getStart(), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getStart(), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getStart(), -2.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getStart(), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getStart(), 2.0);
}

TEST_F(OpenRangeIdManagerTests, getStep)
{
    EXPECT_EQ(OpenRangeIdManager_int.getStep(), 1);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getStep(), 1.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getStep(), 1);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getStep(), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getStep(), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getStep(), -2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getStep(), -2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getStep(), 4);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getStep(), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getStep(), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getStep(), -2.0);
}

TEST_F(OpenRangeIdManagerTests, getBorderValue)
{
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder), -2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -2.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), 2.0);
}

TEST_F(OpenRangeIdManagerTests, size)
{
    EXPECT_EQ(OpenRangeIdManager_int.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 0);
}

TEST_F(OpenRangeIdManagerTests, getBorderState)
{
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, isStandardId)
{
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(0));
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(1));
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(2));
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(10));
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(-1));
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int.isStandardId(-10));

    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(0.0));
    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(1.0));
    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(2.0));
    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(10.0));
    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(-1.0));
    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float.isStandardId(-10.0));
    EXPECT_FALSE(OpenRangeIdManager_float.isStandardId(10.5));
    EXPECT_FALSE(OpenRangeIdManager_float.isStandardId(-10.5));
    EXPECT_FALSE(OpenRangeIdManager_float.isStandardId(-0.5));
    EXPECT_FALSE(OpenRangeIdManager_float.isStandardId(1.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(-1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(-2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isStandardId(-10));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.isStandardId(-20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isStandardId(21));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isStandardId(1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isStandardId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isStandardId(-19));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(3.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(4.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(18.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(-1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(-18.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(19.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(1.501));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isStandardId(-18.001));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(4));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(6));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(20));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(0));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(-20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(21));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(-1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isStandardId(-19));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(-4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(-6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(-20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(21));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isStandardId(-19));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(-1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(0.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(2.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(20.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(-3.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(-5.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(-19.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(19.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(1.501));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isStandardId(-18.001));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(10));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(12));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(14));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(40));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(8));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(6));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(-40));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(21));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(-1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isStandardId(-49));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(22));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(-6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(-10));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(-22));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(21));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isStandardId(-19));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(-4.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(-6.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(19.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(1.501));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isStandardId(-18.001));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(22));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(-22));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(21));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isStandardId(-19));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(4.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(6.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(19.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(1.501));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isStandardId(-18.001));
}

TEST_F(OpenRangeIdManagerTests, getFreeIdsSize)
{
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
}

TEST_F(OpenRangeIdManagerTests, getReservedIdsSize)
{
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);
}

TEST_F(OpenRangeIdManagerTests, GetFreeId)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;


    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(OpenRangeIdManager_int.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 0);


        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);


        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 0.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder), -1.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -1.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder), -2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder), -2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -2.0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder), 2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), 2.0);


        if (i == 1) {
            OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);

            OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

            OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);

            OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

            OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
            OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Ascending);
        }

        if (i == 2) {
            OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Descending);

            OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

            OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);

            OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

            OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
            OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Descending);
        }


        for (int j = 0; j < 22; ++j) {
            optional_id_int = OpenRangeIdManager_int.getFreeId();
            ASSERT_TRUE(optional_id_int.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_int, j)           << "The error occurred when: i == " << i << ", j == " << j;

            optional_id_float = OpenRangeIdManager_float.getFreeId();
            ASSERT_TRUE(optional_id_float.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_FLOAT_EQ(*optional_id_float, j)     << "The error occurred when: i == " << i << ", j == " << j;

            optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
            ASSERT_TRUE(optional_id_unsigned.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_unsigned, j)           << "The error occurred when: i == " << i << ", j == " << j;
        }

        for (int j = 2; j < 22; j += 2) {
            optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
            ASSERT_TRUE(optional_id_int.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_int, j)           << "The error occurred when: i == " << i << ", j == " << j;

            optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
            ASSERT_TRUE(optional_id_unsigned.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_unsigned, j)           << "The error occurred when: i == " << i << ", j == " << j;
        }

        for (float j = 1.5; j < 30.0; j += 1.5) {
            optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
            ASSERT_TRUE(optional_id_float.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_FLOAT_EQ(*optional_id_float, j)     << "The error occurred when: i == " << i << ", j == " << j;
        }

        for (int j = -2; j > -22; j -= 2) {
            optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
            ASSERT_TRUE(optional_id_int.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_int, j)           << "The error occurred when: i == " << i << ", j == " << j;

            optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
            ASSERT_TRUE(optional_id_int.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_int, j + 4)       << "The error occurred when: i == " << i << ", j == " << j;

            optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
            ASSERT_TRUE(optional_id_float.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_FLOAT_EQ(*optional_id_float, j + 4) << "The error occurred when: i == " << i << ", j == " << j;
        }

        for (float j = -2.0; j < 22.0; j += 2.0) {
            optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
            ASSERT_TRUE(optional_id_float.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_FLOAT_EQ(*optional_id_float, j)     << "The error occurred when: i == " << i << ", j == " << j;
        }

        for (int j = -2; j < 44; j += 4) {
            optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
            ASSERT_TRUE(optional_id_int.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_int, j)           << "The error occurred when: i == " << i << ", j == " << j;
        }

        for (int j = 10; j >= 0; j -= 2) {
            optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
            ASSERT_TRUE(optional_id_int.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_EQ(*optional_id_int, j)           << "The error occurred when: i == " << i << ", j == " << j;
        }

        optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
        EXPECT_FALSE(optional_id_int.has_value());

        for (float j = -1.5; j > -22.0; j -= 2.0) {
            optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
            ASSERT_TRUE(optional_id_float.has_value()) << "The error occurred when: i == " << i << ", j == " << j;
            EXPECT_FLOAT_EQ(*optional_id_float, j)     << "The error occurred when: i == " << i << ", j == " << j;
        }


        EXPECT_EQ(OpenRangeIdManager_int.size(), 22);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 22);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 22);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 10);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 19);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 10);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 10);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 12);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 12);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 10);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 10);


        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);


        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));

        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 21);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 21.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 21);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 20);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 28.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 20);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder), -1.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  42);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  20.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -2.0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -16);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -16.0);


        OpenRangeIdManager_int.freeAll();
        OpenRangeIdManager_float.freeAll();
        OpenRangeIdManager_unsigned.freeAll();

        OpenRangeIdManager_int_Start_2_Step_2.freeAll();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.freeAll();
        OpenRangeIdManager_unsigned_Start_2_Step_2.freeAll();

        OpenRangeIdManager_int_Start_n2_Step_n2.freeAll();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeAll();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeAll();

        OpenRangeIdManager_int_Start_n2_Step_4.freeAll();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeAll();

        OpenRangeIdManager_int_Start_2_Step_n2.freeAll();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeAll();
    }
}

TEST_F(OpenRangeIdManagerTests, BorderLimit)
{
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());


    EXPECT_FALSE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder, -300));
    EXPECT_FALSE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder,  300));
    EXPECT_FALSE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder, -300.5));
    EXPECT_FALSE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder,  300.5));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 300));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, -300));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder,  300));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, -300.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder,  300.0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 300));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -300));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder,  300));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::UpperBorder, -300.1));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::LowerBorder,  300.1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::UpperBorder, 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder, 300));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::UpperBorder, -300));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::LowerBorder,  300));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::UpperBorder, -300.9999));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::LowerBorder,  300.9999));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -300));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder,  300));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::UpperBorder, -300.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::LowerBorder,  300.0));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());


    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder,  200));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, -200));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder,  200.5));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, -200.5));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder, 200));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder,  200));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, -200));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder,  200.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -200.0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 200));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  200));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -200));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::UpperBorder,  200.1));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::LowerBorder, -200.1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::UpperBorder, 200));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::UpperBorder,  200));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::LowerBorder, -200));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::UpperBorder,  200.9999));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::LowerBorder, -200.9999));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  200));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -200));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::UpperBorder,  200.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::LowerBorder, -200.0));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  200);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -200);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  200.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -200.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 200);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder),  200);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), -200);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder),  200.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), -200.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 200);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  200);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -200);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::UpperBorder),  200.1);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::LowerBorder), -200.1);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::UpperBorder), 200);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::UpperBorder),  200);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::LowerBorder), -200);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::UpperBorder),  200.9999);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::LowerBorder), -200.9999);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  200);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -200);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::UpperBorder),  200.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::LowerBorder), -200.0);


    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder,  300));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, -300));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder,  300.5));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, -300.5));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder, 300));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder,  300));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, -300));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder,  300.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -300.0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 300));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  300));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -300));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::UpperBorder,  300.1));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::LowerBorder, -300.1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::UpperBorder, 300));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::UpperBorder,  300));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::LowerBorder, -300));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::UpperBorder,  300.9999));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::LowerBorder, -300.9999));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  300));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -300));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::UpperBorder,  300.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::LowerBorder, -300.0));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  300);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -300);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  300.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -300.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 300);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder),  300);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), -300);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder),  300.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), -300.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 300);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  300);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -300);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::UpperBorder),  300.1);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::LowerBorder), -300.1);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::UpperBorder), 300);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::UpperBorder),  300);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::LowerBorder), -300);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::UpperBorder),  300.9999);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::LowerBorder), -300.9999);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  300);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -300);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::UpperBorder),  300.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::LowerBorder), -300.0);


    EXPECT_EQ(OpenRangeIdManager_int.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 0);

    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_EQ(OpenRangeIdManager_int.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 6);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 30);


    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);


    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));


    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder, 29));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, 0));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder, 29.0));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, 0.0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder, 29));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 60));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 2));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, 45.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, 1.5));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 60));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 2));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -60));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::UpperBorder, -1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::LowerBorder, -59.5));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::UpperBorder,  10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder, -48));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder,  0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::UpperBorder,  114));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::LowerBorder, -2));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::UpperBorder,  56.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::LowerBorder, -2.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -56));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::UpperBorder,  2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::LowerBorder, -56.0));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder), 29);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder), 29.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 29);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 60);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 45.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 60);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -60);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::LowerBorder), -59.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::UpperBorder),  114);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::UpperBorder),  56.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::LowerBorder), -2.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -56);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::LowerBorder), -56.0);


    EXPECT_FALSE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder, 28));
    EXPECT_FALSE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, 1));
    EXPECT_FALSE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder, 28.0));
    EXPECT_FALSE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, 1.0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder, 28));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 1));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 58));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 4));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, 43.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, 3.0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 58));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 4));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  -4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -58));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::UpperBorder, -3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::LowerBorder, -57.5));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::UpperBorder, 8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder, 2));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::UpperBorder, 110));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::LowerBorder, 2));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::UpperBorder, 54.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::LowerBorder, 0.0));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -54));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::UpperBorder,  0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::LowerBorder, -54.0));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder), 29);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder), 29.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 29);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 60);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 45.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 60);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -60);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderLimit(BorderRange::LowerBorder), -59.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::UpperBorder),  114);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderLimit(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::UpperBorder),  56.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderLimit(BorderRange::LowerBorder), -2.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -56);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderLimit(BorderRange::LowerBorder), -56.0);
}

TEST_F(OpenRangeIdManagerTests, findId)
{
    EXPECT_FALSE(OpenRangeIdManager_int.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int.findId( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.findId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int.findId(-20));

    EXPECT_FALSE(OpenRangeIdManager_float.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId( 8.5));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId(-1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId(-20));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId(-20));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 3.3));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 18.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId(-3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId(-18.0));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(3));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(4));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(1));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-20));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 18.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-5.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-19.5));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(11));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(12));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(30));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(7));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(0));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-7));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-18));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-20.0));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 5));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId(-3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId(-20));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-20.0));

    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE (OpenRangeIdManager_int.findId( 0));
    EXPECT_TRUE (OpenRangeIdManager_int.findId( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.findId(-1));
    EXPECT_TRUE (OpenRangeIdManager_int.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.findId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int.findId(-20));
    EXPECT_TRUE (OpenRangeIdManager_int.findId( 29));
    EXPECT_FALSE(OpenRangeIdManager_int.findId( 30));
    EXPECT_FALSE(OpenRangeIdManager_int.findId( 500));

    EXPECT_TRUE (OpenRangeIdManager_float.findId( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float.findId( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-1.0));
    EXPECT_TRUE (OpenRangeIdManager_float.findId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float.findId( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId( 8.5));
    EXPECT_FALSE(OpenRangeIdManager_float.findId(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float.findId( 29.0));
    EXPECT_FALSE(OpenRangeIdManager_float.findId( 29.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.findId( 0));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.findId( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId(-1));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId(-20));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.findId( 29));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId( 30));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.findId( 500));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 3));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.findId( 4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.findId( 6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.findId( 60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 61));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.findId( 62));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 3.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 3.3));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 18.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId(-3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId(-18.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 45.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 46.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.findId( 46.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.findId(2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(3));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.findId(4));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.findId(6));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.findId(20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(1));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.findId(60));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(61));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.findId(62));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-3));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.findId(-4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.findId(-6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.findId(-20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.findId(-60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-61));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.findId(-62));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId( 18.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-3.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-5.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-19.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-59.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-60.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.findId(-61.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(11));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(12));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(30));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(7));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.findId(-1));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.findId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.findId( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.findId( 6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.findId( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-7));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId( 7));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId(-18));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.findId( 114));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId( 115));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.findId( 118));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 0.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId(-20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 56.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 56.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.findId( 58.0));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.findId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 5));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId( 20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.findId( 0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.findId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId(-3));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.findId(-20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.findId(-56));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId(-57));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.findId(-58));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-2.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-56.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-57.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.findId(-58.0));
}

TEST_F(OpenRangeIdManagerTests, FreeIds)
{
    EXPECT_FALSE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId(-1));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId(-9));

    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-9.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId(-1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId(-9));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId( 10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId( 8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId( 12));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId( 14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId( 20));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-0.3));

    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_EQ(OpenRangeIdManager_int.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 6);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 30);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 30);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 29);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 29.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 29);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 60);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 45.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 60);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -60);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -59.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  114);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  56.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -2.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -56);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -56.0);

    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));


    EXPECT_TRUE (OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE (OpenRangeIdManager_int.freeId( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId(-1));
    EXPECT_TRUE (OpenRangeIdManager_int.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int.freeId( 9));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId(-9));
    EXPECT_TRUE (OpenRangeIdManager_int.freeId( 29));
    EXPECT_FALSE(OpenRangeIdManager_int.freeId( 30));

    EXPECT_TRUE (OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-1.0));
    EXPECT_TRUE (OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float.freeId( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId(-9.3));
    EXPECT_TRUE (OpenRangeIdManager_float.freeId( 29.0));
    EXPECT_FALSE(OpenRangeIdManager_float.freeId( 30.0));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId(-1));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId(-9));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.freeId( 29));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.freeId( 30));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 62));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId(-1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 46.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 3));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 62));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-62));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 0.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-61.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(12));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(20));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-10));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-4.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-58));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 4.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));


    EXPECT_EQ(OpenRangeIdManager_int.size(), 25);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 25);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 25);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 25);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 25);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 25);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 25);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 26);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 1);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 24);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 24);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 25);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 24);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 28);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 3);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 28.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 3.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 28);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 3);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 58);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 8);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 43.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 6.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 58);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 8);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -8);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -58);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder), -7.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -57.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 4);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 4);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder), 106);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder), 52.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), 4.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), -4);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -54);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder), -4.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -52.0);

    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 1);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 1);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 1);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 1);

    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


    OpenRangeIdManager_int.freeAll();
    OpenRangeIdManager_float.freeAll();
    OpenRangeIdManager_unsigned.freeAll();

    OpenRangeIdManager_int_Start_2_Step_2.freeAll();
    OpenRangeIdManager_float_Start_1p5_Step_1p5.freeAll();
    OpenRangeIdManager_unsigned_Start_2_Step_2.freeAll();

    OpenRangeIdManager_int_Start_n2_Step_n2.freeAll();
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeAll();
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeAll();

    OpenRangeIdManager_int_Start_n2_Step_4.freeAll();
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeAll();

    OpenRangeIdManager_int_Start_2_Step_n2.freeAll();
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeAll();

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -1.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder), -2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -2.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), 2.0);

    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, IdIssuingMethod_Dynamic_to_Dynamic)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;


    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));


    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 9);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 29);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 30);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 29.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 30.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 9);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 29);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 30);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 60);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 62);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 45.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 46.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 6);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 10);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 60);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 62);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -60);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -62);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -5.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -59.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -61.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 18);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 110);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 114);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 118);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 54.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 56.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 58.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -20);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -56);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -58);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -20.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -54.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -56.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -58.0);
}

TEST_F(OpenRangeIdManagerTests, IdIssuingMethod_Dynamic_to_Ascending)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;


    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));


    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Ascending);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 9);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 29);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 30);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 29.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 30.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 9);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 29);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 30);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 60);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 62);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 45.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 46.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 6);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 10);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 60);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 62);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -60);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -62);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -5.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -59.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -61.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 18);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 110);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 114);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 118);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 54.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 56.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 58.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -20);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -56);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -58);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -20.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -54.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -56.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -58.0);
}

TEST_F(OpenRangeIdManagerTests, IdIssuingMethod_Dynamic_to_Descending)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;


    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));


    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Descending);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 9);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 29);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 30);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 29.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 30.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 9);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 29);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 30);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 60);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 62);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 45.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 46.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 10);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 6);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 60);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 62);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -60);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -62);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -5.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -59.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -61.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 18);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 110);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 114);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 118);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 54.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 56.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 58.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -20);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -56);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -58);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -20.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -54.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -56.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -58.0);
}

TEST_F(OpenRangeIdManagerTests, IdIssuingMethod_Descending_to_Descending)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Descending);

    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Descending);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 29);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 9);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 30);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 29.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 30.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 29);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 9);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 30);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 60);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 62);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 45.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 46.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 60);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 10);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 6);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 62);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -60);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -62);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -5.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -59.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -61.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 114);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 110);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 18);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 118);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 56.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 54.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 58.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -20);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -56);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -58);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -20.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -54.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -56.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -58.0);
}

TEST_F(OpenRangeIdManagerTests, IdIssuingMethod_Descending_to_Ascending)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Descending);

    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Ascending);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 9);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 29);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 30);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 29.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 30.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 9);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 29);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 30);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 60);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 62);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 45.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 46.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 6);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 10);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 60);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 62);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -60);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -62);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -59.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -5.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -61.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 18);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 110);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 114);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 118);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 54.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 56.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 58.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -56);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -20);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -58);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -56.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -54.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -20.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -58.0);
}

TEST_F(OpenRangeIdManagerTests, IdIssuingMethod_Descending_to_Dynamic)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Descending);

    for (int i = 0; i < 30; ++i) {
        OpenRangeIdManager_int.getFreeId();
        OpenRangeIdManager_float.getFreeId();
        OpenRangeIdManager_unsigned.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();

        OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();

        OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    }

    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 8));
    EXPECT_TRUE(OpenRangeIdManager_int.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 8));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_float.freeId( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 7));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.freeId( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 12));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 10.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.freeId( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 12));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.freeId( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-12));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.freeId(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-15.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-17.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeId(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeId(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId( 22));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.freeId(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 8.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeId( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-26));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.freeId(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-26.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeId(-56.0));

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 9);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 29);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 30);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 8.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 29.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 30.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 7);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 9);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 29);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 30);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 12);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 60);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 62);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 9.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 45.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 46.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 6);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 10);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 12);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 60);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 62);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -12);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -60);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -62);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -5.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -17.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -15.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -59.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -61.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 18);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 22);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 110);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 114);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 118);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 8.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 10.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 54.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 56.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 58.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -26);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -20);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -56);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -58);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -26.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -20.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -54.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -56.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -58.0);
}

TEST_F(OpenRangeIdManagerTests, ReserveId_DynamicAndAscending_ReserveId)
{
    for (size_t i = 0; i < 2; ++i)
    {
        EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());

        OpenRangeIdManager_int.setHardStep(true);
        OpenRangeIdManager_float.setHardStep(true);
        OpenRangeIdManager_unsigned.setHardStep(true);

        OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

        OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

        OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

        OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

        EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


        EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 0));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 1));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-1));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 9));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-9));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 9));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 0));

        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 1.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-1.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-2.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 9.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 0.5));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-0.5));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 15.3));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-15.3));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0));

        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 0));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 1));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId(-1));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 9));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId(-9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 10));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 3.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 30));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 4));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 6));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 10));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 5));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 1));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 51));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 6));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(-2));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-10));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-3.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-5.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 10.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 20.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(8));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(12));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(6));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(0));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(15));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 18));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-16));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 12));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-4.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-10.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-5.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 20));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-20.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-4.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0));

        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  2);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -2.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  6);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  4.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -1.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 6);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -6);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  0.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -5.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 14);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  6);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -10);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -4.0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  6);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  6.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -2.0);


        EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 7);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 7);


        OpenRangeIdManager_int.setHardStep(false);
        OpenRangeIdManager_float.setHardStep(false);
        OpenRangeIdManager_unsigned.setHardStep(false);

        OpenRangeIdManager_int_Start_2_Step_2.setHardStep(false);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(false);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(false);

        OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(false);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(false);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(false);

        OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(false);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(false);

        OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(false);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(false);

        EXPECT_FALSE(OpenRangeIdManager_int.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_unsigned.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 9));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 0));

        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.5));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-0.5));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 15.3));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-15.3));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0));

        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 5));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 1));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 51));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 6));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(-2));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(15));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-16));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 12));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-5.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.1));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-4.1));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0));


        EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 9);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 11);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 10);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 11);


        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  2);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -2.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  6);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  4.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -1.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 6);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  2);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -6);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  0.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -5.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 14);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  6);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -10);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  2.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -4.0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  6);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  6.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -2.0);


        OpenRangeIdManager_int.setHardStep(true);
        OpenRangeIdManager_float.setHardStep(true);
        OpenRangeIdManager_unsigned.setHardStep(true);

        OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

        OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

        OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

        OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

        EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


        EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 7);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 7);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 7);

        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));


        OpenRangeIdManager_int.freeAll();
        OpenRangeIdManager_float.freeAll();
        OpenRangeIdManager_unsigned.freeAll();

        OpenRangeIdManager_int_Start_2_Step_2.freeAll();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.freeAll();
        OpenRangeIdManager_unsigned_Start_2_Step_2.freeAll();

        OpenRangeIdManager_int_Start_n2_Step_n2.freeAll();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeAll();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeAll();

        OpenRangeIdManager_int_Start_n2_Step_4.freeAll();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeAll();

        OpenRangeIdManager_int_Start_2_Step_n2.freeAll();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeAll();


        OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Ascending);
    }
}

TEST_F(OpenRangeIdManagerTests, ReserveId_DynamicAndAscending_ReserveRange)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

    for (size_t i = 0; i < 2; ++i)
    {
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 1, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-1, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-2, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 9, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-1.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 9.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 15.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-15.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 1, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 0.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 3.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-1.5, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(30, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(40, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(51, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(40, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-3.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-5.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 20.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 10.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(12, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(8,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(15, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 18, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-16, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 12, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-10.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-4.0,   ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 0.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-5.5,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.5,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 20, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 0.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-20.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-4.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::ReserveRange));

        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  9);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  9.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -9.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 40);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 20);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  18);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -18);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  20.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -20.0);


        EXPECT_EQ(OpenRangeIdManager_int.size(), 19);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 19);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 10);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 13);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 20);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 11);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 22);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 11);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 10);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 11);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 21);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 21);


        OpenRangeIdManager_int.setHardStep(false);
        OpenRangeIdManager_float.setHardStep(false);
        OpenRangeIdManager_unsigned.setHardStep(false);

        OpenRangeIdManager_int_Start_2_Step_2.setHardStep(false);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(false);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(false);

        OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(false);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(false);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(false);

        OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(false);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(false);

        OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(false);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(false);

        EXPECT_FALSE(OpenRangeIdManager_int.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_unsigned.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


        EXPECT_TRUE (OpenRangeIdManager_int.reserveId(20, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId(9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId(2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserveId(0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 15.3, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-15.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::ReserveRange));

        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 51, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 2,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(23, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-24, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 24, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3,   ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-8.1,   ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 8.1,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 25.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-25.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::ReserveRange));


        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  20);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  15.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -15.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 50);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 22);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  22);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -22);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  24.0);
        EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -24.0);

        EXPECT_EQ(OpenRangeIdManager_int.size(), 30);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 35);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 10);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 15);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 17);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 28);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 15);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 26);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 16);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 16);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 15);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 25);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 29);


        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 21);
        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 22);
        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 23);

        optional_id_float = OpenRangeIdManager_float.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 16.0);
        optional_id_float = OpenRangeIdManager_float.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 17.0);
        optional_id_float = OpenRangeIdManager_float.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 18.0);

        optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 10);
        optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 11);
        optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 12);

        optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 12);
        optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 14);
        optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 16);

        optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 10.5);
        optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 12.0);
        optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 13.5);

        optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 52);
        optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 54);
        optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 56);

        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -12);
        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -14);
        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -16);

        optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -23.5);
        optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -25.5);
        optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -27.5);

        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 26);
        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 30);
        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 34);

        optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 12.0);
        optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 14.0);
        optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 16.0);

        optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -22);
        optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -24);
        optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -26);

        optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -26.0);
        optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -28.0);
        optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -30.0);


        OpenRangeIdManager_int.setHardStep(true);
        OpenRangeIdManager_float.setHardStep(true);
        OpenRangeIdManager_unsigned.setHardStep(true);

        OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

        OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

        OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

        OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

        EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());

        EXPECT_EQ(OpenRangeIdManager_int.size(), 33);
        EXPECT_EQ(OpenRangeIdManager_float.size(), 34);
        EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 13);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 14);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 16);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 28);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 14);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 25);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 12);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 15);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 14);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 24);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 28);


//        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);               //TODO: Дописать везде.
//        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 2);

//        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 2);

//        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 2);

//        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 2);

//        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 2);
//        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
//        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 2);


        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));


        OpenRangeIdManager_int.freeAll();
        OpenRangeIdManager_float.freeAll();
        OpenRangeIdManager_unsigned.freeAll();

        OpenRangeIdManager_int_Start_2_Step_2.freeAll();
        OpenRangeIdManager_float_Start_1p5_Step_1p5.freeAll();
        OpenRangeIdManager_unsigned_Start_2_Step_2.freeAll();

        OpenRangeIdManager_int_Start_n2_Step_n2.freeAll();
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.freeAll();
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.freeAll();

        OpenRangeIdManager_int_Start_n2_Step_4.freeAll();
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.freeAll();

        OpenRangeIdManager_int_Start_2_Step_n2.freeAll();
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.freeAll();


        OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

        OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Ascending);
    }
}

TEST_F(OpenRangeIdManagerTests, ReserveId_Dynamic_Interpolate)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 1, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-1, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-2, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-1.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 9.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 15.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-15.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 1, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 0.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 3.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-1.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(30, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(40, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(51, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(40, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-3.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-5.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 20.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 10.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(12, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(8,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(15, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 18, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-16, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 12, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-10.0,  ReservationMethod::Interpolate));
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 1);
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-4.0,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 0.0,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-5.5,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.5,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 20, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::Interpolate));
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 1);
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 0.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-20.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-4.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::Interpolate));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  9);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  9.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -9.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 40);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 20);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  18);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -18);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  20.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -20.0);

    EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 6);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 7);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 6);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 7);


    OpenRangeIdManager_int.setHardStep(false);
    OpenRangeIdManager_float.setHardStep(false);
    OpenRangeIdManager_unsigned.setHardStep(false);

    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(false);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(false);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(false);

    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(false);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(false);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(false);

    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(false);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(false);

    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(false);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(false);

    EXPECT_FALSE(OpenRangeIdManager_int.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(20, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 15.3, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-15.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::Interpolate));

    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 51, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(23, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-24, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 24, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-8.1,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 8.1,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 25.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-25.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::Interpolate));


    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  20);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  15.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -15.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 22);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  22);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -22);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  24.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -24.0);

    EXPECT_EQ(OpenRangeIdManager_int.size(), 8);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 13);  //TODO: В статическом режиме было бы 11, проверить.
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 12);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 13);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 13);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 3);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 5);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 3);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 5);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 8);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 6.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 7.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -3.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 8);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 12);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 14);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -8);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -7.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -9.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -11.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 16);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 14);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -14);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -8.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -6.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -8);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 18.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 16.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 14.0);


    OpenRangeIdManager_int.setHardStep(true);
    OpenRangeIdManager_float.setHardStep(true);
    OpenRangeIdManager_unsigned.setHardStep(true);

    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 12);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 11);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 12);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 9);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 12);

    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, ReserveId_Ascending_Interpolate)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Ascending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Ascending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Ascending);


    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 1, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-1, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-2, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId( 0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-1.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 9.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 15.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-15.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 1, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 0.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 3.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-1.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(30, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(40, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(51, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId(40, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-3.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-5.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 20.5, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 10.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(12, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(8,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(15, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 18, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-16, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 12, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-10.0,  ReservationMethod::Interpolate));
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 1);
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-4.0,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 0.0,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-5.5,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.5,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 20, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::Interpolate));
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 1);
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 0.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-20.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 4.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-4.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::Interpolate));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  9);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  9.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -9.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 40);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 20);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  18);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -18);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  20.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -20.0);

    EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 6);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 7);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 6);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 7);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 7);


    OpenRangeIdManager_int.setHardStep(false);
    OpenRangeIdManager_float.setHardStep(false);
    OpenRangeIdManager_unsigned.setHardStep(false);

    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(false);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(false);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(false);

    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(false);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(false);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(false);

    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(false);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(false);

    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(false);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(false);

    EXPECT_FALSE(OpenRangeIdManager_int.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(20, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId( 15.3, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(-15.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(-9.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserveId( 1.0,  ReservationMethod::Interpolate));

    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 2, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 9, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId( 0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 3,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId(-9,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserveId( 9,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserveId(-10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 2.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.3, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId(-9.3, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 4.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 1.5, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserveId( 9.0, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 51, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserveId( 2,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 11, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId(-6,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserveId( 10, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-8.0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 1.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-2.5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-1.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId( 0.5,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserveId(-21.5, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(11, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(9,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(23, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(7,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(14, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserveId(20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 0,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-4,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-24, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserveId( 24, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-10, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserveId(-18, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-3.999, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-1.3,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-8.1,   ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 8.1,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId(-2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 2.0,   ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserveId( 10.0,  ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 5,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 7,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-3,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId( 2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-2,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserveId(-20, ReservationMethod::Interpolate));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-0.1,  ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 25.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId(-25.0, ReservationMethod::Interpolate));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 8.1,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 2.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 6.0,  ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserveId( 20.0, ReservationMethod::Interpolate));


    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  20);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  15.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -15.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 22);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  22);
    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -22);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  24.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -24.0);

    EXPECT_EQ(OpenRangeIdManager_int.size(), 8);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 9);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 11);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 11);


    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -8);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -7);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -15.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -14.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -13.0);

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 3);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 4);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 5);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -8);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -6);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -4);

    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -7.5);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -6.0);
    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -4.5);

    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 8);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 12);
    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 14);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -8);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);

    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -19.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -17.5);
    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -15.5);

    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 16);

    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -22);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -14);
    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 10);

    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -8.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -6.0);
    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -18);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -16);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, -14);

    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -24.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -22.0);
    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, -18.0);


    OpenRangeIdManager_int.setHardStep(true);
    OpenRangeIdManager_float.setHardStep(true);
    OpenRangeIdManager_unsigned.setHardStep(true);

    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 9);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 10);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 9);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 10);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 10);

    EXPECT_TRUE (OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));
}

TEST(SingleTests, Test_1)
{
    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;


    OpenRangeIdManager<int> OpenRangeIdManager_int;
    OpenRangeIdManager<float> OpenRangeIdManager_float;
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned;

    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder,  50));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, -50));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);

    EXPECT_FALSE(OpenRangeIdManager_int.reserveId(-90));
    EXPECT_TRUE (OpenRangeIdManager_int.reserveId(-50));

    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder,  50.5));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, -50.5));

    OpenRangeIdManager_float.setHardStep(false);

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);

    EXPECT_FALSE(OpenRangeIdManager_float.reserveId(90.0));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(50.0));
    EXPECT_TRUE (OpenRangeIdManager_float.reserveId(0.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder,  50));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, -50));

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 2);

    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId(50));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserveId(33));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserveId(90));


    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 5);


    OpenRangeIdManager<int> OpenRangeIdManager_int_cc(OpenRangeIdManager_int);
    OpenRangeIdManager<float> OpenRangeIdManager_float_cc(OpenRangeIdManager_float);
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_cc(OpenRangeIdManager_unsigned);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 5);


    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_cc.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_cc.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.size(), 5);


    OpenRangeIdManager<int> OpenRangeIdManager_int_cm(std::move(OpenRangeIdManager_int));
    OpenRangeIdManager<float> OpenRangeIdManager_float_cm(std::move(OpenRangeIdManager_float));
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_cm(std::move(OpenRangeIdManager_unsigned));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.size(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 0);


    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_cm.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cm.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_cm.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.size(), 5);


    OpenRangeIdManager<int> OpenRangeIdManager_int_oc;
    OpenRangeIdManager<float> OpenRangeIdManager_float_oc;
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_oc;
    OpenRangeIdManager_int_oc = OpenRangeIdManager_int_cc;
    OpenRangeIdManager_float_oc = OpenRangeIdManager_float_cc;
    OpenRangeIdManager_unsigned_oc = OpenRangeIdManager_unsigned_cc;

    EXPECT_EQ(OpenRangeIdManager_int_oc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_oc.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int_oc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_oc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_oc.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_oc.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_oc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_oc.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float_oc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_oc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_oc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_oc.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_oc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.size(), 5);


    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_cc.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_cc.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.size(), 5);


    OpenRangeIdManager<int> OpenRangeIdManager_int_om;
    OpenRangeIdManager<float> OpenRangeIdManager_float_om;
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_om;
    OpenRangeIdManager_int_om = std::move(OpenRangeIdManager_int_cm);
    OpenRangeIdManager_float_om = std::move(OpenRangeIdManager_float_cm);
    OpenRangeIdManager_unsigned_om = std::move(OpenRangeIdManager_unsigned_cm);

    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.size(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE(OpenRangeIdManager_float_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cm.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cm.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.size(), 0);


    EXPECT_EQ(OpenRangeIdManager_int_om.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_om.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE(OpenRangeIdManager_int_om.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_om.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_om.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_om.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_om.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_om.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_FALSE(OpenRangeIdManager_float_om.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_om.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_om.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_om.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_om.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.size(), 5);
}
