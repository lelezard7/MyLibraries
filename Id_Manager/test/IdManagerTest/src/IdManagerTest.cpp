#include "Id_Manager.h"

#include <gtest/gtest.h>

//TODO: Добавить тест с дробным StartId.

//struct IdManagerTests : public ::testing::Test
//{
//    IdManagerTests()
//        : idManager_int_Start_2_Step_2(2, 2),
//          idManager_float_Start_2_Step_1p5(2.0, 1.5),
////          idManager_uInt_Start_2_Step_2(2, 2),

//          idManager_int_Start_n2_Step_2(-2, 2),
//          idManager_float_Start_n2_Step_1p5(-2.0, 1.5),
////          idManager_uInt_Start_n2_Step_2(-2, 2),

//          idManager_int_Start_2_Step_n2(2, -2),
//          idManager_float_Start_2_Step_n1p5(2.0, -1.5),
////          idManager_uInt_Start_2_Step_n2(2, -2),

//          idManager_int_Start_n2_Step_n2(-2, -2),
//          idManager_float_Start_n2_Step_n1p5(-2.0, -1.5) {};
////          idManager_uInt_Start_n2_Step_n2(-2, -2) {};

//    IdManager<int> idManager_int;
//    IdManager<float> idManager_float;
////    IdManager<unsigned int> idManager_uInt;

//    IdManager<int> idManager_int_Start_2_Step_2;
//    IdManager<float> idManager_float_Start_2_Step_1p5;
////    IdManager<unsigned int> idManager_uInt_Start_2_Step_2;

//    IdManager<int> idManager_int_Start_n2_Step_2;
//    IdManager<float> idManager_float_Start_n2_Step_1p5;
////    IdManager<unsigned int> idManager_uInt_Start_n2_Step_2;

//    IdManager<int> idManager_int_Start_2_Step_n2;
//    IdManager<float> idManager_float_Start_2_Step_n1p5;
////    IdManager<unsigned int> idManager_uInt_Start_2_Step_n2;

//    IdManager<int> idManager_int_Start_n2_Step_n2;
//    IdManager<float> idManager_float_Start_n2_Step_n1p5;
////    IdManager<unsigned int> idManager_uInt_Start_n2_Step_n2;

//};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/*
TEST_F(IdManagerTests, Test_Getters)
{
    EXPECT_FALSE(idManager_int.isHardStep());
    EXPECT_FALSE(idManager_float.isHardStep());

    EXPECT_FALSE(idManager_int_Start_2_Step_2.isHardStep());
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.isHardStep());

    EXPECT_FALSE(idManager_int_Start_n2_Step_2.isHardStep());
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.isHardStep());

    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isHardStep());
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.isHardStep());

    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.isHardStep());
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.isHardStep());


    EXPECT_EQ(idManager_int.getStartId(), 0);
    EXPECT_FLOAT_EQ(idManager_float.getStartId(), 0.0);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getStartId(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getStartId(), 2.0);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getStartId(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getStartId(), -2.0);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getStartId(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getStartId(), 2.0);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getStartId(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getStartId(), -2.0);


    EXPECT_EQ(idManager_int.getStep(), 1);
    EXPECT_FLOAT_EQ(idManager_float.getStep(), 1.0);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getStep(), 1.5);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getStep(), 1.5);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getStep(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getStep(), -1.5);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getStep(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getStep(), -1.5);


    EXPECT_EQ(idManager_int.getMaxId(), 0);
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 0.0);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(), 2.0);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(), -2.0);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(), 2.0);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(), -2.0);


    EXPECT_EQ(idManager_int.getMinId(), 0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), 2.0);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -2.0);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), 2);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), 2.0);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -2);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -2.0);
}

