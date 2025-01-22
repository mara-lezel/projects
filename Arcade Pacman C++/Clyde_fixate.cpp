#include "Clyde.h"
#include "Pacman.h"

#include "Map.h"


//WHAT & HOW:
//A function that determines ghost's current target.
//8 tile radius - 8 x 16 - 128

//CHASE MODE:
//Clyde targets Pacman directly when it is 8 or more tiles away;
//When Clyde gets closer than 8 tile radius, it targets its' home corner.

//SCATTER MODE:
//Clyde targets bottom-left corner of the maze.

const Tile& Clyde::fixate(const Map& map, const Pacman& pacman)
{
	static const int chase_radius = 128;

	switch (current_state_)
	{

		case GhostStates::State::CHASE:
		{
			int pac_x = pacman.getIntX() / TILE_W;
			int pac_y = pacman.getIntY() / TILE_H;

			int clyde_x = static_cast<int>(x_) / TILE_W;
			int clyde_y = static_cast<int>(y_) / TILE_H;

			if (calculateDistance(map.grid[clyde_x][clyde_y], map.grid[pac_x][pac_y]) > chase_radius)
				return map.grid[pac_x][pac_y];
			else
				return map.grid[1][34];
		}

		case GhostStates::State::SCATTER:
		{
			int homecorner_x = 1;
			int homecorner_y = 34;

			return map.grid[homecorner_x][homecorner_y];
		}

		case GhostStates::State::EATEN:
		{
			int above_cage_x = 15;
			int above_cage_y = 16;

			return map.grid[above_cage_x][above_cage_y];
		}

		default:
			return map.grid[0][0];
	}
}