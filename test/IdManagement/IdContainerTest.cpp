﻿#include "IdManagement.h"

#include <gtest/gtest.h>

using namespace ONF;


template<class T>
class OpenIdContainer : public IdContainer<T>
{
public:
    OpenIdContainer(IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic)
        : IdContainer<T>(idIssuingMethod) {};

    OpenIdContainer(const OpenIdContainer<T>& other) = default;
    OpenIdContainer(OpenIdContainer<T>&& other) = default;

    OpenIdContainer<T>& operator=(const OpenIdContainer<T>& other) = default;
    OpenIdContainer<T>& operator=(OpenIdContainer<T>&& other) = default;

};

struct IdContainerTests : public ::testing::Test
{
protected:
    OpenIdContainer<int> idContainer_int;
    OpenIdContainer<int> idContainer_int_ascending;
    OpenIdContainer<int> idContainer_int_descending;

    OpenIdContainer<float> idContainer_float;
    OpenIdContainer<float> idContainer_float_ascending;
    OpenIdContainer<float> idContainer_float_descending;

    OpenIdContainer<unsigned> idContainer_unsigned;
    OpenIdContainer<unsigned> idContainer_unsigned_ascending;
    OpenIdContainer<unsigned> idContainer_unsigned_descending;

    OpenIdContainer<bool> idContainer_bool;
    OpenIdContainer<bool> idContainer_bool_ascending;
    OpenIdContainer<bool> idContainer_bool_descending;

    OpenIdContainer<char> idContainer_char;
    OpenIdContainer<char> idContainer_char_ascending;
    OpenIdContainer<char> idContainer_char_descending;


    std::optional<int> optional_int_result;
    std::optional<float> optional_float_result;
    std::optional<unsigned> optional_unsigned_result;
    std::optional<bool> optional_bool_result;
    std::optional<char> optional_char_result;


    IdContainerTests()
        : idContainer_int_ascending(IdIssuingMethod::Static_Ascending),
          idContainer_int_descending(IdIssuingMethod::Static_Descending),

          idContainer_float_ascending(IdIssuingMethod::Static_Ascending),
          idContainer_float_descending(IdIssuingMethod::Static_Descending),

          idContainer_unsigned_ascending(IdIssuingMethod::Static_Ascending),
          idContainer_unsigned_descending(IdIssuingMethod::Static_Descending),

          idContainer_bool_ascending(IdIssuingMethod::Static_Ascending),
          idContainer_bool_descending(IdIssuingMethod::Static_Descending),

          idContainer_char_ascending(IdIssuingMethod::Static_Ascending),
          idContainer_char_descending(IdIssuingMethod::Static_Descending) {};

};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//TODO: Добавить проверку Size там где она была удалена коммитом
//      f40764e07ccc500e96d12c7dd3d76e54ca28622e (Внесен ряд исправлений в IdContainer...).


