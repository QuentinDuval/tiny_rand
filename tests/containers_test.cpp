//
// Created by Duval Quentin on 16/04/2017.
//

#include <gtest/gtest.h>
#include <random>

#include "tiny_rand/generators.h"


struct ContainersTest : public ::testing::Test
{
   ContainersTest() : m_bit_gen(0) {}
   std::mt19937 m_bit_gen;
};

TEST_F(ContainersTest, generation_of_strings)
{
   auto gen = tiny_rand::string_gen(10, tiny_rand::letter_gen());
   std::string val = gen(m_bit_gen);
   ASSERT_LE(val.size(), 10);
}
