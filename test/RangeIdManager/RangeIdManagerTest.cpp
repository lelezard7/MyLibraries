#include "IdManagement.h"

#include <gtest/gtest.h>

using namespace ONF;


template<class T, class T_Step = T>
class OpenRangeIdManager : public RangeIdManager<T, T_Step, std::enable_if_t<!is_forbidden_types_combination<T, T_Step>>>
{
public:
    OpenRangeIdManager(T start = 0, T_Step step = 1)
        : RangeIdManager<T, T_Step>(start, step) {};

    OpenRangeIdManager(const OpenRangeIdManager<T, T_Step>& other) = default;
    OpenRangeIdManager(OpenRangeIdManager<T, T_Step>&& other) = default;

    using RangeIdManager<T, T_Step>::getFreeIdsSize;
    using RangeIdManager<T, T_Step>::getReservedIdsSize;
    using RangeIdManager<T, T_Step>::findNearestStdId;

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

    std::optional<int> optional_id_int;
    std::optional<float> optional_id_float;
    std::optional<unsigned> optional_id_unsigned;

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


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(OpenRangeIdManagerTests, findNearestStdId_1)
{
    EXPECT_EQ( 20, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 21, BorderRange::UpperBorder));
    EXPECT_EQ(-20, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-21, BorderRange::UpperBorder));

    EXPECT_EQ( 20, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 21, BorderRange::LowerBorder));
    EXPECT_EQ(-20, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-21, BorderRange::LowerBorder));


    EXPECT_EQ( 22, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 22, BorderRange::UpperBorder));
    EXPECT_EQ(-22, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-22, BorderRange::UpperBorder));

    EXPECT_EQ( 22, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 22, BorderRange::LowerBorder));
    EXPECT_EQ(-22, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-22, BorderRange::LowerBorder));


    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(3, BorderRange::UpperBorder));
    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(1, BorderRange::UpperBorder));

    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(3, BorderRange::LowerBorder));
    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(1, BorderRange::LowerBorder));


    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(2, BorderRange::UpperBorder));
    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(2, BorderRange::LowerBorder));


    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6));


    EXPECT_EQ( 36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 37, BorderRange::UpperBorder));
    EXPECT_EQ(-36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-37, BorderRange::UpperBorder));

    EXPECT_EQ( 36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 37, BorderRange::LowerBorder));
    EXPECT_EQ(-36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-37, BorderRange::LowerBorder));


    EXPECT_EQ( 32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 32, BorderRange::UpperBorder));
    EXPECT_EQ(-32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-32, BorderRange::UpperBorder));

    EXPECT_EQ( 32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 32, BorderRange::LowerBorder));
    EXPECT_EQ(-32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-32, BorderRange::LowerBorder));


    EXPECT_EQ( 6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 7, BorderRange::UpperBorder));
    EXPECT_EQ(-2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-3, BorderRange::UpperBorder));

    EXPECT_EQ( 6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 7, BorderRange::LowerBorder));
    EXPECT_EQ(-2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-3, BorderRange::LowerBorder));


    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(2, BorderRange::UpperBorder));
    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(2, BorderRange::LowerBorder));


    EXPECT_EQ(4, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(3, BorderRange::UpperBorder));
    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(3, BorderRange::LowerBorder));

    EXPECT_EQ(2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(1, BorderRange::UpperBorder));
    EXPECT_EQ(0, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(1, BorderRange::LowerBorder));


    EXPECT_EQ(4, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(4, BorderRange::UpperBorder));
    EXPECT_EQ(4, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(4, BorderRange::LowerBorder));

    EXPECT_EQ(0, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(0, BorderRange::UpperBorder));
    EXPECT_EQ(0, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(0, BorderRange::LowerBorder));


    EXPECT_EQ(6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(5, BorderRange::UpperBorder));
    EXPECT_EQ(4, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(5, BorderRange::LowerBorder));

    EXPECT_EQ(0,  OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-1, BorderRange::UpperBorder));
    EXPECT_EQ(-2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-1, BorderRange::LowerBorder));


    EXPECT_EQ(6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(6, BorderRange::UpperBorder));
    EXPECT_EQ(6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(6, BorderRange::LowerBorder));

    EXPECT_EQ(-2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-2, BorderRange::UpperBorder));
    EXPECT_EQ(-2, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-2, BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, findNearestStdId_2)
{
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(8));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(12));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(14));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(4));

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 14);
    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 6);


    EXPECT_EQ( 36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 37, BorderRange::UpperBorder));
    EXPECT_EQ(-36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-37, BorderRange::UpperBorder));

    EXPECT_EQ( 36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 37, BorderRange::LowerBorder));
    EXPECT_EQ(-36, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-37, BorderRange::LowerBorder));


    EXPECT_EQ( 32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 32, BorderRange::UpperBorder));
    EXPECT_EQ(-32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-32, BorderRange::UpperBorder));

    EXPECT_EQ( 32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId( 32, BorderRange::LowerBorder));
    EXPECT_EQ(-32, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(-32, BorderRange::LowerBorder));


    EXPECT_EQ(6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(6, BorderRange::UpperBorder));
    EXPECT_EQ(6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(6, BorderRange::LowerBorder));

    EXPECT_EQ(14, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(14, BorderRange::UpperBorder));
    EXPECT_EQ(14, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(14, BorderRange::LowerBorder));

    EXPECT_EQ(10, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(9, BorderRange::UpperBorder));
    EXPECT_EQ(8,  OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(9, BorderRange::LowerBorder));

    EXPECT_EQ(14, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(13, BorderRange::UpperBorder));
    EXPECT_EQ(12, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(13, BorderRange::LowerBorder));

    EXPECT_EQ(8, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(7, BorderRange::UpperBorder));
    EXPECT_EQ(6, OpenRangeIdManager_int_Start_2_Step_2.findNearestStdId(7, BorderRange::LowerBorder));
}

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
            OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        }

        if (i == 2) {
            OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
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
    EXPECT_FALSE(OpenRangeIdManager_int.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_int.find( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.find(-1));
    EXPECT_FALSE(OpenRangeIdManager_int.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int.find(-20));

    EXPECT_FALSE(OpenRangeIdManager_float.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find( 8.5));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find(-1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find(-20));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find(-20));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 3.3));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 18.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find(-3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find(-18.0));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(3));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(4));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(1));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-20));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 18.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-5.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-19.5));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(11));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(12));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(30));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(7));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(0));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-7));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-18));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-20.0));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 5));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find(-3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find(-20));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-20.0));

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

    EXPECT_TRUE (OpenRangeIdManager_int.find( 0));
    EXPECT_TRUE (OpenRangeIdManager_int.find( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.find(-1));
    EXPECT_TRUE (OpenRangeIdManager_int.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.find(-2));
    EXPECT_TRUE (OpenRangeIdManager_int.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int.find(-20));
    EXPECT_TRUE (OpenRangeIdManager_int.find( 29));
    EXPECT_FALSE(OpenRangeIdManager_int.find( 30));
    EXPECT_FALSE(OpenRangeIdManager_int.find( 500));

    EXPECT_TRUE (OpenRangeIdManager_float.find( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float.find( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-1.0));
    EXPECT_TRUE (OpenRangeIdManager_float.find( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float.find( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find( 8.5));
    EXPECT_FALSE(OpenRangeIdManager_float.find(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float.find( 29.0));
    EXPECT_FALSE(OpenRangeIdManager_float.find( 29.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.find( 0));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.find( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find(-1));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find(-20));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.find( 29));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find( 30));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.find( 500));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 3));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.find( 4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.find( 6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find(-1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.find( 60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 61));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.find( 62));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 3.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 3.3));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 18.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find(-3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find(-18.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 45.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 46.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.find( 46.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.find(2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(3));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.find(4));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.find(6));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.find(20));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(1));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.find(60));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(61));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.find(62));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 1));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-3));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.find(-4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.find(-6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.find(-20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.find(-60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-61));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.find(-62));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find( 18.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-3.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-5.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-19.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-59.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-60.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.find(-61.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(11));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(12));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(30));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(7));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.find(-1));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.find(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.find( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.find( 6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.find( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-7));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find( 7));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find(-18));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.find( 114));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find( 115));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.find( 118));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 0.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find(-20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 56.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 56.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.find( 58.0));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.find( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 5));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find( 20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.find( 0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.find(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find(-3));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.find(-20));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.find(-56));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find(-57));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.find(-58));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.find( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-2.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-56.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-57.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.find(-58.0));
}

