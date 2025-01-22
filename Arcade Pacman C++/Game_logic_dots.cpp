#include "Game.h"

//WHAT:
//A function that tracks the number of pellets eaten and handles pellet associated game elements.

//HOW:
//If Pacman is standing on a tile containing a pellet or energizer,
//dot counter is increased by one (that tile is marked as empty on the same frame (READ "Pacman_misc.cpp"));
//Eating a pellet awards 10 pts and eating an energizer awards 50 pts;
//Every time a pellet is consumed, pellet timer (used for determining ghost exit times from cage) resets.

void Game::countDots()
{

	const Tile& current_pacman_tile = game_map.produceCurrentTile(pacman.getPositionX(), pacman.getPositionY());

	if (current_pacman_tile.type == Tile::TileType::PELLET || current_pacman_tile.type == Tile::TileType::RED_ZONE_PELLETS)
	{
		dot_counter++;
		game_score += 10;

		if (dot_counter % 2 == 0)
			game_sounds.munch_2.play();
		else
			game_sounds.munch_1.play();

		pellet_timer.reset();
	}

	if (current_pacman_tile.type == Tile::TileType::ENERGIZER)
	{
		dot_counter++;
		game_score += 50;

		if (dot_counter % 2 == 0)
			game_sounds.munch_2.play();
		else
			game_sounds.munch_1.play();

		pellet_timer.reset();
	}

	if (dot_counter == dot_total)
	{
		level_complete = true;
		scene_playing = true;
	}


	if (dot_counter < 122)
	{
		if (!game_sounds.siren_1.isPlaying() && !game_sounds.energizer.isPlaying() && !game_sounds.retreating.isPlaying())
			game_sounds.siren_1.play(-1);
	}
	else if (dot_counter < 180)
	{
		if (!game_sounds.siren_2.isPlaying() && !game_sounds.energizer.isPlaying() && !game_sounds.retreating.isPlaying())
		{
			game_sounds.siren_1.stop();

			game_sounds.siren_2.play(-1);
		}
	}
	else if (dot_counter < 213)
	{
		if (!game_sounds.siren_3.isPlaying() && !game_sounds.energizer.isPlaying() && !game_sounds.retreating.isPlaying())
		{
			game_sounds.siren_2.stop();

			game_sounds.siren_3.play(-1);
		}
	}
	else if (dot_counter < 228)
	{
		if (!game_sounds.siren_4.isPlaying() && !game_sounds.energizer.isPlaying() && !game_sounds.retreating.isPlaying())
		{
			game_sounds.siren_3.stop();

			game_sounds.siren_4.play(-1);
		}
	}
	else
	{
		if (!game_sounds.siren_5.isPlaying() && !game_sounds.energizer.isPlaying() && !game_sounds.retreating.isPlaying())
		{
			game_sounds.siren_4.stop();

			game_sounds.siren_5.play(-1);
		}
	}
}