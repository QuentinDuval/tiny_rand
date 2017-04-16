//
// Created by Duval Quentin on 16/04/2017.
//

#include "tiny_rand/generators.h"

#include <gtest/gtest.h>


struct ContainersTest : public ::testing::Test
{
   ContainersTest() : m_bit_gen(0) {}
   std::mt19937 m_bit_gen;
};

TEST_F(ContainersTest, should_just_work)
{

}