TEST_F(OpenRangeIdManagerTests, FreeIds)
{
    EXPECT_FALSE(OpenRangeIdManager_int.free( 0));
    EXPECT_FALSE(OpenRangeIdManager_int.free( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.free(-1));
    EXPECT_FALSE(OpenRangeIdManager_int.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_int.free( 9));
    EXPECT_FALSE(OpenRangeIdManager_int.free(-9));

    EXPECT_FALSE(OpenRangeIdManager_float.free( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-9.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned.free( 0));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free(-1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free( 9));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free(-9));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 4));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 10));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 0.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free( 10));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free( 8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free( 12));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free( 14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free( 20));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-0.3));

    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free(-9));

    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 4.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-0.3));

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


    EXPECT_TRUE (OpenRangeIdManager_int.free( 0));
    EXPECT_TRUE (OpenRangeIdManager_int.free( 1));
    EXPECT_FALSE(OpenRangeIdManager_int.free(-1));
    EXPECT_TRUE (OpenRangeIdManager_int.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int.free(-2));
    EXPECT_TRUE (OpenRangeIdManager_int.free( 9));
    EXPECT_FALSE(OpenRangeIdManager_int.free(-9));
    EXPECT_TRUE (OpenRangeIdManager_int.free( 29));
    EXPECT_FALSE(OpenRangeIdManager_int.free( 30));

    EXPECT_TRUE (OpenRangeIdManager_float.free( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float.free( 1.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-1.0));
    EXPECT_TRUE (OpenRangeIdManager_float.free( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float.free( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float.free(-9.3));
    EXPECT_TRUE (OpenRangeIdManager_float.free( 29.0));
    EXPECT_FALSE(OpenRangeIdManager_float.free( 30.0));

    EXPECT_TRUE (OpenRangeIdManager_unsigned.free( 0));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.free( 1));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free(-1));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.free( 9));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free(-9));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.free( 29));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.free( 30));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.free( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.free( 4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.free( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.free( 60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.free( 62));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 3.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 0.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 4.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(-1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(-9.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 45.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 46.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 3));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.free( 4));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(-2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.free( 10));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.free( 60));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 62));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 0));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 10));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-62));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 0.5));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 2.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 10.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-61.5));

    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(12));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(14));
    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(20));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-10));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-18));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.free(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.free(110));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.free(114));

    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-4.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-10.0));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 4));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 6));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 20));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free( 3));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free(-9));
    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.free(-56));
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.free(-58));

    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 4.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 6.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 20.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 9.5));
    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-0.3));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));


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

    EXPECT_TRUE(OpenRangeIdManager_int.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));


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

    EXPECT_TRUE(OpenRangeIdManager_int.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 9));
    EXPECT_TRUE(OpenRangeIdManager_int.free( 29));

    EXPECT_TRUE(OpenRangeIdManager_float.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free( 29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free( 29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free( 60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free( 45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free( 60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));


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

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);


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

    EXPECT_TRUE(OpenRangeIdManager_int.free(0));
    EXPECT_TRUE(OpenRangeIdManager_int.free(1));
    EXPECT_TRUE(OpenRangeIdManager_int.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int.free(9));
    EXPECT_TRUE(OpenRangeIdManager_int.free(29));

    EXPECT_TRUE(OpenRangeIdManager_float.free(0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));


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

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);


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
    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

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

    EXPECT_TRUE(OpenRangeIdManager_int.free(0));
    EXPECT_TRUE(OpenRangeIdManager_int.free(1));
    EXPECT_TRUE(OpenRangeIdManager_int.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int.free(9));
    EXPECT_TRUE(OpenRangeIdManager_int.free(29));

    EXPECT_TRUE(OpenRangeIdManager_float.free(0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);


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
    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

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

    EXPECT_TRUE(OpenRangeIdManager_int.free(0));
    EXPECT_TRUE(OpenRangeIdManager_int.free(1));
    EXPECT_TRUE(OpenRangeIdManager_int.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int.free(9));
    EXPECT_TRUE(OpenRangeIdManager_int.free(29));

    EXPECT_TRUE(OpenRangeIdManager_float.free(0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));

    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);


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
    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

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

    EXPECT_TRUE(OpenRangeIdManager_int.free(0));
    EXPECT_TRUE(OpenRangeIdManager_int.free(1));
    EXPECT_TRUE(OpenRangeIdManager_int.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int.free(9));
    EXPECT_TRUE(OpenRangeIdManager_int.free(8));
    EXPECT_TRUE(OpenRangeIdManager_int.free(29));

    EXPECT_TRUE(OpenRangeIdManager_float.free(0.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(8));
    EXPECT_TRUE(OpenRangeIdManager_float.free(9));
    EXPECT_TRUE(OpenRangeIdManager_float.free(29.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(0));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(1));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(9));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(7));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.free(29));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(12));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(3.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(4.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(9.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(10.5));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.free(45.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(4));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(12));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.free(60));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-4));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-10));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-12));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.free(-60));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-1.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-3.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-5.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-15.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-17.5));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.free(-59.5));

    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(10));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(8));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(6));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(2));
    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.free(0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 18));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free( 22));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(110));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.free(114));

    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 10.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 8.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.free( 56.0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free( 0));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-2));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-20));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-26));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.free(-56));

    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free( 0.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-2.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-20.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-26.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-54.0));
    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.free(-56.0));

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

