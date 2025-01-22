#include "Game.h"

//WHAT:
//A function that assigns speed to Pacman based on current tile.

//MODIFIERS:
//Pacman can have three different speed modifiers:
//1. Regular speed (empty tiles)
//2. Pellet eating speed (pellet tiles)
//3. Ghost chasing speed (after consuming energizer)

//NOTE:
//Pellet eating speed stops Pacman from moving for one frame.

void Game::handlePacmanSpeed()
{

	const Tile& pacman_current_tile = game_map.produceCurrentTile(pacman.getPositionX(), pacman.getPositionY());

	switch (pacman_current_tile.type)
	{
	case Tile::TileType::EMPTY:
	{
		if (fright_timer.isRunning())
			pacman.setVelocity(speed_table.pacmanFright());
		else
			pacman.setVelocity(speed_table.pacman());

		break;
	}

	case Tile::TileType::RED_ZONE_NO_PELLETS:
	{
		if (fright_timer.isRunning())
			pacman.setVelocity(speed_table.pacmanFright());
		else
			pacman.setVelocity(speed_table.pacman());

		break;
	}

	case Tile::TileType::TUNNEL:
	{
		if (fright_timer.isRunning())
			pacman.setVelocity(speed_table.pacmanFright());
		else
			pacman.setVelocity(speed_table.pacman());

		break;
	}

	case Tile::TileType::PELLET:
		pacman.setVelocity(speed_table.pacmanDots());
		break;
	case Tile::TileType::RED_ZONE_PELLETS:
		pacman.setVelocity(speed_table.pacmanDots());
		break;
	case Tile::TileType::ENERGIZER:
		pacman.setVelocity(speed_table.pacmanDots());
		break;
	default:
		break;
	}
}