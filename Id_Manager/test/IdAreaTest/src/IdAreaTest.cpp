#include "Id_Manager.h"

#include <gtest/gtest.h>

using namespace Id_M;


struct IdAreaTests : public ::testing::Test
{
    IdArea<int> IdArea_int;
    IdArea<float> IdArea_float;
    IdArea<unsigned> IdArea_unsigned;

    IdArea<int> IdArea_int_Start_2_Step_2;
    IdArea<float> IdArea_float_Start_2_Step_1p5;
    IdArea<unsigned> IdArea_unsigned_Start_2_Step_2;

    IdArea<int> IdArea_int_Start_n2_Step_2;
    IdArea<float> IdArea_float_Start_n2_Step_1p5;
    IdArea<unsigned> IdArea_unsigned_Start_n2_Step_2;

    IdArea<int> IdArea_int_Start_2_Step_n2;
    IdArea<float> IdArea_float_Start_2_Step_n1p5;
    IdArea<unsigned> IdArea_unsigned_Start_2_Step_n2;

    IdArea<int> IdArea_int_Start_n2_Step_n2;
    IdArea<float> IdArea_float_Start_n2_Step_n1p5;
    IdArea<unsigned> IdArea_unsigned_Start_n2_Step_n2;

    IdAreaTests()
        : IdArea_int_Start_2_Step_2(2, 2),
          IdArea_float_Start_2_Step_1p5(2.0, 1.5),
          IdArea_unsigned_Start_2_Step_2(2, 2),

          IdArea_int_Start_n2_Step_2(-2, 2),
          IdArea_float_Start_n2_Step_1p5(-2.0, 1.5),
          IdArea_unsigned_Start_n2_Step_2(-2, 2),

          IdArea_int_Start_2_Step_n2(2, -2),
          IdArea_float_Start_2_Step_n1p5(2.0, -1.5),
          IdArea_unsigned_Start_2_Step_n2(2, -2),

          IdArea_int_Start_n2_Step_n2(-2, -2),
          IdArea_float_Start_n2_Step_n1p5(-2.0, -1.5),
          IdArea_unsigned_Start_n2_Step_n2(-2, -2) {};
};


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(SingleTests, Function_idm_abs)
{
    EXPECT_EQ(idm_abs(100000), 100000);
    EXPECT_EQ(idm_abs(50000), 50000);
    EXPECT_EQ(idm_abs(1000), 1000);
    EXPECT_EQ(idm_abs(10), 10);
    EXPECT_EQ(idm_abs(1), 1);
    EXPECT_EQ(idm_abs(0), 0);
    EXPECT_EQ(idm_abs(-1), 1);
    EXPECT_EQ(idm_abs(-10), 10);
    EXPECT_EQ(idm_abs(-1000), 1000);
    EXPECT_EQ(idm_abs(-50000), 50000);
    EXPECT_EQ(idm_abs(-100000), 100000);

    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(100000)), 100000.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(50000)), 50000.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(1000)), 1000.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(10)), 10.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(1)), 1.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(0)), 0.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(-1)), 1.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(-10)), 10.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(-1000)), 1000.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(-50000)), 50000.0);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<float>(-100000)), 100000.0);

    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(100000.065)), 100000.065);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(50000.0001)), 50000.0001);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(1000.44)), 1000.44);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(10.9)), 10.9);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(1.1)), 1.1);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(0.3)), 0.3);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(-1.1)), 1.1);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(-10.9)), 10.9);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(-1000.44)), 1000.44);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(-50000.0001)), 50000.0001);
    EXPECT_FLOAT_EQ(idm_abs(static_cast<double>(-100000.065)), 100000.065);
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
}

TEST_F(IdAreaTests, Test1)
{
    EXPECT_EQ(IdArea_int.getStart(), 0);
    EXPECT_FLOAT_EQ(IdArea_float.getStart(), 0.0);
    EXPECT_EQ(IdArea_unsigned.getStart(), 0);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getStart(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_1p5.getStart(), 2.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getStart(), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getStart(), -2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getStart(), -2.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getStart(), -2);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getStart(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getStart(), 2.0);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getStart(), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getStart(), -2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_n1p5.getStart(), -2.0);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getStart(), -2);


    EXPECT_EQ(IdArea_int.getStep(), 1);
    EXPECT_FLOAT_EQ(IdArea_float.getStep(), 1.0);
    EXPECT_EQ(IdArea_unsigned.getStep(), 1);

    EXPECT_EQ(IdArea_int_Start_2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2.getStep(), 2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2.getStep(), 2);

    EXPECT_EQ(IdArea_int_Start_2_Step_n2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_2_Step_n1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_n2.getStep(), -2);

    EXPECT_EQ(IdArea_int_Start_n2_Step_n2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdArea_float_Start_n2_Step_n1p5.getStep(), 1.5);
    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_n2.getStep(), -2);
}

