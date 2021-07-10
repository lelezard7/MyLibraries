#include "Id_Manager.h"

#include <gtest/gtest.h>

using namespace Id_M;


template<class __T>
class OpenIdContainer : public IdContainer<__T>
{
public:
    OpenIdContainer(IdIssuingMethod idIssuingMethod = IdIssuingMethod::Dynamic)
        : IdContainer<__T>(idIssuingMethod) {};

    OpenIdContainer(const OpenIdContainer<__T>& other)
        : IdContainer<__T>(other) {};

    size_t getOrderedFreeIdsSizeT() const {
        return this->getOrderedFreeIdsSize();
    }

    size_t getUnorderedFreeIdsSizeT() const {
        return this->getUnorderedFreeIdsSize();
    }
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


struct IdContainerTests : ::testing::Test
{
protected:
    IdContainerTests()
        : idContainer_int_ascending(IdIssuingMethod::Ascending),
          idContainer_int_descending(IdIssuingMethod::Descending),

          idContainer_float_ascending(IdIssuingMethod::Ascending),
          idContainer_float_descending(IdIssuingMethod::Descending),

          idContainer_unsigned_ascending(IdIssuingMethod::Ascending),
          idContainer_unsigned_descending(IdIssuingMethod::Descending),

          idContainer_bool_ascending(IdIssuingMethod::Ascending),
          idContainer_bool_descending(IdIssuingMethod::Descending),

          idContainer_char_ascending(IdIssuingMethod::Ascending),
          idContainer_char_descending(IdIssuingMethod::Descending),

          id_int(0),
          id_float(0.0),
          id_unsigned(0),
          id_bool(0),
          id_char(0) {};

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