TEST_F(IdManagerTests, Solo_test_IsStandardId_function)
{
    EXPECT_TRUE(idManager_int.isStandardId(-17));
    EXPECT_TRUE(idManager_int.isStandardId(-2));
    EXPECT_TRUE(idManager_int.isStandardId(-1));
    EXPECT_TRUE(idManager_int.isStandardId( 0));
    EXPECT_TRUE(idManager_int.isStandardId( 1));
    EXPECT_TRUE(idManager_int.isStandardId( 2));
    EXPECT_TRUE(idManager_int.isStandardId( 17));

    EXPECT_TRUE(idManager_float.isStandardId(-17.0));
    EXPECT_TRUE(idManager_float.isStandardId(-2.0));
    EXPECT_TRUE(idManager_float.isStandardId(-1.0));
    EXPECT_TRUE(idManager_float.isStandardId( 0.0));
    EXPECT_TRUE(idManager_float.isStandardId( 1.0));
    EXPECT_TRUE(idManager_float.isStandardId( 2.0));
    EXPECT_TRUE(idManager_float.isStandardId( 17.0));


    EXPECT_FALSE(idManager_int_Start_2_Step_2.isStandardId(-17));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.isStandardId(-2));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.isStandardId(-1));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.isStandardId( 0));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.isStandardId( 1));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.isStandardId( 2));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.isStandardId( 3));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.isStandardId( 4));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.isStandardId( 5));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.isStandardId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.isStandardId( 17));

    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId(-19.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId(-1.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.isStandardId( 0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId( 0.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.isStandardId( 0.9));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.isStandardId( 1.2));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId( 2.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.isStandardId( 3.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId( 3.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.isStandardId( 4.3));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId( 5.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.isStandardId( 17.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId(-18));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId(-6));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.isStandardId(-5));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.isStandardId(-3));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId(-2));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.isStandardId( 1));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId( 0));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.isStandardId( 1));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId( 2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.isStandardId( 18));

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId(-17.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId(-5.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.isStandardId(-4.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId(-3.5));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.isStandardId(-3.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId(-2.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.isStandardId(-1.3));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId(-0.5));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.isStandardId( 0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.isStandardId( 0.1));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId( 1.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.isStandardId( 19.0));


    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isStandardId(-17));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.isStandardId(-2));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isStandardId(-1));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.isStandardId( 0));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isStandardId( 1));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.isStandardId( 2));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isStandardId( 3));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.isStandardId( 4));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isStandardId( 5));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.isStandardId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.isStandardId( 17));

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId(-19.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId(-1.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.isStandardId( 0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId( 0.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.isStandardId( 0.9));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.isStandardId( 1.2));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId( 2.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.isStandardId( 3.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId( 3.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.isStandardId( 4.3));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId( 5.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.isStandardId( 17.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId(-18));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId(-6));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.isStandardId(-5));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.isStandardId(-3));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId(-2));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.isStandardId( 1));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId( 0));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.isStandardId( 1));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId( 2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.isStandardId( 18));

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId(-17.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId(-5.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.isStandardId(-4.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId(-3.5));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.isStandardId(-3.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId(-2.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.isStandardId(-1.3));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId(-0.5));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.isStandardId( 0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.isStandardId( 0.1));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId( 1.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.isStandardId( 19.0));
}

TEST_F(IdManagerTests, Solo_test_GetFreeId_function)
{
    for (int i = 0; i <= 15; ++i) {
        EXPECT_EQ(idManager_int.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idManager_int.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int.getMaxId(), i + 1) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int.getMinId(), -1) << "The error occurred when: i == " << i;
    }

    idManager_int.freeId(15);
    EXPECT_EQ(idManager_int.getMaxId(), 15);
    idManager_int.freeId(14);
    EXPECT_EQ(idManager_int.getMaxId(), 14);
    idManager_int.freeId(6);
    EXPECT_EQ(idManager_int.getMaxId(),  14);
    EXPECT_EQ(idManager_int.getMinId(), -1);

    idManager_int.freeId(0);
    EXPECT_EQ(idManager_int.getMaxId(), 14);
    EXPECT_EQ(idManager_int.getMinId(), 0);

    idManager_int.freeId( 0);
    idManager_int.freeId(-1);
    idManager_int.freeId(-2);
    idManager_int.freeId( 22);
    idManager_int.freeId( 23);

    for (int i = 0; i <= 15; ++i) {
        if (i == 15 || i == 14 || i == 6 || i == 0) {
            EXPECT_FALSE(idManager_int.findId(i)) << "The error occurred when: i == " << i;
        }
        else {
            EXPECT_TRUE(idManager_int.findId(i)) << "The error occurred when: i == " << i;
        }
    }

//    EXPECT_EQ(idManager_int.getFreeId(), 0);
//    EXPECT_EQ(idManager_int.getFreeId(), 6);
//    EXPECT_EQ(idManager_int.getFreeId(), 14);
//    EXPECT_EQ(idManager_int.getFreeId(), 15);

//    EXPECT_EQ(idManager_int.getMaxId(),  16);
//    EXPECT_EQ(idManager_int.getMinId(), -1);

    idManager_int.freeAll();
    EXPECT_FALSE(idManager_int.findId(7));
    EXPECT_EQ(idManager_int.getMaxId(), 0);
    EXPECT_EQ(idManager_int.getMinId(), 0);

    for (float i = 0.0; i <= 15.0; ++i) {
        EXPECT_FLOAT_EQ(idManager_float.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float.getMaxId(), i + 1.0) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float.getMinId(), -1.0) << "The error occurred when: i == " << i;
    }

    idManager_float.freeId(15.0);
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 15.0);
    idManager_float.freeId(14.0);
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 14.0);
    idManager_float.freeId(6.0);
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  14.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -1.0);

    idManager_float.freeId(0.0);
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 14.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);

    idManager_float.freeId( 0.0);
    idManager_float.freeId(-1.0);
    idManager_float.freeId(-2.0);
    idManager_float.freeId( 22.0);
    idManager_float.freeId( 23.0);

    EXPECT_TRUE(idManager_float.findId(13.0));
    EXPECT_TRUE(idManager_float.findId(1.0));

    EXPECT_FALSE(idManager_float.findId(9.5));
    idManager_float.freeId(9.5);
    EXPECT_FALSE(idManager_float.findId(9.5));

    for (float i = 0.0; i <= 15.0; ++i) {
        if (i == 15.0 || i == 14.0 || i == 6.0 || i == 0.0) {
            EXPECT_FALSE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
        }
        else {
            EXPECT_TRUE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
        }
    }

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 14.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);

    idManager_float.freeAll();
    EXPECT_FALSE(idManager_float.findId(7.0));
    EXPECT_FALSE(idManager_float.findId(7.5));
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 0.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);

    for (int i = 2; i <= 20; i += 2) {
        EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), i + 2) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), 0) << "The error occurred when: i == " << i;
    }

    idManager_int_Start_2_Step_2.freeId(20);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 20);
    idManager_int_Start_2_Step_2.freeId(18);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 18);
    idManager_int_Start_2_Step_2.freeId(6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 18);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), 0);

    idManager_int_Start_2_Step_2.freeId(2);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 18);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), 2);

    idManager_int_Start_2_Step_2.freeId( 5);
    idManager_int_Start_2_Step_2.freeId( 0);
    idManager_int_Start_2_Step_2.freeId( 1);
    idManager_int_Start_2_Step_2.freeId(-1);
    idManager_int_Start_2_Step_2.freeId(-2);
    idManager_int_Start_2_Step_2.freeId( 22);
    idManager_int_Start_2_Step_2.freeId( 23);

    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(16));
    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(4));

    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(9));
    idManager_int_Start_2_Step_2.freeId(9);
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(9));

    for (int i = 2; i <= 20; i += 2) {
        if (i == 20 || i == 18 || i == 6 || i == 2) {
            EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        }
        else {
            EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        }
    }

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 18);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), 2);

    idManager_int_Start_2_Step_2.freeAll();
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(8));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(7));
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(), 2);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), 2);

    for (float i = 2.0; i <= 20.0; i += 1.5) {
        EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(), i + 1.5) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), 0.5) << "The error occurred when: i == " << i;
    }














//    idManager_float.freeId(15.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 15.0);
//    idManager_float.freeId(14.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 14.0);
//    idManager_float.freeId(6.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  14.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -1.0);

//    idManager_float.freeId(0.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 14.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);

//    idManager_float.freeId( 0.0);
//    idManager_float.freeId(-1.0);
//    idManager_float.freeId(-2.0);
//    idManager_float.freeId( 22.0);
//    idManager_float.freeId( 23.0);

//    EXPECT_TRUE(idManager_float.findId(13.0));
//    EXPECT_TRUE(idManager_float.findId(1.0));