TEST_F(OpenRangeIdManagerTests, Reserve_DynamicAndAscending_ReserveId)
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


        EXPECT_TRUE (OpenRangeIdManager_int.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve( 0));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve( 1));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve(-1));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve( 9));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve(-9));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 9));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 0));

        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 1.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-1.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-2.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 9.0));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 0.5));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-0.5));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 15.3));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-15.3));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0));

        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 0));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 1));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve(-1));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 9));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve(-9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 10));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 1));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-9));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 9));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 3.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 30));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 4));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 6));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 10));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 5));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 1));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 51));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 6));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(-2));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-10));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-3.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-5.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 10.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 20.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(8));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(12));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(6));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(0));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(15));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 18));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-16));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 12));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-4.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-10.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-5.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 6));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 20));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 0.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-20.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-4.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0));

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

        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 4);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 3);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 3);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 2);


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


        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 9));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 0));

        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.5));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-0.5));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 15.3));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-15.3));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0));

        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 3));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 1));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-9));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 9));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 5));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 1));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 51));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 6));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(-2));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(15));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-16));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 12));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-5.5));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.5));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.1));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-4.1));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0));


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

        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 6);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 4);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 6);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 6);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 6);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 7);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 6);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 6);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 6);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 6);


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

        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 4);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 3);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 3);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 2);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 2);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 2);

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


        OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    }
}

