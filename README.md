# tiny_rand

A small header only library to randomly generate data.

Useful to quickly generate test samples without requiring a big library as dependency.

## Features

A small API that allows to generate any kind of STL data structures:

* Primitives: int, double, strings
* Containers: vector, list, maps, sets...

And to combine them together to generate any kind of data by composition.

## Examples

Generating a map from player names to their 3D coordinate in a game. Print the result.

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

Generating a custom data structure `rgb_color` in a few lines of code. Print the result.

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