//    EXPECT_FALSE(idManager_float.findId(9.5));
//    idManager_float.freeId(9.5);
//    EXPECT_FALSE(idManager_float.findId(9.5));

//    for (float i = 0.0; i <= 15.0; ++i) {
//        if (i == 15.0 || i == 14.0 || i == 6.0 || i == 0.0) {
//            EXPECT_FALSE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
//        }
//        else {
//            EXPECT_TRUE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
//        }
//    }

//    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 14.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);

//    idManager_float.freeAll();
//    EXPECT_FALSE(idManager_float.findId(7.0));
//    EXPECT_FALSE(idManager_float.findId(7.5));
//    EXPECT_FLOAT_EQ(idManager_float.getMaxId(), 0.0);
//    EXPECT_FLOAT_EQ(idManager_float.getMinId(), 0.0);










    for (int i = -2; i <= 15; i += 2) {
        EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(), i + 2) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -4) << "The error occurred when: i == " << i;
    }

    for (float i = -2.0; i <= 15.0; i += 1.5) {
        EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(), i + 1.5) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -3.5) << "The error occurred when: i == " << i;
    }


    for (int i = 2; i >= -15; i -= 2) {
        EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(), 4) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), i - 2) << "The error occurred when: i == " << i;
    }

    for (float i = 2.0; i >= -15.0; i -= 1.5) {
        EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(), 3.5) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), i - 1.5) << "The error occurred when: i == " << i;
    }


    for (int i = -2; i >= -20; i -= 2) {
        EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), i - 2) << "The error occurred when: i == " << i;
    }

    for (float i = -2.0; i >= -20.0; i -= 1.5) {
        EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), i) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(), -0.5) << "The error occurred when: i == " << i;
        EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), i - 1.5) << "The error occurred when: i == " << i;
    }
}

TEST_F(IdManagerTests, Solo_test_FindId_function)
{
    for (int i = -15; i <= 15; ++i) {
        EXPECT_FALSE(idManager_int.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(i)) << "The error occurred when: i == " << i;
    }

    for (float i = -15.0; i <= 15.0; i += 0.5) {
        EXPECT_FALSE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(i)) << "The error occurred when: i == " << i;
    }


    idManager_int.getFreeId();
    idManager_float.getFreeId();

    idManager_int_Start_2_Step_2.getFreeId();
    idManager_float_Start_2_Step_1p5.getFreeId();

    idManager_int_Start_n2_Step_2.getFreeId();
    idManager_float_Start_n2_Step_1p5.getFreeId();

    idManager_int_Start_2_Step_n2.getFreeId();
    idManager_float_Start_2_Step_n1p5.getFreeId();

    idManager_int_Start_n2_Step_n2.getFreeId();
    idManager_float_Start_n2_Step_n1p5.getFreeId();


    for (int i = -15; i <= 15; ++i) {
        if (i == 0) {
            EXPECT_TRUE(idManager_int.findId(i)) << "The error occurred when: i == " << i;
            continue;
        }

        EXPECT_FALSE(idManager_int.findId(i)) << "The error occurred when: i == " << i;
    }

    for (float i = -15.0; i <= 15.0; i += 0.5) {
        if (i == 0.0) {
            EXPECT_TRUE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
            continue;
        }

        EXPECT_FALSE(idManager_float.findId(i)) << "The error occurred when: i == " << i;
    }


    for (int i = -15; i <= 15; ++i) {
        if (i == 2) {
            EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(i)) << "The error occurred when: i == " << i;
            EXPECT_TRUE(idManager_int_Start_2_Step_n2.findId(i)) << "The error occurred when: i == " << i;
            continue;
        }

        EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(i)) << "The error occurred when: i == " << i;
    }

    for (float i = -15.0; i <= 15.0; i += 0.5) {
        if (i == 2.0) {
            EXPECT_TRUE(idManager_float_Start_2_Step_1p5.findId(i)) << "The error occurred when: i == " << i;
            EXPECT_TRUE(idManager_float_Start_2_Step_n1p5.findId(i)) << "The error occurred when: i == " << i;
            continue;
        }

        EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(i)) << "The error occurred when: i == " << i;
    }


    for (int i = -15; i <= 15; ++i) {
        if (i == -2) {
            EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(i)) << "The error occurred when: i == " << i;
            EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(i)) << "The error occurred when: i == " << i;
            continue;
        }

        EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(i)) << "The error occurred when: i == " << i;
    }

    for (float i = -15.0; i <= 15.0; i += 0.5) {
        if (i == -2.0) {
            EXPECT_TRUE(idManager_float_Start_n2_Step_1p5.findId(i)) << "The error occurred when: i == " << i;
            EXPECT_TRUE(idManager_float_Start_n2_Step_n1p5.findId(i)) << "The error occurred when: i == " << i;
            continue;
        }

        EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(i)) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(i)) << "The error occurred when: i == " << i;
    }
}


