#include "Game.h"

#include <SDL_Mixer.h>

//WHAT:
//A function that transitions ghosts from eaten state to their positions in cage.

//HOW:
//When ghosts reach the tile on the left above cage door, they are sent down to cage;
//Ghosts get back in their place in cage differently;
//Blinky and Pinky will be marked as 'in cage', when they reach the center of the cage;
//Blinky and Pinky only go DOWN;
//Inky will be marked as in 'in cage', when he gets back to the left side of the cage;
//Inky uses DOWN to get to the center and LEFT to get back to his side;
//Clyde will be marked as 'in cage', when he gets back to the right side of the cage;
//Clyde used DOWN to get to the center and RIGHT to get back to his side.


void Game::ghostTransitionToCage()
{
	//BLINKY
	if (blinky.getState() == GhostStates::State::EATEN)
	{
		const Tile& blinky_current_tile = game_map.produceCurrentTile(blinky.getPositionX(), blinky.getPositionY());

		if (blinky_current_tile == game_map.grid[14][14])
		{
			blinky.setState(GhostStates::State::IN_TRANSITION_TO_CAGE);
			blinky.setDirection(Direction::DOWN);		
		}
	}

	else if (blinky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
	{
		if (blinky.getIntY() == game_map.grid[15][17].mid_y)
		{
			blinky.setState(GhostStates::State::IN_CAGE);

			if (pinky.getState() != GhostStates::State::EATEN && inky.getState() != GhostStates::State::EATEN && clyde.getState() != GhostStates::State::EATEN)
				game_sounds.retreating.stop();

			if (fright_timer.isRunning())
				game_sounds.energizer.play();
		}
			
	}


	//PINKY
	if (pinky.getState() == GhostStates::State::EATEN)
	{
		const Tile& pinky_current_tile = game_map.produceCurrentTile(pinky.getPositionX(), pinky.getPositionY());

		if (pinky_current_tile == game_map.grid[14][14])
		{
			pinky.setState(GhostStates::State::IN_TRANSITION_TO_CAGE);
			pinky.setDirection(Direction::DOWN);
		}
	}

	else if (pinky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
	{
		if (pinky.getIntY() == game_map.grid[15][17].mid_y)
		{
			pinky.setState(GhostStates::State::IN_CAGE);

			if (blinky.getState() != GhostStates::State::EATEN && inky.getState() != GhostStates::State::EATEN && clyde.getState() != GhostStates::State::EATEN)
				game_sounds.retreating.stop();

			if (fright_timer.isRunning())
				game_sounds.energizer.play();
		}
	}


	//INKY
	if (inky.getState() == GhostStates::State::EATEN)
	{
		const Tile& inky_current_tile = game_map.produceCurrentTile(inky.getPositionX(), inky.getPositionY());

		if (inky_current_tile == game_map.grid[14][14])
		{
			inky.setState(GhostStates::State::IN_TRANSITION_TO_CAGE);
			inky.setDirection(Direction::DOWN);
		}
	}

	else if (inky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
	{
		if (inky.getIntY() == game_map.grid[15][17].mid_y)
		{
			inky.setDirection(Direction::LEFT);

			if(inky.getIntX() == game_map.grid[13][17].x)
			{
				inky.setState(GhostStates::State::IN_CAGE);

				if (blinky.getState() != GhostStates::State::EATEN && pinky.getState() != GhostStates::State::EATEN && clyde.getState() != GhostStates::State::EATEN)
					game_sounds.retreating.stop();

				if (fright_timer.isRunning())
					game_sounds.energizer.play();
			}
		}
	}


	//CLYDE
	if (clyde.getState() == GhostStates::State::EATEN)
	{
		const Tile& clyde_current_tile = game_map.produceCurrentTile(clyde.getPositionX(), clyde.getPositionY());

		if (clyde_current_tile == game_map.grid[14][14])
		{
			clyde.setState(GhostStates::State::IN_TRANSITION_TO_CAGE);
			clyde.setDirection(Direction::DOWN);
		}
	}

	else if (clyde.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
	{
		if (clyde.getIntY() == game_map.grid[15][17].mid_y)
		{
			clyde.setDirection(Direction::RIGHT);

			if (clyde.getIntX() == game_map.grid[17][17].x)
			{
				clyde.setState(GhostStates::State::IN_CAGE);

				if (blinky.getState() != GhostStates::State::EATEN && pinky.getState() != GhostStates::State::EATEN && inky.getState() != GhostStates::State::EATEN)
					game_sounds.retreating.stop();

				if (fright_timer.isRunning())
					game_sounds.energizer.play();
			}
		}
	}
}