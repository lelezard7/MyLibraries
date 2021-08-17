#include "IdManagement.h"

#include <gtest/gtest.h>

using namespace ONF;


struct IdRangeTests : public ::testing::Test
{
    IdRange<int> IdRange_int;
    IdRange<float> IdRange_float;
    IdRange<unsigned> IdRange_unsigned;

    IdRange<int> IdRange_int_Start_2_Step_2;
    IdRange<float> IdRange_float_Start_1p5_Step_1p5;
    IdRange<unsigned> IdRange_unsigned_Start_2_Step_2;

    IdRange<int> IdRange_int_Start_n2_Step_2;
    IdRange<float> IdRange_float_Start_n2_Step_1p5;
    IdRange<unsigned> IdRange_unsigned_Start_n2_Step_2;

    IdRange<int> IdRange_int_Start_2_Step_n2;
    IdRange<float> IdRange_float_Start_2_Step_n1p5;
    IdRange<unsigned> IdRange_unsigned_Start_2_Step_n2;

    IdRange<int> IdRange_int_Start_n2_Step_n2;
    IdRange<float> IdRange_float_Start_n1p5_Step_n1p5;
    IdRange<unsigned> IdRange_unsigned_Start_n2_Step_n2;

    IdRangeTests()
        : IdRange_int_Start_2_Step_2(2, 2),
          IdRange_float_Start_1p5_Step_1p5(1.5, 1.5),
          IdRange_unsigned_Start_2_Step_2(2, 2),

          IdRange_int_Start_n2_Step_2(-2, 2),
          IdRange_float_Start_n2_Step_1p5(-2.0, 1.5),
          IdRange_unsigned_Start_n2_Step_2(-2, 2),

          IdRange_int_Start_2_Step_n2(2, -2),
          IdRange_float_Start_2_Step_n1p5(2.0, -1.5),
          IdRange_unsigned_Start_2_Step_n2(2, -2),

          IdRange_int_Start_n2_Step_n2(-2, -2),
          IdRange_float_Start_n1p5_Step_n1p5(-1.5, -1.5),
          IdRange_unsigned_Start_n2_Step_n2(-2, -2) {};

};


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/**
 * Состояние объектов класса: Только созданные.
 * Что проверяем:             Метод getStart().
 * Доп. проверки:             -
 * Проверяемая ситуация:      Проверить работу метода у только созданных объектов класса.
 * Сценарий:                  Просто вызвать getStart() у всех объектов класса.
 */
TEST_F(IdRangeTests, getStart)
{
    EXPECT_EQ(IdRange_int.getStart(), 0);
    EXPECT_FLOAT_EQ(IdRange_float.getStart(), 0.0);
    EXPECT_EQ(IdRange_unsigned.getStart(), 0);

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getStart(), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getStart(), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getStart(), 2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getStart(), -2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getStart(), -2.0);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getStart(), -2);

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getStart(), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getStart(), 2.0);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getStart(), 2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getStart(), -2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getStart(), -1.5);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getStart(), -2);
}

/**
 * Состояние объектов класса: Только созданные.
 * Что проверяем:             Метод getStep().
 * Доп. проверки:             -
 * Проверяемая ситуация:      Проверить работу метода у только созданных объектов класса.
 * Сценарий:                  Просто вызвать getStep() у всех объектов класса.
 */
TEST_F(IdRangeTests, getStep)
{
    EXPECT_EQ(IdRange_int.getStep(), 1);
    EXPECT_FLOAT_EQ(IdRange_float.getStep(), 1.0);
    EXPECT_EQ(IdRange_unsigned.getStep(), 1);

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getStep(), 2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getStep(), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getStep(), 2);

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getStep(), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getStep(), -2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getStep(), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getStep(), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getStep(), -2);
}

/**
 * Состояние объектов класса: Только созданные.
 * Что проверяем:             Метод getBorderState(BorderRange) const и setBorderState(BorderRange, bool).
 * Доп. проверки:             -
 *
 * Проверяемая ситуация:      Меняем состояние границ с помощью setBorderState и проверяем, корректно ли сменился режим
 *                            с помощью getBorderState. Заодно проверим работу getBorderState.
 *
 * Сценарий:                  1) Вызываем getBorderState чтобы проверить корректность начального состояния границ.
 *                            2) Меняем состояние у обеих границ на true методом setBorderState. Затем проверяем
 *                               методом getBorderState что обе границы равны true.
 *                            3) Отключаем BorderRange::UpperBorder и проверяем что теперь BorderRange::UpperBorder
 *                               равен false, а BorderRange::LowerBorder равен true.
 *                            4) Включаем BorderRange::UpperBorder и выключаем BorderRange::LowerBorder. Проверяем что
 *                               теперь BorderRange::UpperBorder равен true, а BorderRange::LowerBorder равен false.
 */
TEST_F(IdRangeTests, BorderState)
{
    // Этап: 1
    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));


    // Этап: 2
    IdRange_int.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int.setBorderState(BorderRange::LowerBorder, true);
    IdRange_float.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float.setBorderState(BorderRange::LowerBorder, true);
    IdRange_unsigned.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned.setBorderState(BorderRange::LowerBorder, true);

    IdRange_int_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, true);
    IdRange_float_Start_1p5_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_1p5_Step_1p5.setBorderState(BorderRange::LowerBorder, true);
    IdRange_unsigned_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, true);

    IdRange_int_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, true);
    IdRange_float_Start_n2_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_n2_Step_1p5.setBorderState(BorderRange::LowerBorder, true);
    IdRange_unsigned_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, true);

    IdRange_int_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, true);
    IdRange_float_Start_2_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_2_Step_n1p5.setBorderState(BorderRange::LowerBorder, true);
    IdRange_unsigned_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, true);

    IdRange_int_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, true);
    IdRange_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::LowerBorder, true);
    IdRange_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, true);

    EXPECT_TRUE(IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdRange_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE(IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE(IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));


    // Этап: 3
    IdRange_int.setBorderState(BorderRange::UpperBorder, false);
    IdRange_float.setBorderState(BorderRange::UpperBorder, false);
    IdRange_unsigned.setBorderState(BorderRange::UpperBorder, false);

    IdRange_int_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, false);
    IdRange_float_Start_1p5_Step_1p5.setBorderState(BorderRange::UpperBorder, false);
    IdRange_unsigned_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, false);

    IdRange_int_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, false);
    IdRange_float_Start_n2_Step_1p5.setBorderState(BorderRange::UpperBorder, false);
    IdRange_unsigned_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, false);

    IdRange_int_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, false);
    IdRange_float_Start_2_Step_n1p5.setBorderState(BorderRange::UpperBorder, false);
    IdRange_unsigned_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, false);

    IdRange_int_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, false);
    IdRange_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::UpperBorder, false);
    IdRange_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, false);

    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));


    // Этап: 4
    IdRange_int.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int.setBorderState(BorderRange::LowerBorder, false);
    IdRange_float.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float.setBorderState(BorderRange::LowerBorder, false);
    IdRange_unsigned.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned.setBorderState(BorderRange::LowerBorder, false);

    IdRange_int_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, false);
    IdRange_float_Start_1p5_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_1p5_Step_1p5.setBorderState(BorderRange::LowerBorder, false);
    IdRange_unsigned_Start_2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_2_Step_2.setBorderState(BorderRange::LowerBorder, false);

    IdRange_int_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, false);
    IdRange_float_Start_n2_Step_1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_n2_Step_1p5.setBorderState(BorderRange::LowerBorder, false);
    IdRange_unsigned_Start_n2_Step_2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_n2_Step_2.setBorderState(BorderRange::LowerBorder, false);

    IdRange_int_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, false);
    IdRange_float_Start_2_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_2_Step_n1p5.setBorderState(BorderRange::LowerBorder, false);
    IdRange_unsigned_Start_2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_2_Step_n2.setBorderState(BorderRange::LowerBorder, false);

    IdRange_int_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, false);
    IdRange_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float_Start_n1p5_Step_n1p5.setBorderState(BorderRange::LowerBorder, false);
    IdRange_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned_Start_n2_Step_n2.setBorderState(BorderRange::LowerBorder, false);

    EXPECT_TRUE (IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdRange_int_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getBorderState(BorderRange::LowerBorder));

    EXPECT_TRUE (IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.getBorderState(BorderRange::LowerBorder));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getBorderState(BorderRange::LowerBorder));
}

