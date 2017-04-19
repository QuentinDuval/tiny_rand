//
// Created by Duval Quentin on 16/04/2017.
//

#include <gtest/gtest.h>
#include <random>

#include "tiny_rand/generators.h"
#include "test_utils.h"


struct ContainersTest : public ::testing::Test
{
   ContainersTest() : m_bit_gen(0) {}
   std::mt19937 m_bit_gen;
};

TEST_F(ContainersTest, generation_of_strings)
{
   std::vector<char> char_set = { 'a', 'b', 'c' };
   auto gen = tiny_rand::string_gen(10, tiny_rand::choice_gen(char_set));

   std::string val = gen(m_bit_gen);
   EXPECT_LE(val.size(), 10);
   ASSERT_TRUE(all_of(val, [&](auto c) {
      return contains(char_set, c);
   }));
}