TEST_F(OpenRangeIdManagerTests, Reserve_DynamicAndAscending_ReserveRange)
{
    for (size_t i = 0; i < 2; ++i)
    {
        EXPECT_TRUE (OpenRangeIdManager_int.reserve( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 1, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve(-1, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve(-2, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve( 9, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int.reserve(-9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve( 0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-1.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 9.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 15.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-15.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 1, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 0.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 3.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-1.5, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(30, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(40, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(51, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(40, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-3.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-5.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 20.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 10.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(12, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(8,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(15, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 6,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 18, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-16, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 12, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-10.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-4.0,   ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 0.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-5.5,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.5,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 20, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 0.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-20.0, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-4.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::ReserveRange));

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

        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


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


        EXPECT_TRUE (OpenRangeIdManager_int.reserve(20, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve(9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve(2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int.reserve(0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve( 15.3, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float.reserve(-15.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::ReserveRange));

        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 3,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-9,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 9,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 51, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 2,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(23, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-24, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 24, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3,   ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-8.1,   ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 8.1,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::ReserveRange));

        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1,  ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 25.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-25.0, ReservationMethod::ReserveRange));
        EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::ReserveRange));
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::ReserveRange));


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

        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 3);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 4);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 4);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 4);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 4);


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

        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 0);
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


        OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

        OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    }
}

//TEST_F(OpenRangeIdManagerTests, Reserve_Dynamic_Interpolate)
//{
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 1, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-1, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-2, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve( 0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-1.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 9.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 15.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-15.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 1, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 0.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 3.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-1.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(30, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(40, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(51, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(40, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-3.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-5.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 20.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 10.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(12, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(8,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(15, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 18, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-16, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 12, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-10.0,  ReservationMethod::Interpolate));
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 1);
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-4.0,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 0.0,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-5.5,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.5,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 20, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::Interpolate));
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 1);
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 0.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-20.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-4.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::Interpolate));

//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  9);
//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  9.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -9.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 40);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 20);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  18);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -18);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  20.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -20.0);

//    EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 6);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 7);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 6);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 7);

//    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 12);
//    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 12);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 15);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 5);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


//    OpenRangeIdManager_int.setHardStep(false);
//    OpenRangeIdManager_float.setHardStep(false);
//    OpenRangeIdManager_unsigned.setHardStep(false);

//    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(false);
//    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(false);
//    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(false);

//    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(false);
//    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(false);
//    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(false);

//    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(false);
//    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(false);

//    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(false);
//    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(false);

//    EXPECT_FALSE(OpenRangeIdManager_int.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(20, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve(9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve(2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve(0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 15.3, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-15.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::Interpolate));

//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 3,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-9,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 51, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(23, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-24, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 24, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-8.1,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 8.1,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 25.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-25.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::Interpolate));


//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  20);
//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  15.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -15.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 50);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 22);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  22);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -22);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  24.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -24.0);

//    EXPECT_EQ(OpenRangeIdManager_int.size(), 8);
//    EXPECT_EQ(OpenRangeIdManager_float.size(), 13);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 10);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 12);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 13);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 10);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 13);

//    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 22);
//    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 22);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 18);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 3);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 15);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 5);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 16);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 4);


//    optional_id_int = OpenRangeIdManager_int.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 3);
//    optional_id_int = OpenRangeIdManager_int.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 4);
//    optional_id_int = OpenRangeIdManager_int.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 5);

//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);

//    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 3);
//    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 4);
//    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 5);

//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 8);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -4);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -6);

//    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 6.0);
//    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 7.5);
//    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -3.0);

//    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 8);
//    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 12);
//    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 14);

//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -8);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 4);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 6);

//    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -7.5);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -9.5);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -11.5);

//    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 4);
//    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 2);
//    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 16);

//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 10);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 14);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -14);

//    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -8.0);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -6.0);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);

//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -4);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -6);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -8);

//    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 18.0);
//    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 16.0);
//    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 14.0);


//    OpenRangeIdManager_int.setHardStep(true);
//    OpenRangeIdManager_float.setHardStep(true);
//    OpenRangeIdManager_unsigned.setHardStep(true);

//    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
//    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
//    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

//    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
//    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
//    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

//    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
//    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

//    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
//    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

//    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());

//    EXPECT_EQ(OpenRangeIdManager_int.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float.size(), 12);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 10);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 11);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 12);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 9);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 12);

//    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 19);
//    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 19);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 15);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 12);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 2);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 11);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 13);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);

//    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));
//}

//TEST_F(OpenRangeIdManagerTests, Reserve_Ascending_Interpolate)
//{
//    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

//    OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

//    OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

//    OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

//    OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);


//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 1, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-1, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-2, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve( 0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-1.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 9.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 15.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-15.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 1, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 0.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 3.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-1.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(30, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(40, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(51, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve(40, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-3.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-5.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 20.5, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 10.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(12, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(8,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(15, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 18, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-16, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve( 12, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-10.0,  ReservationMethod::Interpolate));
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 1);
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-4.0,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 0.0,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-5.5,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.5,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 20, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::Interpolate));
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 1);
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 0.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-20.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 4.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-4.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::Interpolate));

//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  9);
//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  9.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -9.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 40);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 20);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  18);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -18);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  20.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -20.0);