TEST_F(IdManagerTests, ReserveId_function_ReservMethod_NonInterpolate)
{
    EXPECT_TRUE (idManager_int.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int.reserveId(-1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int.reserveId( 0,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int.reserveId( 0,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_EQ(idManager_int.getMaxId(),  1);
    EXPECT_EQ(idManager_int.getMinId(), -2);
    EXPECT_TRUE (idManager_int.reserveId( 15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int.reserveId( 1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int.reserveId( 2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int.reserveId( 5,  IdManager<int>::NonInterpolate));

    EXPECT_EQ(idManager_int.getMaxId(),  3);
    EXPECT_EQ(idManager_int.getMinId(), -2);

    EXPECT_TRUE (idManager_int.findId(-15));
    EXPECT_TRUE (idManager_int.findId( 0));
    EXPECT_TRUE (idManager_int.findId( 5));
    EXPECT_FALSE(idManager_int.findId( 3));
    EXPECT_FALSE(idManager_int.findId(-6));
    EXPECT_FALSE(idManager_int.findId(-16));
    EXPECT_FALSE(idManager_int.findId( 20));

    EXPECT_EQ(idManager_int.getFreeId(), 3);
    EXPECT_EQ(idManager_int.getFreeId(), 4);
    EXPECT_EQ(idManager_int.getFreeId(), 6);
    EXPECT_EQ(idManager_int.getFreeId(), 7);

    EXPECT_EQ(idManager_int.getMaxId(),  8);
    EXPECT_EQ(idManager_int.getMinId(), -2);

    EXPECT_TRUE(idManager_int.findId(3));

    EXPECT_TRUE (idManager_float.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId(-9.9,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId(-1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId( 0.0,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId( 15.0, IdManager<float>::NonInterpolate));
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  1.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -2.0);
    EXPECT_TRUE (idManager_float.reserveId( 1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId( 2.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float.reserveId( 7.7,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float.reserveId( 0.0,  IdManager<float>::NonInterpolate));

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  3.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -2.0);

    EXPECT_TRUE (idManager_float.findId(-15.0));
    EXPECT_TRUE (idManager_float.findId( 0.0));
    EXPECT_TRUE (idManager_float.findId( 5.0));
    EXPECT_TRUE (idManager_float.findId(-9.9));
    EXPECT_TRUE (idManager_float.findId( 2.3));
    EXPECT_FALSE(idManager_float.findId( 3.0));
    EXPECT_FALSE(idManager_float.findId(-6.0));
    EXPECT_FALSE(idManager_float.findId(-16.0));
    EXPECT_FALSE(idManager_float.findId( 20.0));
    EXPECT_FALSE(idManager_float.findId( 7.6));
    EXPECT_FALSE(idManager_float.findId(-15.1));

    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), 3.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), 4.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), 6.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), 7.0);

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  8.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -2.0);

    EXPECT_TRUE(idManager_float.findId(3.0));


    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 0,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 2,  IdManager<int>::NonInterpolate));
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  4);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 4,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 2,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 0,  IdManager<int>::NonInterpolate));

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);

    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 2));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 5));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 1));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-1));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 7));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-7));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 16));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 18));

    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 8);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 10);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 12);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 14);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 16);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 18);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  20);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);

    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(6));
    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(16));
    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(18));


    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-9.9,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 0.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 2.0,  IdManager<float>::NonInterpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(), 3.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), 0.5);
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 3.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 7.7,  IdManager<float>::NonInterpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(), 6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), 0.5);

    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId(-15.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 15.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 3.5));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 5.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 7.7));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 3.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-16.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 20.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 9.5));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 11.0);

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(), 12.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), 0.5);

    EXPECT_TRUE(idManager_float_Start_2_Step_1p5.findId(9.5));


    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 0,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 15, IdManager<int>::NonInterpolate));
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  2);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -4);
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 2,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId(-2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 4,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId( 5,  IdManager<int>::NonInterpolate));

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -4);

    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 5));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 1));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-1));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 7));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-7));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(12));

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), 6);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), 8);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), 10);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), 12);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  14);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -4);

    EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(6));
    EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(12));

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-17.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-9.9,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 0.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-17.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-3.5,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -2.0);
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 16.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 2.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 3.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 7.7,  IdManager<float>::NonInterpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -2.0);

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-17.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 16.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 3.5));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-3.5));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 7.7));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 3.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-16.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 20.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 16.6));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-17.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-0.5));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -0.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(),  2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(),  4.0);

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  5.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -5.0);

    EXPECT_TRUE(idManager_float_Start_n2_Step_1p5.findId(-0.5));


    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 0,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 2,  IdManager<int>::NonInterpolate));
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  4);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -4);
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 4,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId( 5,  IdManager<int>::NonInterpolate));

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -4);

    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 2));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 5));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 1));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId(-1));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 7));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-7));

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -8);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -10);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -12);

    EXPECT_TRUE(idManager_int_Start_2_Step_n2.findId(-4));

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-1.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-9.9,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 0.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 2.0,  IdManager<float>::NonInterpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(), 3.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), 0.5);
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 3.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.7,  IdManager<float>::NonInterpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(), 6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), 0.5);

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-15.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 15.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 3.5));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 5.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 7.7));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 3.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-16.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 20.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-4.0));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  0.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -4.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -5.5);

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(), 6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -7.0);

    EXPECT_TRUE(idManager_float_Start_2_Step_n1p5.findId(-4.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-1,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 0,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId(-15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 15, IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 1,  IdManager<int>::NonInterpolate));
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  2);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -4);
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 2,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 4,  IdManager<int>::NonInterpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId( 5,  IdManager<int>::NonInterpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId(-2,  IdManager<int>::NonInterpolate));

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -4);

    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 5));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 1));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-1));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 7));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-7));

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -8);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -10);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -12);

    EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(-4));

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-1.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-9.9,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 0.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-15.0, IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId( 1.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 15.0, IdManager<float>::NonInterpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -2.0);
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 1.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 2.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 3.5,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId( 2.3,  IdManager<float>::NonInterpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId( 5.0,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 7.7,  IdManager<float>::NonInterpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-8.0,  IdManager<float>::NonInterpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -2.0);

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-15.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 15.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 3.5));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 5.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 7.7));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 3.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-16.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 20.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-5.0));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -3.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -5.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -6.5);

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(), -0.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -9.5);

    EXPECT_TRUE(idManager_float_Start_n2_Step_n1p5.findId(-5.0));
}

