# tiny_rand

A small header only library to randomly generate data.

Useful to quickly generate test samples without requiring a big library as dependency.

## Features

A small API that allows to generate any kind of STL data structures:

* Primitives: int, double, strings
* Containers: vector, list, maps, sets...

And to combine them together to generate any kind of data by composition.

## Examples

Generating a custom data structure `rgb_color` in a few lines of code.

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

    void rgb_color_samples(std::mt19937& bit_gen)
    {
       using namespace tiny_rand;
       auto color_gen = int_gen(0, 255);
       auto rgb_color_gen = apply_gen(make_rgb_color, color_gen, color_gen, color_gen);

       std::cout << "Generating colors\n";
       for (auto c : vector_gen(10, rgb_color_gen)(bit_gen))
          std::cout << c << '\n';
    }
