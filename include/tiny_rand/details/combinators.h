//
// Created by Duval Quentin on 16/04/2017.
//

#ifndef TINYRANDOM_COMBINATORS_H
#define TINYRANDOM_COMBINATORS_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <tuple>
#include <utility>


namespace tiny_rand
{

//FUNCTOR INSTANCE
template<typename Mapper, typename Generator>
auto transform_gen(Mapper map, Generator generator)
{
   return [=](std::mt19937& bit_gen)
   {
      return map(generator(bit_gen));
   };
}

//APPLICATIVE INSTANCE
template<typename Finalizer, typename... Generators>
auto apply_gen(Finalizer finalizer, Generators... generators)
{
   return [=](std::mt19937& bit_gen)
   {
      return finalizer(generators(bit_gen)...);
   };
}

template<typename LhsGenerator, typename RhsGenerator>
auto pair_gen(LhsGenerator lhs_gen, RhsGenerator rhs_gen)
{
   return [=](std::mt19937& bit_gen)
   {
      return std::make_pair(lhs_gen(bit_gen), rhs_gen(bit_gen));
   };
}

template<typename... Generators>
auto tuple_gen(Generators... generators)
{
   return [=](std::mt19937& bit_gen)
   {
      return std::make_tuple(generators(bit_gen)...);
   };
}

template<typename Container>
auto choice_gen(Container const& values)
{
   return [=](std::mt19937& bit_gen) -> typename Container::value_type
   {
      std::uniform_int_distribution<int> distribution(0, values.size() - 1);
      return values[distribution(bit_gen)];
   };
}

template<typename Finalizer, typename Generator, typename... Generators>
auto one_of_gen(Finalizer finalizer, Generator head, Generators... tail)
{
   using Out = decltype(finalizer(head(std::declval<std::mt19937&>())));
   using OutGen = std::function<Out(std::mt19937&)>;
   std::vector<OutGen> gens{
      transform_gen(finalizer, head),
      transform_gen(finalizer, tail)...
   };

   auto generator_picker = choice_gen(gens);
   return [=](std::mt19937& bit_gen)
   {
      return generator_picker(bit_gen)(bit_gen);
   };
}

namespace details
{
template<typename Value>
std::vector<std::pair<double, Value>> to_search_vector(std::vector<std::pair<Value, double>> const& weighted_values)
{
   std::vector<std::pair<double, Value>> value_map;
   value_map.reserve(weighted_values.size());

   double summed_weights = 0.0;
   for (auto const& weighted_value: weighted_values)
   {
      summed_weights += weighted_value.second;
      value_map.emplace_back(summed_weights, weighted_value.first);
   }
   return value_map;
}

template<typename Value>
Value search_by_weight(std::vector<std::pair<double, Value>> const& value_map, double weight)
{
   auto it = std::lower_bound(
      value_map.begin(), value_map.end(), weight,
      [](auto const& element, double weight)
      {
         return element.first < weight;
      });
   return it->second; //By construction, always exists
}
}

template<typename Value>
auto weighted_choice_gen(std::vector<std::pair<Value, double>> const& weighted_values)
{
   auto const& value_map = details::to_search_vector(weighted_values);
   double sum_weights = value_map.back().first;
   return [=](std::mt19937& bit_gen) -> Value
   {
      std::uniform_real_distribution<double> distribution(0., sum_weights);
      return details::search_by_weight(value_map, distribution(bit_gen));
   };
}
}

#endif //TINYRANDOM_COMBINATORS_H
