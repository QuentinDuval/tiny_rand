//
// Created by Duval Quentin on 18/04/2017.
//

#include "tiny_rand/generators.h"

#include <limits>
#include <map>
#include <string>
#include <tuple>

using namespace tiny_rand;

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

void advanced_examples(std::mt19937& bit_gen)
{
   auto game_gen_instance = game_gen(10, 99);
   game_gen_instance(bit_gen);
}