//    EXPECT_EQ(OpenRangeIdManager_int.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 6);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 7);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 6);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 7);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 7);

//    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 12);
//    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 12);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 15);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 5);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);


//    OpenRangeIdManager_int.setHardStep(false);
//    OpenRangeIdManager_float.setHardStep(false);
//    OpenRangeIdManager_unsigned.setHardStep(false);

//    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(false);
//    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(false);
//    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(false);

//    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(false);
//    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(false);
//    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(false);

//    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(false);
//    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(false);

//    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(false);
//    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(false);

//    EXPECT_FALSE(OpenRangeIdManager_int.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());


//    EXPECT_TRUE (OpenRangeIdManager_int.reserve(20, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve(9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve(2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int.reserve(0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve( 15.3, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(-15.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(-9.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve( 1.0,  ReservationMethod::Interpolate));

//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 2, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 9, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve( 0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 3,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve(-9,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.reserve( 9,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 2.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.3, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve(-9.3, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 1.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.reserve( 9.0, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 51, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.reserve( 2,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 11, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve(-6,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.reserve( 10, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-8.0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 1.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-2.5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-1.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve( 0.5,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.reserve(-21.5, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(11, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(9,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(23, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(7,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(14, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.reserve(20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 0,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-4,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve(-24, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.reserve( 24, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-10, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.reserve(-18, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-3.999, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-1.3,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-8.1,   ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 8.1,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve(-2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 2.0,   ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.reserve( 10.0,  ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 5,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve( 7,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.reserve(-3,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve( 2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-2,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.reserve(-20, ReservationMethod::Interpolate));

//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-0.1,  ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 25.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve(-25.0, ReservationMethod::Interpolate));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 8.1,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 2.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 6.0,  ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.reserve( 20.0, ReservationMethod::Interpolate));


//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  20);
//    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -9);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  15.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -15.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 9);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder),  9.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), -9.0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 50);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder),  10);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -10);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::UpperBorder),  20.5);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderValue(BorderRange::LowerBorder), -21.5);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::UpperBorder), 22);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderValue(BorderRange::LowerBorder), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::UpperBorder),  22);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getBorderValue(BorderRange::LowerBorder), -22);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::UpperBorder),  10.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderValue(BorderRange::LowerBorder), -10.0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder),  20);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), -20);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::UpperBorder),  24.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderValue(BorderRange::LowerBorder), -24.0);

//    EXPECT_EQ(OpenRangeIdManager_int.size(), 8);
//    EXPECT_EQ(OpenRangeIdManager_float.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 9);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 11);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 10);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 11);

//    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 22);
//    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 22);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 6);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 18);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 3);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 15);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 5);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 4);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 4);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 16);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 4);


//    optional_id_int = OpenRangeIdManager_int.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -8);
//    optional_id_int = OpenRangeIdManager_int.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -7);
//    optional_id_int = OpenRangeIdManager_int.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -6);

//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -15.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -14.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -13.0);

//    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 3);
//    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 4);
//    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 5);

//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -8);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -6);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -4);

//    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -7.5);
//    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -6.0);
//    optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -4.5);

//    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 8);
//    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 12);
//    optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_unsigned.has_value());
//    EXPECT_EQ(*optional_id_unsigned, 14);

//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -8);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 4);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 6);

//    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -19.5);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -17.5);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -15.5);

//    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 2);
//    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 4);
//    optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 16);

//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -22);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -14);
//    optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, 10);

//    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -8.0);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -6.0);
//    optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);

//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -18);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -16);
//    optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
//    ASSERT_TRUE(optional_id_int.has_value());
//    EXPECT_EQ(*optional_id_int, -14);

//    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -24.0);
//    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -22.0);
//    optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, -18.0);


//    OpenRangeIdManager_int.setHardStep(true);
//    OpenRangeIdManager_float.setHardStep(true);
//    OpenRangeIdManager_unsigned.setHardStep(true);

//    OpenRangeIdManager_int_Start_2_Step_2.setHardStep(true);
//    OpenRangeIdManager_float_Start_1p5_Step_1p5.setHardStep(true);
//    OpenRangeIdManager_unsigned_Start_2_Step_2.setHardStep(true);

//    OpenRangeIdManager_int_Start_n2_Step_n2.setHardStep(true);
//    OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setHardStep(true);
//    OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setHardStep(true);

//    OpenRangeIdManager_int_Start_n2_Step_4.setHardStep(true);
//    OpenRangeIdManager_float_int_Start_n2p0_Step_2.setHardStep(true);

//    OpenRangeIdManager_int_Start_2_Step_n2.setHardStep(true);
//    OpenRangeIdManager_float_Start_2p0_Step_n2p0.setHardStep(true);

//    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.isHardStep());

//    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.isHardStep());
//    EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.isHardStep());

//    EXPECT_EQ(OpenRangeIdManager_int.size(), 11);
//    EXPECT_EQ(OpenRangeIdManager_float.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 7);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.size(), 9);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.size(), 10);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.size(), 9);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.size(), 10);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.size(), 10);

