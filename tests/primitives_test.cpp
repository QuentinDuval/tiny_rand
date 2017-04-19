//
// Created by Duval Quentin on 16/04/2017.
//

#include "tiny_rand/generators.h"
#include "test_utils.h"

#include <gtest/gtest.h>


struct PrimitivesTest : public ::testing::Test
{
   PrimitivesTest() : m_bit_gen(0) {}
   std::mt19937 m_bit_gen;
};

struct IntegerGeneratorShould : PrimitivesTest
{
   int run_gen(int min_val, int max_val)
   {
      return tiny_rand::int_gen(min_val, max_val)(m_bit_gen);
   }
};

TEST_F(IntegerGeneratorShould, be_usable_with_singleton_range)
{
   int val = run_gen(0, 0);
   ASSERT_EQ(val, 0);
}

TEST_F(IntegerGeneratorShould, be_in_the_range)
{
   int val = run_gen(-10, 10);
   ASSERT_GE(val, -10);
   ASSERT_LE(val, 10);
}

struct DoubleGeneratorShould : PrimitivesTest
{
   double run_gen(double min_val, double max_val)
   {
      return tiny_rand::double_gen(min_val, max_val)(m_bit_gen);
   }
};

TEST_F(DoubleGeneratorShould, be_usable_with_singleton_range)
{
   double val = run_gen(0, 0);
   ASSERT_EQ(val, 0);
}

TEST_F(DoubleGeneratorShould, be_in_the_range)
{
   double val = run_gen(-10, 10);
   ASSERT_GE(val, -10);
   ASSERT_LE(val, 10);
}

struct CharGeneratorShould : PrimitivesTest
{
   char run_gen()
   {
      return tiny_rand::char_gen()(m_bit_gen);
   }
};

TEST_F(CharGeneratorShould, be_in_the_range)
{
   char val = run_gen();
   ASSERT_LE(',', val);
}

enum class db_relation
{
   one_to_one,
   one_to_many,
   many_to_many
};

TEST_F(PrimitivesTest, test_enumeration_generator)
{
   std::vector<db_relation> all_relations = {
      db_relation::one_to_one,
      db_relation::one_to_many,
      db_relation::many_to_many
   };
   auto relation = tiny_rand::choice_gen(all_relations)(m_bit_gen);
   ASSERT_TRUE(contains(all_relations, relation));
}
