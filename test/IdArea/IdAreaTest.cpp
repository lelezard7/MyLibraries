#include "IdManager.h"

#include <gtest/gtest.h>

using namespace ONF;


struct IdAreaTests : public ::testing::Test
{
    IdArea<int> IdArea_int;
    IdArea<float> IdArea_float;
    IdArea<unsigned> IdArea_unsigned;

    IdArea<int> IdArea_int_Start_2_Step_2;
    IdArea<float> IdArea_float_Start_1p5_Step_1p5;
    IdArea<unsigned> IdArea_unsigned_Start_2_Step_2;

    IdArea<int> IdArea_int_Start_n2_Step_2;
    IdArea<float> IdArea_float_Start_n2_Step_1p5;
    IdArea<unsigned> IdArea_unsigned_Start_n2_Step_2;

    IdArea<int> IdArea_int_Start_2_Step_n2;
    IdArea<float> IdArea_float_Start_2_Step_n1p5;
    IdArea<unsigned> IdArea_unsigned_Start_2_Step_n2;

    IdArea<int> IdArea_int_Start_n2_Step_n2;
    IdArea<float> IdArea_float_Start_n1p5_Step_n1p5;
    IdArea<unsigned> IdArea_unsigned_Start_n2_Step_n2;

    IdAreaTests()
        : IdArea_int_Start_2_Step_2(2, 2),
          IdArea_float_Start_1p5_Step_1p5(1.5, 1.5),
          IdArea_unsigned_Start_2_Step_2(2, 2),

          IdArea_int_Start_n2_Step_2(-2, 2),
          IdArea_float_Start_n2_Step_1p5(-2.0, 1.5),
          IdArea_unsigned_Start_n2_Step_2(-2, 2),

          IdArea_int_Start_2_Step_n2(2, -2),
          IdArea_float_Start_2_Step_n1p5(2.0, -1.5),
          IdArea_unsigned_Start_2_Step_n2(2, -2),

          IdArea_int_Start_n2_Step_n2(-2, -2),
          IdArea_float_Start_n1p5_Step_n1p5(-1.5, -1.5),
          IdArea_unsigned_Start_n2_Step_n2(-2, -2) {};
};


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(SingleTests, Function_isStandardId)
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

TEST_F(IdAreaTests, getStart)
{
    EXPECT_EQ(IdArea_int.getStart(), 0);
    EXPECT_FLOAT_EQ(IdArea_float.getStart(), 0.0);
    EXPECT_EQ(IdArea_unsigned.getStart(), 0);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getStart(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getStart(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getStart(), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getStart(), -2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getStart(), -2.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getStart(), -2);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getStart(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getStart(), 2.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getStart(), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getStart(), -2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getStart(), -1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getStart(), -2);
}

TEST_F(IdAreaTests, getStep)
{
    EXPECT_EQ(IdArea_int.getStep(), 1);
    EXPECT_FLOAT_EQ(IdArea_float.getStep(), 1.0);
    EXPECT_EQ(IdArea_unsigned.getStep(), 1);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getStep(), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getStep(), 2);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getStep(), -2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getStep(), -2);
}

TEST_F(IdAreaTests, BorderState)
{
    EXPECT_FALSE(IdArea_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));


    IdArea_int.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int.setBorderState(BorderRange::LowerBorder, true);
    IdArea_float.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float.setBorderState(BorderRange::LowerBorder, true);
    IdArea_unsigned.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned.setBorderState(BorderRange::LowerBorder, true);

    IdArea_int_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, true);
    IdArea_float_Start_1p5_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_1p5_Step_1p5.setBorderState(BorderRange::LowerBorder, true);
    IdArea_unsigned_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, true);

    IdArea_int_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, true);
    IdArea_float_Start_n2_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_n2_Step_1p5.setBorderState(BorderRange::LowerBorder, true);
    IdArea_unsigned_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, true);

    IdArea_int_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, true);
    IdArea_float_Start_2_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_2_Step_n1p5.setBorderState(BorderRange::LowerBorder, true);
    IdArea_unsigned_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, true);

    IdArea_int_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, true);
    IdArea_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::LowerBorder, true);
    IdArea_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, true);

    EXPECT_TRUE(IdArea_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdArea_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));


    IdArea_int.setBorderState(BorderRange::UpperBorder, false);
    IdArea_float.setBorderState(BorderRange::UpperBorder, false);
    IdArea_unsigned.setBorderState(BorderRange::UpperBorder, false);

    IdArea_int_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, false);
    IdArea_float_Start_1p5_Step_1p5.setBorderState(BorderRange::UpperBorder, false);
    IdArea_unsigned_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, false);

    IdArea_int_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, false);
    IdArea_float_Start_n2_Step_1p5.setBorderState(BorderRange::UpperBorder, false);
    IdArea_unsigned_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, false);

    IdArea_int_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, false);
    IdArea_float_Start_2_Step_n1p5.setBorderState(BorderRange::UpperBorder, false);
    IdArea_unsigned_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, false);

    IdArea_int_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, false);
    IdArea_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::UpperBorder, false);
    IdArea_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, false);

    EXPECT_FALSE(IdArea_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));


    IdArea_int.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int.setBorderState(BorderRange::LowerBorder, false);
    IdArea_float.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float.setBorderState(BorderRange::LowerBorder, false);
    IdArea_unsigned.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned.setBorderState(BorderRange::LowerBorder, false);

    IdArea_int_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, false);
    IdArea_float_Start_1p5_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_1p5_Step_1p5.setBorderState(BorderRange::LowerBorder, false);
    IdArea_unsigned_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, false);

    IdArea_int_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, false);
    IdArea_float_Start_n2_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_n2_Step_1p5.setBorderState(BorderRange::LowerBorder, false);
    IdArea_unsigned_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, false);

    IdArea_int_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, false);
    IdArea_float_Start_2_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_2_Step_n1p5.setBorderState(BorderRange::LowerBorder, false);
    IdArea_unsigned_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, false);

    IdArea_int_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_int_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, false);
    IdArea_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdArea_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::LowerBorder, false);
    IdArea_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdArea_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, false);

    EXPECT_TRUE (IdArea_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdArea_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
}