//    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 19);
//    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 20);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_1p5_Step_1p5.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeIdsSize(), 15);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_Start_2_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeIdsSize(), 12);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getFreeIdsSize(), 1);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_n2_Step_4.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeIdsSize(), 2);
//    EXPECT_EQ(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getReservedIdsSize(), 0);

//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getFreeIdsSize(), 11);
//    EXPECT_EQ(OpenRangeIdManager_int_Start_2_Step_n2.getReservedIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeIdsSize(), 14);
//    EXPECT_EQ(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getReservedIdsSize(), 0);

//    EXPECT_TRUE (OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getBorderState(BorderRange::LowerBorder));

//    EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_n2_Step_4.getBorderState(BorderRange::LowerBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_int_Start_n2p0_Step_2.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE (OpenRangeIdManager_float_Start_2p0_Step_n2p0.getBorderState(BorderRange::LowerBorder));
//}

TEST_F(OpenRangeIdManagerTests, SituationalTest_1)
{
    for (size_t i = 0; i < 3; ++i)
    {
        EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder,  2));
        EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, -2));
        EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder,  2.0));
        EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, -2.0));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder, 2));
        EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 2));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 2));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder,  5.1));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -5.1));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 7));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 0));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  8));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -2));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::UpperBorder,  2.4));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setBorderLimit(BorderRange::LowerBorder, -2.4));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
        EXPECT_TRUE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setBorderLimit(BorderRange::LowerBorder, 6));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::UpperBorder,  1));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_n2_Step_4.setBorderLimit(BorderRange::LowerBorder, -2));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::UpperBorder,  2));
        EXPECT_TRUE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.setBorderLimit(BorderRange::LowerBorder, -2));

        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder,  2));
        EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -1));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::UpperBorder,  2));
        EXPECT_TRUE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.setBorderLimit(BorderRange::LowerBorder, -2));

        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 0);
        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 1);
        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 2);
        EXPECT_FALSE(OpenRangeIdManager_int.getFreeId().has_value());

        optional_id_float = OpenRangeIdManager_float.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
        optional_id_float = OpenRangeIdManager_float.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
        optional_id_float = OpenRangeIdManager_float.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
        EXPECT_FALSE(OpenRangeIdManager_float.getFreeId().has_value());

        optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 0);
        optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 1);
        optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 2);
        EXPECT_FALSE(OpenRangeIdManager_unsigned.getFreeId().has_value());

        optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 2);
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.getFreeId().has_value());

        optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 1.5);
        optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
        optional_id_float = OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 4.5);
        EXPECT_FALSE(OpenRangeIdManager_float_Start_1p5_Step_1p5.getFreeId().has_value());

        optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 2);
        optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 4);
        optional_id_unsigned = OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_unsigned.has_value());
        EXPECT_EQ(*optional_id_unsigned, 6);
        EXPECT_FALSE(OpenRangeIdManager_unsigned_Start_2_Step_2.getFreeId().has_value());

        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -2);
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_n2.getFreeId().has_value());

        optional_id_float = OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -1.5);
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n1p5_Step_n2.getFreeId().has_value());

        optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 10);
        optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 8);
        optional_id_int = OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 6);
        EXPECT_FALSE(OpenRangeIdManager_unsigned_int_Start_10_Step_n2.getFreeId().has_value());

        optional_id_int = OpenRangeIdManager_int_Start_n2_Step_4.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, -2);
        EXPECT_FALSE(OpenRangeIdManager_int_Start_n2_Step_4.getFreeId().has_value());

        optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
        optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
        optional_id_float = OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
        EXPECT_FALSE(OpenRangeIdManager_float_int_Start_n2p0_Step_2.getFreeId().has_value());

        optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 2);
        optional_id_int = OpenRangeIdManager_int_Start_2_Step_n2.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 0);
        EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_n2.getFreeId().has_value());

        optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
        optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
        optional_id_float = OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId();
        ASSERT_TRUE(optional_id_float.has_value());
        EXPECT_FLOAT_EQ(*optional_id_float, -2.0);
        EXPECT_FALSE(OpenRangeIdManager_float_Start_2p0_Step_n2p0.getFreeId().has_value());


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

        if (i == 1) {
            OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

            OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
            OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
        }

        if (i == 2) {
            OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_Start_1p5_Step_1p5.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_unsigned_Start_2_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_n2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_int_Start_n1p5_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_unsigned_int_Start_10_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_n2_Step_4.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_int_Start_n2p0_Step_2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

            OpenRangeIdManager_int_Start_2_Step_n2.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
            OpenRangeIdManager_float_Start_2p0_Step_n2p0.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
        }
    }
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_2)
{
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(2, ReservationMethod::Interpolate));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder,  3));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, -2));

    EXPECT_TRUE(OpenRangeIdManager_float.reserve(2.0, ReservationMethod::Interpolate));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::UpperBorder,  3.0));
    EXPECT_TRUE(OpenRangeIdManager_float.setBorderLimit(BorderRange::LowerBorder, -2.0));

    EXPECT_TRUE(OpenRangeIdManager_unsigned.reserve(2, ReservationMethod::Interpolate));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::UpperBorder, 3));
    EXPECT_TRUE(OpenRangeIdManager_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.reserve(-2, ReservationMethod::Interpolate));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder,  6));
    EXPECT_TRUE(OpenRangeIdManager_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, -4));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 3);
    EXPECT_FALSE(OpenRangeIdManager_int.getFreeId().has_value());

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    EXPECT_FALSE(OpenRangeIdManager_float.getFreeId().has_value());

    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 1);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 0);
    optional_id_unsigned = OpenRangeIdManager_unsigned.getFreeId();
    ASSERT_TRUE(optional_id_unsigned.has_value());
    EXPECT_EQ(*optional_id_unsigned, 3);
    EXPECT_FALSE(OpenRangeIdManager_unsigned.getFreeId().has_value());

    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int_Start_2_Step_2.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 6);
    EXPECT_FALSE(OpenRangeIdManager_int_Start_2_Step_2.getFreeId().has_value());
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_3)
{
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(6));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(5));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(3));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 3);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 6);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 7);


    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 4.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve(-1.0));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  4.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_4)
{
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(6));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(5));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(3));

    EXPECT_TRUE(OpenRangeIdManager_int.free(5));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 0);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 3);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 5);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 6);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 7);

    EXPECT_TRUE(OpenRangeIdManager_int.free(6));
    EXPECT_TRUE(OpenRangeIdManager_int.free(5));
    EXPECT_TRUE(OpenRangeIdManager_int.free(4));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 7);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int.free(7));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 3);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));


    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 4.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve(-1.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 4);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_float.free(1.0));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  4.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  5.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_float.free(3.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(4.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.free(5.0));

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  5.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
    optional_id_float = OpenRangeIdManager_float.getFreeId();
    ASSERT_TRUE(optional_id_float.has_value());
    EXPECT_FLOAT_EQ(*optional_id_float, 6.0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  6.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
}

//TEST_F(OpenRangeIdManagerTests, SituationalTest_5_1)
//{
//    OpenRangeIdManager_float.setHardStep(false);
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 2);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
//}