    int id_int;
    float id_float;
    unsigned id_unsigned;
    bool id_bool;
    char id_char;
};

TEST_F(IdContainerTests, Test1)
{
    EXPECT_FALSE(idContainer_int.getNextId(id_int));
    EXPECT_FALSE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_FALSE(idContainer_int_descending.getNextId(id_int));

    EXPECT_FALSE(idContainer_float.getNextId(id_float));
    EXPECT_FALSE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FALSE(idContainer_float_descending.getNextId(id_float));

    EXPECT_FALSE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_FALSE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_FALSE(idContainer_unsigned_descending.getNextId(id_unsigned));

    EXPECT_FALSE(idContainer_bool.getNextId(id_bool));
    EXPECT_FALSE(idContainer_bool_ascending.getNextId(id_bool));
    EXPECT_FALSE(idContainer_bool_descending.getNextId(id_bool));

    EXPECT_FALSE(idContainer_char.getNextId(id_char));
    EXPECT_FALSE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_FALSE(idContainer_char_descending.getNextId(id_char));


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


    EXPECT_EQ(idContainer_int.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_int_ascending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_int_descending.getOrderedFreeIdsSizeT(), 0);

    EXPECT_FLOAT_EQ(idContainer_float.getOrderedFreeIdsSizeT(), 0.0);
    EXPECT_FLOAT_EQ(idContainer_float_ascending.getOrderedFreeIdsSizeT(), 0.0);
    EXPECT_FLOAT_EQ(idContainer_float_descending.getOrderedFreeIdsSizeT(), 0.0);

    EXPECT_EQ(idContainer_unsigned.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_unsigned_ascending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_unsigned_descending.getOrderedFreeIdsSizeT(), 0);

    EXPECT_EQ(idContainer_bool.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_bool_ascending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_bool_descending.getOrderedFreeIdsSizeT(), 0);

    EXPECT_EQ(idContainer_char.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_char_ascending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_char_descending.getOrderedFreeIdsSizeT(), 0);


    EXPECT_EQ(idContainer_int.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_int_ascending.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_int_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_FLOAT_EQ(idContainer_float.getUnorderedFreeIdsSizeT(), 0.0);
    EXPECT_FLOAT_EQ(idContainer_float_ascending.getUnorderedFreeIdsSizeT(), 0.0);
    EXPECT_FLOAT_EQ(idContainer_float_descending.getUnorderedFreeIdsSizeT(), 0.0);

    EXPECT_EQ(idContainer_unsigned.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_unsigned_ascending.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_unsigned_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_EQ(idContainer_bool.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_bool_ascending.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_bool_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_EQ(idContainer_char.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_char_ascending.getUnorderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_char_descending.getUnorderedFreeIdsSizeT(), 0);


    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Descending);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Descending);
}

TEST_F(IdContainerTests, Test2)
{
    idContainer_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_int_ascending.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_int_descending.setIdIssuingMethod(IdIssuingMethod::Ascending);

    EXPECT_EQ(idContainer_int.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_int_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_int_descending.getIdIssuingMethod(), IdIssuingMethod::Ascending);


    idContainer_float.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_float_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_float_descending.setIdIssuingMethod(IdIssuingMethod::Descending);

    EXPECT_EQ(idContainer_float.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_float_ascending.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_float_descending.getIdIssuingMethod(), IdIssuingMethod::Descending);


    idContainer_unsigned.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    idContainer_unsigned_ascending.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    idContainer_unsigned_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_unsigned.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_unsigned_ascending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_unsigned_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);


    idContainer_bool.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    idContainer_bool_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_bool_descending.setIdIssuingMethod(IdIssuingMethod::Ascending);

    EXPECT_EQ(idContainer_bool.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_bool_ascending.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_bool_descending.getIdIssuingMethod(), IdIssuingMethod::Ascending);


    idContainer_char.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_char_ascending.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_char_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    EXPECT_EQ(idContainer_char.getIdIssuingMethod(), IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_char_ascending.getIdIssuingMethod(), IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_char_descending.getIdIssuingMethod(), IdIssuingMethod::Dynamic);
}

TEST_F(IdContainerTests, Test3)
{
    EXPECT_TRUE(idContainer_int.add( 3));
    EXPECT_TRUE(idContainer_int.add( 1));
    EXPECT_TRUE(idContainer_int.add(-2));
    EXPECT_TRUE(idContainer_int.add( 0));

    EXPECT_TRUE (idContainer_int.find(3));
    EXPECT_FALSE(idContainer_int.find(6));

    EXPECT_EQ(idContainer_int.size(), 4);

    EXPECT_EQ(idContainer_int.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_int.getUnorderedFreeIdsSizeT(), 4);

    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, 3);
    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, 1);
    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, -2);
    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, 0);
    EXPECT_FALSE(idContainer_int.getNextId(id_int));

    EXPECT_EQ(idContainer_int.size(), 0);


    EXPECT_TRUE(idContainer_int_ascending.add( 3));
    EXPECT_TRUE(idContainer_int_ascending.add( 1));
    EXPECT_TRUE(idContainer_int_ascending.add(-2));
    EXPECT_TRUE(idContainer_int_ascending.add( 0));

    EXPECT_TRUE (idContainer_int_ascending.find(-2));
    EXPECT_FALSE(idContainer_int_ascending.find(-5));

    EXPECT_EQ(idContainer_int_ascending.size(), 4);

    EXPECT_EQ(idContainer_int_ascending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_int_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, -2);
    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, 0);
    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, 1);
    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, 3);
    EXPECT_FALSE(idContainer_int_ascending.getNextId(id_int));

    EXPECT_EQ(idContainer_int_ascending.size(), 0);


    EXPECT_TRUE(idContainer_int_descending.add( 3));
    EXPECT_TRUE(idContainer_int_descending.add( 1));
    EXPECT_TRUE(idContainer_int_descending.add(-2));
    EXPECT_TRUE(idContainer_int_descending.add( 0));

    EXPECT_TRUE (idContainer_int_descending.find(0));
    EXPECT_FALSE(idContainer_int_descending.find(10));

    EXPECT_EQ(idContainer_int_descending.size(), 4);

    EXPECT_EQ(idContainer_int_descending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_int_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, 3);
    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, 1);
    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, 0);
    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, -2);
    EXPECT_FALSE(idContainer_int_descending.getNextId(id_int));

    EXPECT_EQ(idContainer_int_descending.size(), 0);


    EXPECT_TRUE(idContainer_float.add( 3.0));
    EXPECT_TRUE(idContainer_float.add( 1.0));
    EXPECT_TRUE(idContainer_float.add(-2.0));
    EXPECT_TRUE(idContainer_float.add( 0.0));

    EXPECT_TRUE (idContainer_float.find(3.0));
    EXPECT_FALSE(idContainer_float.find(3.3));

    EXPECT_EQ(idContainer_float.size(), 4);

    EXPECT_EQ(idContainer_float.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_float.getUnorderedFreeIdsSizeT(), 4);

    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 3.0);
    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 1.0);
    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, -2.0);
    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 0.0);
    EXPECT_FALSE(idContainer_float.getNextId(id_float));

    EXPECT_EQ(idContainer_float.size(), 0);


    EXPECT_TRUE(idContainer_float_ascending.add( 3.0));
    EXPECT_TRUE(idContainer_float_ascending.add( 1.0));
    EXPECT_TRUE(idContainer_float_ascending.add(-2.0));
    EXPECT_TRUE(idContainer_float_ascending.add( 0.0));

    EXPECT_TRUE (idContainer_float_ascending.find(-2.0));
    EXPECT_FALSE(idContainer_float_ascending.find(-1.9));

    EXPECT_EQ(idContainer_float_ascending.size(), 4);

    EXPECT_EQ(idContainer_float_ascending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_float_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, -2.0);
    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 0.0);
    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 1.0);
    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 3.0);
    EXPECT_FALSE(idContainer_float_ascending.getNextId(id_float));

    EXPECT_EQ(idContainer_float_ascending.size(), 0);


    EXPECT_TRUE(idContainer_float_descending.add( 3.0));
    EXPECT_TRUE(idContainer_float_descending.add( 1.0));
    EXPECT_TRUE(idContainer_float_descending.add(-2.0));
    EXPECT_TRUE(idContainer_float_descending.add( 0.0));

    EXPECT_TRUE (idContainer_float_descending.find(0.0));
    EXPECT_FALSE(idContainer_float_descending.find(2.0));

    EXPECT_EQ(idContainer_float_descending.size(), 4);

    EXPECT_EQ(idContainer_float_descending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_float_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 3.0);
    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 1.0);
    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 0.0);
    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, -2.0);
    EXPECT_FALSE(idContainer_float_descending.getNextId(id_float));

    EXPECT_EQ(idContainer_float_descending.size(), 0);


    EXPECT_TRUE(idContainer_unsigned.add( 3));
    EXPECT_TRUE(idContainer_unsigned.add( 1));
    EXPECT_TRUE(idContainer_unsigned.add(-2));
    EXPECT_TRUE(idContainer_unsigned.add( 0));

    EXPECT_TRUE (idContainer_unsigned.find(3));
    EXPECT_TRUE (idContainer_unsigned.find((unsigned)-2));
    EXPECT_FALSE(idContainer_unsigned.find(6));

    EXPECT_EQ(idContainer_unsigned.size(), 4);

    EXPECT_EQ(idContainer_unsigned.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_unsigned.getUnorderedFreeIdsSizeT(), 4);

    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 3);
    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 1);
    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, -2);
    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 0);
    EXPECT_FALSE(idContainer_unsigned.getNextId(id_unsigned));

    EXPECT_EQ(idContainer_unsigned.size(), 0);


    EXPECT_TRUE(idContainer_unsigned_ascending.add(-2));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 3));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 1));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 0));

    EXPECT_TRUE (idContainer_unsigned_ascending.find(-2));
    EXPECT_FALSE(idContainer_unsigned_ascending.find(-3));

    EXPECT_EQ(idContainer_unsigned_ascending.size(), 4);

    EXPECT_EQ(idContainer_unsigned_ascending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_unsigned_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 0);
    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 1);
    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 3);
    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, -2);
    EXPECT_FALSE(idContainer_unsigned_ascending.getNextId(id_unsigned));

    EXPECT_EQ(idContainer_unsigned_ascending.size(), 0);


    EXPECT_TRUE(idContainer_unsigned_descending.add( 3));
    EXPECT_TRUE(idContainer_unsigned_descending.add( 1));
    EXPECT_TRUE(idContainer_unsigned_descending.add(-2));
    EXPECT_TRUE(idContainer_unsigned_descending.add( 0));

    EXPECT_TRUE (idContainer_unsigned_descending.find( 0));
    EXPECT_FALSE(idContainer_unsigned_descending.find(-7));

    EXPECT_EQ(idContainer_unsigned_descending.size(), 4);

    EXPECT_EQ(idContainer_unsigned_descending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_unsigned_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, -2);
    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 3);
    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 1);
    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 0);
    EXPECT_FALSE(idContainer_unsigned_descending.getNextId(id_unsigned));

    EXPECT_EQ(idContainer_unsigned_descending.size(), 0);


    EXPECT_TRUE (idContainer_bool.add( 3));
    EXPECT_FALSE(idContainer_bool.add( 1));
    EXPECT_FALSE(idContainer_bool.add(-2));
    EXPECT_TRUE (idContainer_bool.add( 0));

    EXPECT_TRUE(idContainer_bool.find(3));
    EXPECT_TRUE(idContainer_bool.find(7));
    EXPECT_TRUE(idContainer_bool.find(0));

    EXPECT_EQ(idContainer_bool.size(), 2);

    EXPECT_EQ(idContainer_bool.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_bool.getUnorderedFreeIdsSizeT(), 2);

    EXPECT_TRUE(idContainer_bool.getNextId(id_bool));
    EXPECT_EQ(id_bool, 1);
    EXPECT_TRUE(idContainer_bool.getNextId(id_bool));
    EXPECT_EQ(id_bool, 0);
    EXPECT_FALSE(idContainer_bool.getNextId(id_bool));

    EXPECT_EQ(idContainer_bool.size(), 0);


    EXPECT_TRUE (idContainer_bool_ascending.add( 3));
    EXPECT_FALSE(idContainer_bool_ascending.add( 1));
    EXPECT_FALSE(idContainer_bool_ascending.add(-2));
    EXPECT_TRUE (idContainer_bool_ascending.add( 0));

    EXPECT_TRUE(idContainer_bool_ascending.find(-3));
    EXPECT_TRUE(idContainer_bool_ascending.find(-10));
    EXPECT_TRUE(idContainer_bool_ascending.find( 0));

    EXPECT_EQ(idContainer_bool_ascending.size(), 2);

    EXPECT_EQ(idContainer_bool_ascending.getOrderedFreeIdsSizeT(), 2);
    EXPECT_EQ(idContainer_bool_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_bool_ascending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 0);
    EXPECT_TRUE(idContainer_bool_ascending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 1);
    EXPECT_FALSE(idContainer_bool_ascending.getNextId(id_bool));

    EXPECT_EQ(idContainer_bool_ascending.size(), 0);


    EXPECT_TRUE (idContainer_bool_descending.add( 3));
    EXPECT_FALSE(idContainer_bool_descending.add( 1));
    EXPECT_FALSE(idContainer_bool_descending.add(-2));
    EXPECT_TRUE (idContainer_bool_descending.add( 0));

    EXPECT_TRUE(idContainer_bool_descending.find(-2));
    EXPECT_TRUE(idContainer_bool_descending.find( 9));
    EXPECT_TRUE(idContainer_bool_descending.find( 0));

    EXPECT_EQ(idContainer_bool_descending.size(), 2);

    EXPECT_EQ(idContainer_bool_descending.getOrderedFreeIdsSizeT(), 2);
    EXPECT_EQ(idContainer_bool_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_bool_descending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 1);
    EXPECT_TRUE(idContainer_bool_descending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 0);
    EXPECT_FALSE(idContainer_bool_descending.getNextId(id_bool));

    EXPECT_EQ(idContainer_bool_descending.size(), 0);


    EXPECT_TRUE(idContainer_char.add(-2));
    EXPECT_TRUE(idContainer_char.add( 3));
    EXPECT_TRUE(idContainer_char.add( 1));
    EXPECT_TRUE(idContainer_char.add( 0));
    EXPECT_TRUE(idContainer_char.add( 125));

    EXPECT_TRUE (idContainer_char.find(3));
    EXPECT_FALSE(idContainer_char.find(4));

    EXPECT_EQ(idContainer_char.size(), 5);

    EXPECT_EQ(idContainer_char.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_char.getUnorderedFreeIdsSizeT(), 5);

    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, -2);
    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 3);
    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 1);
    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 0);
    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 125);
    EXPECT_FALSE(idContainer_char.getNextId(id_char));

    EXPECT_EQ(idContainer_char.size(), 0);


    EXPECT_TRUE(idContainer_char_ascending.add(-2));
    EXPECT_TRUE(idContainer_char_ascending.add( 3));
    EXPECT_TRUE(idContainer_char_ascending.add( 1));
    EXPECT_TRUE(idContainer_char_ascending.add( 0));
    EXPECT_TRUE(idContainer_char_ascending.add( 125));

    EXPECT_TRUE (idContainer_char_ascending.find(-2));
    EXPECT_FALSE(idContainer_char_ascending.find(-4));

    EXPECT_EQ(idContainer_char_ascending.size(), 5);

    EXPECT_EQ(idContainer_char_ascending.getOrderedFreeIdsSizeT(), 5);
    EXPECT_EQ(idContainer_char_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, -2);
    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 0);
    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 1);
    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 3);
    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 125);
    EXPECT_FALSE(idContainer_char_ascending.getNextId(id_char));

    EXPECT_EQ(idContainer_char_ascending.size(), 0);


    EXPECT_TRUE(idContainer_char_descending.add(-2));
    EXPECT_TRUE(idContainer_char_descending.add( 3));
    EXPECT_TRUE(idContainer_char_descending.add( 1));
    EXPECT_TRUE(idContainer_char_descending.add( 0));
    EXPECT_TRUE(idContainer_char_descending.add( 125));

    EXPECT_TRUE (idContainer_char_descending.find(0));
    EXPECT_TRUE (idContainer_char_descending.find(125));
    EXPECT_FALSE(idContainer_char_descending.find(25));

    EXPECT_EQ(idContainer_char_descending.size(), 5);

    EXPECT_EQ(idContainer_char_descending.getOrderedFreeIdsSizeT(), 5);
    EXPECT_EQ(idContainer_char_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 125);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 3);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 1);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 0);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, -2);
    EXPECT_FALSE(idContainer_char_descending.getNextId(id_char));

    EXPECT_EQ(idContainer_char_descending.size(), 0);
}

