#include "Ghost_Navigation.h"

#include "Map.h"

#include <vector>
#include <cstdlib>

//WHAT:
//A function that randomizes entity's direction upon leaving current tile.

//HOW:
//Takes the tile ahead of ghost in its current direction;
//Marks all available movement directions from the aforementioned tile;
//Picks one using pseudo-random number generator;
//Returns randomized direction.

Direction GhostNavigation::chooseRandomDirection(const Map& map, float current_x, float current_y, Direction current_direction)
{

	std::vector<Direction> available_directions;


	const Tile& current_tile = map.produceCurrentTile(current_x, current_y);

	const Tile& next_tile = map.produceNextTile(current_tile, current_direction);

	//Four directions total
	for (int i = 0; i < 4; i++)
	{
		//Directions implicitly are enum 0-3
		Direction possible_direction = static_cast<Direction>(i);

		//Current direction as parameter to remove backwards tiles
		if (map.nextTileIsAvailable(current_direction, next_tile, possible_direction))
		{
			available_directions.push_back(possible_direction);
		}
	}


	unsigned random = rand() % available_directions.size();

	return available_directions[random];
}