TEST_F(IdAreaTests, Test2)
{
//    IdArea<int>::Result<int> IdArea_int_result;
//    IdArea<float>::Result<float> IdArea_float_result;
//    IdArea<unsigned>::Result<unsigned> IdArea_unsigned_result;

//    for(int i = 1; i < 50; ++i) {
//        IdArea_int_result = IdArea_int.getIdInfo(BorderRange::UpperBorder,  i);
//        IdArea_float_result = IdArea_float.getIdInfo(BorderRange::UpperBorder,  i);
//        IdArea_unsigned_result = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  i);

//        EXPECT_EQ(IdArea_int_result.errCode, IDM_ERR_SUCCESSFULLY) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_int_result.position, IDM_POS_OUT_RANGE) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_int_result.border, BorderRange::UpperBorder) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_int_result.state, false) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_int_result.value, i) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_int_result.stepCount, i) << "The error occurred when i == " << i;

//        EXPECT_EQ(IdArea_float_result.errCode, IDM_ERR_SUCCESSFULLY);
//        EXPECT_EQ(IdArea_float_result.position, IDM_POS_OUT_RANGE);
//        EXPECT_EQ(IdArea_float_result.border, BorderRange::UpperBorder);
//        EXPECT_EQ(IdArea_float_result.state, false);
//        EXPECT_FLOAT_EQ(IdArea_float_result.value, i);
//        EXPECT_EQ(IdArea_float_result.stepCount, i);

//        EXPECT_EQ(IdArea_unsigned_result.errCode, IDM_ERR_SUCCESSFULLY) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_unsigned_result.position, IDM_POS_OUT_RANGE) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_unsigned_result.border, BorderRange::UpperBorder) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_unsigned_result.state, false) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_unsigned_result.value, i) << "The error occurred when i == " << i;
//        EXPECT_EQ(IdArea_unsigned_result.stepCount, i) << "The error occurred when i == " << i;
//    }









//    IdArea<int>::Result<int> IdArea_int_result[2];
//    IdArea<float>::Result<float> IdArea_float_result[2];
//    IdArea<unsigned>::Result<unsigned> IdArea_unsigned_result[2];

//    IdArea_int_result[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);
//    IdArea_int_result[1] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);

//    for(int i = 0; i < 2; ++i) {
//        EXPECT_EQ(IdArea_int_result[i].errCode, IDM_ERR_SUCCESSFULLY);
//        EXPECT_EQ(IdArea_int_result[i].position, IDM_POS_OUT_RANGE);
//        EXPECT_EQ(IdArea_int_result[i].border, BorderRange::UpperBorder);
//        EXPECT_EQ(IdArea_int_result[i].state, false);
//        EXPECT_EQ(IdArea_int_result[i].value, 100);
//        EXPECT_EQ(IdArea_int_result[i].stepCount, 100);

//        EXPECT_EQ(IdArea_float_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//        EXPECT_EQ(IdArea_float_result_1.position, IDM_POS_OUT_RANGE);
//        EXPECT_EQ(IdArea_float_result_1.border, BorderRange::UpperBorder);
//        EXPECT_EQ(IdArea_float_result_1.state, false);
//        EXPECT_FLOAT_EQ(IdArea_float_result_1.value, 100.0);
//        EXPECT_EQ(IdArea_float_result_1.stepCount, 100);

//        EXPECT_EQ(IdArea_unsigned_result_1.errCode, IDM_ERR_SUCCESSFULLY);
//        EXPECT_EQ(IdArea_unsigned_result_1.position, IDM_POS_OUT_RANGE);
//        EXPECT_EQ(IdArea_unsigned_result_1.border, BorderRange::UpperBorder);
//        EXPECT_EQ(IdArea_unsigned_result_1.state, false);
//        EXPECT_EQ(IdArea_unsigned_result_1.value, 100);
//        EXPECT_EQ(IdArea_unsigned_result_1.stepCount, 100);
//    }






//    IdArea_int_result_1[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);
//    IdArea_int_result_2[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder,  0);
//    IdArea_int_result_3[0] = IdArea_int.getIdInfo(BorderRange::UpperBorder, -100);

//    IdArea_float_result_1 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  100);
//    IdArea_float_result_2 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  0);
//    IdArea_float_result_3 = IdArea_float.getIdInfo(BorderRange::UpperBorder, -100);

//    IdArea_unsigned_result_1 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  100);
//    IdArea_unsigned_result_2 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  0);
//    IdArea_unsigned_result_3 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -100);


//    auto IdArea_int_Start_2_Step_2_result_1 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_int_Start_2_Step_2_result_2 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_int_Start_2_Step_2_result_3 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

//    auto IdArea_float_Start_2_Step_1p5_result_1 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_float_Start_2_Step_1p5_result_2 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_float_Start_2_Step_1p5_result_3 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -100);

//    auto IdArea_unsigned_Start_2_Step_2_result_1 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_unsigned_Start_2_Step_2_result_2 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_unsigned_Start_2_Step_2_result_3 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);








    auto IdArea_int_result_1 = IdArea_int.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_int_result_2 = IdArea_int.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_int_result_3 = IdArea_int.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_int_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_int_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_int_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_result_1.state, false);
    EXPECT_EQ(IdArea_int_result_1.value, 100);
    EXPECT_EQ(IdArea_int_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_int_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_int_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_int_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_result_2.state, false);
    EXPECT_EQ(IdArea_int_result_2.value, 0);
    EXPECT_EQ(IdArea_int_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_int_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_int_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_int_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_result_3.state, false);
    EXPECT_EQ(IdArea_int_result_3.value, 0);
    EXPECT_EQ(IdArea_int_result_3.stepCount, 0);

    auto IdArea_float_result_1 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_float_result_2 = IdArea_float.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_float_result_3 = IdArea_float.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_float_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_float_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_float_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_result_1.state, false);
    EXPECT_FLOAT_EQ(IdArea_float_result_1.value, 100.0);
    EXPECT_EQ(IdArea_float_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_float_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_float_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_float_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_result_2.state, false);
    EXPECT_FLOAT_EQ(IdArea_float_result_2.value, 0.0);
    EXPECT_EQ(IdArea_float_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_float_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_float_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_float_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_result_3.state, false);
    EXPECT_FLOAT_EQ(IdArea_float_result_3.value, 0.0);
    EXPECT_EQ(IdArea_float_result_3.stepCount, 0);

    auto IdArea_unsigned_result_1 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_unsigned_result_2 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_unsigned_result_3 = IdArea_unsigned.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_unsigned_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_unsigned_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_unsigned_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_unsigned_result_1.state, false);
    EXPECT_EQ(IdArea_unsigned_result_1.value, 100);
    EXPECT_EQ(IdArea_unsigned_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_unsigned_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_unsigned_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_unsigned_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_unsigned_result_2.state, false);
    EXPECT_EQ(IdArea_unsigned_result_2.value, 0);
    EXPECT_EQ(IdArea_unsigned_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_unsigned_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_unsigned_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_unsigned_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_unsigned_result_3.state, false);
    EXPECT_EQ(IdArea_unsigned_result_3.value, 0);
    EXPECT_EQ(IdArea_unsigned_result_3.stepCount, 0);


    auto IdArea_int_Start_2_Step_2_result_1 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_int_Start_2_Step_2_result_2 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_int_Start_2_Step_2_result_3 = IdArea_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.state, false);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.value, 202);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.state, false);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.value, 2);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.state, false);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.value, 2);
    EXPECT_EQ(IdArea_int_Start_2_Step_2_result_3.stepCount, 0);

    auto IdArea_float_Start_2_Step_1p5_result_1 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_float_Start_2_Step_1p5_result_2 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_float_Start_2_Step_1p5_result_3 = IdArea_float_Start_2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.state, false);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.value, 152);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.state, false);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.value, 2);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.state, false);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.value, 2);
    EXPECT_EQ(IdArea_float_Start_2_Step_1p5_result_3.stepCount, 0);

    auto IdArea_unsigned_Start_2_Step_2_result_1 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_unsigned_Start_2_Step_2_result_2 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_unsigned_Start_2_Step_2_result_3 = IdArea_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.state, false);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.value, 202);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.state, false);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.value, 2);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.state, false);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.value, 2);
    EXPECT_EQ(IdArea_unsigned_Start_2_Step_2_result_3.stepCount, 0);


    auto IdArea_int_Start_n2_Step_2_result_1 = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_int_Start_n2_Step_2_result_2 = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_int_Start_n2_Step_2_result_3 = IdArea_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.state, false);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.value, 198);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.state, false);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.value, -2);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.state, false);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.value, -2);
    EXPECT_EQ(IdArea_int_Start_n2_Step_2_result_3.stepCount, 0);

    auto IdArea_float_Start_n2_Step_1p5_result_1 = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  100);
    auto IdArea_float_Start_n2_Step_1p5_result_2 = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder,  0);
    auto IdArea_float_Start_n2_Step_1p5_result_3 = IdArea_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -100);

    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.position, IDM_POS_OUT_RANGE);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.state, false);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.value, 148);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_1.stepCount, 100);

    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.errCode, IDM_ERR_SUCCESSFULLY);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.state, false);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.value, -2);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_2.stepCount, 0);

    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.position, IDM_POS_ON_BORDER);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.border, BorderRange::UpperBorder);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.state, false);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.value, -2);
    EXPECT_EQ(IdArea_float_Start_n2_Step_1p5_result_3.stepCount, 0);

//    auto IdArea_unsigned_Start_n2_Step_2_result_1 = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  100);
//    auto IdArea_unsigned_Start_n2_Step_2_result_2 = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder,  0);
//    auto IdArea_unsigned_Start_n2_Step_2_result_3 = IdArea_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -100);

//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.errCode, IDM_ERR_IDS_RUN_OUT);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.position, IDM_POS_OUT_RANGE);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.state, false);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.value, -2); //??
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_1.stepCount, 1);

//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.errCode, IDM_ERR_SUCCESSFULLY);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.state, false);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.value, 2);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_2.stepCount, 0);

//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.errCode, IDM_ERR_IMPOSSIBLE_REDUCE_RANGE);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.position, IDM_POS_ON_BORDER);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.border, BorderRange::UpperBorder);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.state, false);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.value, 2);
//    EXPECT_EQ(IdArea_unsigned_Start_n2_Step_2_result_3.stepCount, 0);
}
