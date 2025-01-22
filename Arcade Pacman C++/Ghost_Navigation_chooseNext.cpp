#include "Ghost_Navigation.h"

#include "Map.h"

#include <vector>
#include <functional>


//WHAT:
//A function that projects entity's direction upon leaving current tile.

//HOW:
//Takes the tile ahead of ghost in its current direction;
//Gets all available tiles around aforementioned tile;
//Marks all available movement directions from the aforementioned tile;
//Picks the tile that has the shortest distance to target;
//Returns direction that entity has to take to reach that tile.

Direction GhostNavigation::chooseNextDirection(const Map& map, const Tile& target_tile, float current_x, float current_y, Direction current_direction)
{

	//Available tiles - no walls, no backwards tiles
	std::vector<std::reference_wrapper<const Tile>> available_tiles;

	//Size and order matches available_tiles
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
			available_tiles.push_back(map.produceNextTile(next_tile, possible_direction));

			available_directions.push_back(possible_direction);
		}
	}




	//Placeholder value higher than any possible distance
	int shortest_distance = 1000;

	//Placeholder preventing entity from moving if its returned
	Direction shortest_distance_direction = Direction::NONE;

	for (unsigned i = 0; i < available_tiles.size(); i++)
	{
		int current_distance = calculateDistance(available_tiles[i], target_tile);

		if (current_distance < shortest_distance)
		{
			shortest_distance = current_distance;
			shortest_distance_direction = available_directions[i];
		}

		else if (current_distance == shortest_distance)
		{
			//Lower score - higher priority
			if (priorityScore(shortest_distance_direction) > priorityScore(available_directions[i]))
			{
				shortest_distance_direction = available_directions[i];
			}
		}
	}

	return shortest_distance_direction;
}