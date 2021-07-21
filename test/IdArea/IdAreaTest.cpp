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


TEST_F(IdAreaTests, Test1)
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
    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_EQ(IdArea_float.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());


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
    EXPECT_EQ(IdArea_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_FLOAT_EQ(IdArea_float.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::min());
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::min());
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::min());


    EXPECT_FALSE(IdArea_int.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_int.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdArea_float.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdArea_float.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdArea_unsigned.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdArea_unsigned.setBorderLimit(BorderRange::LowerBorder, -10));

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
