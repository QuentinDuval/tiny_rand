#include <iostream>
#include <random>

#include "tiny_rand/generators.h"
#include "rgb_color.h"

int main()
{
   std::random_device random_seed;
   std::mt19937 gen(random_seed());

   rgb_color_samples(gen);
   return 0;
}