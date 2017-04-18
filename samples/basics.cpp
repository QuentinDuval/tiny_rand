//
// Created by Duval Quentin on 16/04/2017.
//

#include "basics.h"

#include <iostream>
#include <tuple>
#include <string>
#include <utility>

#include "tiny_rand/generators.h"

template<size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream&, const std::tuple<T...>&)
{}

template<size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream& os, const std::tuple<T...>& tup)
{
   if (n != 0)
      os << ", ";
   os << std::get<n>(tup);
   print_tuple<n + 1>(os, tup);
}

template<typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tup)
{
   os << "[";
   print_tuple<0>(os, tup);
   return os << "]";
}

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, std::pair<A, B> const& p)
{
   return os << "[ " << p.first << ", " << p.second << " ]";
}

//----------------------------------------------------------------------------------------------------------------------

inline auto cpp_identifier_gen(int max_size)
{
   using namespace tiny_rand;
   static const std::string HEAD_CHARS = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   static const auto head_char_gen = choice_gen(HEAD_CHARS);
   static const auto rest_gen = string_gen(max_size - 1, choice_gen(HEAD_CHARS + "1234567890"));

   return [=](std::mt19937& bit_gen) -> std::string
   {
      return std::string {1, head_char_gen(bit_gen)} + rest_gen(bit_gen);
   };
}

//----------------------------------------------------------------------------------------------------------------------

void basics(std::mt19937& bit_gen)
{
   using namespace tiny_rand;

   std::cout << "Generate square numbers:\n";
   auto square_gen = transform_gen([](int i) { return i * i; }, int_gen(0, 10));
   for (int i = 0; i < 10; ++i)
      std::cout << square_gen(bit_gen) << ",";
   std::cout << '\n';

   std::cout << "Generating random characters\n";
   for (char c: vector_gen(50, char_gen())(bit_gen))
      std::cout << c;
   std::cout << '\n';

   std::cout << "Generating valid function names for C++\n";
   for (auto const& id: vector_gen(10, cpp_identifier_gen(30))(bit_gen))
      std::cout << id << '\n';

   auto words_gen = string_gen(10, letter_gen());
   auto coord_1d_gen = double_gen(-10, 10);
   auto coord_3d_gen = tuple_gen(coord_1d_gen, coord_1d_gen, coord_1d_gen);
   auto string_to_coord_gen = unordered_map_gen(10, words_gen, coord_3d_gen);

   std::cout << "Generating a map from string to coordinates:\n";
   for (auto map_entry: string_to_coord_gen(bit_gen))
      std::cout << map_entry << '\n';
}