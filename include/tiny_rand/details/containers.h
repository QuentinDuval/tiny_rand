//
// Created by Duval Quentin on 16/04/2017.
//

#ifndef TINYRANDOM_CONTAINERS_H
#define TINYRANDOM_CONTAINERS_H

#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "tiny_rand/details/primitives.h"


namespace tiny_rand
{
namespace details
{
template<typename ValueGenerator, typename OutputIterator>
void repeat_n_gen(OutputIterator out, int count,
                  ValueGenerator value_gen,
                  std::mt19937& bit_gen)
{
   std::generate_n(out, count,
                   [&]
                   { return value_gen(bit_gen); });
}
}

// ---------------------------------------------------------------------------------------------------------------------
// String random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename SizeGenerator, typename CharGenerator>
auto string_gen(SizeGenerator size_gen, CharGenerator char_generator)
{
   return [=](std::mt19937& bit_gen) -> std::string
   {
      std::string out(size_gen(bit_gen), ' ');
      details::repeat_n_gen(out.begin(), out.size(), char_generator, bit_gen);
      return out;
   };
}

template<typename CharGenerator>
auto string_gen(int max_size, CharGenerator char_generator)
{
   return string_gen(int_gen(0, max_size), char_generator);
}

// ---------------------------------------------------------------------------------------------------------------------
// Vector random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename SizeGenerator, typename ValueGenerator>
auto vector_gen(SizeGenerator size_gen, ValueGenerator value_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = size_gen(bit_gen);
      std::vector<decltype(value_gen(bit_gen))> out;
      out.reserve(count);
      details::repeat_n_gen(std::back_inserter(out), count, value_gen, bit_gen);
      return out;
   };
}

template<typename ValueGenerator>
auto vector_gen(int max_size, ValueGenerator value_gen)
{
   return vector_gen(int_gen(0, max_size), value_gen);
}

// ---------------------------------------------------------------------------------------------------------------------
// Deque random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename SizeGenerator, typename ValueGenerator>
auto deque_gen(SizeGenerator size_gen, ValueGenerator value_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = size_gen(bit_gen);
      std::deque<decltype(value_gen(bit_gen))> out;
      details::repeat_n_gen(std::back_inserter(out), count, value_gen, bit_gen);
      return out;
   };
}

template<typename ValueGenerator>
auto deque_gen(int max_size, ValueGenerator value_gen)
{
   return deque_gen(int_gen(0, max_size), value_gen);
}

// ---------------------------------------------------------------------------------------------------------------------
// List random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename SizeGenerator, typename ValueGenerator>
auto list_gen(SizeGenerator size_gen, ValueGenerator value_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = size_gen(bit_gen);
      std::list<decltype(value_gen(bit_gen))> out;
      details::repeat_n_gen(std::back_inserter(out), count, value_gen, bit_gen);
      return out;
   };
}

template<typename ValueGenerator>
auto list_gen(int max_size, ValueGenerator value_gen)
{
   return list_gen(int_gen(0, max_size), value_gen);
}

// ---------------------------------------------------------------------------------------------------------------------
// Set random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename RollCountGenerator, typename KeyGenerator>
auto sorted_set_gen(RollCountGenerator roll_count_gen, KeyGenerator key_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = roll_count_gen(bit_gen);
      std::set<decltype(key_gen(bit_gen))> out;
      details::repeat_n_gen(std::inserter(out, out.end()), count, key_gen, bit_gen);
      return out;
   };
}

template<typename KeyGenerator>
auto sorted_set_gen(int max_rolls, KeyGenerator key_gen)
{
   return sorted_set_gen(int_gen(0, max_rolls), key_gen);
}

// ---------------------------------------------------------------------------------------------------------------------
// Hash set random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename RollCountGenerator, typename KeyGenerator>
auto unordered_set_gen(RollCountGenerator roll_count_gen, KeyGenerator key_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = roll_count_gen(bit_gen);
      std::unordered_set<decltype(key_gen(bit_gen))> out;
      out.reserve(count);
      details::repeat_n_gen(std::inserter(out, out.end()), count, key_gen, bit_gen);
      return out;
   };
}

template<typename KeyGenerator>
auto unordered_set_gen(int max_rolls, KeyGenerator key_gen)
{
   return unordered_set_gen(int_gen(0, max_rolls), key_gen);
}

// ---------------------------------------------------------------------------------------------------------------------
// Map random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename RollCountGenerator, typename KeyGenerator, typename ValueGenerator>
auto sorted_map_gen(RollCountGenerator roll_count_gen, KeyGenerator key_gen, ValueGenerator value_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = roll_count_gen(bit_gen);
      std::map<decltype(key_gen(bit_gen)), decltype(value_gen(bit_gen))> out;
      details::repeat_n_gen(std::inserter(out, out.end()), count, pair_gen(key_gen, value_gen), bit_gen);
      return out;
   };
}

template<typename KeyGenerator, typename ValueGenerator>
auto sorted_map_gen(int max_rolls, KeyGenerator key_gen, ValueGenerator value_gen)
{
   return sorted_map_gen(int_gen(0, max_rolls), key_gen, value_gen);
}

// ---------------------------------------------------------------------------------------------------------------------
// Hash map random generator
// ---------------------------------------------------------------------------------------------------------------------

template<typename RollCountGenerator, typename KeyGenerator, typename ValueGenerator>
auto unordered_map_gen(RollCountGenerator roll_count_gen, KeyGenerator key_gen, ValueGenerator value_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      int count = roll_count_gen(bit_gen);
      std::unordered_map<decltype(key_gen(bit_gen)), decltype(value_gen(bit_gen))> out;
      out.reserve(count);
      details::repeat_n_gen(std::inserter(out, out.end()), count, pair_gen(key_gen, value_gen), bit_gen);
      return out;
   };
}

template<typename KeyGenerator, typename ValueGenerator>
auto unordered_map_gen(int max_rolls, KeyGenerator key_gen, ValueGenerator value_gen)
{
   return unordered_map_gen(int_gen(0, max_rolls), key_gen, value_gen);
}

}

#endif //TINYRANDOM_CONTAINERS_H