TEST_F(IdContainerTests, Test4)
{
    EXPECT_TRUE(idContainer_int.add( 3));
    EXPECT_TRUE(idContainer_int.add( 1));
    EXPECT_TRUE(idContainer_int.add(-2));
    EXPECT_TRUE(idContainer_int.add( 0));

    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, 3);

    idContainer_int.freeId(-2);
    EXPECT_EQ(idContainer_int.size(), 2);

    idContainer_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_int.getOrderedFreeIdsSizeT(), 2);
    EXPECT_EQ(idContainer_int.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, 0);
    EXPECT_TRUE(idContainer_int.getNextId(id_int));
    EXPECT_EQ(id_int, 1);


    EXPECT_TRUE(idContainer_int_ascending.add( 3));
    EXPECT_TRUE(idContainer_int_ascending.add( 1));
    EXPECT_TRUE(idContainer_int_ascending.add(-2));
    EXPECT_TRUE(idContainer_int_ascending.add( 0));

    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, -2);

    idContainer_int_ascending.freeId(3);
    EXPECT_EQ(idContainer_int_ascending.size(), 2);

    idContainer_int_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_int_ascending.getOrderedFreeIdsSizeT(), 2);
    EXPECT_EQ(idContainer_int_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, 1);
    EXPECT_TRUE(idContainer_int_ascending.getNextId(id_int));
    EXPECT_EQ(id_int, 0);


    EXPECT_TRUE(idContainer_int_descending.add( 3));
    EXPECT_TRUE(idContainer_int_descending.add( 1));
    EXPECT_TRUE(idContainer_int_descending.add(-2));
    EXPECT_TRUE(idContainer_int_descending.add( 0));

    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, 3);

    idContainer_int_descending.freeId(1);
    EXPECT_EQ(idContainer_int_descending.size(), 2);

    idContainer_int_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_int_descending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_int_descending.getUnorderedFreeIdsSizeT(), 2);

    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, -2);
    EXPECT_TRUE(idContainer_int_descending.getNextId(id_int));
    EXPECT_EQ(id_int, 0);


    EXPECT_TRUE(idContainer_float.add( 3.0));
    EXPECT_TRUE(idContainer_float.add( 1.0));
    EXPECT_TRUE(idContainer_float.add(-2.0));
    EXPECT_TRUE(idContainer_float.add( 0.0));

    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 3.0);

    idContainer_float.freeId(1.0);
    EXPECT_EQ(idContainer_float.size(), 2);

    idContainer_float.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_float.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_float.getUnorderedFreeIdsSizeT(), 2);

    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, -2.0);
    EXPECT_TRUE(idContainer_float.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 0.0);


    EXPECT_TRUE(idContainer_float_ascending.add( 3.0));
    EXPECT_TRUE(idContainer_float_ascending.add( 1.0));
    EXPECT_TRUE(idContainer_float_ascending.add(-2.0));
    EXPECT_TRUE(idContainer_float_ascending.add( 0.0));

    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, -2.0);

    idContainer_float_ascending.freeId(1.0);
    EXPECT_EQ(idContainer_float_ascending.size(), 2);

    idContainer_float_ascending.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_float_ascending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_float_ascending.getUnorderedFreeIdsSizeT(), 2);

    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 0.0);
    EXPECT_TRUE(idContainer_float_ascending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 3.0);


    EXPECT_TRUE(idContainer_float_descending.add( 3.0));
    EXPECT_TRUE(idContainer_float_descending.add( 1.0));
    EXPECT_TRUE(idContainer_float_descending.add(-2.0));
    EXPECT_TRUE(idContainer_float_descending.add( 0.0));

    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 3.0);

    idContainer_float_descending.freeId(-2.0);
    EXPECT_EQ(idContainer_float_descending.size(), 2);

    idContainer_float_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);
    EXPECT_EQ(idContainer_float_descending.getOrderedFreeIdsSizeT(), 0);
    EXPECT_EQ(idContainer_float_descending.getUnorderedFreeIdsSizeT(), 2);

    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 0.0);
    EXPECT_TRUE(idContainer_float_descending.getNextId(id_float));
    EXPECT_FLOAT_EQ(id_float, 1.0);


    EXPECT_TRUE(idContainer_unsigned.add( 3));
    EXPECT_TRUE(idContainer_unsigned.add( 1));
    EXPECT_TRUE(idContainer_unsigned.add(-2));
    EXPECT_TRUE(idContainer_unsigned.add( 0));

    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 3);

    idContainer_unsigned.freeId(0);
    EXPECT_EQ(idContainer_unsigned.size(), 2);

    idContainer_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_unsigned.getOrderedFreeIdsSizeT(), 2);
    EXPECT_EQ(idContainer_unsigned.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 1);
    EXPECT_TRUE(idContainer_unsigned.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, -2);


    EXPECT_TRUE(idContainer_unsigned_ascending.add(-2));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 3));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 1));
    EXPECT_TRUE(idContainer_unsigned_ascending.add( 0));

    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 0);

    idContainer_unsigned_ascending.freeId(0);
    EXPECT_EQ(idContainer_unsigned_ascending.size(), 3);

    idContainer_unsigned_ascending.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_unsigned_ascending.getOrderedFreeIdsSizeT(), 3);
    EXPECT_EQ(idContainer_unsigned_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 1);
    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 3);
    EXPECT_TRUE(idContainer_unsigned_ascending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, -2);


    EXPECT_TRUE(idContainer_unsigned_descending.add( 3));
    EXPECT_TRUE(idContainer_unsigned_descending.add( 1));
    EXPECT_TRUE(idContainer_unsigned_descending.add(-2));
    EXPECT_TRUE(idContainer_unsigned_descending.add( 0));

    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, -2);

    idContainer_unsigned_descending.freeId(5);
    EXPECT_EQ(idContainer_unsigned_descending.size(), 3);

    idContainer_unsigned_descending.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_unsigned_descending.getOrderedFreeIdsSizeT(), 3);
    EXPECT_EQ(idContainer_unsigned_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 0);
    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 1);
    EXPECT_TRUE(idContainer_unsigned_descending.getNextId(id_unsigned));
    EXPECT_EQ(id_unsigned, 3);


    EXPECT_TRUE (idContainer_bool.add( 3));
    EXPECT_FALSE(idContainer_bool.add( 1));
    EXPECT_FALSE(idContainer_bool.add(-2));
    EXPECT_TRUE (idContainer_bool.add( 0));

    EXPECT_TRUE(idContainer_bool.getNextId(id_bool));
    EXPECT_EQ(id_bool, 1);

    idContainer_bool.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_bool.getOrderedFreeIdsSizeT(), 1);
    EXPECT_EQ(idContainer_bool.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_bool.getNextId(id_bool));
    EXPECT_EQ(id_bool, 0);


    EXPECT_TRUE (idContainer_bool_ascending.add( 3));
    EXPECT_FALSE(idContainer_bool_ascending.add( 1));
    EXPECT_FALSE(idContainer_bool_ascending.add(-2));
    EXPECT_TRUE (idContainer_bool_ascending.add( 0));

    EXPECT_TRUE(idContainer_bool_ascending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 0);

    idContainer_bool_ascending.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_bool_ascending.getOrderedFreeIdsSizeT(), 1);
    EXPECT_EQ(idContainer_bool_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_bool_ascending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 1);


    EXPECT_TRUE (idContainer_bool_descending.add( 3));
    EXPECT_FALSE(idContainer_bool_descending.add( 1));
    EXPECT_FALSE(idContainer_bool_descending.add(-2));
    EXPECT_TRUE (idContainer_bool_descending.add( 0));

    EXPECT_TRUE(idContainer_bool_descending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 1);

    idContainer_bool_descending.setIdIssuingMethod(IdIssuingMethod::Ascending);
    EXPECT_EQ(idContainer_bool_descending.getOrderedFreeIdsSizeT(), 1);
    EXPECT_EQ(idContainer_bool_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_bool_descending.getNextId(id_bool));
    EXPECT_EQ(id_bool, 0);


    EXPECT_TRUE(idContainer_char.add(-2));
    EXPECT_TRUE(idContainer_char.add( 3));
    EXPECT_TRUE(idContainer_char.add( 1));
    EXPECT_TRUE(idContainer_char.add( 0));
    EXPECT_TRUE(idContainer_char.add( 125));

    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, -2);

    idContainer_char.freeId(0);
    EXPECT_EQ(idContainer_char.size(), 3);

    idContainer_char.setIdIssuingMethod(IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_char.getOrderedFreeIdsSizeT(), 3);
    EXPECT_EQ(idContainer_char.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 125);
    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 3);
    EXPECT_TRUE(idContainer_char.getNextId(id_char));
    EXPECT_EQ(id_char, 1);


    EXPECT_TRUE(idContainer_char_ascending.add(-2));
    EXPECT_TRUE(idContainer_char_ascending.add( 3));
    EXPECT_TRUE(idContainer_char_ascending.add( 1));
    EXPECT_TRUE(idContainer_char_ascending.add( 0));
    EXPECT_TRUE(idContainer_char_ascending.add( 125));

    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, -2);

    idContainer_char_ascending.freeId(0);
    EXPECT_EQ(idContainer_char_ascending.size(), 3);

    idContainer_char_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_char_ascending.getOrderedFreeIdsSizeT(), 3);
    EXPECT_EQ(idContainer_char_ascending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 125);
    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 3);
    EXPECT_TRUE(idContainer_char_ascending.getNextId(id_char));
    EXPECT_EQ(id_char, 1);


    EXPECT_TRUE(idContainer_char_descending.add(-2));
    EXPECT_TRUE(idContainer_char_descending.add( 3));
    EXPECT_TRUE(idContainer_char_descending.add( 1));
    EXPECT_TRUE(idContainer_char_descending.add( 0));
    EXPECT_TRUE(idContainer_char_descending.add( 125));

    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 125);

    idContainer_char_descending.freeId(125);
    EXPECT_EQ(idContainer_char_descending.size(), 4);

    idContainer_char_descending.setIdIssuingMethod(IdIssuingMethod::Descending);
    EXPECT_EQ(idContainer_char_descending.getOrderedFreeIdsSizeT(), 4);
    EXPECT_EQ(idContainer_char_descending.getUnorderedFreeIdsSizeT(), 0);

    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 3);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 1);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, 0);
    EXPECT_TRUE(idContainer_char_descending.getNextId(id_char));
    EXPECT_EQ(id_char, -2);
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

    EXPECT_TRUE (idContainer_bool.add(0));
    EXPECT_TRUE (idContainer_bool.add(1));
    EXPECT_TRUE (idContainer_bool_ascending.add(1));
    EXPECT_TRUE (idContainer_bool_ascending.add(0));
    EXPECT_TRUE (idContainer_bool_descending.add(1));
    EXPECT_TRUE (idContainer_bool_descending.add(0));


    idContainer_int.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_int_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_int_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_float.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_float_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_float_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_unsigned.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_unsigned_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_unsigned_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_bool.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_bool_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_bool_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);

    idContainer_char.setIdIssuingMethod(IdIssuingMethod::Ascending);
    idContainer_char_ascending.setIdIssuingMethod(IdIssuingMethod::Descending);
    idContainer_char_descending.setIdIssuingMethod(IdIssuingMethod::Dynamic);


    OpenIdContainer<int> idContainer_int_m[2];
    OpenIdContainer<int> idContainer_int_ascending_m[2];
    OpenIdContainer<int> idContainer_int_descending_m[2];

    OpenIdContainer<float> idContainer_float_m[2];
    OpenIdContainer<float> idContainer_float_ascending_m[2];
    OpenIdContainer<float> idContainer_float_descending_m[2];

    OpenIdContainer<unsigned> idContainer_unsigned_m[2];
    OpenIdContainer<unsigned> idContainer_unsigned_ascending_m[2];
    OpenIdContainer<unsigned> idContainer_unsigned_descending_m[2];

    OpenIdContainer<bool> idContainer_bool_m[2];
    OpenIdContainer<bool> idContainer_bool_ascending_m[2];
    OpenIdContainer<bool> idContainer_bool_descending_m[2];

    OpenIdContainer<char> idContainer_char_m[2];
    OpenIdContainer<char> idContainer_char_ascending_m[2];
    OpenIdContainer<char> idContainer_char_descending_m[2];


    idContainer_int_m[0] = OpenIdContainer<int>(idContainer_int);
    idContainer_int_ascending_m[0] = OpenIdContainer<int>(idContainer_int_ascending);
    idContainer_int_descending_m[0] = OpenIdContainer<int>(idContainer_int_descending);

    idContainer_float_m[0] = OpenIdContainer<float>(idContainer_float);
    idContainer_float_ascending_m[0] = OpenIdContainer<float>(idContainer_float_ascending);
    idContainer_float_descending_m[0] = OpenIdContainer<float>(idContainer_float_descending);

    idContainer_unsigned_m[0] = OpenIdContainer<unsigned>(idContainer_unsigned);
    idContainer_unsigned_ascending_m[0] = OpenIdContainer<unsigned>(idContainer_unsigned_ascending);
    idContainer_unsigned_descending_m[0] = OpenIdContainer<unsigned>(idContainer_unsigned_descending);

    idContainer_bool_m[0] = OpenIdContainer<bool>(idContainer_bool);
    idContainer_bool_ascending_m[0] = OpenIdContainer<bool>(idContainer_bool_ascending);
    idContainer_bool_descending_m[0] = OpenIdContainer<bool>(idContainer_bool_descending);

    idContainer_char_m[0] = OpenIdContainer<char>(idContainer_char);
    idContainer_char_ascending_m[0] = OpenIdContainer<char>(idContainer_char_ascending);
    idContainer_char_descending_m[0] = OpenIdContainer<char>(idContainer_char_descending);


    idContainer_int_m[1] = idContainer_int;
    idContainer_int_ascending_m[1] = idContainer_int_ascending;
    idContainer_int_descending_m[1] = idContainer_int_descending;

    idContainer_float_m[1] = idContainer_float;
    idContainer_float_ascending_m[1] = idContainer_float_ascending;
    idContainer_float_descending_m[1] = idContainer_float_descending;

    idContainer_unsigned_m[1] = idContainer_unsigned;
    idContainer_unsigned_ascending_m[1] = idContainer_unsigned_ascending;
    idContainer_unsigned_descending_m[1] = idContainer_unsigned_descending;

    idContainer_bool_m[1] = idContainer_bool;
    idContainer_bool_ascending_m[1] = idContainer_bool_ascending;
    idContainer_bool_descending_m[1] = idContainer_bool_descending;

    idContainer_char_m[1] = idContainer_char;
    idContainer_char_ascending_m[1] = idContainer_char_ascending;
    idContainer_char_descending_m[1] = idContainer_char_descending;


    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(idContainer_int_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_m[i].getOrderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_int_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_ascending_m[i].getOrderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_int_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_descending_m[i].getUnorderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_float_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_m[i].getOrderedFreeIdsSizeT(), 16) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_float_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_ascending_m[i].getOrderedFreeIdsSizeT(), 16) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_float_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_descending_m[i].getUnorderedFreeIdsSizeT(), 16) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_unsigned_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_m[i].getOrderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_unsigned_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_ascending_m[i].getOrderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_unsigned_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_descending_m[i].getUnorderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_bool_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_m[i].getOrderedFreeIdsSizeT(), 2) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_bool_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_ascending_m[i].getOrderedFreeIdsSizeT(), 2) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_bool_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_descending_m[i].getUnorderedFreeIdsSizeT(), 2) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_char_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_m[i].getOrderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_char_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_ascending_m[i].getOrderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_char_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_descending_m[i].getUnorderedFreeIdsSizeT(), 7) << "The error occurred when: i == " << i;
    }

    for (size_t i = 0; i < 2; ++i) {
        idContainer_int_m[i].clear();
        idContainer_int_ascending_m[i].clear();
        idContainer_int_descending_m[i].clear();

        idContainer_float_m[i].clear();
        idContainer_float_ascending_m[i].clear();
        idContainer_float_descending_m[i].clear();

        idContainer_unsigned_m[i].clear();
        idContainer_unsigned_ascending_m[i].clear();
        idContainer_unsigned_descending_m[i].clear();

        idContainer_bool_m[i].clear();
        idContainer_bool_ascending_m[i].clear();
        idContainer_bool_descending_m[i].clear();

        idContainer_char_m[i].clear();
        idContainer_char_ascending_m[i].clear();
        idContainer_char_descending_m[i].clear();


        EXPECT_EQ(idContainer_int_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_int_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_ascending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_int_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_int_descending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_float_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_float_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_ascending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_float_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_float_descending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_unsigned_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_unsigned_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_ascending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_unsigned_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_unsigned_descending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_bool_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_bool_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_ascending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_bool_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_bool_descending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;


        EXPECT_EQ(idContainer_char_m[i].getIdIssuingMethod(), IdIssuingMethod::Ascending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_char_ascending_m[i].getIdIssuingMethod(), IdIssuingMethod::Descending) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_ascending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_ascending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;

        EXPECT_EQ(idContainer_char_descending_m[i].getIdIssuingMethod(), IdIssuingMethod::Dynamic) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_descending_m[i].getOrderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
        EXPECT_EQ(idContainer_char_descending_m[i].getUnorderedFreeIdsSizeT(), 0) << "The error occurred when: i == " << i;
    }
}