TEST_F(IdManagerTests, ReserveId_function_ReservMethod_Interpolate)
{
    EXPECT_TRUE (idManager_int.reserveId(-15, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int.reserveId(-1,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int.reserveId( 0,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int.reserveId( 0,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int.reserveId(-15, IdManager<int>::Interpolate));
    EXPECT_EQ(idManager_int.getMaxId(), 1);
    EXPECT_EQ(idManager_int.getMinId(), -16);
    EXPECT_TRUE (idManager_int.reserveId( 5,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int.reserveId( 5,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int.reserveId( 1,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int.reserveId( 15, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int.reserveId( 7,  IdManager<int>::Interpolate));

    EXPECT_EQ(idManager_int.getMaxId(),  16);
    EXPECT_EQ(idManager_int.getMinId(), -16);

    EXPECT_TRUE (idManager_int.findId(-15));
    EXPECT_TRUE (idManager_int.findId( 0));
    EXPECT_TRUE (idManager_int.findId( 5));
    EXPECT_TRUE (idManager_int.findId( 1));
    EXPECT_TRUE (idManager_int.findId( 15));
    EXPECT_FALSE(idManager_int.findId(-16));
    EXPECT_FALSE(idManager_int.findId( 17));
    EXPECT_FALSE(idManager_int.findId( 6));
    EXPECT_FALSE(idManager_int.findId(-4));
    EXPECT_FALSE(idManager_int.findId(-7));

    EXPECT_EQ(idManager_int.getFreeId(), -2);
    EXPECT_EQ(idManager_int.getFreeId(), -3);
    EXPECT_EQ(idManager_int.getFreeId(), -4);
    EXPECT_EQ(idManager_int.getFreeId(), -5);

    EXPECT_EQ(idManager_int.getMaxId(),  16);
    EXPECT_EQ(idManager_int.getMinId(), -16);

    EXPECT_TRUE(idManager_int.findId(-4));

    EXPECT_TRUE (idManager_float.reserveId(-15.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId(-3.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId(-9.9,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId(-1.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float.reserveId(-15.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId(-15.5, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId(-14.9, IdManager<float>::Interpolate));
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  0.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -16.0);
    EXPECT_TRUE (idManager_float.reserveId( 7.7,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId( 3.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId( 7.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId( 8.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float.reserveId( 7.7,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId( 7.8,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float.reserveId( 0.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float.reserveId( 0.0,  IdManager<float>::Interpolate));

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  9.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -16.0);

    EXPECT_TRUE (idManager_float.findId(-15.0));
    EXPECT_TRUE (idManager_float.findId( 8.0));
    EXPECT_TRUE (idManager_float.findId( 0.0));
    EXPECT_TRUE (idManager_float.findId( 3.0));
    EXPECT_TRUE (idManager_float.findId(-9.9));
    EXPECT_TRUE (idManager_float.findId(-1.0));
    EXPECT_FALSE(idManager_float.findId(-1.1));
    EXPECT_FALSE(idManager_float.findId( 2.4));
    EXPECT_FALSE(idManager_float.findId(-16.0));
    EXPECT_FALSE(idManager_float.findId( 20.0));
    EXPECT_FALSE(idManager_float.findId( 7.6));
    EXPECT_FALSE(idManager_float.findId(-15.1));
    EXPECT_FALSE(idManager_float.findId(-4.0));

    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), -4.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), -5.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), -6.0);

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  9.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -16.0);

    EXPECT_TRUE(idManager_float.findId(-4.0));


    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 2,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 0,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 4,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-2,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId(-2,  IdManager<int>::Interpolate));
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-15, IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 2,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 0,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 10, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 15, IdManager<int>::Interpolate));

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  16);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -16);

    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 2));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 4));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 15));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 7));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-7));

    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), -8);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), -12);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), -14);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(),  8);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(),  12);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  16);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -16);

    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(-4));
    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId( 6));

    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 3.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 0.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-1.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 5.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 2.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId(-1.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId( 0.5,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId( 2.0,  IdManager<float>::Interpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(),  6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), -2.5);
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 6.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 6.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-2.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-0.3,  IdManager<float>::Interpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(),  8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), -4.0);

    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId(-2.5));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 6.5));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 2.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 6.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId(-0.3));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 0.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 0.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 8.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-15.1));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 11.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 12.5);

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(),  14.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), -4.0);

    EXPECT_TRUE(idManager_float_Start_2_Step_1p5.findId(8.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-16, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-8,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-2,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId(-2,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId(-16, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 6,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId( 6,  IdManager<int>::Interpolate));
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  8);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -18);
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 1,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 16, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 7,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 8,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 0,  IdManager<int>::Interpolate));

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -18);

    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 7));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-8));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 1));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 18));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 5));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-10));

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -12);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -14);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(),  2);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(),  4);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -18);

    EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(-4));
    EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(-10));

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 16.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-14.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-3.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-5.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-0.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 1.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-2.0,  IdManager<float>::Interpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -15.5);
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 0.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-2.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-5.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-3.5,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId( 1.0,  IdManager<float>::Interpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -15.5);

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-14.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 16.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-2.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-5.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 1.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-2.4));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 0.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 8.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 16.2));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 7.0));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), 2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), 4.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), 5.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), 7.0);

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -15.5);

    EXPECT_TRUE(idManager_float_Start_n2_Step_1p5.findId(7.0));


    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-15, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-1,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 0,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId( 0,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId(-15, IdManager<int>::Interpolate));
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -16);
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 4,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 5,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId( 5,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 1,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 15, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 7,  IdManager<int>::Interpolate));

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  16);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -16);

    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 0));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 5));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 1));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 15));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-7));

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(),  2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -8);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -12);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -14);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(),  8);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  16);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -16);

    EXPECT_TRUE(idManager_int_Start_2_Step_n2.findId( 6));
    EXPECT_TRUE(idManager_int_Start_2_Step_n2.findId(-4));

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-3.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-9.9,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-1.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId(-15.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.5, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-14.9, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.7,  IdManager<float>::Interpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(),  8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -16.0);
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 3.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 8.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 7.7,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.8,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 0.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 0.0,  IdManager<float>::Interpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(),  9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -16.0);

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-15.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 8.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 3.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-9.9));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-1.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-16.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 20.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-15.1));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  0.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -4.0);

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(),  9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -16.0);

    EXPECT_TRUE(idManager_float_Start_2_Step_n1p5.findId(-4.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-16, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-8,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-2,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId(-2,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId(-16, IdManager<int>::Interpolate));
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  0);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -18);
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 6,  IdManager<int>::Interpolate));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId( 6,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 1,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 16, IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 7,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 8,  IdManager<int>::Interpolate));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 0,  IdManager<int>::Interpolate));

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -18);

    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 7));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-8));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 1));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 18));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 5));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-10));

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -12);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -14);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  2);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  4);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  10);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  12);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  14);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -20);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -22);

    EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(-10));
    EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(-4));

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 16.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-14.0, IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-3.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-5.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-0.5,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 1.0,  IdManager<float>::Interpolate));
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -15.5);
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-2.0,  IdManager<float>::Interpolate));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 0.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-2.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-5.0,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-3.5,  IdManager<float>::Interpolate));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId( 1.0,  IdManager<float>::Interpolate));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -15.5);

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 16.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-14.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-2.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-5.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 1.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-2.4));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 0.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 8.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 16.2));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 8.5));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 4.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 5.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 7.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 8.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 10.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), 11.5);

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -15.5);

    EXPECT_TRUE(idManager_float_Start_n2_Step_n1p5.findId(8.5));
}

