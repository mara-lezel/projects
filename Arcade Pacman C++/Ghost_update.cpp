#include "Ghost.h"

#include "Map.h"


//WHAT:
//A function that assigns direction to ghost based on current state.

//HOW:
//In addition to current state, ghost keeps track of its previous state as well;
//Previous state is used to determine whether ghost needs to reverse direction;
//Current and previous state discrepency will exist for only one frame after the mode change
//in order to prevent repeated action;
//Next direction is chosen pre-emtively every time ghost enters a new tile;
//And assigned upon entering aforementioned tile.


void Ghost::updateMovement(const Map& map, const Tile& target_tile)
{

	switch (current_state_)
	{
		case GhostStates::State::CHASE:
		{

			if (previous_state_ == GhostStates::State::SCATTER)
				reverseDirection();
			else
				direction_ = next_direction_;

			next_direction_ = chooseNextDirection(map, target_tile, x_, y_, direction_);

			previous_state_ = current_state_;

			break;
		}

		case GhostStates::State::SCATTER:
		{

			if (previous_state_ == GhostStates::State::CHASE)
				reverseDirection();
			else
				direction_ = next_direction_;

			next_direction_ = chooseNextDirection(map, target_tile, x_, y_, direction_);

			previous_state_ = current_state_;

			break;
		}

		case GhostStates::State::FRIGHTENED:
		{

			if(previous_state_ == GhostStates::State::SCATTER || previous_state_ == GhostStates::State::CHASE)
				reverseDirection();
			else
				direction_ = next_direction_;

			next_direction_ = chooseRandomDirection(map, x_, y_, direction_);

			previous_state_ = current_state_;

			break;
		}

		case GhostStates::State::EATEN:
		{
			direction_ = next_direction_;

			next_direction_ = chooseNextDirection(map, target_tile, x_, y_, direction_);

			previous_state_ = current_state_;

			break;
		}

		default:
			break;
	}
}