TEST_F(IdAreaTests, BorderLimit)
{
    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdArea_float.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());


    EXPECT_TRUE (IdArea_int.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_int.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdArea_float.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdArea_unsigned.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_unsigned.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdArea_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, -1));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, -1));

    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdArea_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdArea_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -1));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -1));

    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdArea_float.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());


    EXPECT_FALSE(IdArea_int.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_int.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdArea_float.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdArea_float.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_TRUE (IdArea_unsigned.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_FALSE(IdArea_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdArea_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 1));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 1));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdArea_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 1));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 1));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdArea_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 1);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder),  10);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), 1);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder),  10);
}

TEST_F(IdAreaTests, BorderValue)
{
    EXPECT_EQ(IdArea_int.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(IdArea_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(IdArea_unsigned.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(IdArea_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderValue(BorderRange::UpperBorder), -2.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderValue(BorderRange::LowerBorder), -2.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), -2);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderValue(BorderRange::LowerBorder), 2.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::LowerBorder), -1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);


    EXPECT_TRUE(IdArea_int.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE(IdArea_int.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_TRUE(IdArea_float.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_TRUE(IdArea_float.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE(IdArea_unsigned.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE(IdArea_unsigned.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_int_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdArea_int_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_EQ(IdArea_int.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderValue(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderValue(BorderRange::LowerBorder), 10.0);
    EXPECT_EQ(IdArea_unsigned.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderValue(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderValue(BorderRange::LowerBorder), 10.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderValue(BorderRange::LowerBorder), 2.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::LowerBorder), -1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);


    EXPECT_FALSE(IdArea_int.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdArea_int.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_FALSE(IdArea_float.setBorderValue(BorderRange::LowerBorder, 20.0));
    EXPECT_TRUE (IdArea_float.setBorderValue(BorderRange::UpperBorder, 20.0));
    EXPECT_FALSE(IdArea_unsigned.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdArea_unsigned.setBorderValue(BorderRange::UpperBorder, 20));

    EXPECT_FALSE(IdArea_int_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdArea_int_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::LowerBorder, 18.0));
    EXPECT_TRUE (IdArea_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::UpperBorder, 18.0));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 21));

    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdArea_int_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.setBorderValue(BorderRange::LowerBorder, 17.5));
    EXPECT_TRUE (IdArea_float_Start_n2_Step_1p5.setBorderValue(BorderRange::UpperBorder, 17.5));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, -4));
    EXPECT_TRUE (IdArea_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, -4));

    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdArea_int_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_TRUE (IdArea_float_Start_2_Step_n1p5.setBorderValue(BorderRange::LowerBorder, -11.5));
    EXPECT_TRUE (IdArea_float_Start_2_Step_n1p5.setBorderValue(BorderRange::UpperBorder, -11.5));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 2));
    EXPECT_TRUE (IdArea_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 2));

    EXPECT_TRUE(IdArea_int_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, -22));
    EXPECT_TRUE(IdArea_int_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, -22));
    EXPECT_TRUE(IdArea_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::LowerBorder, -16.5));
    EXPECT_TRUE(IdArea_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::UpperBorder, -16.5));
    EXPECT_TRUE(IdArea_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, -2));
    EXPECT_TRUE(IdArea_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, -2));
}

TEST_F(IdAreaTests, moveBorder)
{
    IdArea<int>::Result result_int[10];
    IdArea<float>::Result result_float[10];
    IdArea<unsigned>::Result result_unsigned[10];

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.moveBorder(BorderRange::UpperBorder, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    result_int[5] = IdArea_int.moveBorder(BorderRange::LowerBorder, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.moveBorder(BorderRange::UpperBorder, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);

    result_float[5] = IdArea_float.moveBorder(BorderRange::LowerBorder, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[1] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[2] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[3] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[4] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    result_unsigned[5] = IdArea_unsigned.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[6] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[7] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[8] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[9] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_unsigned[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_unsigned[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_unsigned[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_unsigned[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.moveBorder(BorderRange::UpperBorder, 10);
    result_int[1] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    result_int[2] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    result_int[3] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    result_int[4] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    result_int[5] = IdArea_int.moveBorder(BorderRange::LowerBorder, 10);
    result_int[6] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    result_int[7] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    result_int[8] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    result_int[9] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 10)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value, 10) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, 18) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, 18) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value, -10) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -22) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -22) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.moveBorder(BorderRange::UpperBorder, 10);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);

    result_float[5] = IdArea_float.moveBorder(BorderRange::LowerBorder, 10);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 10)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value, 10.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value, 16.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, 13.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value, 17.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, 13.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value, -10.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value, -13.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -17.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value, -13.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -16.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 10);
    EXPECT_EQ(result_unsigned[0].stepCount, 10);

    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 22);
    EXPECT_EQ(result_unsigned[0].stepCount, 10);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 1);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -22);
    EXPECT_EQ(result_unsigned[0].stepCount, 10);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 1);

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.moveBorder(BorderRange::UpperBorder, -3);
    result_int[1] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    result_int[2] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    result_int[3] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    result_int[4] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);

    result_int[5] = IdArea_int.moveBorder(BorderRange::LowerBorder, -3);
    result_int[6] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    result_int[7] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    result_int[8] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    result_int[9] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, -3)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.moveBorder(BorderRange::UpperBorder, -3);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);

    result_float[5] = IdArea_float.moveBorder(BorderRange::LowerBorder, -3);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, -3)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 7);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 3);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 16);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 6);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -8);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -16);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, -1);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.moveBorder(BorderRange::UpperBorder, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    result_int[5] = IdArea_int.moveBorder(BorderRange::LowerBorder, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.moveBorder(BorderRange::UpperBorder, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);

    result_float[5] = IdArea_float.moveBorder(BorderRange::LowerBorder, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 7);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 3);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 16);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 6);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -8);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -16);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.moveBorder(BorderRange::UpperBorder, -7);
    result_int[1] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    result_int[2] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    result_int[3] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);
    result_int[4] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);

    result_int[5] = IdArea_int.moveBorder(BorderRange::LowerBorder, -7);
    result_int[6] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    result_int[7] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    result_int[8] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);
    result_int[9] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, -7)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.moveBorder(BorderRange::UpperBorder, -7);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, -7);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, -7);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, -7);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, -7);

    result_float[5] = IdArea_float.moveBorder(BorderRange::LowerBorder, -7);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -7);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, -7);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, -7);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -7);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, -7)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 3);
    EXPECT_EQ(result_unsigned[0].stepCount, -4);

    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 3);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 6);
    EXPECT_EQ(result_unsigned[0].stepCount, -5);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 6);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -16);
    EXPECT_EQ(result_unsigned[0].stepCount, -4);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -16);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);
}

