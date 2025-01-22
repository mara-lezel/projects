#include "Ghost.h"

//WHAT:
//A function that returns the opposite of current direction.
//Used when ghost state changes.

void Ghost::reverseDirection()
{
	switch (direction_)
	{
		case Direction::RIGHT:
			direction_ = Direction::LEFT;
			break;
		case Direction::LEFT:
			direction_ = Direction::RIGHT;
			break;
		case Direction::UP:
			direction_ = Direction::DOWN;
			break;
		case Direction::DOWN:
			direction_ = Direction::UP;
			break;
		default:
			break;
	}
}
