#include "Game.h"

//WHAT:
//A function that spawns and manages bonus fruit.

//HOW:
//Bonus fruit appear twice a round;
//First after 70 pellets have been eaten by Pacman, second after 170 pellets;
//After bonus fruit appears, it will stay on the map for 9-10 seconds;
//Bonus fruit can be consumed in that time frame for extra points;
//After fruit has been consumed, bonus_score_timer is started;
//Bonus score timer counts how long the awarded points will stay on screen
//after eating a ghost.

void Game::handleBonusFruit(bool round_reset, bool level_reset)
{
	static bool first_bonus = true;
	static bool second_bonus = true;

	const Tile& pacman_current_tile = game_map.produceCurrentTile(pacman.getPositionX(), pacman.getPositionY());
	Tile& bonus_fruit_tile = game_map.grid[15][20];

	if (round_reset)
	{
		bonus_timer.stop();
		bonus_score_timer.stop();

		bonus_fruit_tile.type = Tile::TileType::EMPTY;
	}


	else if (level_reset)
	{
		first_bonus = true;
		second_bonus = true;

		bonus_timer.stop();
		bonus_score_timer.stop();

		bonus_fruit_tile.type = Tile::TileType::EMPTY;
	}


	else
	{
		if (bonus_timer.isRunning())
		{
			if (bonus_timer.getElapsedTime() >= 9.75f || bonus_fruit_tile.type == Tile::TileType::EMPTY)
			{
				bonus_timer.stop();
				bonus_fruit_tile.type = Tile::TileType::EMPTY;
			}

			else if (pacman_current_tile == bonus_fruit_tile)
			{
				game_score += game_values_table.bonusPoints();

				bonus_fruit_tile.type = Tile::TileType::EMPTY;

				bonus_score_timer.start();

				game_sounds.eat_fruit.play();
			}
		}


		if (first_bonus)
		{
			if (dot_counter >= 70)
			{
				bonus_fruit_tile.type = Tile::TileType::BONUS;
				bonus_timer.start();
				first_bonus = false;
			}
		}

		if (second_bonus)
		{
			if (dot_counter >= 170)
			{
				bonus_fruit_tile.type = Tile::TileType::BONUS;

				if (bonus_timer.isRunning())
					bonus_timer.reset();
				else
					bonus_timer.start();

				second_bonus = false;
			}
		}



		if (bonus_score_timer.isRunning())
		{
			if (bonus_score_timer.getElapsedTime() >= 3.0f)
				bonus_score_timer.stop();
		}
	}
}