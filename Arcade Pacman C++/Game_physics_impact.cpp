#include "Game.h"

//WHAT:
//A function that manages Pacman and ghost collision.

//HOW:
//Impact occurs when ghost and Pacman occupy the same tile;
//If ghost is in scatter/chase states, player loses a life;
//If ghost is in fright, its state changes to eaten and he goes back to respawn.


void Game::handleImpact(bool round_reset)
{
	static int ghost_combo = 0;

	if (round_reset)
	{
		ghost_combo = 0;
	}
	else
	{
		const Tile& pacman_current_tile = game_map.produceCurrentTile(pacman.getPositionX(), pacman.getPositionY());

		const Tile& blinky_current_tile = game_map.produceCurrentTile(blinky.getPositionX(), blinky.getPositionY());
		const Tile& pinky_current_tile = game_map.produceCurrentTile(pinky.getPositionX(), pinky.getPositionY());
		const Tile& inky_current_tile = game_map.produceCurrentTile(inky.getPositionX(), inky.getPositionY());
		const Tile& clyde_current_tile = game_map.produceCurrentTile(clyde.getPositionX(), clyde.getPositionY());

		//BLINKY
		if (pacman_current_tile == blinky_current_tile)
		{
			if (blinky.getState() == GhostStates::State::CHASE || blinky.getState() == GhostStates::State::SCATTER)
			{
				life_lost = true;
				scene_playing = true;
			}

			if (blinky.getState() == GhostStates::State::FRIGHTENED)
			{
				blinky.setState(GhostStates::State::EATEN);
				ghost_eaten = true;

				ghost_combo++;
				game_score += game_values_table.ghostPoints(ghost_combo);

				game_sounds.eat_ghost.play();
			}
		}

		//PINKY
		else if (pacman_current_tile == pinky_current_tile)
		{
			if (pinky.getState() == GhostStates::State::CHASE || pinky.getState() == GhostStates::State::SCATTER)
			{
				life_lost = true;
				scene_playing = true;
			}

			if (pinky.getState() == GhostStates::State::FRIGHTENED)
			{
				pinky.setState(GhostStates::State::EATEN);
				ghost_eaten = true;

				ghost_combo++;
				game_score += game_values_table.ghostPoints(ghost_combo);

				game_sounds.eat_ghost.play();
			}
		}

		//INKY
		else if (pacman_current_tile == inky_current_tile)
		{
			if (inky.getState() == GhostStates::State::CHASE || inky.getState() == GhostStates::State::SCATTER)
			{
				life_lost = true;
				scene_playing = true;
			}

			if (inky.getState() == GhostStates::State::FRIGHTENED)
			{
				inky.setState(GhostStates::State::EATEN);
				ghost_eaten = true;

				ghost_combo++;
				game_score += game_values_table.ghostPoints(ghost_combo);

				game_sounds.eat_ghost.play();
			}
		}

		//CLYDE
		else if (pacman_current_tile == clyde_current_tile)
		{
			if (clyde.getState() == GhostStates::State::CHASE || clyde.getState() == GhostStates::State::SCATTER)
			{
				life_lost = true;
				scene_playing = true;
			}

			if (clyde.getState() == GhostStates::State::FRIGHTENED)
			{
				clyde.setState(GhostStates::State::EATEN);
				ghost_eaten = true;

				ghost_combo++;
				game_score += game_values_table.ghostPoints(ghost_combo);

				game_sounds.eat_ghost.play();
			}
		}
	}
}