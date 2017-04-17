//
// Created by Duval Quentin on 16/04/2017.
//
#include "rgb_color.h"

#include <iostream>

#include "tiny_rand/generators.h"


struct rgb_color
{
   int m_red;
   int m_green;
   int m_blue;
};

std::ostream& operator<<(std::ostream& os, rgb_color const& c)
{
   return os << "{ red: " << c.m_red
             << ", green: " << c.m_green
             << ", blue: " << c.m_blue << " }";
}

void rgb_color_samples(std::mt19937& bit_gen)
{
   using namespace tiny_rand;
   auto color_gen = int_gen(0, 255);
   auto rgb_color_gen = apply_gen(to_object<rgb_color>(), color_gen, color_gen, color_gen);

   std::cout << "Generating colors\n";
   for (auto c : vector_gen(10, rgb_color_gen)(bit_gen))
      std::cout << c << '\n';
}