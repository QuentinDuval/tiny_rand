//
// Created by Duval Quentin on 16/04/2017.
//

#include "tiny_rand/generators.h"

#include <iostream>


struct rgb_color
{
   int m_red;
   int m_green;
   int m_blue;
};

rgb_color make_rgb_color(int red, int green, int blue)
{
   return rgb_color{ red, green, blue };
}

std::ostream& operator<< (std::ostream& os, rgb_color const& c)
{
   return os << "{ red: " << c.m_red
             << ", green: " << c.m_green
             << ", blue: " << c.m_blue << " }";
}

void rgb_color_samples(std::mt19937& bit_gen)
{
   using namespace tiny_rand;
   auto color_gen = int_gen(0, 255);
   auto rgb_color_gen = apply_gen(make_rgb_color, color_gen, color_gen, color_gen);

   std::cout << "Generating colors\n";
   for (auto c : vector_gen(10, rgb_color_gen)(bit_gen))
      std::cout << c << '\n';
}