//TEST_F(OpenRangeIdManagerTests, SituationalTest_5_2)
//{
//    OpenRangeIdManager_float.setHardStep(false);
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.0));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 2);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
//}

TEST_F(OpenRangeIdManagerTests, SituationalTest_6_1)
{
    OpenRangeIdManager_float.setHardStep(false);
    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.0, ReservationMethod::Interpolate));
    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_float.free(4.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
}

//TEST_F(OpenRangeIdManagerTests, SituationalTest_6_2)
//{
//    OpenRangeIdManager_float.setHardStep(false);
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.0));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.0, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 4.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
//}

//TEST_F(OpenRangeIdManagerTests, SituationalTest_7_1)
//{
//    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float.setHardStep(false);
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_FALSE(OpenRangeIdManager_float.free(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);
//}

//TEST_F(OpenRangeIdManagerTests, SituationalTest_7_2)
//{
//    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
//    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
//    OpenRangeIdManager_float.setHardStep(false);
//    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.0));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_TRUE (OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5, ReservationMethod::Interpolate));
//    EXPECT_FALSE(OpenRangeIdManager_float.reserve(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 2);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
//    EXPECT_TRUE (OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.5));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 1);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
//    EXPECT_TRUE (OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    EXPECT_TRUE(OpenRangeIdManager_float.free(4.0));

//    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
//    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 3);
//    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 4.0);
//    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
//    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 0.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 1.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 2.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 3.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 4.0);
//    optional_id_float = OpenRangeIdManager_float.getFreeId();
//    ASSERT_TRUE(optional_id_float.has_value());
//    EXPECT_FLOAT_EQ(*optional_id_float, 5.0);
//}

TEST_F(OpenRangeIdManagerTests, SituationalTest_8_1)
{
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-2));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-1));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 1);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int.reserve(0));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 5);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));


    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve(-1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve(-2.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 4);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 1.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_float.reserve(0.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 5);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -2.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_8_2)
{
    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-2));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-1));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int.reserve(0));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 5);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));


    OpenRangeIdManager_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    EXPECT_EQ(OpenRangeIdManager_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 2.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve( 1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve(-1.0));
    EXPECT_TRUE(OpenRangeIdManager_float.reserve(-2.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 4);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -2.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_float.reserve(0.0));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 5);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder),  2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), -2.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_9)
{
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_TRUE(OpenRangeIdManager_int.reserve( 2));
        EXPECT_TRUE(OpenRangeIdManager_int.reserve(-2));

        EXPECT_EQ(OpenRangeIdManager_int.size(), 2);
        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);

        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
        EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
        EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

        if (i == 0)
            EXPECT_TRUE(OpenRangeIdManager_int.reserve(0));
        if (i == 1)
            EXPECT_TRUE(OpenRangeIdManager_int.reserve(0, ReservationMethod::Interpolate));
        if (i == 2)
            EXPECT_TRUE(OpenRangeIdManager_int.reserve(0, ReservationMethod::ReserveRange));

        EXPECT_EQ(OpenRangeIdManager_int.size(), 3);
        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 2);

        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

        optional_id_int = OpenRangeIdManager_int.getFreeId();
        ASSERT_TRUE(optional_id_int.has_value());
        EXPECT_EQ(*optional_id_int, 1);

        EXPECT_EQ(OpenRangeIdManager_int.size(), 4);
        EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
        EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 1);

        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 2);
        EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
        EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

        OpenRangeIdManager_int.freeAll();
    }
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_10)
{
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(2));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(1));
    EXPECT_TRUE(OpenRangeIdManager_int.free(1));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, 1));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 1);

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 3);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 3);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 1);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_11)
{
    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);

    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-1));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 2));
    EXPECT_TRUE(OpenRangeIdManager_int.free(2));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 3);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -1);
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int.reserve(3));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  3);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -1);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 2);

    optional_id_int = OpenRangeIdManager_int.getFreeId();
    ASSERT_TRUE(optional_id_int.has_value());
    EXPECT_EQ(*optional_id_int, 4);
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_12)
{
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 0));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve( 1));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-1));

    EXPECT_TRUE(OpenRangeIdManager_int.reserve(6));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(7));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(9));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(12));

    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-6));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-7));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-9));
    EXPECT_TRUE(OpenRangeIdManager_int.reserve(-12));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 11);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 8);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  1);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -1);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::UpperBorder,  3));
    EXPECT_TRUE(OpenRangeIdManager_int.setBorderLimit(BorderRange::LowerBorder, -3));

    EXPECT_EQ(OpenRangeIdManager_int.size(), 3);
    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder),  1);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), -1);
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_14)
{
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);


    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);


    OpenRangeIdManager_int.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(OpenRangeIdManager_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
}

