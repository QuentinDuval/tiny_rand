//
// Created by Duval Quentin on 16/04/2017.
//

#include "tiny_rand/generators.h"
#include "test_utils.h"

#include <gtest/gtest.h>
#include <random>

using namespace tiny_rand;

struct CombinatorsTest : public ::testing::Test
{
   CombinatorsTest() : m_bit_gen(0)
   {}

   std::mt19937 m_bit_gen;
};


TEST_F(CombinatorsTest, test_functor)
{
   auto negative_gen = transform_gen([](int i)
                                     { return -i; }, int_gen(1, 10));
   ASSERT_LT(negative_gen(m_bit_gen), 0);
}

TEST_F(CombinatorsTest, test_applicative)
{
   auto string_test =
      apply_gen(
         [](int i, char c)
         { return std::string(i, c); },
         int_gen(2, 10),
         letter_gen()
      );

   std::string result = string_test(m_bit_gen);
   ASSERT_GT(result.size(), 2);
   EXPECT_LT(result.size(), 10);
   EXPECT_TRUE(all_equal_to(result, result[0]));
}

TEST_F(CombinatorsTest, test_choice_generator)
{
   std::vector<int> choices = {1, 2, 3, 5, 8, 13, 21};
   auto fib_choice = choice_gen(choices);
   EXPECT_TRUE(contains(choices, fib_choice(m_bit_gen)));
}

TEST_F(CombinatorsTest, test_pair_generator)
{
   auto p = pair_gen(int_gen(1, 10), int_gen(-10, -1))(m_bit_gen);
   ASSERT_LT(0, p.first);
   ASSERT_LT(p.second, 0);
}

TEST_F(CombinatorsTest, test_tuple_generator)
{
   auto t = tuple_gen(int_gen(1, 10), int_gen(-10, -1))(m_bit_gen);
   ASSERT_LT(0, std::get<0>(t));
   ASSERT_LT(std::get<1>(t), 0);
}

TEST_F(CombinatorsTest, test_one_of_generator)
{
   struct finalizer
   {
      int operator()(int i) const
      { return i; }

      int operator()(std::string const& s) const
      { return s.size(); }
   };

   auto words_gen = string_gen(10, letter_gen());
   auto weird_gen = one_of_gen(finalizer{}, int_gen(-10, 0), words_gen);

   int val = weird_gen(m_bit_gen);
   ASSERT_LE(val, 10);
   ASSERT_GE(val, -10);
}

TEST_F(CombinatorsTest, test_to_search_vector)
{
   std::vector<std::pair<int, double>> weighted_choices = {
      {1, 2.},
      {2, 1.},
      {3, 1.5}
   };

   std::vector<std::pair<double, int>> search_vector = details::to_search_vector(weighted_choices);
   ASSERT_EQ(weighted_choices.size(), search_vector.size());
   EXPECT_EQ(std::make_pair(2., 1), search_vector[0]);
   EXPECT_EQ(std::make_pair(3., 2), search_vector[1]);
   EXPECT_EQ(std::make_pair(4.5, 3), search_vector[2]);
}

TEST_F(CombinatorsTest, test_search_by_weight)
{
   std::vector<std::pair<double, int>> search_vector = {
      {2.,  1},
      {3.,  2},
      {4.5, 3}
   };

   EXPECT_EQ(1, details::search_by_weight(search_vector, 0.0));
   EXPECT_EQ(1, details::search_by_weight(search_vector, 2.0));
   EXPECT_EQ(2, details::search_by_weight(search_vector, 2.1));
   EXPECT_EQ(2, details::search_by_weight(search_vector, 3.0));
   EXPECT_EQ(3, details::search_by_weight(search_vector, 3.1));
   EXPECT_EQ(3, details::search_by_weight(search_vector, 4.5));
}

TEST_F(CombinatorsTest, test_weighted_choice_generator)
{
   m_bit_gen.seed(std::random_device()());

   std::vector<std::pair<int, double>> weighted_choices = {
      {1, 2.},
      {2, 1.},
      {3, 1.}
   };

   auto int_choice = weighted_choice_gen(weighted_choices);

   int count_1 = 0;
   int count_2 = 0;
   int count_3 = 0;
   for (int i = 0; i < 10000; ++i)
   {
      int roll = int_choice(m_bit_gen);
      if (roll == 1)
         ++count_1;
      else if (roll == 2)
         ++count_2;
      else
         ++count_3;
   }

   std::cout << count_1 << ", ";
   std::cout << count_2 << ", ";
   std::cout << count_3 << '\n';
}
