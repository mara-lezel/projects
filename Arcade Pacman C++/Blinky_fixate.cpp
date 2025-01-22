#include "Blinky.h"
#include "Pacman.h"

#include "Map.h"

//WHAT:
//A function that determines ghost's current target.

//CHASE MODE:
//Blinky targets Pacman directly.

//SCATTER MODE:
//Blinky targets top-right corner of the maze.

const Tile& Blinky::fixate(const Map& map, const Pacman& pacman)
{
	switch (current_state_)
	{
	case GhostStates::State::CHASE:
	{
		int pac_x = pacman.getIntX() / TILE_W;
		int pac_y = pacman.getIntY() / TILE_H;

		return map.grid[pac_x][pac_y];
	}

	case GhostStates::State::SCATTER:
	{
		int homecorner_x = 26;
		int homecorner_y = 0;

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