#include "Ghost.h"

#include "Map.h"

//WHAT:
//A function that coordinates ghost exit from the cage.

//HOW:
//Transition from the cage happens immediately after bouncing movement;
//Ghosts use different coordinated movements depending on their position in the cage;
//In order to leave, ghost must be in the center of the cage;
//For Pinky, the direction is always UP - he is in the middle;
//For Inky, the direction is RIGHT until he reaches the center, UP afterwards;
//For Clyde, the direction is LEFT until he reaches the center, UP afterwards.

//None of the ghosts use DOWN direction while in transition from cage.

void Ghost::transitionOut(const Map& map)
{

	switch (direction_)
	{
	case Direction::RIGHT:
	{
		if (static_cast<int>(x_) < map.grid[15][17].x)
		{
			x_ += velocity_;

			if (static_cast<int>(x_) >= map.grid[15][17].x)
			{
				x_ = static_cast<float>(map.grid[15][17].x);
				direction_ = Direction::UP;
			}
		}

		break;
	}

	case Direction::LEFT:
	{
		if (static_cast<int>(x_) > map.grid[15][17].x)
		{
			x_ -= velocity_;

			if (static_cast<int>(x_) <= map.grid[15][17].x)
			{
				x_ = static_cast<float>(map.grid[15][17].x);
				direction_ = Direction::UP;
			}
		}

		break;
	}

	case Direction::UP:
	{
		if (static_cast<int>(y_) > map.grid[15][14].mid_y)
		{
			y_ -= velocity_;

			if (static_cast<int>(y_) <= map.grid[15][14].mid_y)
				y_ = static_cast<float>(map.grid[15][14].mid_y);
		}

		break;
	}

	default:
		break;

	}
}