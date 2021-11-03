#include "EditingStrings.h"

#include <gtest/gtest.h>

using namespace ONF;


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*
 * Что проверяем:             Функцию trimString(std::wstring&, const std::wstring&, unsigned).
 * Доп. проверки:             -
 *
 * Проверяемая ситуация:      Удаляем разное количество символов с левой стороны строки и проверяем,
 *                            корректно ли они удалились (сравниваем количество удаленных символов
 *                            и строку полученную на выходе).
 *
 * Сценарий (поэтапно):       1) Просим ничего не удалять. Вызываем функцию вхолостую. Функция должна
 *                               ничего не удалять, а строка на выходе должна быть равна строке на входе.
 *                            2) Просим функцию удалить 1 тип символа справа и 1 тип символа где-то
 *                               из центра. Функция должна ничего не удалять.
 *                            3) Просим функцию удалить 1 тип символа справа, 1 тип символа где-то
 *                               из центра и еще 1 слева. Функция должна удалить только символы слева.
 *                            4) Просим удалить все символы кроме последнего справа. Функция должна
 *                               удалить все символы кроме последнего справа.
 *                            5) Просим удалить все оставшиеся символы. Функция должна удалить все
 *                               оставшиеся символы.
 *                            6) Передаем в функцию пустую строку и просим удалить из нее разные
 *                               символы слева. Функция должна вернуть ту же пустую строку и
 *                               количество удаленных символов равное 0.
 */
TEST(trimString, TrimmingSide_Left)
{
    //врГОР - ru. Потому нужны wide строки.
    std::wstring sourceStr  = L"  /*%`1233210-+ \n\t\\ yfFbHJ  врГОР";
    std::wstring str = sourceStr;

    //Этап 1.
    EXPECT_EQ(trimString(str, L"", TrimmingSide_Left), 0);
    EXPECT_EQ(str, sourceStr);

    //Этап 2.
    EXPECT_EQ(trimString(str, L"yР", TrimmingSide_Left), 0);
    EXPECT_EQ(str, sourceStr);

    //Этап 3.
    EXPECT_EQ(trimString(str, L"Г Р", TrimmingSide_Left), 2);
    EXPECT_EQ(str, L"/*%`1233210-+ \n\t\\ yfFbHJ  врГОР");

    //Этап 4.
    EXPECT_EQ(trimString(str, L"  /*%`1233210-+ \n\t\\ yfFbHJ  врГО", TrimmingSide_Left), 30);
    EXPECT_EQ(str, L"Р");

    //Этап 5.
    EXPECT_EQ(trimString(str, sourceStr, TrimmingSide_Left), 1);
    EXPECT_EQ(str, L"");

    //Этап 6.
    EXPECT_EQ(trimString(str, sourceStr, TrimmingSide_Left), 0);
    EXPECT_EQ(str, L"");
}

/*
 * Что проверяем:             Функцию trimString(std::wstring&, const std::wstring&, unsigned).
 * Доп. проверки:             -
 *
 * Проверяемая ситуация:      Удаляем разное количество символов с правой стороны строки и проверяем,
 *                            корректно ли они удалились (сравниваем количество удаленных символов
 *                            и строку полученную на выходе).
 *
 * Сценарий (поэтапно):       1) Просим ничего не удалять. Вызываем функцию вхолостую. Функция должна
 *                               ничего не удалять, а строка на выходе должна быть равна строке на входе.
 *                            2) Просим функцию удалить 1 тип символа слева и 1 тип символа где-то
 *                               из центра. Функция должна ничего не удалять.
 *                            3) Просим функцию удалить 1 тип символа справа, 1 тип символа где-то
 *                               из центра и еще 1 слева. Функция должна удалить только символы справа.
 *                            4) Просим удалить все символы кроме последнего слева. Функция должна
 *                               удалить все символы кроме последнего слева.
 *                            5) Просим удалить все оставшиеся символы. Функция должна удалить все
 *                               оставшиеся символы.
 *                            6) Передаем в функцию пустую строку и просим удалить из нее разные
 *                               символы справа. Функция должна вернуть ту же пустую строку и
 *                               количество удаленных символов равное 0.
 */
