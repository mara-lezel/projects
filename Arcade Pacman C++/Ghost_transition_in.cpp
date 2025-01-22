#include "Ghost.h"

#include "Map.h"


//WHAT:
//A function that coordinates ghost transition to cage after being eaten.

//HOW:
//Transition to cage happens immediately after a ghost enters the tile on the left above cage;
//Ghosts use different directions based on their position in cage;
//All ghosts move DOWN to the center of the cage first;
//Blinky respawns immediately after moving directly down;
//Pinky respawns the same way, since it occupies the middle spot;
//Inky moves LEFT after going DOWN, then respawns;
//Clyde moves RIGHT after going DOWN, then respawns.

//NOTE:
//While moving down ghosts will also shift position to align with the middle of the cage.

//NOTE #2:
//None of the ghosts move UP during transition into the cage.


void Ghost::transitionIn(const Map& map)
{
	switch (direction_)
	{
	case Direction::RIGHT:
	{
		if (static_cast<int>(x_) < map.grid[17][17].x)
		{
			x_ += velocity_;

			if (static_cast<int>(x_) >= map.grid[17][17].x)
				x_ = static_cast<float>(map.grid[17][17].x);
		}

		break;
	}

	case Direction::LEFT:
	{
		if (static_cast<int>(x_) > map.grid[13][17].x)
		{
			x_ -= velocity_;

			if (static_cast<int>(x_) <= map.grid[13][17].x)
				x_ = static_cast<float>(map.grid[13][17].x);
		}

		break;
	}

	case Direction::DOWN:
	{
		if (static_cast<int>(y_) < map.grid[15][17].mid_y)
		{
			y_ += velocity_;

			if (static_cast<int>(y_) >= map.grid[15][17].mid_y)
				y_ = static_cast<float>(map.grid[15][17].mid_y);
		}

		if (static_cast<int>(x_) != map.grid[15][17].x)
			x_ = static_cast<float>(map.grid[15][17].x);

		break;
	}

	default:
		break;
	}
}