TEST_F(IdContainerTests, Test1)
{
    EXPECT_FALSE(idContainer_int.getNextId().has_value());
    EXPECT_FALSE(idContainer_int_ascending.getNextId().has_value());
    EXPECT_FALSE(idContainer_int_descending.getNextId().has_value());

    EXPECT_FALSE(idContainer_float.getNextId().has_value());
    EXPECT_FALSE(idContainer_float_ascending.getNextId().has_value());
    EXPECT_FALSE(idContainer_float_descending.getNextId().has_value());

    EXPECT_FALSE(idContainer_unsigned.getNextId().has_value());
    EXPECT_FALSE(idContainer_unsigned_ascending.getNextId().has_value());
    EXPECT_FALSE(idContainer_unsigned_descending.getNextId().has_value());

    EXPECT_FALSE(idContainer_bool.getNextId().has_value());
    EXPECT_FALSE(idContainer_bool_ascending.getNextId().has_value());
    EXPECT_FALSE(idContainer_bool_descending.getNextId().has_value());

    EXPECT_FALSE(idContainer_char.getNextId().has_value());
    EXPECT_FALSE(idContainer_char_ascending.getNextId().has_value());
    EXPECT_FALSE(idContainer_char_descending.getNextId().has_value());


    EXPECT_FALSE(idContainer_int.find(3));
    EXPECT_FALSE(idContainer_int_ascending.find(-3));
    EXPECT_FALSE(idContainer_int_descending.find(0));

    EXPECT_FALSE(idContainer_float.find(3));
    EXPECT_FALSE(idContainer_float_ascending.find(-3));
    EXPECT_FALSE(idContainer_float_descending.find(0));

    EXPECT_FALSE(idContainer_unsigned.find(3));
    EXPECT_FALSE(idContainer_unsigned_ascending.find(-3));
    EXPECT_FALSE(idContainer_unsigned_descending.find(0));

    EXPECT_FALSE(idContainer_bool.find(3));
    EXPECT_FALSE(idContainer_bool_ascending.find(-3));
    EXPECT_FALSE(idContainer_bool_descending.find(0));

    EXPECT_FALSE(idContainer_char.find(3));
    EXPECT_FALSE(idContainer_char_ascending.find(-3));
    EXPECT_FALSE(idContainer_char_descending.find(0));


    for (int i = -3; i < 3; ++i) {
        ASSERT_FALSE(idContainer_int.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_int_ascending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_int_descending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;

        ASSERT_FALSE(idContainer_float.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_float_ascending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_float_descending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;

        ASSERT_FALSE(idContainer_unsigned.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_unsigned_ascending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_unsigned_descending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;

        ASSERT_FALSE(idContainer_bool.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_bool_ascending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_bool_descending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;

        ASSERT_FALSE(idContainer_char.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_char_ascending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
        ASSERT_FALSE(idContainer_char_descending.findByIndex(i).has_value()) << "The error occurred when: i == " << i;
    }


    EXPECT_EQ(idContainer_int.size(), 0);
    EXPECT_EQ(idContainer_int_ascending.size(), 0);
    EXPECT_EQ(idContainer_int_descending.size(), 0);

    EXPECT_EQ(idContainer_float.size(), 0);
    EXPECT_EQ(idContainer_float_ascending.size(), 0);
    EXPECT_EQ(idContainer_float_descending.size(), 0);

    EXPECT_EQ(idContainer_unsigned.size(), 0);
    EXPECT_EQ(idContainer_unsigned_ascending.size(), 0);
    EXPECT_EQ(idContainer_unsigned_descending.size(), 0);

    EXPECT_EQ(idContainer_bool.size(), 0);
    EXPECT_EQ(idContainer_bool_ascending.size(), 0);
    EXPECT_EQ(idContainer_bool_descending.size(), 0);

    EXPECT_EQ(idContainer_char.size(), 0);
    EXPECT_EQ(idContainer_char_ascending.size(), 0);
    EXPECT_EQ(idContainer_char_descending.size(), 0);


    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
}

TEST_F(IdContainerTests, Test2)
{
    idContainer_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_int_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_int_descending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);


    idContainer_float.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_float_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_float_descending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);


    idContainer_unsigned.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    idContainer_unsigned_ascending.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    idContainer_unsigned_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    idContainer_bool.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    idContainer_bool_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_bool_descending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);


    idContainer_char.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_char_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_char_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
}

TEST_F(IdContainerTests, Test3)
{
    EXPECT_TRUE (idContainer_int.add( 3));
    EXPECT_TRUE (idContainer_int.add( 1));
    EXPECT_FALSE(idContainer_int.add( 3));
    EXPECT_TRUE (idContainer_int.add(-2));
    EXPECT_TRUE (idContainer_int.add( 0));
    EXPECT_FALSE(idContainer_int.add( 0));

    EXPECT_TRUE (idContainer_int.find(3));
    EXPECT_FALSE(idContainer_int.find(6));

    EXPECT_EQ(idContainer_int.size(), 4);


    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  3);
    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  1);
    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -2);
    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  0);

    EXPECT_FALSE(idContainer_int.getNextId().has_value());
    EXPECT_EQ(idContainer_int.size(), 0);


    EXPECT_TRUE (idContainer_int_ascending.add( 3));
    EXPECT_TRUE (idContainer_int_ascending.add( 1));
    EXPECT_TRUE (idContainer_int_ascending.add(-2));
    EXPECT_FALSE(idContainer_int_ascending.add(-2));
    EXPECT_TRUE (idContainer_int_ascending.add( 0));

    EXPECT_TRUE (idContainer_int_ascending.find(-2));
    EXPECT_FALSE(idContainer_int_ascending.find(-5));

    EXPECT_EQ(idContainer_int_ascending.size(), 4);


    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -2);
    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  0);
    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  1);
    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  3);

    EXPECT_FALSE(idContainer_int_ascending.getNextId().has_value());
    EXPECT_EQ(idContainer_int_ascending.size(), 0);


    EXPECT_TRUE (idContainer_int_descending.add( 3));
    EXPECT_FALSE(idContainer_int_descending.add( 3));
    EXPECT_TRUE (idContainer_int_descending.add( 1));
    EXPECT_TRUE (idContainer_int_descending.add(-2));
    EXPECT_TRUE (idContainer_int_descending.add( 0));

    EXPECT_TRUE (idContainer_int_descending.find(0));
    EXPECT_FALSE(idContainer_int_descending.find(10));

    EXPECT_EQ(idContainer_int_descending.size(), 4);


    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  3);
    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  1);
    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result,  0);
    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -2);

    EXPECT_FALSE(idContainer_int_descending.getNextId().has_value());
    EXPECT_EQ(idContainer_int_descending.size(), 0);


    EXPECT_TRUE (idContainer_float.add( 3.0));
    EXPECT_TRUE (idContainer_float.add( 1.0));
    EXPECT_TRUE (idContainer_float.add(-2.0));
    EXPECT_TRUE (idContainer_float.add( 0.0));
    EXPECT_FALSE(idContainer_float.add( 0.0));

    EXPECT_TRUE (idContainer_float.find(3.0));
    EXPECT_FALSE(idContainer_float.find(3.3));

    EXPECT_EQ(idContainer_float.size(), 4);


    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  3.0);
    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  1.0);
    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -2.0);
    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  0.0);

    EXPECT_FALSE(idContainer_float.getNextId().has_value());
    EXPECT_EQ(idContainer_float.size(), 0);


    EXPECT_TRUE (idContainer_float_ascending.add( 3.0));
    EXPECT_TRUE (idContainer_float_ascending.add( 1.0));
    EXPECT_TRUE (idContainer_float_ascending.add(-2.0));
    EXPECT_FALSE(idContainer_float_ascending.add( 1.0));
    EXPECT_TRUE (idContainer_float_ascending.add( 0.0));

    EXPECT_TRUE (idContainer_float_ascending.find(-2.0));
    EXPECT_FALSE(idContainer_float_ascending.find(-1.9));

    EXPECT_EQ(idContainer_float_ascending.size(), 4);


    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -2.0);
    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  0.0);
    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  1.0);
    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  3.0);

    EXPECT_FALSE(idContainer_float_ascending.getNextId().has_value());
    EXPECT_EQ(idContainer_float_ascending.size(), 0);


    EXPECT_TRUE (idContainer_float_descending.add( 3.0));
    EXPECT_TRUE (idContainer_float_descending.add( 1.0));
    EXPECT_FALSE(idContainer_float_descending.add( 1.0));
    EXPECT_TRUE (idContainer_float_descending.add(-2.0));
    EXPECT_TRUE (idContainer_float_descending.add( 0.0));

    EXPECT_TRUE (idContainer_float_descending.find(0.0));
    EXPECT_FALSE(idContainer_float_descending.find(2.0));

    EXPECT_EQ(idContainer_float_descending.size(), 4);


    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  3.0);
    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  1.0);
    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  0.0);
    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -2.0);

    EXPECT_FALSE(idContainer_float_descending.getNextId().has_value());
    EXPECT_EQ(idContainer_float_descending.size(), 0);


    EXPECT_TRUE (idContainer_unsigned.add( 3));
    EXPECT_TRUE (idContainer_unsigned.add( 1));
    EXPECT_TRUE (idContainer_unsigned.add(-2));
    EXPECT_FALSE(idContainer_unsigned.add( 3));
    EXPECT_TRUE (idContainer_unsigned.add( 0));

    EXPECT_TRUE (idContainer_unsigned.find(3));
    EXPECT_TRUE (idContainer_unsigned.find((unsigned)-2));
    EXPECT_FALSE(idContainer_unsigned.find(6));

    EXPECT_EQ(idContainer_unsigned.size(), 4);


    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  3);
    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  1);
    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);
    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  0);

    EXPECT_FALSE(idContainer_unsigned.getNextId().has_value());
    EXPECT_EQ(idContainer_unsigned.size(), 0);


    EXPECT_TRUE (idContainer_unsigned_ascending.add(-2));
    EXPECT_FALSE(idContainer_unsigned_ascending.add(-2));
    EXPECT_TRUE (idContainer_unsigned_ascending.add( 3));
    EXPECT_TRUE (idContainer_unsigned_ascending.add( 1));
    EXPECT_TRUE (idContainer_unsigned_ascending.add( 0));

    EXPECT_TRUE (idContainer_unsigned_ascending.find(-2));
    EXPECT_FALSE(idContainer_unsigned_ascending.find(-3));

    EXPECT_EQ(idContainer_unsigned_ascending.size(), 4);


    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  0);
    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  1);
    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  3);
    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);

    EXPECT_FALSE(idContainer_unsigned_ascending.getNextId().has_value());
    EXPECT_EQ(idContainer_unsigned_ascending.size(), 0);


    EXPECT_TRUE (idContainer_unsigned_descending.add( 3));
    EXPECT_TRUE (idContainer_unsigned_descending.add( 1));
    EXPECT_TRUE (idContainer_unsigned_descending.add(-2));
    EXPECT_TRUE (idContainer_unsigned_descending.add( 0));
    EXPECT_FALSE(idContainer_unsigned_descending.add( 0));

    EXPECT_TRUE (idContainer_unsigned_descending.find( 0));
    EXPECT_FALSE(idContainer_unsigned_descending.find(-7));

    EXPECT_EQ(idContainer_unsigned_descending.size(), 4);


    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);
    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  3);
    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  1);
    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  0);

    EXPECT_FALSE(idContainer_unsigned_descending.getNextId().has_value());
    EXPECT_EQ(idContainer_unsigned_descending.size(), 0);


    EXPECT_TRUE (idContainer_bool.add( 3));
    EXPECT_FALSE(idContainer_bool.add( 1));
    EXPECT_FALSE(idContainer_bool.add(-2));
    EXPECT_TRUE (idContainer_bool.add( 0));

    EXPECT_TRUE(idContainer_bool.find(3));
    EXPECT_TRUE(idContainer_bool.find(7));
    EXPECT_TRUE(idContainer_bool.find(0));

    EXPECT_EQ(idContainer_bool.size(), 2);


    optional_bool_result = idContainer_bool.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);
    optional_bool_result = idContainer_bool.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);

    EXPECT_FALSE(idContainer_bool.getNextId().has_value());
    EXPECT_EQ(idContainer_bool.size(), 0);


    EXPECT_TRUE (idContainer_bool_ascending.add( 3));
    EXPECT_FALSE(idContainer_bool_ascending.add( 1));
    EXPECT_FALSE(idContainer_bool_ascending.add(-2));
    EXPECT_TRUE (idContainer_bool_ascending.add( 0));

    EXPECT_TRUE(idContainer_bool_ascending.find(-3));
    EXPECT_TRUE(idContainer_bool_ascending.find(-10));
    EXPECT_TRUE(idContainer_bool_ascending.find( 0));

    EXPECT_EQ(idContainer_bool_ascending.size(), 2);


    optional_bool_result = idContainer_bool_ascending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);
    optional_bool_result = idContainer_bool_ascending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);

    EXPECT_FALSE(idContainer_bool_ascending.getNextId().has_value());
    EXPECT_EQ(idContainer_bool_ascending.size(), 0);


    EXPECT_TRUE (idContainer_bool_descending.add( 3));
    EXPECT_FALSE(idContainer_bool_descending.add( 1));
    EXPECT_FALSE(idContainer_bool_descending.add(-2));
    EXPECT_TRUE (idContainer_bool_descending.add( 0));

    EXPECT_TRUE(idContainer_bool_descending.find(-2));
    EXPECT_TRUE(idContainer_bool_descending.find( 9));
    EXPECT_TRUE(idContainer_bool_descending.find( 0));

    EXPECT_EQ(idContainer_bool_descending.size(), 2);


    optional_bool_result = idContainer_bool_descending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);
    optional_bool_result = idContainer_bool_descending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);

    EXPECT_FALSE(idContainer_bool_descending.getNextId().has_value());
    EXPECT_EQ(idContainer_bool_descending.size(), 0);


    EXPECT_TRUE (idContainer_char.add(-2));
    EXPECT_TRUE (idContainer_char.add( 3));
    EXPECT_TRUE (idContainer_char.add( 1));
    EXPECT_TRUE (idContainer_char.add( 0));
    EXPECT_TRUE (idContainer_char.add( 125));
    EXPECT_FALSE(idContainer_char.add( 0));
    EXPECT_FALSE(idContainer_char.add( 125));

    EXPECT_TRUE (idContainer_char.find(3));
    EXPECT_FALSE(idContainer_char.find(4));

    EXPECT_EQ(idContainer_char.size(), 5);


    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -2);
    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  (char)3);
    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  1);
    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  0);
    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  125);

    EXPECT_FALSE(idContainer_char.getNextId().has_value());
    EXPECT_EQ(idContainer_char.size(), 0);


    EXPECT_TRUE (idContainer_char_ascending.add(-2));
    EXPECT_TRUE (idContainer_char_ascending.add( 3));
    EXPECT_TRUE (idContainer_char_ascending.add( 1));
    EXPECT_TRUE (idContainer_char_ascending.add( 0));
    EXPECT_TRUE (idContainer_char_ascending.add( 125));
    EXPECT_FALSE(idContainer_char_ascending.add(-2));

    EXPECT_TRUE (idContainer_char_ascending.find(-2));
    EXPECT_FALSE(idContainer_char_ascending.find(-4));

    EXPECT_EQ(idContainer_char_ascending.size(), 5);


    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -2);
    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  0);
    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  (char)1);
    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  3);
    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  125);

    EXPECT_FALSE(idContainer_char_ascending.getNextId().has_value());
    EXPECT_EQ(idContainer_char_ascending.size(), 0);


    EXPECT_TRUE (idContainer_char_descending.add(-2));
    EXPECT_TRUE (idContainer_char_descending.add( 3));
    EXPECT_TRUE (idContainer_char_descending.add( 1));
    EXPECT_FALSE(idContainer_char_descending.add(-2));
    EXPECT_TRUE (idContainer_char_descending.add( 0));
    EXPECT_TRUE (idContainer_char_descending.add( 125));

    EXPECT_TRUE (idContainer_char_descending.find(0));
    EXPECT_TRUE (idContainer_char_descending.find(125));
    EXPECT_FALSE(idContainer_char_descending.find(25));

    EXPECT_EQ(idContainer_char_descending.size(), 5);


    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, (char)125);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 3);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 1);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, (char)0);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, (char)-2);

    EXPECT_FALSE(idContainer_char_descending.getNextId().has_value());
    EXPECT_EQ(idContainer_char_descending.size(), 0);
}

