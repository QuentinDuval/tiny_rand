//
// Created by Duval Quentin on 16/04/2017.
//

#ifndef TINYRANDOM_COMBINATORS_H
#define TINYRANDOM_COMBINATORS_H

#include <random>

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

template<typename... ValueGenerators>
auto tuple_gen(ValueGenerators... value_generators)
{
   return [=](std::mt19937& bit_gen)
   {
      return std::make_tuple(value_generators(bit_gen)...);
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

template<typename Finalizer, typename ValueGenerator, typename... ValueGenerators>
auto one_of_gen(Finalizer finalizer, ValueGenerator value_gen, ValueGenerators... value_gens)
{
   using Out = decltype(finalizer(value_gen(std::declval<std::mt19937&>())));
   std::vector<std::function<Out(std::mt19937&)>> gens{
      transform_gen(finalizer, value_gen),
      transform_gen(finalizer, value_gens)...
   };

   return [=](std::mt19937& gen)
   {
      std::uniform_int_distribution<int> distribution(0, gens.size() - 1);
      return gens[distribution(gen)](gen);
   };
}
}

#endif //TINYRANDOM_COMBINATORS_H