TEST_F(IdAreaTests, reset)
{
    IdArea_int.moveBorder(BorderRange::UpperBorder, -17);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 20);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -2);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 44);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 900);

    IdArea_int.moveBorder(BorderRange::LowerBorder, 0);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -90);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -55);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 1);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 3111);

    IdArea_float.moveBorder(BorderRange::UpperBorder, 1);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 3);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 6099);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 6);

    IdArea_float.moveBorder(BorderRange::LowerBorder, 0);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -10);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 1);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 700);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -50);

    IdArea_unsigned.moveBorder(BorderRange::UpperBorder, -17);
    IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 20);
    IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -2);
    IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 44);
    IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 900);

    IdArea_unsigned.moveBorder(BorderRange::LowerBorder, 1);
    IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 31111);
    IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 3);
    IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 2);


    IdArea_int.reset();
    IdArea_int_Start_2_Step_2.reset();
    IdArea_int_Start_n2_Step_2.reset();
    IdArea_int_Start_2_Step_n2.reset();
    IdArea_int_Start_n2_Step_n2.reset();

    IdArea_float.reset();
    IdArea_float_Start_1p5_Step_1p5.reset();
    IdArea_float_Start_n2_Step_1p5.reset();
    IdArea_float_Start_2_Step_n1p5.reset();
    IdArea_float_Start_n1p5_Step_n1p5.reset();

    IdArea_unsigned.reset();
    IdArea_unsigned_Start_2_Step_2.reset();
    IdArea_unsigned_Start_n2_Step_2.reset();
    IdArea_unsigned_Start_2_Step_n2.reset();
    IdArea_unsigned_Start_n2_Step_n2.reset();


    IdArea<int>::Result result_int[10];
    IdArea<float>::Result result_float[10];
    IdArea<unsigned>::Result result_unsigned[10];

    result_int[0] = IdArea_int.moveBorder(BorderRange::UpperBorder, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    result_int[5] = IdArea_int.moveBorder(BorderRange::LowerBorder, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.moveBorder(BorderRange::UpperBorder, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);

    result_float[5] = IdArea_float.moveBorder(BorderRange::LowerBorder, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[1] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[2] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[3] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    result_unsigned[4] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    result_unsigned[5] = IdArea_unsigned.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[6] = IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[7] = IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[8] = IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    result_unsigned[9] = IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_unsigned[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_unsigned[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_unsigned[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_unsigned[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }
}

TEST_F(IdAreaTests, getIdInfo_1)
{
    IdArea<int>::Result result_int[10];
    IdArea<float>::Result result_float[10];
    IdArea<unsigned>::Result result_unsigned[10];


    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 0);
    result_unsigned[1] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    result_unsigned[2] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    result_unsigned[3] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    result_unsigned[4] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);

    result_unsigned[5] = IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 0);
    result_unsigned[6] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    result_unsigned[7] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    result_unsigned[8] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    result_unsigned[9] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_unsigned[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_unsigned[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_unsigned[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_unsigned[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 10);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 10);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_OUT_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 10)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value, 10) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, 18) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, 18) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value, -10) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -22) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -22) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 10);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 10);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 10);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 10);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 10);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 10);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 10);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 10);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 10);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_OUT_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 10)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value, 10.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value, 16.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, 13.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value, 17.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, 13.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value, -10.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value, -13.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -17.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value, -13.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -16.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 10);
    EXPECT_EQ(result_unsigned[0].stepCount, 10);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 22);
    EXPECT_EQ(result_unsigned[0].stepCount, 10);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 1);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -22);
    EXPECT_EQ(result_unsigned[0].stepCount, 10);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 1);

    //-----------------------------------------------------------------------------

    IdArea_int.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    IdArea_int.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, -3);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, -3);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_IN_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, -3)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    IdArea_float.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);

    IdArea_float.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);

    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, -3);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -3);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -3);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -3);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -3);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, -3);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -3);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -3);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -3);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_IN_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, -3)                     << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    IdArea_unsigned.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    IdArea_unsigned.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 7);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 3);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 16);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 6);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -8);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -16);
    EXPECT_EQ(result_unsigned[0].stepCount, -3);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, -1);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -2);
    EXPECT_EQ(result_unsigned[0].stepCount, -1);

    //-----------------------------------------------------------------------------

    IdArea_int.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);

    IdArea_int.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    IdArea_float.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);

    IdArea_float.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);

    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i].errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i].state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i].stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    IdArea_unsigned.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);

    IdArea_unsigned.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    IdArea_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 7);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 3);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 16);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 6);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -8);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, -16);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 2);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(result_unsigned[0].errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0].position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0].state);
    EXPECT_EQ(result_unsigned[0].value, 0);
    EXPECT_EQ(result_unsigned[0].stepCount, 0);
}