/**
 * Состояние объектов класса: Только созданные.
 * Что проверяем:             Метод getBorderLimit(BorderRange) const и setBorderLimit(BorderRange, T).
 * Доп. проверки:             -
 *
 * Проверяемая ситуация:      Меняем значение границ с помощью setBorderLimit и проверяем, корректно ли сменилось значение
 *                            с помощью метода getBorderLimit. Заодно проверим работу getBorderLimit.
 *
 * Сценарий:                  1) Вызываем getBorderLimit чтобы проверить корректность начального значения границ.
 *                            2) Меняем значение обеих границ на 10 у всех объектов кроме IdRange_unsigned_Start_n2_Step_2
 *                               и IdRange_unsigned_Start_n2_Step_n2. У них мы устанановим Лимит на -1, это создаст те же условия
 *                               что и у других объектов + мы проверим установку Лимита на более коротких дистанциях.
 *                               После проверяем методом getBorderLimit что у BorderRange::UpperBorder Лимит установился
 *                               успешно, а у BorderRange::LowerBorder Лимит не установился и его значение равно значению по умолчанию.
 *
 *                            3) Меняем значение обеих границ на -10 у всех объектов кроме:
 *                               IdRange_unsigned                  (BorderRange::UpperBorder = 10, BorderRange::LowerBorder = 0),
 *                               IdRange_unsigned_Start_2_Step_2   (BorderRange::UpperBorder = 1,  BorderRange::LowerBorder = 1),
 *                               IdRange_unsigned_Start_n2_Step_2  (BorderRange::UpperBorder = 10, BorderRange::LowerBorder = 10),
 *                               IdRange_unsigned_Start_2_Step_n2  (BorderRange::UpperBorder = 1,  BorderRange::LowerBorder = 1),
 *                               IdRange_unsigned_Start_n2_Step_n2 (BorderRange::UpperBorder = 10, BorderRange::LowerBorder = 10)
 *
 *                               После проверяем методом getBorderLimit что у BorderRange::LowerBorder Лимит установился
 *                               успешно, а у BorderRange::UpperBorder Лимит не установился и его значение равно предыдущему значению.
 *                               Единственное где успешно должен обновиться BorderRange::UpperBorder это IdRange_unsigned, так как
 *                               у него мы установили значение на 10 как на шаге 2. Так мы проверим вдобавок установку лимита на
 *                               то же значение что уже установленно.
 */
TEST_F(IdRangeTests, BorderLimit)
{
    // Этап: 1
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdRange_float.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdRange_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<int>::max());
    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<float>::max());
    EXPECT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), std::numeric_limits<unsigned>::max());
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());


    // Этап: 2
    EXPECT_TRUE (IdRange_int.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_int.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdRange_float.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdRange_unsigned.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_unsigned.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdRange_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, -1));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, -1));

    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdRange_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdRange_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -1));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -1));

    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<int>::lowest());
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<float>::lowest());
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), std::numeric_limits<unsigned>::lowest());


    // Этап: 3
    EXPECT_FALSE(IdRange_int.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdRange_int.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdRange_float.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdRange_float.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_TRUE (IdRange_unsigned.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_unsigned.setBorderLimit(BorderRange::LowerBorder, 0));

    EXPECT_FALSE(IdRange_int_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdRange_int_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdRange_float_Start_1p5_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::UpperBorder, 1));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_2.setBorderLimit(BorderRange::LowerBorder, 1));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdRange_float_Start_2_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 1));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 1));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, -10));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, -10));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::UpperBorder, -10.0));
    EXPECT_TRUE (IdRange_float_Start_n1p5_Step_n1p5.setBorderLimit(BorderRange::LowerBorder, -10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_n2.setBorderLimit(BorderRange::LowerBorder, 10));

    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::LowerBorder), 0);

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderLimit(BorderRange::LowerBorder), 1);

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderLimit(BorderRange::LowerBorder),  10);

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderLimit(BorderRange::LowerBorder), 1);

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder), -10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderLimit(BorderRange::LowerBorder), -10.0);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::UpperBorder), -1);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderLimit(BorderRange::LowerBorder),  10);
}

TEST_F(IdRangeTests, BorderValue)
{
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::LowerBorder), 0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::UpperBorder), 0.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::LowerBorder), 0.0);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::UpperBorder), 0);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::LowerBorder), 0);

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderValue(BorderRange::UpperBorder), -2.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderValue(BorderRange::LowerBorder), -2.0);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), -2);

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderValue(BorderRange::LowerBorder), 2.0);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::LowerBorder), -1.5);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);


    EXPECT_TRUE(IdRange_int.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE(IdRange_int.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_TRUE(IdRange_float.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_TRUE(IdRange_float.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE(IdRange_unsigned.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE(IdRange_unsigned.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_int_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_TRUE (IdRange_int_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::UpperBorder, 10.0));
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::LowerBorder, 10.0));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, 10));
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, 10));

    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::LowerBorder), 10.0);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::UpperBorder), 1.5);
    EXPECT_FLOAT_EQ(IdRange_float_Start_1p5_Step_1p5.getBorderValue(BorderRange::LowerBorder), 1.5);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderValue(BorderRange::UpperBorder), 10.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n2_Step_1p5.getBorderValue(BorderRange::LowerBorder), 10.0);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_2.getBorderValue(BorderRange::LowerBorder), 10);

    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderValue(BorderRange::UpperBorder), 2.0);
    EXPECT_FLOAT_EQ(IdRange_float_Start_2_Step_n1p5.getBorderValue(BorderRange::LowerBorder), 2.0);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::UpperBorder), 2);
    EXPECT_EQ(IdRange_unsigned_Start_2_Step_n2.getBorderValue(BorderRange::LowerBorder), 2);

    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_int_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), 10);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::UpperBorder), -1.5);
    EXPECT_FLOAT_EQ(IdRange_float_Start_n1p5_Step_n1p5.getBorderValue(BorderRange::LowerBorder), -1.5);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::UpperBorder), -2);
    EXPECT_EQ(IdRange_unsigned_Start_n2_Step_n2.getBorderValue(BorderRange::LowerBorder), -2);


    EXPECT_FALSE(IdRange_int.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdRange_int.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_FALSE(IdRange_float.setBorderValue(BorderRange::LowerBorder, 20.0));
    EXPECT_TRUE (IdRange_float.setBorderValue(BorderRange::UpperBorder, 20.0));
    EXPECT_FALSE(IdRange_unsigned.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdRange_unsigned.setBorderValue(BorderRange::UpperBorder, 20));

    EXPECT_FALSE(IdRange_int_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdRange_int_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::LowerBorder, 18.0));
    EXPECT_TRUE (IdRange_float_Start_1p5_Step_1p5.setBorderValue(BorderRange::UpperBorder, 18.0));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.setBorderValue(BorderRange::UpperBorder, 21));

    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdRange_int_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.setBorderValue(BorderRange::LowerBorder, 17.5));
    EXPECT_TRUE (IdRange_float_Start_n2_Step_1p5.setBorderValue(BorderRange::UpperBorder, 17.5));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::LowerBorder, -4));
    EXPECT_TRUE (IdRange_unsigned_Start_n2_Step_2.setBorderValue(BorderRange::UpperBorder, -4));

    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 20));
    EXPECT_TRUE (IdRange_int_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 20));
    EXPECT_TRUE (IdRange_float_Start_2_Step_n1p5.setBorderValue(BorderRange::LowerBorder, -11.5));
    EXPECT_TRUE (IdRange_float_Start_2_Step_n1p5.setBorderValue(BorderRange::UpperBorder, -11.5));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::LowerBorder, 2));
    EXPECT_TRUE (IdRange_unsigned_Start_2_Step_n2.setBorderValue(BorderRange::UpperBorder, 2));

    EXPECT_TRUE(IdRange_int_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, -22));
    EXPECT_TRUE(IdRange_int_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, -22));
    EXPECT_TRUE(IdRange_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::LowerBorder, -16.5));
    EXPECT_TRUE(IdRange_float_Start_n1p5_Step_n1p5.setBorderValue(BorderRange::UpperBorder, -16.5));
    EXPECT_TRUE(IdRange_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::LowerBorder, -2));
    EXPECT_TRUE(IdRange_unsigned_Start_n2_Step_n2.setBorderValue(BorderRange::UpperBorder, -2));
}

