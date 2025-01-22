#include "Inky.h"
#include "Pacman.h"

#include "Map.h"


//WHAT & HOW:
//A function that determines ghost's current target.
//Makes sure requested tiles aren't outside of game map.

//CHASE MODE:
//Inky targets a tile by doing the following:
//Take a tile 2 tiles ahead of Pacman in current direction;
//Take Blinky's tile;
//Draw a vector from Blinky's tile to a tile ahead of Pacman;
//Extend that vector by the same length;
//The tile at the end of that vector is the target tile.

//QUIRK(from original game):
//When Pacman is moving upwards, tile ahead of Pacman will be 2 tiles ahead AND
//2 tiles to the left.

//NOTE:
//Sections commented with "Without overflow" implement the corrected behaviour.

//SCATTER MODE:
//Inky targets bottom-right corner of the maze.

const Tile& Inky::fixate(const Map& map, const Pacman& pacman, const Ghost& blinky)
{
	static const int tile_offset = 2;

	switch (current_state_)
	{

		case GhostStates::State::CHASE:
		{
			int pac_x = pacman.getIntX() / TILE_W;
			int pac_y = pacman.getIntY() / TILE_H;

			int blinky_x = blinky.getIntX() / TILE_W;
			int blinky_y = blinky.getIntY() / TILE_H;

			switch (pacman.getDirection())
			{
			case Direction::RIGHT:
			{
				if (pac_x + tile_offset > 29)
					pac_x = 29;
				else
					pac_x = pac_x + tile_offset;

				break;
			}

			case Direction::LEFT:
			{
				if (pac_x - tile_offset < 0)
					pac_x = 0;
				else
					pac_x = pac_x - tile_offset;

				break;
			}

			case Direction::UP:
			{

				//Without overflow
				//if (pac_y - tile_offset < 0)
					//pac_y = 0;
				//else
					//pac_y = pac_y - tile_offset;

				//UP & LEFT
				if ((pac_y - tile_offset < 0) && (pac_x - tile_offset < 0))
				{
					pac_y = 0;
					pac_x = 0;
				}

				//LEFT
				else if (pac_x - tile_offset < 0)
					pac_x = 0;

				//UP
				else if (pac_y - tile_offset < 0)
					pac_y = 0;

				else
				{
					pac_y = pac_y - tile_offset;
					pac_x = pac_x - tile_offset;
				}

				break;
			}

			case Direction::DOWN:
			{
				if (pac_y + tile_offset > 35)
					pac_y = 35;
				else
					pac_y = pac_y + tile_offset;

				break;
			}

			default:
				break;
			}

			//Distance between Blinky's tile and ahead of Pacman tile
			int difference_x = pac_x - blinky_x;
			int difference_y = pac_y - blinky_y;

			//By adding that distance, it is projecting target tile
			int target_x = pac_x + difference_x;
			int target_y = pac_y + difference_y;

			if (target_x > 29)
				target_x = 29;

			if (target_x < 0)
				target_x = 0;

			if (target_y < 0)
				target_y = 0;

			if (target_y > 35)
				target_y = 35;

			return map.grid[target_x][target_y];
		}

		case GhostStates::State::SCATTER:
		{
			int homecorner_x = 28;
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