TEST_F(IdAreaTests, getIdInfo_2)
{
    std::optional<IdArea<int>::Result> result_int[10];
    std::optional<IdArea<float>::Result> result_float[10];
    std::optional<IdArea<unsigned>::Result> result_unsigned[10];


    EXPECT_TRUE (IdArea_int.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());

    EXPECT_TRUE (IdArea_int.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());


    EXPECT_FALSE(IdArea_float.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());

    EXPECT_FALSE(IdArea_float.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());


    EXPECT_TRUE (IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());

    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 30, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 0);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 30, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 0);

    ASSERT_TRUE(result_int[0].has_value());
    ASSERT_TRUE(result_int[1].has_value());
    ASSERT_TRUE(result_int[2].has_value());
    ASSERT_TRUE(result_int[3].has_value());
    ASSERT_TRUE(result_int[4].has_value());

    EXPECT_FALSE(result_int[5].has_value());
    EXPECT_FALSE(result_int[6].has_value());
    EXPECT_FALSE(result_int[7].has_value());
    EXPECT_FALSE(result_int[8].has_value());
    EXPECT_FALSE(result_int[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
        }
    }

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, -30, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 0);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, -30, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 0);

    EXPECT_FALSE(result_int[0].has_value());
    EXPECT_FALSE(result_int[1].has_value());
    EXPECT_FALSE(result_int[2].has_value());
    EXPECT_FALSE(result_int[3].has_value());
    EXPECT_FALSE(result_int[4].has_value());

    ASSERT_TRUE(result_int[5].has_value());
    ASSERT_TRUE(result_int[6].has_value());
    ASSERT_TRUE(result_int[7].has_value());
    ASSERT_TRUE(result_int[8].has_value());
    ASSERT_TRUE(result_int[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_EQ(result_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 30.0, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 31.5, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 32.5, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 32.0, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 30.0, 0);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 30.0, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 31.5, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 32.5, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 32.0, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 30.0, 0);

    ASSERT_TRUE(result_float[0].has_value());
    ASSERT_TRUE(result_float[1].has_value());
    ASSERT_TRUE(result_float[2].has_value());
    ASSERT_TRUE(result_float[3].has_value());
    ASSERT_TRUE(result_float[4].has_value());

    EXPECT_FALSE(result_float[5].has_value());
    EXPECT_FALSE(result_float[6].has_value());
    EXPECT_FALSE(result_float[7].has_value());
    EXPECT_FALSE(result_float[8].has_value());
    EXPECT_FALSE(result_float[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i]->value, 30.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i]->value, 31.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i]->value, 32.5) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i]->value, 32.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i]->value, 30.0) << "The error occurred when: i == " << i;    break;
        }
    }

    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, -30.0, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -31.5, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -32.0, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -32.5, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -30.0, 0);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, -30.0, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -31.5, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -32.0, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -32.5, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -30.0, 0);

    EXPECT_FALSE(result_float[0].has_value());
    EXPECT_FALSE(result_float[1].has_value());
    EXPECT_FALSE(result_float[2].has_value());
    EXPECT_FALSE(result_float[3].has_value());
    EXPECT_FALSE(result_float[4].has_value());

    ASSERT_TRUE(result_float[5].has_value());
    ASSERT_TRUE(result_float[6].has_value());
    ASSERT_TRUE(result_float[7].has_value());
    ASSERT_TRUE(result_float[8].has_value());
    ASSERT_TRUE(result_float[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_FLOAT_EQ(result_float[i]->value, -30.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i]->value, -31.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i]->value, -32.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i]->value, -32.5) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i]->value, -30.0) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 30, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 30);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -30, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -30);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 30, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, -30, 0).has_value());


    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 30);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0, 0).has_value());

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 0);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);


    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 30);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);


    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder,  30, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder,  30, 0).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 0).has_value());


    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 0).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0, 0);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 0);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -1, 0).has_value());

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 0, 0);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 0);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 0, 0);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -2, 0);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -2, 0);

    ASSERT_TRUE(result_int[0].has_value());
    ASSERT_TRUE(result_int[1].has_value());
    ASSERT_TRUE(result_int[2].has_value());
    ASSERT_TRUE(result_int[3].has_value());
    ASSERT_TRUE(result_int[4].has_value());

    ASSERT_TRUE(result_int[5].has_value());
    ASSERT_TRUE(result_int[6].has_value());
    ASSERT_TRUE(result_int[7].has_value());
    ASSERT_TRUE(result_int[8].has_value());
    ASSERT_TRUE(result_int[9].has_value());

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_int[i]->border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_int[i]->border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i]->value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_int[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i]->value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 0.0, 0);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 1.5, 0);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -2.0, 0);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 2.0, 0);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -1.5, 0);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 0.0, 0);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 1.5, 0);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -2.0, 0);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 2.0, 0);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -1.5, 0);

    ASSERT_TRUE(result_float[0].has_value());
    ASSERT_TRUE(result_float[1].has_value());
    ASSERT_TRUE(result_float[2].has_value());
    ASSERT_TRUE(result_float[3].has_value());
    ASSERT_TRUE(result_float[4].has_value());

    ASSERT_TRUE(result_float[5].has_value());
    ASSERT_TRUE(result_float[6].has_value());
    ASSERT_TRUE(result_float[7].has_value());
    ASSERT_TRUE(result_float[8].has_value());
    ASSERT_TRUE(result_float[9].has_value());

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_float[i]->border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_float[i]->border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i]->value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i]->value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i]->value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i]->value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i]->value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(result_float[i]->value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i]->value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i]->value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i]->value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i]->value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 0, 0);
    result_unsigned[1] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    result_unsigned[2] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    result_unsigned[3] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    result_unsigned[4] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 0);

    result_unsigned[5] = IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 0, 0);
    result_unsigned[6] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    result_unsigned[7] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -2, 0);
    result_unsigned[8] = IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    result_unsigned[9] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -2, 0);

    ASSERT_TRUE(result_unsigned[0].has_value());
    ASSERT_TRUE(result_unsigned[1].has_value());
    ASSERT_TRUE(result_unsigned[2].has_value());
    ASSERT_TRUE(result_unsigned[3].has_value());
    ASSERT_TRUE(result_unsigned[4].has_value());

    ASSERT_TRUE(result_unsigned[5].has_value());
    ASSERT_TRUE(result_unsigned[6].has_value());
    ASSERT_TRUE(result_unsigned[7].has_value());
    ASSERT_TRUE(result_unsigned[8].has_value());
    ASSERT_TRUE(result_unsigned[9].has_value());

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result_unsigned[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i]->position, IDM_POS_ON_BORDER)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_unsigned[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_unsigned[i]->stepCount, 0)                      << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(result_unsigned[i]->border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(result_unsigned[i]->border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_unsigned[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(result_unsigned[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;
        }
    }

    //-----------------------------------------------------------------------------

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 30, 5);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 5);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 30, 5);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 5);

    ASSERT_TRUE(result_int[0].has_value());
    ASSERT_TRUE(result_int[1].has_value());
    ASSERT_TRUE(result_int[2].has_value());
    ASSERT_TRUE(result_int[3].has_value());
    ASSERT_TRUE(result_int[4].has_value());

    EXPECT_FALSE(result_int[5].has_value());
    EXPECT_FALSE(result_int[6].has_value());
    EXPECT_FALSE(result_int[7].has_value());
    EXPECT_FALSE(result_int[8].has_value());
    EXPECT_FALSE(result_int[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_OUT_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i]->value, 35) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
        }
    }

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, 30, -5);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, -5);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, 30, -5);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, -5);

    ASSERT_TRUE(result_int[0].has_value());
    ASSERT_TRUE(result_int[1].has_value());
    ASSERT_TRUE(result_int[2].has_value());
    ASSERT_TRUE(result_int[3].has_value());
    ASSERT_TRUE(result_int[4].has_value());

    EXPECT_FALSE(result_int[5].has_value());
    EXPECT_FALSE(result_int[6].has_value());
    EXPECT_FALSE(result_int[7].has_value());
    EXPECT_FALSE(result_int[8].has_value());
    EXPECT_FALSE(result_int[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_IN_RANGE)        << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(result_int[i]->value, 25) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(result_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(result_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(result_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(result_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
        }
    }

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, -30, 5);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 5);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 5);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 5);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 5);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, -30, 5);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 5);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 5);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 5);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 5);

    EXPECT_FALSE(result_int[0].has_value());
    EXPECT_FALSE(result_int[1].has_value());
    EXPECT_FALSE(result_int[2].has_value());
    EXPECT_FALSE(result_int[3].has_value());
    EXPECT_FALSE(result_int[4].has_value());

    ASSERT_TRUE(result_int[5].has_value());
    ASSERT_TRUE(result_int[6].has_value());
    ASSERT_TRUE(result_int[7].has_value());
    ASSERT_TRUE(result_int[8].has_value());
    ASSERT_TRUE(result_int[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_OUT_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_EQ(result_int[i]->value, -35) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
        }
    }

    result_int[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, -30, -5);
    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, -5);
    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, -5);
    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, -5);
    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, -5);

    result_int[5] = IdArea_int.getIdInfo(BorderRange::LowerBorder, -30, -5);
    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, -5);
    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, -5);
    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, -5);
    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, -5);

    EXPECT_FALSE(result_int[0].has_value());
    EXPECT_FALSE(result_int[1].has_value());
    EXPECT_FALSE(result_int[2].has_value());
    EXPECT_FALSE(result_int[3].has_value());
    EXPECT_FALSE(result_int[4].has_value());

    ASSERT_TRUE(result_int[5].has_value());
    ASSERT_TRUE(result_int[6].has_value());
    ASSERT_TRUE(result_int[7].has_value());
    ASSERT_TRUE(result_int[8].has_value());
    ASSERT_TRUE(result_int[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->position, IDM_POS_IN_RANGE)        << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(result_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_EQ(result_int[i]->value, -25) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
        }
    }


    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 30.0, 5);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 31.5, 5);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 32.5, 5);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 32.0, 5);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 30.0, 5);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 30.0, 5);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 31.5, 5);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 32.5, 5);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 32.0, 5);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 30.0, 5);

    ASSERT_TRUE(result_float[0].has_value());
    ASSERT_TRUE(result_float[1].has_value());
    ASSERT_TRUE(result_float[2].has_value());
    ASSERT_TRUE(result_float[3].has_value());
    ASSERT_TRUE(result_float[4].has_value());

    EXPECT_FALSE(result_float[5].has_value());
    EXPECT_FALSE(result_float[6].has_value());
    EXPECT_FALSE(result_float[7].has_value());
    EXPECT_FALSE(result_float[8].has_value());
    EXPECT_FALSE(result_float[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_OUT_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i]->value, 35.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i]->value, 39.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i]->value, 40.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i]->value, 39.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i]->value, 37.5) << "The error occurred when: i == " << i;    break;
        }
    }

    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, 30.0, -5);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 31.5, -5);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 32.5, -5);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 32.0, -5);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 30.0, -5);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, 30.0, -5);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 31.5, -5);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 32.5, -5);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 32.0, -5);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 30.0, -5);

    ASSERT_TRUE(result_float[0].has_value());
    ASSERT_TRUE(result_float[1].has_value());
    ASSERT_TRUE(result_float[2].has_value());
    ASSERT_TRUE(result_float[3].has_value());
    ASSERT_TRUE(result_float[4].has_value());

    EXPECT_FALSE(result_float[5].has_value());
    EXPECT_FALSE(result_float[6].has_value());
    EXPECT_FALSE(result_float[7].has_value());
    EXPECT_FALSE(result_float[8].has_value());
    EXPECT_FALSE(result_float[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_IN_RANGE)        << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(result_float[i]->value, 25.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(result_float[i]->value, 24.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(result_float[i]->value, 25.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(result_float[i]->value, 24.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(result_float[i]->value, 22.5) << "The error occurred when: i == " << i;    break;
        }
    }

    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, -30.0, 5);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -31.5, 5);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -32.0, 5);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -32.5, 5);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -30.0, 5);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, -30.0, 5);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -31.5, 5);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -32.0, 5);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -32.5, 5);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -30.0, 5);

    EXPECT_FALSE(result_float[0].has_value());
    EXPECT_FALSE(result_float[1].has_value());
    EXPECT_FALSE(result_float[2].has_value());
    EXPECT_FALSE(result_float[3].has_value());
    EXPECT_FALSE(result_float[4].has_value());

    ASSERT_TRUE(result_float[5].has_value());
    ASSERT_TRUE(result_float[6].has_value());
    ASSERT_TRUE(result_float[7].has_value());
    ASSERT_TRUE(result_float[8].has_value());
    ASSERT_TRUE(result_float[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_OUT_RANGE)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_FLOAT_EQ(result_float[i]->value, -35.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i]->value, -39.0) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i]->value, -39.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i]->value, -40.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i]->value, -37.5) << "The error occurred when: i == " << i;    break;
        }
    }

    result_float[0] = IdArea_float.getIdInfo(BorderRange::UpperBorder, -30.0, -5);
    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -31.5, -5);
    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -32.0, -5);
    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -32.5, -5);
    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -30.0, -5);

    result_float[5] = IdArea_float.getIdInfo(BorderRange::LowerBorder, -30.0, -5);
    result_float[6] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -31.5, -5);
    result_float[7] = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -32.0, -5);
    result_float[8] = IdArea_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -32.5, -5);
    result_float[9] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -30.0, -5);

    EXPECT_FALSE(result_float[0].has_value());
    EXPECT_FALSE(result_float[1].has_value());
    EXPECT_FALSE(result_float[2].has_value());
    EXPECT_FALSE(result_float[3].has_value());
    EXPECT_FALSE(result_float[4].has_value());

    ASSERT_TRUE(result_float[5].has_value());
    ASSERT_TRUE(result_float[6].has_value());
    ASSERT_TRUE(result_float[7].has_value());
    ASSERT_TRUE(result_float[8].has_value());
    ASSERT_TRUE(result_float[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(result_float[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->position, IDM_POS_IN_RANGE)        << "The error occurred when: i == " << i;
        EXPECT_FALSE(result_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(result_float[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_FLOAT_EQ(result_float[i]->value, -25.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(result_float[i]->value, -24.0) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(result_float[i]->value, -24.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(result_float[i]->value, -25.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(result_float[i]->value, -22.5) << "The error occurred when: i == " << i;    break;
        }
    }


    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 30, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 35);
    EXPECT_EQ(result_unsigned[0]->stepCount, 5);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -30, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -25);
    EXPECT_EQ(result_unsigned[0]->stepCount, 5);

    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 30, 5).has_value());
    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, -30, 5).has_value());

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, 30, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 25);
    EXPECT_EQ(result_unsigned[0]->stepCount, -5);

    result_unsigned[0] = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -30, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -35);
    EXPECT_EQ(result_unsigned[0]->stepCount, -5);

    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, 30, -5).has_value());
    EXPECT_FALSE(IdArea_unsigned.getIdInfo(BorderRange::LowerBorder, -30, -5).has_value());


    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 40);
    EXPECT_EQ(result_unsigned[0]->stepCount, 5);

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0, 5).has_value());

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 0);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 20);
    EXPECT_EQ(result_unsigned[0]->stepCount, -5);

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0, -5).has_value());

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 2);
    EXPECT_EQ(result_unsigned[0]->stepCount, -1);


    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 20);
    EXPECT_EQ(result_unsigned[0]->stepCount, 5);

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -1, 5).has_value());

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_SUCCESSFULLY);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 40);
    EXPECT_EQ(result_unsigned[0]->stepCount, -5);

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -1, -5).has_value());


    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder,  30, 5).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 5).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder,  30, 5).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 5).has_value());

    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder,  30, -5).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, -5).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder,  30, -5).has_value());
    EXPECT_FALSE(IdArea_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, -5).has_value());


    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 5).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0, 5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IDS_RUN_OUT);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, 0);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -1, 5).has_value());

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, -5).has_value());

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_ON_BORDER);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, 0);

    result_unsigned[0] = IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0, -5);
    ASSERT_TRUE(result_unsigned[0].has_value());
    EXPECT_EQ(result_unsigned[0]->errCode, IDAREA_ERRC_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(result_unsigned[0]->position, IDM_POS_IN_RANGE);
    EXPECT_EQ(result_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(result_unsigned[0]->state);
    EXPECT_EQ(result_unsigned[0]->value, -2);
    EXPECT_EQ(result_unsigned[0]->stepCount, -1);

    EXPECT_FALSE(IdArea_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -1, -5).has_value());
}