TEST_F(OpenRangeIdManagerTests, SituationalTest_15)
{
    OpenRangeIdManager_float.setHardStep(false);
    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);

    EXPECT_TRUE(OpenRangeIdManager_float.reserve(0.5, ReservationMethod::ReserveRange));

    EXPECT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(OpenRangeIdManager_float.getBorderState(BorderRange::LowerBorder));

    EXPECT_EQ(OpenRangeIdManager_float.size(), 2);
    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 1);
}

TEST(SingleTests, CopyAndMoveTest)
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

    EXPECT_FALSE(OpenRangeIdManager_int.reserve(-90));
    EXPECT_TRUE (OpenRangeIdManager_int.reserve(-50));

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

    EXPECT_FALSE(OpenRangeIdManager_float.reserve(90.0));
    EXPECT_TRUE (OpenRangeIdManager_float.reserve(50.0));
    EXPECT_TRUE (OpenRangeIdManager_float.reserve(0.5));

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

    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve(50));
    EXPECT_TRUE (OpenRangeIdManager_unsigned.reserve(33));
    EXPECT_FALSE(OpenRangeIdManager_unsigned.reserve(90));


    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 5);


    OpenRangeIdManager<int> OpenRangeIdManager_int_cc(OpenRangeIdManager_int);
    OpenRangeIdManager<float> OpenRangeIdManager_float_cc(OpenRangeIdManager_float);
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_cc(OpenRangeIdManager_unsigned);

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 5);


    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_cc.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_cc.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.size(), 5);


    OpenRangeIdManager<int> OpenRangeIdManager_int_cm(std::move(OpenRangeIdManager_int));
    OpenRangeIdManager<float> OpenRangeIdManager_float_cm(std::move(OpenRangeIdManager_float));
    OpenRangeIdManager<unsigned> OpenRangeIdManager_unsigned_cm(std::move(OpenRangeIdManager_unsigned));

    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int.size(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned.size(), 0);


    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_cm.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cm.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_cm.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderValue(BorderRange::LowerBorder), 0);

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
    EXPECT_EQ(OpenRangeIdManager_int_oc.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_oc.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int_oc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_oc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_oc.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_oc.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_oc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_oc.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_oc.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_oc.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float_oc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_oc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_oc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_oc.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_oc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_oc.size(), 5);


    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cc.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_cc.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cc.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float_cc.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cc.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cc.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_cc.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cc.getBorderValue(BorderRange::LowerBorder), 0);

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
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_cm.size(), 0);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_cm.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cm.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_cm.size(), 0);

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_cm.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.getReservedIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_cm.size(), 0);


    EXPECT_EQ(OpenRangeIdManager_int_om.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(OpenRangeIdManager_int_om.getBorderLimit(BorderRange::LowerBorder), -50);
    EXPECT_EQ(OpenRangeIdManager_int_om.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_int_om.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_int_om.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_int_om.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_int_om.getReservedIdsSize(), 1);
    EXPECT_EQ(OpenRangeIdManager_int_om.size(), 4);

    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_om.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_om.getBorderLimit(BorderRange::LowerBorder), -50.5);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_om.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(OpenRangeIdManager_float_om.getBorderValue(BorderRange::LowerBorder), 0.0);

    EXPECT_FALSE(OpenRangeIdManager_float_om.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_float_om.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_float_om.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_float_om.size(), 5);

    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getBorderLimit(BorderRange::LowerBorder), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_TRUE(OpenRangeIdManager_unsigned_om.isHardStep());

    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getFreeIdsSize(), 0);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.getReservedIdsSize(), 2);
    EXPECT_EQ(OpenRangeIdManager_unsigned_om.size(), 5);
}
