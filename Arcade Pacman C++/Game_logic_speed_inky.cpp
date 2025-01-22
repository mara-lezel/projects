#include "Game.h"

//WHAT:
//A function that assigns Inky speeds based on state or current tile.

//MODIFIERS:
//Ghosts have five different speed modifiers:
//1. Regular speed (scatter/chase)
//2. Frightened speed
//3. Tunnel speed (when on tunnel tiles)
//4. Eaten speed (while going back to cage)
//5. Scripted movement speed (in cage, in transition)


void Game::handleInkySpeed()
{

	switch (inky.getState())
	{
	case GhostStates::State::CHASE:
		inky.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::SCATTER:
		inky.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::FRIGHTENED:
		inky.setVelocity(speed_table.ghostFright());
		break;
	case GhostStates::State::IN_CAGE:
		inky.setVelocity(speed_table.ghostCage());
		break;
	case GhostStates::State::IN_TRANSITION_FROM_CAGE:
		inky.setVelocity(speed_table.ghostTransition());
		break;
	case GhostStates::State::IN_TRANSITION_TO_CAGE:
		inky.setVelocity(speed_table.ghostEaten());
	default:
		break;
	}


	//TUNNEL SPEED OVERRIDES ALL MODIFIERS EXCEPT EATEN
	const Tile& inky_current_tile = game_map.produceCurrentTile(inky.getPositionX(), inky.getPositionY());

	if (inky_current_tile.type == Tile::TileType::TUNNEL)
		inky.setVelocity(speed_table.ghostTunnel());


	//EATEN SPEED OVERRIDES ANY OTHER MODIFIER
	if (inky.getState() == GhostStates::State::EATEN)
		inky.setVelocity(speed_table.ghostEaten());
}