TEST_F(IdManagerTests, ReserveId_function_ReservMethod_AutoSelect)
{
    EXPECT_TRUE (idManager_int.reserveId(-15, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int.reserveId(-1,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int.reserveId( 0,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int.reserveId( 0,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int.reserveId(-15, IdManager<int>::AutoSelect));
    EXPECT_EQ(idManager_int.getMaxId(),  1);
    EXPECT_EQ(idManager_int.getMinId(), -16);
    EXPECT_TRUE (idManager_int.reserveId( 5,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int.reserveId( 5,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int.reserveId( 1,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int.reserveId( 15, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int.reserveId( 7,  IdManager<int>::AutoSelect));

    EXPECT_EQ(idManager_int.getMaxId(),  16);
    EXPECT_EQ(idManager_int.getMinId(), -16);

    EXPECT_TRUE (idManager_int.findId(-15));
    EXPECT_TRUE (idManager_int.findId( 0));
    EXPECT_TRUE (idManager_int.findId( 5));
    EXPECT_TRUE (idManager_int.findId( 1));
    EXPECT_TRUE (idManager_int.findId( 15));
    EXPECT_FALSE(idManager_int.findId(-16));
    EXPECT_FALSE(idManager_int.findId( 17));
    EXPECT_FALSE(idManager_int.findId( 6));
    EXPECT_FALSE(idManager_int.findId(-4));
    EXPECT_FALSE(idManager_int.findId(-7));

    EXPECT_EQ(idManager_int.getFreeId(), -2);
    EXPECT_EQ(idManager_int.getFreeId(), -3);
    EXPECT_EQ(idManager_int.getFreeId(), -4);
    EXPECT_EQ(idManager_int.getFreeId(), -5);

    EXPECT_EQ(idManager_int.getMaxId(),  16);
    EXPECT_EQ(idManager_int.getMinId(), -16);

    EXPECT_TRUE(idManager_int.findId(-4));

    EXPECT_TRUE (idManager_float.reserveId(-15.3,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId(-3.0,   IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId(-9.9,   IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId(-1.0,   IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float.reserveId(-15.3,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId(-15.2,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId(-15.02, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId( 7.7,   IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId( 3.0,   IdManager<float>::AutoSelect));
    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  4.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -4.0);
    EXPECT_TRUE (idManager_float.reserveId( 7.0,   IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId( 8.0,   IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float.reserveId( 7.7,   IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId( 7.8,   IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float.reserveId( 0.0,   IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float.reserveId( 0.0,   IdManager<float>::AutoSelect));

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  9.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -4.0);

    EXPECT_TRUE (idManager_float.findId(-15.02));
    EXPECT_TRUE (idManager_float.findId( 8.0));
    EXPECT_TRUE (idManager_float.findId( 0.0));
    EXPECT_TRUE (idManager_float.findId( 3.0));
    EXPECT_TRUE (idManager_float.findId(-9.9));
    EXPECT_TRUE (idManager_float.findId(-1.0));
    EXPECT_FALSE(idManager_float.findId(-1.1));
    EXPECT_FALSE(idManager_float.findId( 2.4));
    EXPECT_FALSE(idManager_float.findId(-16.0));
    EXPECT_FALSE(idManager_float.findId( 20.0));
    EXPECT_FALSE(idManager_float.findId( 7.6));
    EXPECT_FALSE(idManager_float.findId(-15.1));
    EXPECT_FALSE(idManager_float.findId( 9.0));
    EXPECT_FALSE(idManager_float.findId( 10.0));

    EXPECT_FLOAT_EQ(idManager_float.getFreeId(), -2.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  1.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  2.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  4.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  5.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  6.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  9.0);
    EXPECT_FLOAT_EQ(idManager_float.getFreeId(),  10.0);

    EXPECT_FLOAT_EQ(idManager_float.getMaxId(),  11.0);
    EXPECT_FLOAT_EQ(idManager_float.getMinId(), -4.0);

    EXPECT_TRUE(idManager_float.findId(10.0));
    EXPECT_TRUE(idManager_float.findId(9.0));


    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 2,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 0,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 4,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-2,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId(-2,  IdManager<int>::AutoSelect));
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId(-15, IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 2,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.reserveId( 0,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.reserveId( 15, IdManager<int>::AutoSelect));

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);

    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 2));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 4));
    EXPECT_TRUE (idManager_int_Start_2_Step_2.findId( 15));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId( 7));
    EXPECT_FALSE(idManager_int_Start_2_Step_2.findId(-7));

    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 6);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 8);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 10);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 12);

    EXPECT_EQ(idManager_int_Start_2_Step_2.getMaxId(),  14);
    EXPECT_EQ(idManager_int_Start_2_Step_2.getMinId(), -4);

    EXPECT_TRUE(idManager_int_Start_2_Step_2.findId(6));

    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 3.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 0.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-1.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 5.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 2.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId(-1.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId( 0.5,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.reserveId( 2.0,  IdManager<float>::AutoSelect));
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(),  6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), -2.5);
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 6.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId( 6.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-2.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.reserveId(-0.3,  IdManager<float>::AutoSelect));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(),  8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), -4.0);

    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId(-2.5));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 6.5));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 2.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 6.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId(-0.3));
    EXPECT_TRUE (idManager_float_Start_2_Step_1p5.findId( 0.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 0.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 8.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_2_Step_1p5.findId(-15.1));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 11.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 12.5);

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMaxId(),  14.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_1p5.getMinId(), -4.0);

    EXPECT_TRUE(idManager_float_Start_2_Step_1p5.findId(8.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-16, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-8,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId(-2,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId(-2,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId(-16, IdManager<int>::AutoSelect));
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  0);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -18);
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 6,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.reserveId( 6,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 1,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 16, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 7,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 8,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.reserveId( 0,  IdManager<int>::AutoSelect));

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -18);

    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 7));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId(-8));
    EXPECT_TRUE (idManager_int_Start_n2_Step_2.findId( 1));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 18));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId( 5));
    EXPECT_FALSE(idManager_int_Start_n2_Step_2.findId(-10));

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -12);

    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_2.getMinId(), -18);

    EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(-4));
    EXPECT_TRUE(idManager_int_Start_n2_Step_2.findId(-10));

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-34.4, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-14.0, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 16.0, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-3.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-5.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-0.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 1.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId(-2.0,  IdManager<float>::AutoSelect));
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -15.5);
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.reserveId( 0.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-2.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-5.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId(-3.5,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.reserveId( 1.0,  IdManager<float>::AutoSelect));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -15.5);

    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-14.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 16.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-2.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId(-5.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_1p5.findId( 1.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-2.4));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 0.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 8.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId( 16.2));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_1p5.findId(-9.5));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -11.0);

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_1p5.getMinId(), -15.5);

    EXPECT_TRUE(idManager_float_Start_n2_Step_1p5.findId(-9.5));


    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-15, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId(-1,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 0,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId( 0,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId(-15, IdManager<int>::AutoSelect));
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -2);
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 5,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.reserveId( 5,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 1,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 15, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.reserveId( 7,  IdManager<int>::AutoSelect));

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -2);

    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId(-15));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 0));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 5));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 1));
    EXPECT_TRUE (idManager_int_Start_2_Step_n2.findId( 15));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-16));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId( 6));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_2_Step_n2.findId(-7));

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(),  2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -2);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -8);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -12);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -14);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -16);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -18);

    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMaxId(),  4);
    EXPECT_EQ(idManager_int_Start_2_Step_n2.getMinId(), -20);

    EXPECT_TRUE(idManager_int_Start_2_Step_n2.findId(-4));

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.3,       IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-4.0,        IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-9.9,        IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-1.0,        IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId(-15.3,       IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.2,       IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.0000002, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId(-15.000002,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.7,        IdManager<float>::AutoSelect));
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(),  2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -5.5);
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 3.0,        IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.0,        IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 8.0,        IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 7.7,        IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 7.8,        IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.reserveId( 0.0,        IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.reserveId( 0.0,        IdManager<float>::AutoSelect));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(),  9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -5.5);

    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-15.0000002));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 8.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId( 3.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-9.9));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-1.0));
    EXPECT_TRUE (idManager_float_Start_2_Step_n1p5.findId(-15.000002));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 2.4));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-16.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 20.0));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 7.6));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId( 6.5));
    EXPECT_FALSE(idManager_float_Start_2_Step_n1p5.findId(-7.0));

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  2.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  0.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  3.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  5.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -5.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -7.0);

    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMaxId(),  9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_2_Step_n1p5.getMinId(), -8.5);

    EXPECT_TRUE(idManager_float_Start_2_Step_n1p5.findId(6.5));
    EXPECT_TRUE(idManager_float_Start_2_Step_n1p5.findId(-7.0));


    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 16, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-16, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-8,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId(-2,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId(-2,  IdManager<int>::AutoSelect));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId(-16, IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 6,  IdManager<int>::AutoSelect));
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -18);
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.reserveId( 6,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 1,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 7,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 8,  IdManager<int>::AutoSelect));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.reserveId( 0,  IdManager<int>::AutoSelect));

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -18);

    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 16));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-2));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 7));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId(-8));
    EXPECT_TRUE (idManager_int_Start_n2_Step_n2.findId( 1));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 18));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-4));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId( 5));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-10));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-17));
    EXPECT_FALSE(idManager_int_Start_n2_Step_n2.findId(-18));

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  2);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  4);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  10);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  12);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(),  14);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -4);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -6);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -10);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -12);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -14);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -20);

    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMaxId(),  18);
    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getMinId(), -22);

    EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(-4));
    EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(-10));
    EXPECT_TRUE(idManager_int_Start_n2_Step_n2.findId(-18));

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-14.0, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 16.0, IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-3.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-5.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-0.5,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 1.0,  IdManager<float>::AutoSelect));
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -15.5);
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId(-2.0,  IdManager<float>::AutoSelect));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.reserveId( 0.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-2.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-5.0,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId(-3.5,  IdManager<float>::AutoSelect));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.reserveId( 1.0,  IdManager<float>::AutoSelect));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -15.5);

    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-14.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 16.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-2.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 0.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId(-5.0));
    EXPECT_TRUE (idManager_float_Start_n2_Step_n1p5.findId( 1.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-1.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-2.4));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 0.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 8.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-4.0));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId( 16.2));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-15.1));
    EXPECT_FALSE(idManager_float_Start_n2_Step_n1p5.findId(-12.5));

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -6.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -8.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -9.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -11.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -12.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(),  2.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(),  4.0);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(),  5.5);

    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMaxId(),  17.5);
    EXPECT_FLOAT_EQ(idManager_float_Start_n2_Step_n1p5.getMinId(), -15.5);

    EXPECT_TRUE(idManager_float_Start_n2_Step_n1p5.findId(-12.5));
}

