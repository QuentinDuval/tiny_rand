//
// Created by Duval Quentin on 16/04/2017.
//

#include "basics.h"

#include <iostream>
#include <tuple>
#include <string>
#include <utility>

#include "tiny_rand/generators.h"

template <size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream&, const std::tuple<T...>&)
{}

template <size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream& os, const std::tuple<T...>& tup)
{
   if (n != 0)
      os << ", ";
   os << std::get<n>(tup);
   print_tuple<n+1>(os, tup);
}

template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tup)
{
   os << "[";
   print_tuple<0>(os, tup);
   return os << "]";
}

template <typename A, typename B>
std::ostream& operator<< (std::ostream& os, std::pair<A, B> const& p)
{
   return os << "[ " << p.first << ", " << p.second << " ]";
}

void basics(std::mt19937& bit_gen)
{
   using namespace tiny_rand;
   auto words_gen = string_gen(10, letter_gen());
   auto coord_1d_gen = double_gen(-10, 10);
   auto coord_3d_gen = tuple_gen(coord_1d_gen, coord_1d_gen, coord_1d_gen);
   auto map_coord_to_string_gen = unordered_map_gen(10, words_gen, coord_3d_gen);

   for (auto map_entry: map_coord_to_string_gen(bit_gen))
      std::cout << map_entry << '\n';
}