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
#include <vector>
#include <unordered_set>
#include <unordered_map>


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

   template<typename ValueGenerator>
   auto vector_gen(int max_size, ValueGenerator value_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::vector<decltype(value_gen(bit_gen))> out;
         out.reserve(count);
         details::repeat_n_gen(std::back_inserter(out), count, value_gen, bit_gen);
         return out;
      };
   }

   template<typename ValueGenerator>
   auto deque_gen(int max_size, ValueGenerator value_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::deque<decltype(value_gen(bit_gen))> out;
         details::repeat_n_gen(std::back_inserter(out), count, value_gen, bit_gen);
         return out;
      };
   }

   template<typename ValueGenerator>
   auto list_gen(int max_size, ValueGenerator value_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::list<decltype(value_gen(bit_gen))> out;
         details::repeat_n_gen(std::back_inserter(out), count, value_gen, bit_gen);
         return out;
      };
   }

   template<typename KeyGenerator>
   auto sorted_set_gen(int max_size, KeyGenerator key_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::set<decltype(key_gen(bit_gen))> out;
         details::repeat_n_gen(std::inserter(out, out.end()), count, key_gen, bit_gen);
         return out;
      };
   }

   template<typename KeyGenerator>
   auto unordered_set_gen(int max_size, KeyGenerator key_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::unordered_set<decltype(key_gen(bit_gen))> out;
         details::repeat_n_gen(std::inserter(out, out.end()), count, key_gen, bit_gen);
         return out;
      };
   }

   template<typename KeyGenerator, typename ValueGenerator>
   auto sorted_map_gen(int max_size, KeyGenerator key_gen, ValueGenerator value_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::map<decltype(key_gen(bit_gen)), decltype(value_gen(bit_gen))> out;
         details::repeat_n_gen(std::inserter(out, out.end()), count, pair_gen(key_gen, value_gen), bit_gen);
         return out;
      };
   }

   template<typename KeyGenerator, typename ValueGenerator>
   auto unordered_map_gen(int max_size, KeyGenerator key_gen, ValueGenerator value_gen)
   {
      return [=](std::mt19937& bit_gen)
      {
         int count = std::uniform_int_distribution<int>{0, max_size}(bit_gen);
         std::unordered_map<decltype(key_gen(bit_gen)), decltype(value_gen(bit_gen))> out;
         out.reserve(count);
         details::repeat_n_gen(std::inserter(out, out.end()), count, pair_gen(key_gen, value_gen), bit_gen);
         return out;
      };
   }
}

#endif //TINYRANDOM_CONTAINERS_H
