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

TEST_F(CombinatorsTest, should_be_true)
{

}
