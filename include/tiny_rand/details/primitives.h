//
// Created by Duval Quentin on 16/04/2017.
//

#ifndef TINYRANDOM_PRIMITIVES_H
#define TINYRANDOM_PRIMITIVES_H

#include "tiny_rand/details/combinators.h"

#include <random>

namespace tiny_rand
{
   inline auto int_gen(double min_val, double max_val)
   {
      return [=](std::mt19937& bit_gen)
      {
         std::uniform_int_distribution<int> distribution(min_val, max_val);
         return distribution(bit_gen);
      };
   }

   inline auto pos_int_gen(int max_val)
   {
      return int_gen(0, max_val);
   }

   inline auto double_gen(double min_val, double max_val)
   {
      return [=](std::mt19937& bit_gen)
      {
         std::uniform_real_distribution<double> distribution(min_val, max_val);
         return distribution(bit_gen);
      };
   }

   inline auto letter_gen()
   {
      static const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
      return choice_gen(ALPHABET);
   }
}

#endif //TINYRANDOM_PRIMITIVES_H