TEST_F(IdAreaTests, getIdInfo_3)
{
    std::optional<IdArea<int>::Result> result_int[10];
    std::optional<IdArea<float>::Result> result_float[10];
    std::optional<IdArea<unsigned>::Result> result_unsigned[10];


    IdArea_int.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    IdArea_int.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    IdArea_float.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);

    IdArea_float.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdArea_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);

    //-----------------------------------------------------------------------------

//    result_int[0] = IdArea_int.getIdInfo(0);
//    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(2);
//    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(-2);
//    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(2);
//    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(-2);

//    ASSERT_TRUE(result_int[0].has_value());
//    ASSERT_TRUE(result_int[1].has_value());
//    ASSERT_TRUE(result_int[2].has_value());
//    ASSERT_TRUE(result_int[3].has_value());
//    ASSERT_TRUE(result_int[4].has_value());

////    for (size_t i = 0; i < 5; ++i) {
////        EXPECT_EQ(result_int[i]->errCode, IDAREA_ERRC_SUCCESSFULLY) << "The error occurred when: i == " << i;
////        EXPECT_EQ(result_int[i]->position, IDM_POS_IN_RANGE)        << "The error occurred when: i == " << i;
////        EXPECT_FALSE(result_int[i]->state)                          << "The error occurred when: i == " << i;
////        EXPECT_EQ(result_int[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
////        EXPECT_EQ(result_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

