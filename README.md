# tiny_rand

A small header only library to randomly generate data.

Useful to quickly generate test samples without requiring a big library as dependency.

## Features

A small API that allows to generate any kind of STL data structures:

* Primitives: int, double, strings
* Containers: vector, list, maps, sets...

And to combine them together to generate any kind of data by composition.

## Examples

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

Generating an instance of a game object, that contains an integer for the current round number, and a map from player names to their respective 3D position:

    using PlayerName = std::string;
    using Coordinate = std::tuple<double, double, double>;

    struct Game
    {
       int m_current_round;
       std::map<PlayerName, Coordinate> m_players_location;
    };

    auto round_gen()
    {
       return int_gen(0, std::numeric_limits<int>::max());
    }

    auto player_name_gen()
    {
       return string_gen(
          int_gen(1, 30), //Player name cannot be empty
          alphanum_gen()  //Restriction on the character set
       );
    }

    auto coord_3d_gen(double map_size)
    {
       auto coord_1d_gen = double_gen(0, map_size);
       return tuple_gen(coord_1d_gen, coord_1d_gen, coord_1d_gen);
    }

    auto game_gen(int max_player, double map_size)
    {
       return apply_gen(
          to_object<Game>(), //Combine into a game
          round_gen(),
          sorted_map_gen(max_player,
                         player_name_gen(),
                         coord_3d_gen(map_size))
       );
    }
 