TEST_F(IdRangeTests, moveBorder)
{
    IdRange<int>::IdInfo idInfo_int[10];
    IdRange<float>::IdInfo idInfo_float[10];
    IdRange<unsigned>::IdInfo idInfo_unsigned[10];

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_int[5] = IdRange_int.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_START + IDRP_AT_BORDER)  << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY)       << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                       << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 0)                   << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_float[5] = IdRange_float.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[1] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[2] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[3] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[4] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_unsigned[5] = IdRange_unsigned.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[6] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[7] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[8] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[9] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_unsigned[i].position, IDRP_AT_START + IDRP_AT_BORDER)  << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_unsigned[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_unsigned[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_unsigned[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_unsigned[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_unsigned[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    idInfo_int[5] = IdRange_int.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 10)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value, 10) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, 18) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, 18) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value, -10) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -22) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -22) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);

    idInfo_float[5] = IdRange_float.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 10)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 10.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 16.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 13.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 17.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 13.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -10.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -13.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -17.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -13.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -16.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 10);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 10);

    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 22);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 10);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 1);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -22);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 10);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 1);

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);

    idInfo_int[5] = IdRange_int.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, -3)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);

    idInfo_float[5] = IdRange_float.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, -3)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 7);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 3);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 6);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -8);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -1);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_int[5] = IdRange_int.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_float[5] = IdRange_float.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 7);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 3);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 6);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -8);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);

    idInfo_int[5] = IdRange_int.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, -7)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, -7);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, -7);

    idInfo_float[5] = IdRange_float.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, -7);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -7);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_START + IDRP_AT_BORDER)  << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, -7)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 3);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -4);

    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 3);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 6);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -5);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 6);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -4);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -7);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);
}

TEST_F(IdRangeTests, reset)
{
    IdRange_int.moveBorder(BorderRange::UpperBorder, -17);
    IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 20);
    IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -2);
    IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 44);
    IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 900);

    IdRange_int.moveBorder(BorderRange::LowerBorder, 0);
    IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -90);
    IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -55);
    IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 1);
    IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 3111);

    IdRange_float.moveBorder(BorderRange::UpperBorder, 1);
    IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 3);
    IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 6099);
    IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 6);

    IdRange_float.moveBorder(BorderRange::LowerBorder, 0);
    IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -10);
    IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 1);
    IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 700);
    IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -50);

    IdRange_unsigned.moveBorder(BorderRange::UpperBorder, -17);
    IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 20);
    IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -2);
    IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 44);
    IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 900);

    IdRange_unsigned.moveBorder(BorderRange::LowerBorder, 1);
    IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 31111);
    IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 3);
    IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 2);


    IdRange_int.reset();
    IdRange_int_Start_2_Step_2.reset();
    IdRange_int_Start_n2_Step_2.reset();
    IdRange_int_Start_2_Step_n2.reset();
    IdRange_int_Start_n2_Step_n2.reset();

    IdRange_float.reset();
    IdRange_float_Start_1p5_Step_1p5.reset();
    IdRange_float_Start_n2_Step_1p5.reset();
    IdRange_float_Start_2_Step_n1p5.reset();
    IdRange_float_Start_n1p5_Step_n1p5.reset();

    IdRange_unsigned.reset();
    IdRange_unsigned_Start_2_Step_2.reset();
    IdRange_unsigned_Start_n2_Step_2.reset();
    IdRange_unsigned_Start_2_Step_n2.reset();
    IdRange_unsigned_Start_n2_Step_n2.reset();


    IdRange<int>::IdInfo idInfo_int[10];
    IdRange<float>::IdInfo idInfo_float[10];
    IdRange<unsigned>::IdInfo idInfo_unsigned[10];

    idInfo_int[0] = IdRange_int.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_int[5] = IdRange_int.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_float[5] = IdRange_float.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[1] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[2] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[3] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);
    idInfo_unsigned[4] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 0);

    idInfo_unsigned[5] = IdRange_unsigned.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[6] = IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[7] = IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[8] = IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);
    idInfo_unsigned[9] = IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_unsigned[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_unsigned[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_unsigned[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_unsigned[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_unsigned[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_unsigned[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }
}

TEST_F(IdRangeTests, getIdInfo_1)
{
    IdRange<int>::IdInfo idInfo_int[10];
    IdRange<float>::IdInfo idInfo_float[10];
    IdRange<unsigned>::IdInfo idInfo_unsigned[10];


    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_unsigned[1] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_unsigned[2] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_unsigned[3] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_unsigned[4] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);

    idInfo_unsigned[5] = IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_unsigned[6] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_unsigned[7] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_unsigned[8] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_unsigned[9] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_unsigned[i].position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_unsigned[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_unsigned[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_unsigned[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_unsigned[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_unsigned[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_unsigned[i].value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_unsigned[i].value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_unsigned[i].value, -2) << "The error occurred when: i == " << i;    break;
        }
    }

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].position, IDRP_OUT_OF_RANGE) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 10)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value, 10) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, 18) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value, 22) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, 18) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value, -10) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -22) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value, -18) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -22) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 10);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 10);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 10);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 10);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].position, IDRP_OUT_OF_RANGE) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 10)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 10.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 16.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 13.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 17.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 13.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -10.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -13.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -17.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -13.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -16.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 10);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 10);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 22);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 10);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 1);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -22);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 10);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 10);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 1);

    //-----------------------------------------------------------------------------

    IdRange_int.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    IdRange_int.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].position, IDRP_WITHIN_RANGE)  << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, -3)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    IdRange_float.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, 10);

    IdRange_float.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, 10);

    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -3);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -3);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -3);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -3);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].position, IDRP_WITHIN_RANGE)  << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, -3)            << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    IdRange_unsigned.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, 10);

    IdRange_unsigned.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, 10);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 7);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 3);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 6);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -8);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -3);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -1);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -3);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, -1);

    //-----------------------------------------------------------------------------

    IdRange_int.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_int_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);

    IdRange_int.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_int_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_int_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_int_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_int_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i].value, 7)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i].value, 16) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i].value, 12) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i].value, -7)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i].value, -12) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i].value, -16) << "The error occurred when: i == " << i;    break;
        }
    }


    IdRange_float.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::UpperBorder, -3);

    IdRange_float.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_float_Start_1p5_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_float_Start_n2_Step_1p5.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_float_Start_2_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_float_Start_n1p5_Step_n1p5.moveBorder(BorderRange::LowerBorder, -3);

    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 0);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 0);

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i].flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].position, IDRP_AT_BORDER) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i].state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i].stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i].border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i].border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 7.0)  << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 8.5)  << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 12.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i].value, 9.0)  << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -7.0)  << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -9.0)  << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -8.5)  << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i].value, -12.0) << "The error occurred when: i == " << i;    break;
        }
    }


    IdRange_unsigned.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);
    IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::UpperBorder, -3);

    IdRange_unsigned.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_unsigned_Start_2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_unsigned_Start_n2_Step_2.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_unsigned_Start_2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);
    IdRange_unsigned_Start_n2_Step_n2.moveBorder(BorderRange::LowerBorder, -3);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 7);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 3);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 6);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -8);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, -16);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 2);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0);
    EXPECT_EQ(idInfo_unsigned[0].flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0].position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0].border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0].state);
    EXPECT_EQ(idInfo_unsigned[0].value, 0);
    EXPECT_EQ(idInfo_unsigned[0].stepCount, 0);
}