////        switch (i) {
////            case 5:    EXPECT_EQ(result_int[i]->value, -25) << "The error occurred when: i == " << i;    break;
////            case 6:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
////            case 7:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
////            case 8:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
////            case 9:    EXPECT_EQ(result_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
////        }
////    }


//    result_float[0] = IdArea_float.getIdInfo(0.0);
//    result_float[1] = IdArea_float_Start_1p5_Step_1p5.getIdInfo(1.5);
//    result_float[2] = IdArea_float_Start_n2_Step_1p5.getIdInfo(-2);
//    result_float[3] = IdArea_float_Start_2_Step_n1p5.getIdInfo(2);
//    result_float[4] = IdArea_float_Start_n1p5_Step_n1p5.getIdInfo(-1.5);

//    ASSERT_TRUE(result_float[0].has_value());
//    ASSERT_TRUE(result_float[1].has_value());
//    ASSERT_TRUE(result_float[2].has_value());
//    ASSERT_TRUE(result_float[3].has_value());
//    ASSERT_TRUE(result_float[4].has_value());














//    result_int[0] = IdArea_int.getIdInfo(30);
//    result_int[1] = IdArea_int_Start_2_Step_2.getIdInfo(30);
//    result_int[2] = IdArea_int_Start_n2_Step_2.getIdInfo(30);
//    result_int[3] = IdArea_int_Start_2_Step_n2.getIdInfo(30);
//    result_int[4] = IdArea_int_Start_n2_Step_n2.getIdInfo(30);

