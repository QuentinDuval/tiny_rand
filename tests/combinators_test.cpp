//
// Created by Duval Quentin on 16/04/2017.
//

#include "tiny_rand/generators.h"

#include <gtest/gtest.h>
#include <random>

struct CombinatorsTest : public ::testing::Test
{
   CombinatorsTest() : m_bit_gen(0) {}
   std::mt19937 m_bit_gen;
};

TEST_F(CombinatorsTest, one_of_generator_with_finalizer)
{
   using namespace tiny_rand;

   struct finalizer
   {
      int operator() (int i) const { return i; }
      int operator() (std::string const& s) const { return s.size(); }
   };

   auto words_gen = string_gen(10, letter_gen());
   auto weird_gen = one_of_gen(finalizer{}, int_gen(-10, 0), words_gen);

   int val = weird_gen(m_bit_gen);
   ASSERT_LE(val, 10);
   ASSERT_GE(val, -10);
}