TEST_F(IdRangeTests, getIdInfo_2)
{
    std::optional<IdRange<int>::IdInfo> idInfo_int[10];
    std::optional<IdRange<float>::IdInfo> idInfo_float[10];
    std::optional<IdRange<unsigned>::IdInfo> idInfo_unsigned[10];


    EXPECT_TRUE (IdRange_int.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());

    EXPECT_TRUE (IdRange_int.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());


    EXPECT_FALSE(IdRange_float.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 11.1, 0).has_value());

    EXPECT_FALSE(IdRange_float.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());
    EXPECT_FALSE(IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -11.1, 0).has_value());


    EXPECT_TRUE (IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 11, 0).has_value());

    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -11, 0).has_value());

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 30, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 0);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 30, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 0);

    ASSERT_TRUE(idInfo_int[0].has_value());
    ASSERT_TRUE(idInfo_int[1].has_value());
    ASSERT_TRUE(idInfo_int[2].has_value());
    ASSERT_TRUE(idInfo_int[3].has_value());
    ASSERT_TRUE(idInfo_int[4].has_value());

    EXPECT_FALSE(idInfo_int[5].has_value());
    EXPECT_FALSE(idInfo_int[6].has_value());
    EXPECT_FALSE(idInfo_int[7].has_value());
    EXPECT_FALSE(idInfo_int[8].has_value());
    EXPECT_FALSE(idInfo_int[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->position, IDRP_AT_BORDER)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i]->value, 30) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, -30, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 0);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, -30, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 0);

    EXPECT_FALSE(idInfo_int[0].has_value());
    EXPECT_FALSE(idInfo_int[1].has_value());
    EXPECT_FALSE(idInfo_int[2].has_value());
    EXPECT_FALSE(idInfo_int[3].has_value());
    EXPECT_FALSE(idInfo_int[4].has_value());

    ASSERT_TRUE(idInfo_int[5].has_value());
    ASSERT_TRUE(idInfo_int[6].has_value());
    ASSERT_TRUE(idInfo_int[7].has_value());
    ASSERT_TRUE(idInfo_int[8].has_value());
    ASSERT_TRUE(idInfo_int[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->position, IDRP_AT_BORDER)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_EQ(idInfo_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i]->value, -30) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 30.0, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 31.5, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 32.5, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 32.0, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 30.0, 0);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 30.0, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 31.5, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 32.5, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 32.0, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 30.0, 0);

    ASSERT_TRUE(idInfo_float[0].has_value());
    ASSERT_TRUE(idInfo_float[1].has_value());
    ASSERT_TRUE(idInfo_float[2].has_value());
    ASSERT_TRUE(idInfo_float[3].has_value());
    ASSERT_TRUE(idInfo_float[4].has_value());

    EXPECT_FALSE(idInfo_float[5].has_value());
    EXPECT_FALSE(idInfo_float[6].has_value());
    EXPECT_FALSE(idInfo_float[7].has_value());
    EXPECT_FALSE(idInfo_float[8].has_value());
    EXPECT_FALSE(idInfo_float[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->position, IDRP_AT_BORDER)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 30.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 31.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 32.5) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 32.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 30.0) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, -30.0, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -31.5, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -32.0, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -32.5, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -30.0, 0);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, -30.0, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -31.5, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -32.0, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -32.5, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -30.0, 0);

    EXPECT_FALSE(idInfo_float[0].has_value());
    EXPECT_FALSE(idInfo_float[1].has_value());
    EXPECT_FALSE(idInfo_float[2].has_value());
    EXPECT_FALSE(idInfo_float[3].has_value());
    EXPECT_FALSE(idInfo_float[4].has_value());

    ASSERT_TRUE(idInfo_float[5].has_value());
    ASSERT_TRUE(idInfo_float[6].has_value());
    ASSERT_TRUE(idInfo_float[7].has_value());
    ASSERT_TRUE(idInfo_float[8].has_value());
    ASSERT_TRUE(idInfo_float[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->position, IDRP_AT_BORDER)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, 0)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -30.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -31.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -32.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -32.5) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -30.0) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 30, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 30);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, -30, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -30);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 30, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, -30, 0).has_value());


    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 30);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0, 0).has_value());

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 0);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);


    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 0).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 30);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);


    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder,  30, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder,  30, 0).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 0).has_value());


    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 0).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0, 0);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 0);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -1, 0).has_value());

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 0, 0);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 0);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 0, 0);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -2, 0);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -2, 0);

    ASSERT_TRUE(idInfo_int[0].has_value());
    ASSERT_TRUE(idInfo_int[1].has_value());
    ASSERT_TRUE(idInfo_int[2].has_value());
    ASSERT_TRUE(idInfo_int[3].has_value());
    ASSERT_TRUE(idInfo_int[4].has_value());

    ASSERT_TRUE(idInfo_int[5].has_value());
    ASSERT_TRUE(idInfo_int[6].has_value());
    ASSERT_TRUE(idInfo_int[7].has_value());
    ASSERT_TRUE(idInfo_int[8].has_value());
    ASSERT_TRUE(idInfo_int[9].has_value());

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i]->position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_int[i]->border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_int[i]->border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i]->value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_int[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i]->value, -2) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 0.0, 0);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 1.5, 0);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -2.0, 0);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 2.0, 0);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -1.5, 0);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 0.0, 0);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 1.5, 0);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -2.0, 0);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 2.0, 0);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -1.5, 0);

    ASSERT_TRUE(idInfo_float[0].has_value());
    ASSERT_TRUE(idInfo_float[1].has_value());
    ASSERT_TRUE(idInfo_float[2].has_value());
    ASSERT_TRUE(idInfo_float[3].has_value());
    ASSERT_TRUE(idInfo_float[4].has_value());

    ASSERT_TRUE(idInfo_float[5].has_value());
    ASSERT_TRUE(idInfo_float[6].has_value());
    ASSERT_TRUE(idInfo_float[7].has_value());
    ASSERT_TRUE(idInfo_float[8].has_value());
    ASSERT_TRUE(idInfo_float[9].has_value());

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i]->position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_float[i]->border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_float[i]->border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i]->value,  0.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i]->value,  1.5) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -2.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i]->value,  2.0) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -1.5) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i]->value,  0.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i]->value,  1.5) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -2.0) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i]->value,  2.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -1.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 0, 0);
    idInfo_unsigned[1] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    idInfo_unsigned[2] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 0);
    idInfo_unsigned[3] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 2, 0);
    idInfo_unsigned[4] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 0);

    idInfo_unsigned[5] = IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 0, 0);
    idInfo_unsigned[6] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    idInfo_unsigned[7] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -2, 0);
    idInfo_unsigned[8] = IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 2, 0);
    idInfo_unsigned[9] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -2, 0);

    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    ASSERT_TRUE(idInfo_unsigned[1].has_value());
    ASSERT_TRUE(idInfo_unsigned[2].has_value());
    ASSERT_TRUE(idInfo_unsigned[3].has_value());
    ASSERT_TRUE(idInfo_unsigned[4].has_value());

    ASSERT_TRUE(idInfo_unsigned[5].has_value());
    ASSERT_TRUE(idInfo_unsigned[6].has_value());
    ASSERT_TRUE(idInfo_unsigned[7].has_value());
    ASSERT_TRUE(idInfo_unsigned[8].has_value());
    ASSERT_TRUE(idInfo_unsigned[9].has_value());

    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(idInfo_unsigned[i]->position, IDRP_AT_START + IDRP_AT_BORDER) << "The error occurred when: i == " << i;

        EXPECT_EQ(idInfo_unsigned[i]->flags, IDRF_SUCCESSFULLY) << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_unsigned[i]->state)                 << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_unsigned[i]->stepCount, 0)             << "The error occurred when: i == " << i;

        if (i <= 4)
            EXPECT_EQ(idInfo_unsigned[i]->border, BorderRange::UpperBorder) << "The error occurred when: i == " << i;
        else
            EXPECT_EQ(idInfo_unsigned[i]->border, BorderRange::LowerBorder) << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_unsigned[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;

            case 5:    EXPECT_EQ(idInfo_unsigned[i]->value,  0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_unsigned[i]->value,  2) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_unsigned[i]->value, -2) << "The error occurred when: i == " << i;    break;
        }
    }

    //-----------------------------------------------------------------------------

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 30, 5);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 5);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 30, 5);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, 5);

    ASSERT_TRUE(idInfo_int[0].has_value());
    ASSERT_TRUE(idInfo_int[1].has_value());
    ASSERT_TRUE(idInfo_int[2].has_value());
    ASSERT_TRUE(idInfo_int[3].has_value());
    ASSERT_TRUE(idInfo_int[4].has_value());

    EXPECT_FALSE(idInfo_int[5].has_value());
    EXPECT_FALSE(idInfo_int[6].has_value());
    EXPECT_FALSE(idInfo_int[7].has_value());
    EXPECT_FALSE(idInfo_int[8].has_value());
    EXPECT_FALSE(idInfo_int[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->position, IDRP_OUT_OF_RANGE)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i]->value, 35) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i]->value, 40) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, 30, -5);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, -5);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, 30, -5);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 30, -5);

    ASSERT_TRUE(idInfo_int[0].has_value());
    ASSERT_TRUE(idInfo_int[1].has_value());
    ASSERT_TRUE(idInfo_int[2].has_value());
    ASSERT_TRUE(idInfo_int[3].has_value());
    ASSERT_TRUE(idInfo_int[4].has_value());

    EXPECT_FALSE(idInfo_int[5].has_value());
    EXPECT_FALSE(idInfo_int[6].has_value());
    EXPECT_FALSE(idInfo_int[7].has_value());
    EXPECT_FALSE(idInfo_int[8].has_value());
    EXPECT_FALSE(idInfo_int[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->position, IDRP_WITHIN_RANGE)           << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_EQ(idInfo_int[i]->value, 25) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_EQ(idInfo_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_EQ(idInfo_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_EQ(idInfo_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_EQ(idInfo_int[i]->value, 20) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, -30, 5);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 5);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, 5);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 5);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 5);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, -30, 5);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 5);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, 5);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 5);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 5);

    EXPECT_FALSE(idInfo_int[0].has_value());
    EXPECT_FALSE(idInfo_int[1].has_value());
    EXPECT_FALSE(idInfo_int[2].has_value());
    EXPECT_FALSE(idInfo_int[3].has_value());
    EXPECT_FALSE(idInfo_int[4].has_value());

    ASSERT_TRUE(idInfo_int[5].has_value());
    ASSERT_TRUE(idInfo_int[6].has_value());
    ASSERT_TRUE(idInfo_int[7].has_value());
    ASSERT_TRUE(idInfo_int[8].has_value());
    ASSERT_TRUE(idInfo_int[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->position, IDRP_OUT_OF_RANGE)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_EQ(idInfo_int[i]->value, -35) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i]->value, -40) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_int[0] = IdRange_int.getIdInfo(BorderRange::UpperBorder, -30, -5);
    idInfo_int[1] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, -5);
    idInfo_int[2] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -30, -5);
    idInfo_int[3] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, -5);
    idInfo_int[4] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, -5);

    idInfo_int[5] = IdRange_int.getIdInfo(BorderRange::LowerBorder, -30, -5);
    idInfo_int[6] = IdRange_int_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, -5);
    idInfo_int[7] = IdRange_int_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -30, -5);
    idInfo_int[8] = IdRange_int_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, -5);
    idInfo_int[9] = IdRange_int_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, -5);

    EXPECT_FALSE(idInfo_int[0].has_value());
    EXPECT_FALSE(idInfo_int[1].has_value());
    EXPECT_FALSE(idInfo_int[2].has_value());
    EXPECT_FALSE(idInfo_int[3].has_value());
    EXPECT_FALSE(idInfo_int[4].has_value());

    ASSERT_TRUE(idInfo_int[5].has_value());
    ASSERT_TRUE(idInfo_int[6].has_value());
    ASSERT_TRUE(idInfo_int[7].has_value());
    ASSERT_TRUE(idInfo_int[8].has_value());
    ASSERT_TRUE(idInfo_int[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(idInfo_int[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->position, IDRP_WITHIN_RANGE)           << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_int[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_int[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_EQ(idInfo_int[i]->value, -25) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_EQ(idInfo_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_EQ(idInfo_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_EQ(idInfo_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_EQ(idInfo_int[i]->value, -20) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 30.0, 5);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 31.5, 5);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 32.5, 5);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 32.0, 5);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 30.0, 5);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 30.0, 5);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 31.5, 5);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 32.5, 5);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 32.0, 5);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 30.0, 5);

    ASSERT_TRUE(idInfo_float[0].has_value());
    ASSERT_TRUE(idInfo_float[1].has_value());
    ASSERT_TRUE(idInfo_float[2].has_value());
    ASSERT_TRUE(idInfo_float[3].has_value());
    ASSERT_TRUE(idInfo_float[4].has_value());

    EXPECT_FALSE(idInfo_float[5].has_value());
    EXPECT_FALSE(idInfo_float[6].has_value());
    EXPECT_FALSE(idInfo_float[7].has_value());
    EXPECT_FALSE(idInfo_float[8].has_value());
    EXPECT_FALSE(idInfo_float[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->position, IDRP_OUT_OF_RANGE)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 35.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 39.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 40.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 39.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 37.5) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, 30.0, -5);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, 31.5, -5);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, 32.5, -5);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 32.0, -5);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, 30.0, -5);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, 30.0, -5);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, 31.5, -5);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, 32.5, -5);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 32.0, -5);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, 30.0, -5);

    ASSERT_TRUE(idInfo_float[0].has_value());
    ASSERT_TRUE(idInfo_float[1].has_value());
    ASSERT_TRUE(idInfo_float[2].has_value());
    ASSERT_TRUE(idInfo_float[3].has_value());
    ASSERT_TRUE(idInfo_float[4].has_value());

    EXPECT_FALSE(idInfo_float[5].has_value());
    EXPECT_FALSE(idInfo_float[6].has_value());
    EXPECT_FALSE(idInfo_float[7].has_value());
    EXPECT_FALSE(idInfo_float[8].has_value());
    EXPECT_FALSE(idInfo_float[9].has_value());

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->position, IDRP_WITHIN_RANGE)           << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->border, BorderRange::UpperBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 0:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 25.0) << "The error occurred when: i == " << i;    break;
            case 1:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 24.0) << "The error occurred when: i == " << i;    break;
            case 2:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 25.0) << "The error occurred when: i == " << i;    break;
            case 3:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 24.5) << "The error occurred when: i == " << i;    break;
            case 4:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, 22.5) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, -30.0, 5);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -31.5, 5);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -32.0, 5);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -32.5, 5);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -30.0, 5);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, -30.0, 5);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -31.5, 5);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -32.0, 5);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -32.5, 5);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -30.0, 5);

    EXPECT_FALSE(idInfo_float[0].has_value());
    EXPECT_FALSE(idInfo_float[1].has_value());
    EXPECT_FALSE(idInfo_float[2].has_value());
    EXPECT_FALSE(idInfo_float[3].has_value());
    EXPECT_FALSE(idInfo_float[4].has_value());

    ASSERT_TRUE(idInfo_float[5].has_value());
    ASSERT_TRUE(idInfo_float[6].has_value());
    ASSERT_TRUE(idInfo_float[7].has_value());
    ASSERT_TRUE(idInfo_float[8].has_value());
    ASSERT_TRUE(idInfo_float[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->position, IDRP_OUT_OF_RANGE)          << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, 5)                      << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -35.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -39.0) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -39.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -40.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -37.5) << "The error occurred when: i == " << i;    break;
        }
    }

    idInfo_float[0] = IdRange_float.getIdInfo(BorderRange::UpperBorder, -30.0, -5);
    idInfo_float[1] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::UpperBorder, -31.5, -5);
    idInfo_float[2] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::UpperBorder, -32.0, -5);
    idInfo_float[3] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -32.5, -5);
    idInfo_float[4] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::UpperBorder, -30.0, -5);

    idInfo_float[5] = IdRange_float.getIdInfo(BorderRange::LowerBorder, -30.0, -5);
    idInfo_float[6] = IdRange_float_Start_1p5_Step_1p5.getIdInfo(BorderRange::LowerBorder, -31.5, -5);
    idInfo_float[7] = IdRange_float_Start_n2_Step_1p5.getIdInfo(BorderRange::LowerBorder, -32.0, -5);
    idInfo_float[8] = IdRange_float_Start_2_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -32.5, -5);
    idInfo_float[9] = IdRange_float_Start_n1p5_Step_n1p5.getIdInfo(BorderRange::LowerBorder, -30.0, -5);

    EXPECT_FALSE(idInfo_float[0].has_value());
    EXPECT_FALSE(idInfo_float[1].has_value());
    EXPECT_FALSE(idInfo_float[2].has_value());
    EXPECT_FALSE(idInfo_float[3].has_value());
    EXPECT_FALSE(idInfo_float[4].has_value());

    ASSERT_TRUE(idInfo_float[5].has_value());
    ASSERT_TRUE(idInfo_float[6].has_value());
    ASSERT_TRUE(idInfo_float[7].has_value());
    ASSERT_TRUE(idInfo_float[8].has_value());
    ASSERT_TRUE(idInfo_float[9].has_value());

    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(idInfo_float[i]->flags, IDRF_SUCCESSFULLY)          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->position, IDRP_WITHIN_RANGE)           << "The error occurred when: i == " << i;
        EXPECT_FALSE(idInfo_float[i]->state)                          << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->stepCount, -5)                     << "The error occurred when: i == " << i;
        EXPECT_EQ(idInfo_float[i]->border, BorderRange::LowerBorder)  << "The error occurred when: i == " << i;

        switch (i) {
            case 5:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -25.0) << "The error occurred when: i == " << i;    break;
            case 6:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -24.0) << "The error occurred when: i == " << i;    break;
            case 7:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -24.5) << "The error occurred when: i == " << i;    break;
            case 8:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -25.0) << "The error occurred when: i == " << i;    break;
            case 9:    EXPECT_FLOAT_EQ(idInfo_float[i]->value, -22.5) << "The error occurred when: i == " << i;    break;
        }
    }


    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 30, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 35);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 5);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, -30, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -25);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 5);

    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 30, 5).has_value());
    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, -30, 5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, 30, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 25);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, -5);

    idInfo_unsigned[0] = IdRange_unsigned.getIdInfo(BorderRange::UpperBorder, -30, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -35);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, -5);

    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, 30, -5).has_value());
    EXPECT_FALSE(IdRange_unsigned.getIdInfo(BorderRange::LowerBorder, -30, -5).has_value());


    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 40);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 5);

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0, 5).has_value());

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 0);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 20);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, -5);

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::UpperBorder, 0, -5).has_value());

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_2_Step_2.getIdInfo(BorderRange::LowerBorder, 0, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, -1);


    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, 5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 20);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 5);

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -1, 5).has_value());

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, 30, -5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::UpperBorder, -2, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, 30, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 40);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, -5);

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_2.getIdInfo(BorderRange::LowerBorder, -1, -5).has_value());


    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder,  30, 5).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, 5).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder,  30, 5).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, 5).has_value());

    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder,  30, -5).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::UpperBorder, -30, -5).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder,  30, -5).has_value());
    EXPECT_FALSE(IdRange_unsigned_Start_2_Step_n2.getIdInfo(BorderRange::LowerBorder, -30, -5).has_value());


    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, 5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0, 5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, 0);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -1, 5).has_value());

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, 30, -5).has_value());

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::UpperBorder, -2, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::UpperBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, 0);

    idInfo_unsigned[0] = IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, 0, -5);
    ASSERT_TRUE(idInfo_unsigned[0].has_value());
    EXPECT_EQ(idInfo_unsigned[0]->flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(idInfo_unsigned[0]->position, IDRP_AT_START + IDRP_AT_BORDER);
    EXPECT_EQ(idInfo_unsigned[0]->border, BorderRange::LowerBorder);
    EXPECT_FALSE(idInfo_unsigned[0]->state);
    EXPECT_EQ(idInfo_unsigned[0]->value, -2);
    EXPECT_EQ(idInfo_unsigned[0]->stepCount, -1);

    EXPECT_FALSE(IdRange_unsigned_Start_n2_Step_n2.getIdInfo(BorderRange::LowerBorder, -1, -5).has_value());
}