TEST_F(IdContainerTests, Test4)
{
    EXPECT_TRUE(idContainer_int.add( 3));
    EXPECT_TRUE(idContainer_int.add( 1));
    EXPECT_TRUE(idContainer_int.add(-2));
    EXPECT_TRUE(idContainer_int.add( 0));

    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 3);

    idContainer_int.erase(-2);
    EXPECT_EQ(idContainer_int.size(), 2);

    idContainer_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 0);
    optional_int_result = idContainer_int.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 1);


    EXPECT_TRUE(idContainer_int_ascending.add( 3));
    EXPECT_TRUE(idContainer_int_ascending.add( 1));
    EXPECT_TRUE(idContainer_int_ascending.add(-2));
    EXPECT_TRUE(idContainer_int_ascending.add( 0));

    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -2);

    idContainer_int_ascending.erase(3);
    EXPECT_EQ(idContainer_int_ascending.size(), 2);

    idContainer_int_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 1);
    optional_int_result = idContainer_int_ascending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 0);


    EXPECT_TRUE(idContainer_int_descending.add( 3));
    EXPECT_TRUE(idContainer_int_descending.add( 1));
    EXPECT_TRUE(idContainer_int_descending.add(-2));
    EXPECT_TRUE(idContainer_int_descending.add( 0));

    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 3);

    idContainer_int_descending.erase(1);
    EXPECT_EQ(idContainer_int_descending.size(), 2);

    idContainer_int_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 0);
    optional_int_result = idContainer_int_descending.getNextId();
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -2);


    EXPECT_TRUE(idContainer_float.add( 3.0));
    EXPECT_TRUE(idContainer_float.add( 1.0));
    EXPECT_TRUE(idContainer_float.add(-2.0));
    EXPECT_TRUE(idContainer_float.add( 0.0));

    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 3.0);

    idContainer_float.erase(1.0);
    EXPECT_EQ(idContainer_float.size(), 2);

    idContainer_float.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -2.0);
    optional_float_result = idContainer_float.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result,  0.0);


    EXPECT_TRUE(idContainer_float_ascending.add( 3.0));
    EXPECT_TRUE(idContainer_float_ascending.add( 1.0));
    EXPECT_TRUE(idContainer_float_ascending.add(-2.0));
    EXPECT_TRUE(idContainer_float_ascending.add( 0.0));

    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -2.0);

    idContainer_float_ascending.erase(1.0);
    EXPECT_EQ(idContainer_float_ascending.size(), 2);

    idContainer_float_ascending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 0.0);
    optional_float_result = idContainer_float_ascending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 3.0);


    EXPECT_TRUE(idContainer_float_descending.add( 3.0));
    EXPECT_TRUE(idContainer_float_descending.add( 1.0));
    EXPECT_TRUE(idContainer_float_descending.add(-2.0));
    EXPECT_TRUE(idContainer_float_descending.add( 0.0));

    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 3.0);

    idContainer_float_descending.erase(-2.0);
    EXPECT_EQ(idContainer_float_descending.size(), 2);

    idContainer_float_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 1.0);
    optional_float_result = idContainer_float_descending.getNextId();
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 0.0);


    EXPECT_TRUE(idContainer_unsigned.add( 3));
    EXPECT_TRUE(idContainer_unsigned.add( 1));
    EXPECT_TRUE(idContainer_unsigned.add(-2));
    EXPECT_TRUE(idContainer_unsigned.add( 0));

    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 3);

    idContainer_unsigned.erase(0);
    EXPECT_EQ(idContainer_unsigned.size(), 2);

    idContainer_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  1);
    optional_unsigned_result = idContainer_unsigned.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);


    EXPECT_TRUE(idContainer_unsigned_ascending.add(-2));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 3));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 1));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 0));

    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 0);

    idContainer_unsigned_ascending.erase(0);
    EXPECT_EQ(idContainer_unsigned_ascending.size(), 3);

    idContainer_unsigned_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  1);
    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result,  3);
    optional_unsigned_result = idContainer_unsigned_ascending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);


    EXPECT_TRUE(idContainer_unsigned_descending.add( 3));
    EXPECT_TRUE(idContainer_unsigned_descending.add( 1));
    EXPECT_TRUE(idContainer_unsigned_descending.add(-2));
    EXPECT_TRUE(idContainer_unsigned_descending.add( 0));

    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);

    idContainer_unsigned_descending.erase(5);
    EXPECT_EQ(idContainer_unsigned_descending.size(), 3);

    idContainer_unsigned_descending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 0);
    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 1);
    optional_unsigned_result = idContainer_unsigned_descending.getNextId();
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 3);


    EXPECT_TRUE (idContainer_bool.add( 3));
    EXPECT_FALSE(idContainer_bool.add( 1));
    EXPECT_FALSE(idContainer_bool.add(-2));
    EXPECT_TRUE (idContainer_bool.add( 0));

    optional_bool_result = idContainer_bool.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);

    idContainer_bool.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_bool_result = idContainer_bool.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);


    EXPECT_TRUE (idContainer_bool_ascending.add( 3));
    EXPECT_FALSE(idContainer_bool_ascending.add( 1));
    EXPECT_FALSE(idContainer_bool_ascending.add(-2));
    EXPECT_TRUE (idContainer_bool_ascending.add( 0));

    optional_bool_result = idContainer_bool_ascending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);

    idContainer_bool_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_bool_result = idContainer_bool_ascending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);


    EXPECT_TRUE (idContainer_bool_descending.add( 3));
    EXPECT_FALSE(idContainer_bool_descending.add( 1));
    EXPECT_FALSE(idContainer_bool_descending.add(-2));
    EXPECT_TRUE (idContainer_bool_descending.add( 0));

    optional_bool_result = idContainer_bool_descending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);

    idContainer_bool_descending.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);

    optional_bool_result = idContainer_bool_descending.getNextId();
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);


    EXPECT_TRUE(idContainer_char.add(-2));
    EXPECT_TRUE(idContainer_char.add( 3));
    EXPECT_TRUE(idContainer_char.add( 1));
    EXPECT_TRUE(idContainer_char.add( 0));
    EXPECT_TRUE(idContainer_char.add( 125));

    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -2);

    idContainer_char.erase(0);
    EXPECT_EQ(idContainer_char.size(), 3);

    idContainer_char.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 125);
    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 3);
    optional_char_result = idContainer_char.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 1);


    EXPECT_TRUE(idContainer_char_ascending.add(-2));
    EXPECT_TRUE(idContainer_char_ascending.add( 3));
    EXPECT_TRUE(idContainer_char_ascending.add( 1));
    EXPECT_TRUE(idContainer_char_ascending.add( 0));
    EXPECT_TRUE(idContainer_char_ascending.add( 125));

    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -2);

    idContainer_char_ascending.erase(0);
    EXPECT_EQ(idContainer_char_ascending.size(), 3);

    idContainer_char_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 125);
    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 3);
    optional_char_result = idContainer_char_ascending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 1);


    EXPECT_TRUE(idContainer_char_descending.add(-2));
    EXPECT_TRUE(idContainer_char_descending.add( 3));
    EXPECT_TRUE(idContainer_char_descending.add( 1));
    EXPECT_TRUE(idContainer_char_descending.add( 0));
    EXPECT_TRUE(idContainer_char_descending.add( 125));

    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 125);

    idContainer_char_descending.erase(125);
    EXPECT_EQ(idContainer_char_descending.size(), 4);

    idContainer_char_descending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);

    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  3);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  1);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result,  0);
    optional_char_result = idContainer_char_descending.getNextId();
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -2);
}