TEST_F(IdManagerTests, Solo_test_ReserveId_function)
{

}

*/


































//TEST_F(IdManagerTests, checking_initial_values)
//{
//    EXPECT_EQ(idManager_int.getFreeId(), 0);
//    EXPECT_EQ(idManager_float.getFreeId(), 0.0);

//    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 2);
//    EXPECT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 2.0);

//    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -2);
//    EXPECT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -2.0);

//    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), 2);
//    EXPECT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), 2.0);

//    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -2);
//    EXPECT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -2.0);
//}









//TEST_F(IdManagerTests, checking_reserveId_function)
//{/*
//    EXPECT_TRUE(idManager_int.reserveId(3));
//    EXPECT_TRUE(idManager_int.reserveId(6));

//    EXPECT_EQ(idManager_float.getFreeId(), 0.0);
//    EXPECT_EQ(idManager_float.getFreeId(), 1.0);
//    EXPECT_EQ(idManager_float.getFreeId(), 2.0);
//    EXPECT_EQ(idManager_float.getFreeId(), 3.0);

//    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 2);
//    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 4);
//    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 6);
//    EXPECT_EQ(idManager_int_Start_2_Step_2.getFreeId(), 8);

//    EXPECT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 2.0);
//    EXPECT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 3.5);
//    EXPECT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 5.0);
//    EXPECT_EQ(idManager_float_Start_2_Step_1p5.getFreeId(), 6.5);

