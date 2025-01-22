#include "Game.h"

//WHAT:
//A function that assigns Clyde speeds based on state or current tile.

//MODIFIERS:
//Ghosts have five different speed modifiers:
//1. Regular speed (scatter/chase)
//2. Frightened speed
//3. Tunnel speed (when on tunnel tiles)
//4. Eaten speed (while going back to cage)
//5. Scripted movement speed (in cage, in transition)

void Game::handleClydeSpeed()
{

	switch (clyde.getState())
	{
	case GhostStates::State::CHASE:
		clyde.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::SCATTER:
		clyde.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::FRIGHTENED:
		clyde.setVelocity(speed_table.ghostFright());
		break;
	case GhostStates::State::IN_CAGE:
		clyde.setVelocity(speed_table.ghostCage());
		break;
	case GhostStates::State::IN_TRANSITION_FROM_CAGE:
		clyde.setVelocity(speed_table.ghostTransition());
		break;
	case GhostStates::State::IN_TRANSITION_TO_CAGE:
		clyde.setVelocity(speed_table.ghostEaten());
		break;
	default:
		break;
	}


	//TUNNEL SPEED OVERRIDES ALL MODIFIERS EXCEPT EATEN
	const Tile& clyde_current_tile = game_map.produceCurrentTile(clyde.getPositionX(), clyde.getPositionY());

	if (clyde_current_tile.type == Tile::TileType::TUNNEL)
		clyde.setVelocity(speed_table.ghostTunnel());


	//EATEN SPEED OVERRIDES ANY OTHER MODIFIER
	if (clyde.getState() == GhostStates::State::EATEN)
		clyde.setVelocity(speed_table.ghostEaten());
}