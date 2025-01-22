#include "Ghost.h"

#include "Map.h"

//WHAT:
//A function that manages all ghost movement related options.

void Ghost::lookAhead(const Map& map, const Tile& target_tile)
{
	int current_tile_x = static_cast<int>(x_) / TILE_W;
	int current_tile_y = static_cast<int>(y_) / TILE_H;


	if (start_tile_x_ != current_tile_x || start_tile_y_ != current_tile_y)
	{
		if (current_state_ != GhostStates::State::IN_CAGE &&
			current_state_ != GhostStates::State::IN_TRANSITION_FROM_CAGE &&
			current_state_ != GhostStates::State::IN_TRANSITION_TO_CAGE)
			updateMovement(map, target_tile);

		start_tile_x_ = current_tile_x;
		start_tile_y_ = current_tile_y;
	}	
}
