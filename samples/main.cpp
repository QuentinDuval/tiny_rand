#include <iostream>
#include <random>

#include "advanced.h"
#include "basics.h"
#include "rgb_color.h"

int main()
{
   std::random_device random_seed;
   std::mt19937 gen(random_seed());

   basics(gen);
   rgb_color_samples(gen);
   advanced_examples(gen);
   return 0;
}