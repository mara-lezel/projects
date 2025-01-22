#include "Game.h"


//WHAT:
//A function that forces ghosts out of cage based on pellets consumed or a timer.

//HOW:
//INDIVIDUAL COUNTERS
//All ghosts, except Blinky, have individual pellet limit;
//When the number of pellets eaten by Pacman exceed that limit,
//the ghost will be put into transition state and head for the exit.

//Ghost limit values go up in order: PINKY < INKY < CLYDE ;
//By adding the last two limit values when comparing to pellets eaten (dot_counter), pellet counter is effectively reset:
//If Inky's limit is 30 and Clyde's is 60, then after eating 30 pellets or more,
//the next limit target will be 90, same as counting from 0 to 60.

//GLOBAL COUNTER
//After losing a life, individual pellet counters are disabled;
//Instead, a global counter is responsible for forcing ghosts out;
//Global counter checks for three specific values: 7, 17 and 32;
//Global counter tracks continuous dots, no reset needed;
//If Clyde is not in cage when global counter reaches 32, the system cannot be disabled;
//Meaning, for that round ghosts will no longer be forced out by either of the counters;
//If Clyde is in cage at that time, global counter is disabled and individual counters are re-enabled.

//TIMER
//Third measure to force ghosts out is the pellet timer;
//When time since last pellet eaten gets bigger than 4 seconds, one of the ghosts are forced out;
//Order: PINKY -> INKY -> CLYDE;
//Then pellet timer is reset.

void Game::handleInCageGhosts(bool round_reset, bool level_reset)
{

	static int dot_counter_on_reset = 0;

	static bool individual_counters = true;
	static bool global_counter = false;

	if (round_reset)
	{
		dot_counter_on_reset = dot_counter;
		global_counter = true;
		individual_counters = false;
	}

	else if (level_reset)
	{
		global_counter = false;
		individual_counters = true;
	}

	else
	{
		if (individual_counters)
		{
			//BLINKY
			if (blinky.getState() == GhostStates::State::IN_CAGE)
			{
				blinky.setIntCoordinates(game_map.grid[15][17].x, game_map.grid[15][17].mid_y);

				blinky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
				blinky.setDirection(Direction::UP);
			}

			//PINKY
			if (dot_counter >= game_values_table.pinkyDotLimit())
			{
				if (pinky.getState() == GhostStates::State::IN_CAGE)
				{
					pinky.setIntCoordinates(game_map.grid[15][17].x, game_map.grid[15][17].mid_y);

					pinky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
					pinky.setDirection(Direction::UP);
				}
			}

			//INKY
			if (dot_counter >= game_values_table.inkyDotLimit() + game_values_table.pinkyDotLimit())
			{
				if (inky.getState() == GhostStates::State::IN_CAGE)
				{
					inky.setIntCoordinates(game_map.grid[13][17].x, game_map.grid[13][17].mid_y);

					inky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
					inky.setDirection(Direction::RIGHT);
				}
			}

			//CLYDE
			if (dot_counter >= game_values_table.clydeDotLimit() + game_values_table.inkyDotLimit())
			{
				if (clyde.getState() == GhostStates::State::IN_CAGE)
				{
					clyde.setIntCoordinates(game_map.grid[17][17].x, game_map.grid[17][17].mid_y);

					clyde.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
					clyde.setDirection(Direction::LEFT);
				}
			}
		}


		else if (global_counter)
		{
			int global_dot_counter = dot_counter - dot_counter_on_reset;

			//BLINKY
			if (blinky.getState() == GhostStates::State::IN_CAGE)
			{
				blinky.setIntCoordinates(game_map.grid[15][17].x, game_map.grid[15][17].mid_y);

				blinky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
				blinky.setDirection(Direction::UP);
			}

			//PINKY
			if (global_dot_counter == game_values_table.pinkyGlobalDotLimit())
			{
				if (pinky.getState() == GhostStates::State::IN_CAGE)
				{
					pinky.setIntCoordinates(game_map.grid[15][17].x, game_map.grid[15][17].mid_y);

					pinky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
					pinky.setDirection(Direction::UP);
				}
			}

			//INKY
			if (global_dot_counter == game_values_table.inkyGlobalDotLimit())
			{
				if (inky.getState() == GhostStates::State::IN_CAGE)
				{
					inky.setIntCoordinates(game_map.grid[13][17].x, game_map.grid[13][17].mid_y);

					inky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
					inky.setDirection(Direction::RIGHT);
				}
			}

			//CLYDE
			if (global_dot_counter == game_values_table.clydeGlobalDotLimit())
			{
				if (clyde.getState() == GhostStates::State::IN_CAGE)
				{
					clyde.setIntCoordinates(game_map.grid[17][17].x, game_map.grid[17][17].mid_y);

					clyde.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
					clyde.setDirection(Direction::LEFT);

					global_counter = false;
					individual_counters = true;
				}
			}
		}



		if (pellet_timer.getElapsedTime() >= 4.0f)
		{
			//BLINKY IS NEVER LOCKED IN CAGE

			//PINKY
			if (pinky.getState() == GhostStates::State::IN_CAGE)
			{
				pinky.setIntCoordinates(game_map.grid[15][17].x, game_map.grid[15][17].mid_y);

				pinky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
				pinky.setDirection(Direction::UP);

				pellet_timer.reset();
			}

			//INKY
			else if (inky.getState() == GhostStates::State::IN_CAGE)
			{
				inky.setIntCoordinates(game_map.grid[13][17].x, game_map.grid[13][17].mid_y);

				inky.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
				inky.setDirection(Direction::RIGHT);

				pellet_timer.reset();
			}

			//CLYDE
			else if (clyde.getState() == GhostStates::State::IN_CAGE)
			{
				clyde.setIntCoordinates(game_map.grid[17][17].x, game_map.grid[17][17].mid_y);

				clyde.setState(GhostStates::State::IN_TRANSITION_FROM_CAGE);
				clyde.setDirection(Direction::LEFT);

				pellet_timer.reset();
			}
		}
	}
}