//    result_int[5] = IdArea_int.getIdInfo(-30);
//    result_int[6] = IdArea_int_Start_2_Step_2.getIdInfo(-30);
//    result_int[7] = IdArea_int_Start_n2_Step_2.getIdInfo(-30);
//    result_int[8] = IdArea_int_Start_2_Step_n2.getIdInfo(-30);
//    result_int[9] = IdArea_int_Start_n2_Step_n2.getIdInfo(-10);

//    ASSERT_TRUE(result_int[0].has_value());
//    ASSERT_TRUE(result_int[1].has_value());
//    ASSERT_TRUE(result_int[2].has_value());
//    ASSERT_TRUE(result_int[3].has_value());
//    ASSERT_TRUE(result_int[4].has_value());

//    ASSERT_TRUE(result_int[5].has_value());
//    ASSERT_TRUE(result_int[6].has_value());
//    ASSERT_TRUE(result_int[7].has_value());
//    ASSERT_TRUE(result_int[8].has_value());
//    ASSERT_TRUE(result_int[9].has_value());
}











//TEST_F(IdAreaTests, Test2)
//{
////    IdArea<int>::Result<int> IdArea_int_result;
////    IdArea<float>::Result<float> IdArea_float_result;
////    IdArea<unsigned>::Result<unsigned> IdArea_unsigned_result;

////    for(int i = 1; i < 50; ++i) {
////        IdArea_int_result = IdArea_int.getIdInfo(BorderRange::UpperBorder,  i);
////        IdArea_float_result = IdArea_float.getIdInfo(BorderRange::UpperBorder,  i);
////        IdArea_unsigned_result = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  i);

////        EXPECT_EQ(IdArea_int_result.errCode, IDM_ERR_SUCCESSFULLY) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_int_result.position, IDM_POS_OUT_RANGE) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_int_result.border, BorderRange::UpperBorder) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_int_result.state, false) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_int_result.value, i) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_int_result.stepCount, i) << "The error occurred when i == " << i;

////        EXPECT_EQ(IdArea_float_result.errCode, IDM_ERR_SUCCESSFULLY);
////        EXPECT_EQ(IdArea_float_result.position, IDM_POS_OUT_RANGE);
////        EXPECT_EQ(IdArea_float_result.border, BorderRange::UpperBorder);
////        EXPECT_EQ(IdArea_float_result.state, false);
////        EXPECT_FLOAT_EQ(IdArea_float_result.value, i);
////        EXPECT_EQ(IdArea_float_result.stepCount, i);

////        EXPECT_EQ(IdArea_unsigned_result.errCode, IDM_ERR_SUCCESSFULLY) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_unsigned_result.position, IDM_POS_OUT_RANGE) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_unsigned_result.border, BorderRange::UpperBorder) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_unsigned_result.state, false) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_unsigned_result.value, i) << "The error occurred when i == " << i;
////        EXPECT_EQ(IdArea_unsigned_result.stepCount, i) << "The error occurred when i == " << i;
////    }









////    IdArea<int>::Result<int> IdArea_int_result[2];
////    IdArea<float>::Result<float> IdArea_float_result[2];
////    IdArea<unsigned>::Result<unsigned> IdArea_unsigned_result[2];

////    IdArea_int_result[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);
////    IdArea_int_result[1] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);

////    for(int i = 0; i < 2; ++i) {
////        EXPECT_EQ(IdArea_int_result[i].errCode, IDM_ERR_SUCCESSFULLY);
////        EXPECT_EQ(IdArea_int_result[i].position, IDM_POS_OUT_RANGE);
////        EXPECT_EQ(IdArea_int_result[i].border, BorderRange::UpperBorder);
////        EXPECT_EQ(IdArea_int_result[i].state, false);
////        EXPECT_EQ(IdArea_int_result[i].value, 100);
////        EXPECT_EQ(IdArea_int_result[i].stepCount, 100);

////        EXPECT_EQ(IdArea_float_result_1.errCode, IDM_ERR_SUCCESSFULLY);
////        EXPECT_EQ(IdArea_float_result_1.position, IDM_POS_OUT_RANGE);
////        EXPECT_EQ(IdArea_float_result_1.border, BorderRange::UpperBorder);
////        EXPECT_EQ(IdArea_float_result_1.state, false);
////        EXPECT_FLOAT_EQ(IdArea_float_result_1.value, 100.0);
////        EXPECT_EQ(IdArea_float_result_1.stepCount, 100);

