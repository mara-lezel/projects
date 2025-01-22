#include "Game.h"


//WHAT:
//A function that handles timers for scatter and chase modes.

//HOW:
//Ghosts in the maze alternate between chase and scatter modes;
//These modes are mutually exclusive;

//phase_timer tracks how much time has elapsed in current phase of current mode.
//When timer reaches set phase duration:
//1. Timer is reset and starts counting time for other mode;
//2. Phase time for a mode is updated to provide next value;
//3. Ghost state change is triggered.

//NOTE:
//When scatter duration lasts only for one frame, ghosts will
//reverse their direction to indicate state change.


void Game::handleModeChanges(bool round_reset)
{
	static bool chase_phase = false;
	static bool scatter_phase = true;

	if (round_reset)
	{
		chase_phase = false;
		scatter_phase = true;

		phase_timer.reset();
		ghost_time_table.reset();
	}
	else
	{
		if (phase_timer.isRunning())
		{
			if (scatter_phase)
			{
				//One frame scatter
				/*if (ghost_time_table.scatterPhaseDuration() < 0.02f)
				{
					blinky.updateMovement(game_map, blinky.b_fixate(game_map, pacman));
					pinky.updateMovement(game_map, pinky.p_fixate(game_map, pacman));
					inky.updateMovement(game_map, inky.i_fixate(game_map, pacman, blinky));
					clyde.updateMovement(game_map, clyde.c_fixate(game_map, pacman));
				}*/


				if (phase_timer.getElapsedTime() >= ghost_time_table.scatterPhaseDuration())
				{
					phase_timer.reset();
					ghost_time_table.updatePhaseScatter();

					if (blinky.getState() == GhostStates::State::SCATTER)
						blinky.setState(GhostStates::State::CHASE);
					if (pinky.getState() == GhostStates::State::SCATTER)
						pinky.setState(GhostStates::State::CHASE);
					if (inky.getState() == GhostStates::State::SCATTER)
						inky.setState(GhostStates::State::CHASE);
					if (clyde.getState() == GhostStates::State::SCATTER)
						clyde.setState(GhostStates::State::CHASE);

					scatter_phase = false;
					chase_phase = true;
				}
			}


			if (chase_phase)
			{
				if (phase_timer.getElapsedTime() >= ghost_time_table.chasePhaseDuration())
				{
					phase_timer.reset();
					ghost_time_table.updatePhaseChase();

					if (blinky.getState() == GhostStates::State::CHASE)
						blinky.setState(GhostStates::State::SCATTER);
					if (pinky.getState() == GhostStates::State::CHASE)
						pinky.setState(GhostStates::State::SCATTER);
					if (inky.getState() == GhostStates::State::CHASE)
						inky.setState(GhostStates::State::SCATTER);
					if (clyde.getState() == GhostStates::State::CHASE)
						clyde.setState(GhostStates::State::SCATTER);

					scatter_phase = true;
					chase_phase = false;
				}
			}
		}
	}
}