TEST(SingleTests, Test_1)
{
    IdRange<int> IdRange_int;
    IdRange<float> IdRange_float;
    IdRange<unsigned> IdRange_unsigned;

    IdRange_int.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_int.setBorderLimit(BorderRange::UpperBorder,  50);
    IdRange_int.setBorderLimit(BorderRange::LowerBorder, -50);

    IdRange_float.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_float.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_float.setBorderLimit(BorderRange::UpperBorder,  50.5);
    IdRange_float.setBorderLimit(BorderRange::LowerBorder, -50.5);

    IdRange_unsigned.setBorderState(BorderRange::UpperBorder, true);
    IdRange_unsigned.moveBorder(BorderRange::UpperBorder,  10);
    IdRange_unsigned.moveBorder(BorderRange::LowerBorder, -5);
    IdRange_unsigned.setBorderLimit(BorderRange::UpperBorder, 50);
    IdRange_unsigned.setBorderLimit(BorderRange::LowerBorder, 3);

    EXPECT_TRUE (IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::LowerBorder), 3);


    IdRange<int> IdRange_int_cc(IdRange_int);
    IdRange<float> IdRange_float_cc(IdRange_float);
    IdRange<unsigned> IdRange_unsigned_cc(IdRange_unsigned);

    EXPECT_TRUE (IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_int_cc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_cc.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int_cc.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_cc.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int_cc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int_cc.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_float_cc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_cc.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::LowerBorder), 3);

    EXPECT_TRUE (IdRange_unsigned_cc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_cc.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned_cc.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_cc.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned_cc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned_cc.getBorderLimit(BorderRange::LowerBorder), 3);


    IdRange<int> IdRange_int_cm(std::move(IdRange_int));
    IdRange<float> IdRange_float_cm(std::move(IdRange_float));
    IdRange<unsigned> IdRange_unsigned_cm(std::move(IdRange_unsigned));

    EXPECT_TRUE (IdRange_int.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_int_cm.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_cm.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int_cm.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_cm.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int_cm.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int_cm.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_float.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_float_cm.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_cm.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_unsigned.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned.getBorderLimit(BorderRange::LowerBorder), 3);

    EXPECT_TRUE (IdRange_unsigned_cm.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_cm.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned_cm.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_cm.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned_cm.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned_cm.getBorderLimit(BorderRange::LowerBorder), 3);


    IdRange<int> IdRange_int_oc;
    IdRange<float> IdRange_float_oc;
    IdRange<unsigned> IdRange_unsigned_oc;

    IdRange_int_oc = IdRange_int_cc;
    IdRange_float_oc = IdRange_float_cc;
    IdRange_unsigned_oc = IdRange_unsigned_cc;

    EXPECT_TRUE (IdRange_int_oc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_oc.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int_oc.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_oc.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int_oc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int_oc.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_int_cc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_cc.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int_cc.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_cc.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int_cc.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int_cc.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_float_oc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_oc.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float_oc.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_oc.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float_oc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float_oc.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_float_cc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_cc.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float_cc.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_unsigned_oc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_oc.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned_oc.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_oc.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned_oc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned_oc.getBorderLimit(BorderRange::LowerBorder), 3);

    EXPECT_TRUE (IdRange_unsigned_cc.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_cc.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned_cc.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_cc.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned_cc.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned_cc.getBorderLimit(BorderRange::LowerBorder), 3);


    IdRange<int> IdRange_int_om;
    IdRange<float> IdRange_float_om;
    IdRange<unsigned> IdRange_unsigned_om;

    IdRange_int_om = std::move(IdRange_int_cm);
    IdRange_float_om = std::move(IdRange_float_cm);
    IdRange_unsigned_om = std::move(IdRange_unsigned_cm);

    EXPECT_TRUE (IdRange_int_cm.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_cm.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int_cm.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_cm.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int_cm.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int_cm.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_int_om.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_int_om.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_int_om.getBorderValue(BorderRange::UpperBorder),  10);
    EXPECT_EQ(IdRange_int_om.getBorderValue(BorderRange::LowerBorder), -10);
    EXPECT_EQ(IdRange_int_om.getBorderLimit(BorderRange::UpperBorder),  50);
    EXPECT_EQ(IdRange_int_om.getBorderLimit(BorderRange::LowerBorder), -50);

    EXPECT_TRUE (IdRange_float_cm.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_cm.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float_cm.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_float_om.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_float_om.getBorderState(BorderRange::LowerBorder));
    EXPECT_FLOAT_EQ(IdRange_float_om.getBorderValue(BorderRange::UpperBorder),  10.0);
    EXPECT_FLOAT_EQ(IdRange_float_om.getBorderValue(BorderRange::LowerBorder), -10.0);
    EXPECT_FLOAT_EQ(IdRange_float_om.getBorderLimit(BorderRange::UpperBorder),  50.5);
    EXPECT_FLOAT_EQ(IdRange_float_om.getBorderLimit(BorderRange::LowerBorder), -50.5);

    EXPECT_TRUE (IdRange_unsigned_cm.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_cm.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned_cm.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_cm.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned_cm.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned_cm.getBorderLimit(BorderRange::LowerBorder), 3);

    EXPECT_TRUE (IdRange_unsigned_om.getBorderState(BorderRange::UpperBorder));
    EXPECT_FALSE(IdRange_unsigned_om.getBorderState(BorderRange::LowerBorder));
    EXPECT_EQ(IdRange_unsigned_om.getBorderValue(BorderRange::UpperBorder), 10);
    EXPECT_EQ(IdRange_unsigned_om.getBorderValue(BorderRange::LowerBorder), 5);
    EXPECT_EQ(IdRange_unsigned_om.getBorderLimit(BorderRange::UpperBorder), 50);
    EXPECT_EQ(IdRange_unsigned_om.getBorderLimit(BorderRange::LowerBorder), 3);
}