TEST(trimString, TrimmingSide_Right)
{
    //врГОР - ru. Потому нужны wide строки.
    std::wstring sourceStr  = L"t  /*%`1233210-+ \n\t\\ yfFbHJ  врГОР";
    std::wstring str = sourceStr;

    //Этап 1.
    EXPECT_EQ(trimString(str, L"", TrimmingSide_Right), 0);
    EXPECT_EQ(str, sourceStr);

    //Этап 2.
    EXPECT_EQ(trimString(str, L"t+", TrimmingSide_Right), 0);
    EXPECT_EQ(str, sourceStr);

    //Этап 3.
    EXPECT_EQ(trimString(str, L"ГtР", TrimmingSide_Right), 1);
    EXPECT_EQ(str, L"t  /*%`1233210-+ \n\t\\ yfFbHJ  врГО");

    //Этап 4.
    EXPECT_EQ(trimString(str, L"  /*%`1233210-+ \n\t\\ yfFbHJ  врГОР", TrimmingSide_Right), 32);
    EXPECT_EQ(str, L"t");

    //Этап 5.
    EXPECT_EQ(trimString(str, sourceStr, TrimmingSide_Right), 1);
    EXPECT_EQ(str, L"");

    //Этап 6.
    EXPECT_EQ(trimString(str, sourceStr, TrimmingSide_Right), 0);
    EXPECT_EQ(str, L"");
}

/*
 * Что проверяем:             Функцию trimString(std::wstring&, const std::wstring&, unsigned).
 * Доп. проверки:             -
 *
 * Проверяемая ситуация:      Удаляем разное количество символов с правой и с левой стороны строки
 *                            и проверяем, корректно ли они удалились (сравниваем количество
 *                            удаленных символов и строку полученную на выходе).
 *
 * Сценарий (поэтапно):       1) Просим ничего не удалять. Вызываем функцию вхолостую. Функция должна
 *                               ничего не удалять, а строка на выходе должна быть равна строке на входе.
 *                            2) Просим функцию удалить 1 тип символа слева, 1 справа и еще 1 где-то
 *                               из центра. Функция должна удалить только символы справа и слева.
 *                            3) Просим удалить все символы кроме 2 символов разного типа находящихся
 *                               в центре. Функция должна удалить все символы кроме этих двух.
 *                            4) Копируем строку. Этот этап мы работаем с копией. Просим удалить
 *                               символ слева. Функция должна удалить только символ слева.
 *                            5) Просим удалить символ справа. Функция должна удалить только символ
 *                               справа.
 *                            6) Просим удалить все оставшиеся символы. Функция должна удалить все
 *                               оставшиеся символы.
 *                            7) Передаем в функцию пустую строку и просим удалить из нее разные
 *                               символы слева и справа. Функция должна вернуть ту же пустую строку и
 *                               количество удаленных символов равное 0.
 */
TEST(trimString, TrimmingSide_Both)
{
    //врГОР - ru. Потому нужны wide строки.
    std::wstring sourceStr  = L"t  /*%`1233210-+ \n\t\\ yfFbHJ  врГОР";
    std::wstring str = sourceStr;

    //Этап 1.
    EXPECT_EQ(trimString(str, L"", TrimmingSide_Left | TrimmingSide_Right), 0);
    EXPECT_EQ(str, sourceStr);

    //Этап 2.
    EXPECT_EQ(trimString(str, L"0tР", TrimmingSide_Left | TrimmingSide_Right), 2);
    EXPECT_EQ(str, L"  /*%`1233210-+ \n\t\\ yfFbHJ  врГО");

    //Этап 3.
    EXPECT_EQ(trimString(str, L"t  /*%`1233210 \n\t\\ yfFbHJ  врГОР", TrimmingSide_Left | TrimmingSide_Right), 30);
    EXPECT_EQ(str, L"-+");

    //Этап 4.
    std::wstring str_copy = str;
    EXPECT_EQ(trimString(str_copy, L"-", TrimmingSide_Left | TrimmingSide_Right), 1);
    EXPECT_EQ(str_copy, L"+");

    //Этап 5.
    EXPECT_EQ(trimString(str, L"+", TrimmingSide_Left | TrimmingSide_Right), 1);
    EXPECT_EQ(str, L"-");

    //Этап 6.
    EXPECT_EQ(trimString(str, sourceStr, TrimmingSide_Left | TrimmingSide_Right), 1);
    EXPECT_EQ(str, L"");

    //Этап 7.
    EXPECT_EQ(trimString(str, sourceStr, TrimmingSide_Left | TrimmingSide_Right), 0);
    EXPECT_EQ(str, L"");
}
