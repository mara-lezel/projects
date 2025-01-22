#include "Game.h"


//WHAT:
//A function that assigns state and direction to ghosts leaving the cage.

//HOW:
//Based on whether an energizer has been consumed while ghost is in the cage,
//ghost will move either left or right:
//LEFT - no energizers were eaten by Pacman;
//RIGHT - one or more energizers were eaten by Pacman;

//Ghost will be considered as 'leaving the cage' if:
//Ghost is currently flagged as in transition;
//Ghost is directly above the cage exit.

//Ghost will be assigned a state based on current phase:
//SCATTER / CHASE - depending on phase counter (READ "Game_logic_energizers.cpp");
//FRIGHTENED - if fright is currently in effect.


void Game::ghostTransitionToMaze(bool round_reset, bool level_reset)
{
	static bool top_left_energizer = true;
	static bool top_right_energizer = true;
	static bool bottom_left_energizer = true;
	static bool bottom_right_energizer = true;

	static bool energizer_consumed = false;

	if (round_reset)
	{
		energizer_consumed = false;
	}
	else if (level_reset)
	{
		top_left_energizer = true;
		top_right_energizer = true;
		bottom_left_energizer = true;
		bottom_right_energizer = true;

		energizer_consumed = false;
	}
	else
	{
		if (!energizer_consumed)
		{
			if (top_left_energizer)
			{
				if (game_map.grid[2][6].type != Tile::TileType::ENERGIZER)
				{
					top_left_energizer = false;
					energizer_consumed = true;
				}
			}

			if (top_right_energizer)
			{
				if (game_map.grid[27][6].type != Tile::TileType::ENERGIZER)
				{
					top_right_energizer = false;
					energizer_consumed = true;
				}
			}

			if (bottom_left_energizer)
			{
				if (game_map.grid[2][26].type != Tile::TileType::ENERGIZER)
				{
					bottom_left_energizer = false;
					energizer_consumed = true;
				}
			}

			if (bottom_right_energizer)
			{
				if (game_map.grid[27][26].type != Tile::TileType::ENERGIZER)
				{
					bottom_right_energizer = false;
					energizer_consumed = true;
				}
			}
		}


		//------------------------------------------------------------------------BLINKY--------------------------
		//--------------------------------------------------------------------------------------------------------

		if (blinky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
		{
			if (blinky.getIntY() == game_map.grid[15][14].mid_y)
			{
				//Respawned ghosts don't go into fright again
				if (fright_timer.isRunning() && (blinky.getPreviousState() != GhostStates::State::EATEN))
					blinky.setState(GhostStates::State::FRIGHTENED);

				else
				{
					if (ghost_time_table.getScatterCounter() == ghost_time_table.getChaseCounter())
						blinky.setState(GhostStates::State::SCATTER);
					else
						blinky.setState(GhostStates::State::CHASE);
				}


				if (energizer_consumed)
				{
					blinky.setDirection(Direction::RIGHT);
					blinky.setNextDirection(Direction::RIGHT);
				}
				else
				{
					blinky.setDirection(Direction::LEFT);
					blinky.setNextDirection(Direction::LEFT);
				}
			}
		}


		//------------------------------------------------------------------------PINKY---------------------------
		//--------------------------------------------------------------------------------------------------------

		if (pinky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
		{
			if (pinky.getIntY() == game_map.grid[15][14].mid_y)
			{
				if (fright_timer.isRunning() && (pinky.getPreviousState() != GhostStates::State::EATEN))
					pinky.setState(GhostStates::State::FRIGHTENED);

				else
				{
					if (ghost_time_table.getScatterCounter() == ghost_time_table.getChaseCounter())
						pinky.setState(GhostStates::State::SCATTER);
					else
						pinky.setState(GhostStates::State::CHASE);
				}


				if (energizer_consumed)
				{
					pinky.setDirection(Direction::RIGHT);
					pinky.setNextDirection(Direction::RIGHT);
				}
				else
				{
					pinky.setDirection(Direction::LEFT);
					pinky.setNextDirection(Direction::LEFT);
				}
			}
		}


		//------------------------------------------------------------------------INKY----------------------------
		//--------------------------------------------------------------------------------------------------------

		if (inky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
		{
			if (inky.getIntY() == game_map.grid[15][14].mid_y)
			{
				if (fright_timer.isRunning() && (inky.getPreviousState() != GhostStates::State::EATEN))
					inky.setState(GhostStates::State::FRIGHTENED);

				else
				{
					if (ghost_time_table.getScatterCounter() == ghost_time_table.getChaseCounter())
						inky.setState(GhostStates::State::SCATTER);
					else
						inky.setState(GhostStates::State::CHASE);
				}


				if (energizer_consumed)
				{
					inky.setDirection(Direction::RIGHT);
					inky.setNextDirection(Direction::RIGHT);
				}
				else
				{
					inky.setDirection(Direction::LEFT);
					inky.setNextDirection(Direction::LEFT);
				}
			}
		}


		//------------------------------------------------------------------------CLYDE---------------------------
		//--------------------------------------------------------------------------------------------------------

		if (clyde.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
		{
			if (clyde.getIntY() == game_map.grid[15][14].mid_y)
			{
				if (fright_timer.isRunning() && (clyde.getPreviousState() != GhostStates::State::EATEN))
					clyde.setState(GhostStates::State::FRIGHTENED);

				else
				{
					if (ghost_time_table.getScatterCounter() == ghost_time_table.getChaseCounter())
						clyde.setState(GhostStates::State::SCATTER);
					else
						clyde.setState(GhostStates::State::CHASE);
				}


				if (energizer_consumed)
				{
					clyde.setDirection(Direction::RIGHT);
					clyde.setNextDirection(Direction::RIGHT);
				}
				else
				{
					clyde.setDirection(Direction::LEFT);
					clyde.setNextDirection(Direction::LEFT);
				}
			}
		}
	}
}