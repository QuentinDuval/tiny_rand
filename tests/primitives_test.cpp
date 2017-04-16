//
// Created by Duval Quentin on 16/04/2017.
//

#include "tiny_rand/generators.h"

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
