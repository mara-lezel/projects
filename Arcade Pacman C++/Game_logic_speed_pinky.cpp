#include "Game.h"

//WHAT:
//A function that assigns Pinky speeds based on state or current tile.

//MODIFIERS:
//Ghosts have five different speed modifiers:
//1. Regular speed (scatter/chase)
//2. Frightened speed
//3. Tunnel speed (when on tunnel tiles)
//4. Eaten speed (while going back to cage)
//5. Scripted movement speed (in cage, in transition)


void Game::handlePinkySpeed()
{

	switch (pinky.getState())
	{
	case GhostStates::State::CHASE:
		pinky.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::SCATTER:
		pinky.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::FRIGHTENED:
		pinky.setVelocity(speed_table.ghostFright());
		break;
	case GhostStates::State::IN_CAGE:
		pinky.setVelocity(speed_table.ghostCage());
		break;
	case GhostStates::State::IN_TRANSITION_FROM_CAGE:
		pinky.setVelocity(speed_table.ghostTransition());
		break;
	case GhostStates::State::IN_TRANSITION_TO_CAGE:
		pinky.setVelocity(speed_table.ghostEaten());
		break;
	default:
		break;
	}


	//TUNNEL SPEED OVERRIDES ALL MODIFIERS EXCEPT EATEN
	const Tile& pinky_current_tile = game_map.produceCurrentTile(pinky.getPositionX(), pinky.getPositionY());

	if (pinky_current_tile.type == Tile::TileType::TUNNEL)
		pinky.setVelocity(speed_table.ghostTunnel());


	//EATEN SPEED OVERRIDES ANY OTHER MODIFIER
	if (pinky.getState() == GhostStates::State::EATEN)
		pinky.setVelocity(speed_table.ghostEaten());
}