TEST(SingleTests, Test_2)
{
    IdRange<int> IdRange_int;
    IdRange<int>::IdInfo IdInfo_int;

    IdRange_int.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int.setBorderLimit(BorderRange::UpperBorder,  50);
    IdRange_int.setBorderLimit(BorderRange::LowerBorder, -50);
    IdRange_int.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int.moveBorder(BorderRange::LowerBorder, 10);


    EXPECT_EQ(IdInfo_int.flags, IDRF_NOT_SET);
    EXPECT_EQ(IdInfo_int.position, IDRP_NOT_SET);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_FALSE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 0);
    EXPECT_EQ(IdInfo_int.stepCount, 0);

    IdInfo_int = IdRange_int.getIdInfo(BorderRange::UpperBorder, 0);

    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 10);
    EXPECT_EQ(IdInfo_int.stepCount, 0);


    IdRange<int>::IdInfo IdInfo_int_cc(IdInfo_int);

    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 10);
    EXPECT_EQ(IdInfo_int.stepCount, 0);

    EXPECT_EQ(IdInfo_int_cc.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int_cc.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int_cc.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int_cc.state);
    EXPECT_EQ(IdInfo_int_cc.value, 10);
    EXPECT_EQ(IdInfo_int_cc.stepCount, 0);


    IdRange<int>::IdInfo IdInfo_int_cm(std::move(IdInfo_int));

    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 10);
    EXPECT_EQ(IdInfo_int.stepCount, 0);

    EXPECT_EQ(IdInfo_int_cm.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int_cm.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int_cm.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int_cm.state);
    EXPECT_EQ(IdInfo_int_cm.value, 10);
    EXPECT_EQ(IdInfo_int_cm.stepCount, 0);


    IdRange<int>::IdInfo IdInfo_int_oc;
    IdInfo_int_oc = IdInfo_int_cc;

    EXPECT_EQ(IdInfo_int_oc.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int_oc.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int_oc.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int_oc.state);
    EXPECT_EQ(IdInfo_int_oc.value, 10);
    EXPECT_EQ(IdInfo_int_oc.stepCount, 0);

    EXPECT_EQ(IdInfo_int_cc.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int_cc.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int_cc.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int_cc.state);
    EXPECT_EQ(IdInfo_int_cc.value, 10);
    EXPECT_EQ(IdInfo_int_cc.stepCount, 0);


    IdRange<int>::IdInfo IdInfo_int_om;
    IdInfo_int_om = std::move(IdInfo_int_cm);

    EXPECT_EQ(IdInfo_int_om.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int_om.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int_om.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int_om.state);
    EXPECT_EQ(IdInfo_int_om.value, 10);
    EXPECT_EQ(IdInfo_int_om.stepCount, 0);

    EXPECT_EQ(IdInfo_int_cm.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int_cm.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int_cm.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int_cm.state);
    EXPECT_EQ(IdInfo_int_cm.value, 10);
    EXPECT_EQ(IdInfo_int_cm.stepCount, 0);
}