//    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(), -2);
//    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(),  0);
//    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(),  2);
//    EXPECT_EQ(idManager_int_Start_n2_Step_2.getFreeId(),  4);

//    EXPECT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -2.0);
//    EXPECT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(), -0.5);
//    EXPECT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(),  1.0);
//    EXPECT_EQ(idManager_float_Start_n2_Step_1p5.getFreeId(),  2.5);

//    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(),  2);
//    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(),  0);
//    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -2);
//    EXPECT_EQ(idManager_int_Start_2_Step_n2.getFreeId(), -4);

//    EXPECT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  2.0);
//    EXPECT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(),  0.5);
//    EXPECT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -1.0);
//    EXPECT_EQ(idManager_float_Start_2_Step_n1p5.getFreeId(), -2.5);

//    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -2);
//    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -4);
//    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -6);
//    EXPECT_EQ(idManager_int_Start_n2_Step_n2.getFreeId(), -8);

//    EXPECT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -2.0);
//    EXPECT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -3.5);
//    EXPECT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -5.0);
//    EXPECT_EQ(idManager_float_Start_n2_Step_n1p5.getFreeId(), -6.5);*/
//}
















//    IdManager<int> constrDef_idManager_int;
//    IdManager<float> constrDef_idManager_float;
//    IdManager<int> idManager_int_start_n5_step_2(-5, 2);
//    IdManager<float> idManager_float_start_n5_step_1p5(-5, 1.5);
//    IdManager<int> idManager_int_start_n5_step_n2(-5, -2);
//    IdManager<float> idManager_float_start_n5_step_n1p5(-5, -1.5);
//    IdManager<int> idManager_int_start_5_step_n2(5, -2);
//    IdManager<float> idManager_float_start_5_step_n1p5(5, -1.5);


//    assert(constrDef_idManager_int.getStartId() == 0);
//    assert(constrDef_idManager_int.getStep() == 1);

//    assert(constrDef_idManager_int.getFreeId() == 0);
//    assert(constrDef_idManager_int.getFreeId() == 1);
//    assert(constrDef_idManager_int.getFreeId() == 2);
//    assert(constrDef_idManager_int.getMaxId() == 3);

//    assert(constrDef_idManager_int.reserveId(5) == true);
//    assert(constrDef_idManager_int.getMaxId() == 6);

//    assert(constrDef_idManager_int.checkId(3) == true);
//    assert(constrDef_idManager_int.checkId(0) == false);
//    assert(constrDef_idManager_int.checkId(-1) == false);
//    assert(constrDef_idManager_int.checkId(5) == false);

//    assert(constrDef_idManager_int.getFreeId() == 3);
//    assert(constrDef_idManager_int.getFreeId() == 4);
//    assert(constrDef_idManager_int.getFreeId() == 6);
//    assert(constrDef_idManager_int.getMaxId() == 7);

//    assert(constrDef_idManager_int.checkId(3) == false);

//    constrDef_idManager_int.freeId(1);
//    assert(constrDef_idManager_int.getFreeId() == 1);
//    assert(constrDef_idManager_int.getMaxId() == 7);

//    constrDef_idManager_int.freeId(6);
//    assert(constrDef_idManager_int.getMaxId() == 6);
//    assert(constrDef_idManager_int.getFreeId() == 6);
//    assert(constrDef_idManager_int.getMaxId() == 7);

//    constrDef_idManager_int.freeId(7);
//    assert(constrDef_idManager_int.getMaxId() == 7);

//    assert(constrDef_idManager_int.getFreeId() == 7);
//    constrDef_idManager_int.freeAll();
//    assert(constrDef_idManager_int.getFreeId() == 0);

//    assert(constrDef_idManager_int.checkId(0) == false);
//    assert(constrDef_idManager_int.checkId(1) == true);

//    std::cout << "IdManager<int>(): OK." << std::endl;


//    assert(constrDef_idManager_float.getStartId() == 0.0);
//    assert(constrDef_idManager_float.getStep() == 1.0);

//    assert(constrDef_idManager_float.getFreeId() == 0.0);
//    assert(constrDef_idManager_float.getFreeId() == 1.0);
//    assert(constrDef_idManager_float.getFreeId() == 2.0);
//    assert(constrDef_idManager_float.getMaxId() == 3.0);

//    assert(constrDef_idManager_float.reserveId(5.0) == true);
//    assert(constrDef_idManager_float.getMaxId() == 6.0);

//    assert(constrDef_idManager_float.checkId(3.0) == true);
//    assert(constrDef_idManager_float.checkId(0.0) == false);
//    assert(constrDef_idManager_float.checkId(-1.0) == false);
//    assert(constrDef_idManager_float.checkId(5.0) == false);

//    assert(constrDef_idManager_float.getFreeId() == 3.0);
//    assert(constrDef_idManager_float.getFreeId() == 4.0);
//    assert(constrDef_idManager_float.getFreeId() == 6.0);
//    assert(constrDef_idManager_float.getMaxId() == 7.0);

//    assert(constrDef_idManager_float.checkId(3.0) == false);

//    constrDef_idManager_float.freeId(1.0);
//    assert(constrDef_idManager_float.getFreeId() == 1.0);
//    assert(constrDef_idManager_float.getMaxId() == 7.0);

//    constrDef_idManager_float.freeId(6.0);
//    assert(constrDef_idManager_float.getMaxId() == 6.0);
//    assert(constrDef_idManager_float.getFreeId() == 6.0);
//    assert(constrDef_idManager_float.getMaxId() == 7.0);

//    constrDef_idManager_float.freeId(7.0);
//    assert(constrDef_idManager_float.getMaxId() == 7.0);

//    assert(constrDef_idManager_float.getFreeId() == 7.0);
//    constrDef_idManager_float.freeAll();
//    assert(constrDef_idManager_float.getFreeId() == 0.0);

//    assert(constrDef_idManager_int.checkId(0.0) == false);
//    assert(constrDef_idManager_int.checkId(1.0) == true);

//    std::cout << "IdManager<float>(): OK." << std::endl;

////    idManager_int_step_2_start_n5