////        EXPECT_EQ(IdArea_unsigned_result_1.errCode, IDM_ERR_SUCCESSFULLY);
////        EXPECT_EQ(IdArea_unsigned_result_1.position, IDM_POS_OUT_RANGE);
////        EXPECT_EQ(IdArea_unsigned_result_1.border, BorderRange::UpperBorder);
////        EXPECT_EQ(IdArea_unsigned_result_1.state, false);
////        EXPECT_EQ(IdArea_unsigned_result_1.value, 100);
////        EXPECT_EQ(IdArea_unsigned_result_1.stepCount, 100);
////    }






////    IdArea_int_result_1[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);
////    IdArea_int_result_2[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  0);
////    IdArea_int_result_3[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, -100);

////    IdArea_float_result_1 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  100);
////    IdArea_float_result_2 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  0);
////    IdArea_float_result_3 = IdArea_float.getIdInfo(BorderRange::UpperBorder, -100);

////    IdArea_unsigned_result_1 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  100);
////    IdArea_unsigned_result_2 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  0);
////    IdArea_unsigned_result_3 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -100);


////    auto IdArea_int_Start_2_Step_2_result_1 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
////    auto IdArea_int_Start_2_Step_2_result_2 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
////    auto IdArea_int_Start_2_Step_2_result_3 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

////    auto IdArea_float_Start_2_Step_1p5_result_1 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  100);
////    auto IdArea_float_Start_2_Step_1p5_result_2 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  0);
////    auto IdArea_float_Start_2_Step_1p5_result_3 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -100);

////    auto IdArea_unsigned_Start_2_Step_2_result_1 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
////    auto IdArea_unsigned_Start_2_Step_2_result_2 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
////    auto IdArea_unsigned_Start_2_Step_2_result_3 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);








//    auto IdArea_int_result_1 = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_int_result_2 = IdArea_int.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_int_result_3 = IdArea_int.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_int_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_int_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_int_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_result_1.state, false);
//    EXPECT_EQ(IdArea_int_result_1.value, 100);
//    EXPECT_EQ(IdArea_int_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_int_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_int_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_int_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_result_2.state, false);
//    EXPECT_EQ(IdArea_int_result_2.value, 0);
//    EXPECT_EQ(IdArea_int_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_int_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_int_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_int_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_result_3.state, false);
//    EXPECT_EQ(IdArea_int_result_3.value, 0);
//    EXPECT_EQ(IdArea_int_result_3.stepCount, 0);

//    auto IdArea_float_result_1 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_float_result_2 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_float_result_3 = IdArea_float.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_float_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_float_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_float_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_result_1.state, false);
//    EXPECT_FLOAT_EQ(IdArea_float_result_1.value, 100.0);
//    EXPECT_EQ(IdArea_float_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_float_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_float_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_float_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_result_2.state, false);
//    EXPECT_FLOAT_EQ(IdArea_float_result_2.value, 0.0);
//    EXPECT_EQ(IdArea_float_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_float_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_float_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_float_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_result_3.state, false);
//    EXPECT_FLOAT_EQ(IdArea_float_result_3.value, 0.0);
//    EXPECT_EQ(IdArea_float_result_3.stepCount, 0);

//    auto IdArea_unsigned_result_1 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_unsigned_result_2 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_unsigned_result_3 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_unsigned_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_unsigned_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_unsigned_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_result_1.state, false);
//    EXPECT_EQ(IdArea_unsigned_result_1.value, 100);
//    EXPECT_EQ(IdArea_unsigned_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_unsigned_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_unsigned_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_unsigned_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_result_2.state, false);
//    EXPECT_EQ(IdArea_unsigned_result_2.value, 0);
//    EXPECT_EQ(IdArea_unsigned_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_unsigned_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_unsigned_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_unsigned_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_result_3.state, false);
//    EXPECT_EQ(IdArea_unsigned_result_3.value, 0);
//    EXPECT_EQ(IdArea_unsigned_result_3.stepCount, 0);


//    auto IdArea_int_Start_2_Step_2_result_1 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_int_Start_2_Step_2_result_2 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_int_Start_2_Step_2_result_3 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.state, false);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.value, 202);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.state, false);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.value, 2);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.state, false);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.value, 2);
//    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.stepCount, 0);

//    auto IdArea_float_Start_2_Step_1p5_result_1 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_float_Start_2_Step_1p5_result_2 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_float_Start_2_Step_1p5_result_3 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.state, false);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.value, 152);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.state, false);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.value, 2);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.state, false);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.value, 2);
//    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.stepCount, 0);

//    auto IdArea_unsigned_Start_2_Step_2_result_1 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_unsigned_Start_2_Step_2_result_2 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_unsigned_Start_2_Step_2_result_3 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.state, false);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.value, 202);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.state, false);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.value, 2);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.state, false);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.value, 2);
//    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.stepCount, 0);


//    auto IdArea_int_Start_n2_Step_2_result_1 = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_int_Start_n2_Step_2_result_2 = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_int_Start_n2_Step_2_result_3 = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.state, false);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.value, 198);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.state, false);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.value, -2);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.state, false);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.value, -2);
//    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.stepCount, 0);

//    auto IdArea_float_Start_n2_Step_1p5_result_1 = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_float_Start_n2_Step_1p5_result_2 = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_float_Start_n2_Step_1p5_result_3 = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.state, false);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.value, 148);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.stepCount, 100);

//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.state, false);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.value, -2);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.state, false);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.value, -2);
//    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.stepCount, 0);

////    auto IdArea_unsigned_Start_n2_Step_2_result_1 = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
////    auto IdArea_unsigned_Start_n2_Step_2_result_2 = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
////    auto IdArea_unsigned_Start_n2_Step_2_result_3 = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.errCode, IDM_ERR_IDS_RUN_OUT);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.border, BorderRange::UpperBorder);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.state, false);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.value, -2); //??
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.stepCount, 1);

////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.position, IDM_POS_ON_BORDER);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.border, BorderRange::UpperBorder);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.state, false);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.value, 2);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.stepCount, 0);

////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.position, IDM_POS_ON_BORDER);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.border, BorderRange::UpperBorder);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.state, false);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.value, 2);
////    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.stepCount, 0);
//}