TEST(SingleTests, Test_3)
{
    IdRange<int> IdRange_int;
    IdRange<float> IdRange_float;

    IdRange<int>::IdInfo IdInfo_int;
    IdRange<float>::IdInfo IdInfo_float;

    IdRange_int.setBorderState(BorderRange::UpperBorder, true);
    IdRange_int.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_int.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_int.setBorderLimit(BorderRange::UpperBorder,  50);
    IdRange_int.setBorderLimit(BorderRange::LowerBorder, -50);

    IdRange_float.setBorderState(BorderRange::UpperBorder, true);
    IdRange_float.moveBorder(BorderRange::UpperBorder, 10);
    IdRange_float.moveBorder(BorderRange::LowerBorder, 10);
    IdRange_float.setBorderLimit(BorderRange::UpperBorder,  50.5);
    IdRange_float.setBorderLimit(BorderRange::LowerBorder, -50.5);


    IdInfo_int = IdRange_int.getIdInfo(BorderRange::UpperBorder, -15);
    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(IdInfo_int.border, BorderRange::LowerBorder);
    EXPECT_FALSE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, -5);
    EXPECT_EQ(IdInfo_int.stepCount, -15);

    IdInfo_int = IdRange_int.getIdInfo(BorderRange::LowerBorder, -15);
    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 5);
    EXPECT_EQ(IdInfo_int.stepCount, -15);

    IdInfo_float = IdRange_float.getIdInfo(BorderRange::UpperBorder, -15);
    EXPECT_EQ(IdInfo_float.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_float.position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(IdInfo_float.border, BorderRange::LowerBorder);
    EXPECT_FALSE(IdInfo_float.state);
    EXPECT_FLOAT_EQ(IdInfo_float.value, -5.0);
    EXPECT_EQ(IdInfo_float.stepCount, -15);

    IdInfo_float = IdRange_float.getIdInfo(BorderRange::LowerBorder, -15);
    EXPECT_EQ(IdInfo_float.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_float.position, IDRP_WITHIN_RANGE);
    EXPECT_EQ(IdInfo_float.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_float.state);
    EXPECT_FLOAT_EQ(IdInfo_float.value, 5.0);
    EXPECT_EQ(IdInfo_float.stepCount, -15);


    IdInfo_int = IdRange_int.getIdInfo(BorderRange::UpperBorder, 40);
    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 50);
    EXPECT_EQ(IdInfo_int.stepCount, 40);

    IdInfo_int = IdRange_int.getIdInfo(BorderRange::LowerBorder, 40);
    EXPECT_EQ(IdInfo_int.flags, IDRF_SUCCESSFULLY);
    EXPECT_EQ(IdInfo_int.position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(IdInfo_int.border, BorderRange::LowerBorder);
    EXPECT_FALSE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, -50);
    EXPECT_EQ(IdInfo_int.stepCount, 40);

    IdInfo_float = IdRange_float.getIdInfo(BorderRange::UpperBorder, 50);
    EXPECT_EQ(IdInfo_float.flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(IdInfo_float.position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(IdInfo_float.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_float.state);
    EXPECT_FLOAT_EQ(IdInfo_float.value, 50.0);
    EXPECT_EQ(IdInfo_float.stepCount, 40);

    IdInfo_float = IdRange_float.getIdInfo(BorderRange::LowerBorder, 50);
    EXPECT_EQ(IdInfo_float.flags, IDRF_ID_OUT_OF_LIMIT);
    EXPECT_EQ(IdInfo_float.position, IDRP_OUT_OF_RANGE);
    EXPECT_EQ(IdInfo_float.border, BorderRange::LowerBorder);
    EXPECT_FALSE(IdInfo_float.state);
    EXPECT_FLOAT_EQ(IdInfo_float.value, -50.0);
    EXPECT_EQ(IdInfo_float.stepCount, 40);


    IdInfo_int = IdRange_int.getIdInfo(BorderRange::UpperBorder, -60);
    EXPECT_EQ(IdInfo_int.flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(IdInfo_int.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int.border, BorderRange::LowerBorder);
    EXPECT_FALSE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, -10);
    EXPECT_EQ(IdInfo_int.stepCount, -20);

    IdInfo_int = IdRange_int.getIdInfo(BorderRange::LowerBorder, -60);
    EXPECT_EQ(IdInfo_int.flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(IdInfo_int.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_int.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_int.state);
    EXPECT_EQ(IdInfo_int.value, 10);
    EXPECT_EQ(IdInfo_int.stepCount, -20);

    IdInfo_float = IdRange_float.getIdInfo(BorderRange::UpperBorder, -70);
    EXPECT_EQ(IdInfo_float.flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(IdInfo_float.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_float.border, BorderRange::LowerBorder);
    EXPECT_FALSE(IdInfo_float.state);
    EXPECT_FLOAT_EQ(IdInfo_float.value, -10.0);
    EXPECT_EQ(IdInfo_float.stepCount, -20);

    IdInfo_float = IdRange_float.getIdInfo(BorderRange::LowerBorder, -70);
    EXPECT_EQ(IdInfo_float.flags, IDRF_RANGE_ARE_BENT);
    EXPECT_EQ(IdInfo_float.position, IDRP_AT_BORDER);
    EXPECT_EQ(IdInfo_float.border, BorderRange::UpperBorder);
    EXPECT_TRUE(IdInfo_float.state);
    EXPECT_FLOAT_EQ(IdInfo_float.value, 10.0);
    EXPECT_EQ(IdInfo_float.stepCount, -20);
}