TEST_F(IdContainerTests, Test5)
{
    for (int i = -3; i < 4; ++i) {
        EXPECT_TRUE(idContainer_int.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_int_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_int_descending.add(i)) << "The error occurred when: i == " << i;

        EXPECT_TRUE(idContainer_unsigned.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_unsigned_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_unsigned_descending.add(i)) << "The error occurred when: i == " << i;

        EXPECT_TRUE(idContainer_char.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_char_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_char_descending.add(i)) << "The error occurred when: i == " << i;
    }

    for (float i = -3.5; i < 4.5; i += 0.5) {
        EXPECT_TRUE(idContainer_float.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_float_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_float_descending.add(i)) << "The error occurred when: i == " << i;
    }

    EXPECT_TRUE(idContainer_bool.add(0));
    EXPECT_TRUE(idContainer_bool.add(1));
    EXPECT_TRUE(idContainer_bool_ascending.add(1));
    EXPECT_TRUE(idContainer_bool_ascending.add(0));
    EXPECT_TRUE(idContainer_bool_descending.add(1));
    EXPECT_TRUE(idContainer_bool_descending.add(0));


    EXPECT_TRUE(idContainer_int.add(10));
    EXPECT_TRUE(idContainer_int_ascending.add(111));
    EXPECT_TRUE(idContainer_int_descending.add(-9));

    EXPECT_TRUE(idContainer_unsigned.add(10));
    EXPECT_TRUE(idContainer_unsigned_ascending.add(111));
    EXPECT_TRUE(idContainer_unsigned_descending.add(-9));

    EXPECT_TRUE(idContainer_char.add(10));
    EXPECT_TRUE(idContainer_char_ascending.add(-9));
    EXPECT_TRUE(idContainer_char_descending.add(111));

    EXPECT_TRUE(idContainer_float.add(10.0));
    EXPECT_TRUE(idContainer_float_ascending.add(111.0));
    EXPECT_TRUE(idContainer_float_descending.add(-9.0));

    EXPECT_FALSE(idContainer_bool.add(10));
    EXPECT_FALSE(idContainer_bool_ascending.add(111));
    EXPECT_FALSE(idContainer_bool_descending.add(-9));


    optional_int_result = idContainer_int.findByIndex(0);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -3);
    optional_int_result = idContainer_int.findByIndex(7);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 10);
    EXPECT_FALSE(idContainer_int.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_int.findByIndex(-3).has_value());

    optional_int_result = idContainer_int_ascending.findByIndex(2);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -1);
    optional_int_result = idContainer_int_ascending.findByIndex(7);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 111);
    EXPECT_FALSE(idContainer_int_ascending.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_int_ascending.findByIndex(-3).has_value());

    optional_int_result = idContainer_int_descending.findByIndex(0);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, 3);
    optional_int_result = idContainer_int_descending.findByIndex(6);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -3);
    optional_int_result = idContainer_int_descending.findByIndex(7);
    ASSERT_TRUE(optional_int_result.has_value());
    EXPECT_EQ(*optional_int_result, -9);
    EXPECT_FALSE(idContainer_int_descending.findByIndex(8).has_value());
    EXPECT_FALSE(idContainer_int_descending.findByIndex(-1).has_value());


    optional_unsigned_result = idContainer_unsigned.findByIndex(0);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -3);
    optional_unsigned_result = idContainer_unsigned.findByIndex(7);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 10);
    EXPECT_FALSE(idContainer_unsigned.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_unsigned.findByIndex(-3).has_value());

    optional_unsigned_result = idContainer_unsigned_ascending.findByIndex(0);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 0);
    optional_unsigned_result = idContainer_unsigned_ascending.findByIndex(6);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -2);
    optional_unsigned_result = idContainer_unsigned_ascending.findByIndex(7);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -1);
    EXPECT_FALSE(idContainer_unsigned_ascending.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_unsigned_ascending.findByIndex(-3).has_value());

    optional_unsigned_result = idContainer_unsigned_descending.findByIndex(0);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, -1);
    optional_unsigned_result = idContainer_unsigned_descending.findByIndex(6);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 1);
    optional_unsigned_result = idContainer_unsigned_descending.findByIndex(7);
    ASSERT_TRUE(optional_unsigned_result.has_value());
    EXPECT_EQ(*optional_unsigned_result, 0);
    EXPECT_FALSE(idContainer_unsigned_descending.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_unsigned_descending.findByIndex(-3).has_value());


    optional_char_result = idContainer_char.findByIndex(0);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -3);
    optional_char_result = idContainer_char.findByIndex(6);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 3);
    optional_char_result = idContainer_char.findByIndex(7);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 10);
    EXPECT_FALSE(idContainer_char.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_char.findByIndex(-3).has_value());

    optional_char_result = idContainer_char_ascending.findByIndex(0);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -9);
    optional_char_result = idContainer_char_ascending.findByIndex(6);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 2);
    optional_char_result = idContainer_char_ascending.findByIndex(7);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 3);
    EXPECT_FALSE(idContainer_char_ascending.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_char_ascending.findByIndex(-3).has_value());

    optional_char_result = idContainer_char_descending.findByIndex(0);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 111);
    optional_char_result = idContainer_char_descending.findByIndex(4);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, 0);
    optional_char_result = idContainer_char_descending.findByIndex(7);
    ASSERT_TRUE(optional_char_result.has_value());
    EXPECT_EQ(*optional_char_result, -3);
    EXPECT_FALSE(idContainer_char_descending.findByIndex(100).has_value());
    EXPECT_FALSE(idContainer_char_descending.findByIndex(-3).has_value());


    optional_float_result = idContainer_float.findByIndex(0);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -3.5);
    optional_float_result = idContainer_float.findByIndex(1);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -3.0);
    optional_float_result = idContainer_float.findByIndex(16);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 10.0);
    EXPECT_FALSE(idContainer_float.findByIndex(17).has_value());
    EXPECT_FALSE(idContainer_float.findByIndex(-1000).has_value());

    optional_float_result = idContainer_float_ascending.findByIndex(0);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -3.5);
    optional_float_result = idContainer_float_ascending.findByIndex(7);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 0.0);
    optional_float_result = idContainer_float_ascending.findByIndex(16);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 111.0);
    EXPECT_FALSE(idContainer_float_ascending.findByIndex(1000).has_value());
    EXPECT_FALSE(idContainer_float_ascending.findByIndex(-1).has_value());

    optional_float_result = idContainer_float_descending.findByIndex(0);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 4.0);
    optional_float_result = idContainer_float_descending.findByIndex(7);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, 0.5);
    optional_float_result = idContainer_float_descending.findByIndex(16);
    ASSERT_TRUE(optional_float_result.has_value());
    EXPECT_FLOAT_EQ(*optional_float_result, -9.0);
    EXPECT_FALSE(idContainer_float_descending.findByIndex(17).has_value());
    EXPECT_FALSE(idContainer_float_descending.findByIndex(-17).has_value());


    optional_bool_result = idContainer_bool.findByIndex(0);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);
    optional_bool_result = idContainer_bool.findByIndex(1);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);
    EXPECT_FALSE(idContainer_bool.findByIndex(2).has_value());
    EXPECT_FALSE(idContainer_bool.findByIndex(-1).has_value());

    optional_bool_result = idContainer_bool_ascending.findByIndex(0);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);
    optional_bool_result = idContainer_bool_ascending.findByIndex(1);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);
    EXPECT_FALSE(idContainer_bool_ascending.findByIndex(20).has_value());
    EXPECT_FALSE(idContainer_bool_ascending.findByIndex(-10).has_value());

    optional_bool_result = idContainer_bool_descending.findByIndex(0);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 1);
    optional_bool_result = idContainer_bool_descending.findByIndex(1);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);
    optional_bool_result = idContainer_bool_descending.findByIndex(1);
    ASSERT_TRUE(optional_bool_result.has_value());
    EXPECT_EQ(*optional_bool_result, 0);
    EXPECT_FALSE(idContainer_bool_descending.findByIndex(2).has_value());
    EXPECT_FALSE(idContainer_bool_descending.findByIndex(-100).has_value());
}

