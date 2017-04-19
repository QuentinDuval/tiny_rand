//
// Created by Duval Quentin on 16/04/2017.
//

#include <gtest/gtest.h>
#include <random>

#include "tiny_rand/generators.h"
#include "test_utils.h"

using namespace tiny_rand;

struct ContainersTest : public ::testing::Test
{
   ContainersTest() : m_bit_gen(0) {}
   std::mt19937 m_bit_gen;

   template <typename ContainerGen>
   void sequential_container_test(ContainerGen container_gen)
   {
      std::vector<char> char_set = { 'a', 'b', 'c' };
      auto gen = container_gen(2, 10, choice_gen(char_set));

      auto val = gen(m_bit_gen);
      EXPECT_GE(val.size(), 2);
      EXPECT_LE(val.size(), 10);
      ASSERT_TRUE(all_of(val, [&](auto c) {
         return contains(char_set, c);
      }));
   }
};

TEST_F(ContainersTest, generation_of_strings)
{
   sequential_container_test(
      [](int min_size, int max_size, auto gen) {
         return string_gen(int_gen(min_size, max_size), gen);
      });
}

TEST_F(ContainersTest, generation_of_vector)
{
   sequential_container_test(
      [](int min_size, int max_size, auto gen) {
         return vector_gen(int_gen(min_size, max_size), gen);
      });
}

TEST_F(ContainersTest, generation_of_list)
{
   sequential_container_test(
      [](int min_size, int max_size, auto gen) {
         return list_gen(int_gen(min_size, max_size), gen);
      });
}

TEST_F(ContainersTest, generation_of_deque)
{
   sequential_container_test(
      [](int min_size, int max_size, auto gen) {
         return deque_gen(int_gen(min_size, max_size), gen);
      });
}
