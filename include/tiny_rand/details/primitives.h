//
// Created by Duval Quentin on 16/04/2017.
//

#ifndef TINYRANDOM_PRIMITIVES_H
#define TINYRANDOM_PRIMITIVES_H

#include "tiny_rand/details/combinators.h"

#include <limits>
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

   inline auto char_gen()
   {
      return [=](std::mt19937& bit_gen) -> char
      {
         std::uniform_int_distribution<int> distribution{
            std::numeric_limits<char>::min(), std::numeric_limits<char>::max()};
         return distribution(bit_gen);
      };
   }

   namespace details
   {
      inline const std::string letters()
      {
         return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
      }

      inline const std::string numerics()
      {
         return "0123456789";
      }
   }

   inline auto letter_gen()
   {
      static const std::string ALPHABET = details::letters();
      return choice_gen(ALPHABET);
   }

   inline auto numeric_char_gen()
   {
      static const std::string ALPHABET = details::numerics();
      return choice_gen(ALPHABET);
   }

   inline auto alphanum_gen()
   {
      static const std::string ALPHABET = details::letters() + details::numerics();
      return choice_gen(ALPHABET);
   }
}

#endif //TINYRANDOM_PRIMITIVES_H
