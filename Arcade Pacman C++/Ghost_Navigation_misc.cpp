#include "Ghost_Navigation.h"

#include "Tile.h"

#include <cmath>


//WHAT:
//A function used to decide which direction to take when other measures are equal.
//Lower score means higher priority.
int GhostNavigation::priorityScore(Direction direction)
{
	switch (direction)
	{
	case Direction::UP:
		return 1;
	case Direction::LEFT:
		return 2;
	case Direction::DOWN:
		return 3;
	case Direction::RIGHT:
		return 4;
	default:
		return 0;
	}
}


//WHAT:
//A function used to measure distance between two tiles.
//Uses Euclidean distance for calculation.
int GhostNavigation::calculateDistance(const Tile& ghost_tile, const Tile& target_tile)
{
	return static_cast<int>(sqrt(pow(target_tile.mid_x - ghost_tile.mid_x, 2) + pow(target_tile.mid_y - ghost_tile.mid_y, 2)));
}