TEST_F(IdContainerTests, Test6)
{
    for (int i = -3; i < 4; ++i) {
        EXPECT_TRUE(idContainer_int.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_int_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_int_descending.add(i)) << "The error occurred when: i == " << i;

        EXPECT_TRUE(idContainer_unsigned.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_unsigned_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_unsigned_descending.add(i)) << "The error occurred when: i == " << i;

        EXPECT_TRUE(idContainer_char.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_char_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_char_descending.add(i)) << "The error occurred when: i == " << i;
    }

    for (float i = -3.5; i < 4.5; i += 0.5) {
        EXPECT_TRUE(idContainer_float.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_float_ascending.add(i)) << "The error occurred when: i == " << i;
        EXPECT_TRUE(idContainer_float_descending.add(i)) << "The error occurred when: i == " << i;
    }

    EXPECT_TRUE(idContainer_bool.add(0));
    EXPECT_TRUE(idContainer_bool.add(1));
    EXPECT_TRUE(idContainer_bool_ascending.add(1));
    EXPECT_TRUE(idContainer_bool_ascending.add(0));
    EXPECT_TRUE(idContainer_bool_descending.add(1));
    EXPECT_TRUE(idContainer_bool_descending.add(0));


    idContainer_int.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_int_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_int_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_float.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_float_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_float_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_unsigned.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_unsigned_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_unsigned_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_bool.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_bool_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_bool_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_char.setIdIssuingMethod(IdIssuingMethod::Static_Ascending);
    idContainer_char_ascending.setIdIssuingMethod(IdIssuingMethod::Static_Descending);
    idContainer_char_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);


    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    OpenIdContainer<int> idContainer_int_cc(idContainer_int);
    OpenIdContainer<int> idContainer_int_ascending_cc(idContainer_int_ascending);
    OpenIdContainer<int> idContainer_int_descending_cc(idContainer_int_descending);

    OpenIdContainer<float> idContainer_float_cc(idContainer_float);
    OpenIdContainer<float> idContainer_float_ascending_cc(idContainer_float_ascending);
    OpenIdContainer<float> idContainer_float_descending_cc(idContainer_float_descending);

    OpenIdContainer<unsigned> idContainer_unsigned_cc(idContainer_unsigned);
    OpenIdContainer<unsigned> idContainer_unsigned_ascending_cc(idContainer_unsigned_ascending);
    OpenIdContainer<unsigned> idContainer_unsigned_descending_cc(idContainer_unsigned_descending);

    OpenIdContainer<bool> idContainer_bool_cc(idContainer_bool);
    OpenIdContainer<bool> idContainer_bool_ascending_cc(idContainer_bool_ascending);
    OpenIdContainer<bool> idContainer_bool_descending_cc(idContainer_bool_descending);

    OpenIdContainer<char> idContainer_char_cc(idContainer_char);
    OpenIdContainer<char> idContainer_char_ascending_cc(idContainer_char_ascending);
    OpenIdContainer<char> idContainer_char_descending_cc(idContainer_char_descending);

    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_int_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    OpenIdContainer<int> idContainer_int_cm(std::move(idContainer_int));
    OpenIdContainer<int> idContainer_int_ascending_cm(std::move(idContainer_int_ascending));
    OpenIdContainer<int> idContainer_int_descending_cm(std::move(idContainer_int_descending));

    OpenIdContainer<float> idContainer_float_cm(std::move(idContainer_float));
    OpenIdContainer<float> idContainer_float_ascending_cm(std::move(idContainer_float_ascending));
    OpenIdContainer<float> idContainer_float_descending_cm(std::move(idContainer_float_descending));

    OpenIdContainer<unsigned> idContainer_unsigned_cm(std::move(idContainer_unsigned));
    OpenIdContainer<unsigned> idContainer_unsigned_ascending_cm(std::move(idContainer_unsigned_ascending));
    OpenIdContainer<unsigned> idContainer_unsigned_descending_cm(std::move(idContainer_unsigned_descending));

    OpenIdContainer<bool> idContainer_bool_cm(std::move(idContainer_bool));
    OpenIdContainer<bool> idContainer_bool_ascending_cm(std::move(idContainer_bool_ascending));
    OpenIdContainer<bool> idContainer_bool_descending_cm(std::move(idContainer_bool_descending));

    OpenIdContainer<char> idContainer_char_cm(std::move(idContainer_char));
    OpenIdContainer<char> idContainer_char_ascending_cm(std::move(idContainer_char_ascending));
    OpenIdContainer<char> idContainer_char_descending_cm(std::move(idContainer_char_descending));

    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_int_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    OpenIdContainer<int> idContainer_int_oc;
    OpenIdContainer<int> idContainer_int_ascending_oc;
    OpenIdContainer<int> idContainer_int_descending_oc;

    OpenIdContainer<float> idContainer_float_oc;
    OpenIdContainer<float> idContainer_float_ascending_oc;
    OpenIdContainer<float> idContainer_float_descending_oc;

    OpenIdContainer<unsigned> idContainer_unsigned_oc;
    OpenIdContainer<unsigned> idContainer_unsigned_ascending_oc;
    OpenIdContainer<unsigned> idContainer_unsigned_descending_oc;

    OpenIdContainer<bool> idContainer_bool_oc;
    OpenIdContainer<bool> idContainer_bool_ascending_oc;
    OpenIdContainer<bool> idContainer_bool_descending_oc;

    OpenIdContainer<char> idContainer_char_oc;
    OpenIdContainer<char> idContainer_char_ascending_oc;
    OpenIdContainer<char> idContainer_char_descending_oc;

    idContainer_int_oc = idContainer_int_cc;
    idContainer_int_ascending_oc = idContainer_int_ascending_cc;
    idContainer_int_descending_oc = idContainer_int_descending_cc;

    idContainer_float_oc = idContainer_float_cc;
    idContainer_float_ascending_oc = idContainer_float_ascending_cc;
    idContainer_float_descending_oc = idContainer_float_descending_cc;

    idContainer_unsigned_oc = idContainer_unsigned_cc;
    idContainer_unsigned_ascending_oc = idContainer_unsigned_ascending_cc;
    idContainer_unsigned_descending_oc = idContainer_unsigned_descending_cc;

    idContainer_bool_oc = idContainer_bool_cc;
    idContainer_bool_ascending_oc = idContainer_bool_ascending_cc;
    idContainer_bool_descending_oc = idContainer_bool_descending_cc;

    idContainer_char_oc = idContainer_char_cc;
    idContainer_char_ascending_oc = idContainer_char_ascending_cc;
    idContainer_char_descending_oc = idContainer_char_descending_cc;

    EXPECT_EQ(idContainer_int_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_cc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_cc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_int_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    OpenIdContainer<int> idContainer_int_om;
    OpenIdContainer<int> idContainer_int_ascending_om;
    OpenIdContainer<int> idContainer_int_descending_om;

    OpenIdContainer<float> idContainer_float_om;
    OpenIdContainer<float> idContainer_float_ascending_om;
    OpenIdContainer<float> idContainer_float_descending_om;

    OpenIdContainer<unsigned> idContainer_unsigned_om;
    OpenIdContainer<unsigned> idContainer_unsigned_ascending_om;
    OpenIdContainer<unsigned> idContainer_unsigned_descending_om;

    OpenIdContainer<bool> idContainer_bool_om;
    OpenIdContainer<bool> idContainer_bool_ascending_om;
    OpenIdContainer<bool> idContainer_bool_descending_om;

    OpenIdContainer<char> idContainer_char_om;
    OpenIdContainer<char> idContainer_char_ascending_om;
    OpenIdContainer<char> idContainer_char_descending_om;

    idContainer_int_om = std::move(idContainer_int_cm);
    idContainer_int_ascending_om = std::move(idContainer_int_ascending_cm);
    idContainer_int_descending_om = std::move(idContainer_int_descending_cm);

    idContainer_float_om = std::move(idContainer_float_cm);
    idContainer_float_ascending_om = std::move(idContainer_float_ascending_cm);
    idContainer_float_descending_om = std::move(idContainer_float_descending_cm);

    idContainer_unsigned_om = std::move(idContainer_unsigned_cm);
    idContainer_unsigned_ascending_om = std::move(idContainer_unsigned_ascending_cm);
    idContainer_unsigned_descending_om = std::move(idContainer_unsigned_descending_cm);

    idContainer_bool_om = std::move(idContainer_bool_cm);
    idContainer_bool_ascending_om = std::move(idContainer_bool_ascending_cm);
    idContainer_bool_descending_om = std::move(idContainer_bool_descending_cm);

    idContainer_char_om = std::move(idContainer_char_cm);
    idContainer_char_ascending_om = std::move(idContainer_char_ascending_cm);
    idContainer_char_descending_om = std::move(idContainer_char_descending_cm);

    EXPECT_EQ(idContainer_int_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_cm.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_cm.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_int_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    idContainer_int_om.clear();
    idContainer_int_ascending_om.clear();
    idContainer_int_descending_om.clear();

    idContainer_float_om.clear();
    idContainer_float_ascending_om.clear();
    idContainer_float_descending_om.clear();

    idContainer_unsigned_om.clear();
    idContainer_unsigned_ascending_om.clear();
    idContainer_unsigned_descending_om.clear();

    idContainer_bool_om.clear();
    idContainer_bool_ascending_om.clear();
    idContainer_bool_descending_om.clear();

    idContainer_char_om.clear();
    idContainer_char_ascending_om.clear();
    idContainer_char_descending_om.clear();

    EXPECT_EQ(idContainer_int_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_om.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_om.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_om.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    idContainer_int_oc.clear();
    idContainer_int_ascending_oc.clear();
    idContainer_int_descending_oc.clear();

    idContainer_float_oc.clear();
    idContainer_float_ascending_oc.clear();
    idContainer_float_descending_oc.clear();

    idContainer_unsigned_oc.clear();
    idContainer_unsigned_ascending_oc.clear();
    idContainer_unsigned_descending_oc.clear();

    idContainer_bool_oc.clear();
    idContainer_bool_ascending_oc.clear();
    idContainer_bool_descending_oc.clear();

    idContainer_char_oc.clear();
    idContainer_char_ascending_oc.clear();
    idContainer_char_descending_oc.clear();

    EXPECT_EQ(idContainer_int_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_int_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_int_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_float_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_float_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_float_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_unsigned_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_bool_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_bool_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_bool_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Ascending);
    EXPECT_EQ(idContainer_char_ascending_oc.getIdIssuingMethod(), IdIssuingMethod::Static_Descending);
    EXPECT_EQ(idContainer_char_descending_oc.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
}
