#include "Game.h"

//WHAT:
//A function that assigns Blinky speeds based on state or current tile.
//Blinky's speed also changes depending on the number of pellets left in the maze.

//MODIFIERS:
//Ghosts have five different speed modifiers:
//1. Regular speed (scatter/chase)
//2. Frightened speed
//3. Tunnel speed (when on tunnel tiles)
//4. Eaten speed (while going back to cage)
//5. Scripted movement speed (in cage, in transition)

//Blinky has two extra speed modifiers:
//1. Cruise Elroy (after first pellet threshold is met)
//2. Cruise Elroy Super (after second pellet threshold is met)

void Game::handleBlinkySpeed()
{

	switch (blinky.getState())
	{
	case GhostStates::State::CHASE:
		blinky.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::SCATTER:
		blinky.setVelocity(speed_table.ghost());
		break;
	case GhostStates::State::FRIGHTENED:
		blinky.setVelocity(speed_table.ghostFright());
		break;
	case GhostStates::State::IN_CAGE:
		blinky.setVelocity(speed_table.ghostCage());
		break;
	case GhostStates::State::IN_TRANSITION_FROM_CAGE:
		blinky.setVelocity(speed_table.ghostTransition());
		break;
	case GhostStates::State::IN_TRANSITION_TO_CAGE:
		blinky.setVelocity(speed_table.ghostEaten());
		break;
	default:
		break;
	}


	//STILL NEEDS FIXING
	//CRUISE ELROY SPEED
	if (dot_total - dot_counter <= game_values_table.elroyDotCount() && blinky.getState() != GhostStates::State::FRIGHTENED
		&& clyde.getState() != GhostStates::State::IN_CAGE)
	{
		if (dot_total - dot_counter <= game_values_table.superElroyDotCount())
			blinky.setVelocity(speed_table.elroySuper());
		else
			blinky.setVelocity(speed_table.elroy());
	}


	//TUNNEL SPEED OVERRIDES ALL MODIFIERS EXCEPT EATEN
	const Tile& blinky_current_tile = game_map.produceCurrentTile(blinky.getPositionX(), blinky.getPositionY());

	if (blinky_current_tile.type == Tile::TileType::TUNNEL)
		blinky.setVelocity(speed_table.ghostTunnel());


	//EATEN SPEED OVERRIDES ANY OTHER MODIFIER
	if (blinky.getState() == GhostStates::State::EATEN)
		blinky.setVelocity(speed_table.ghostEaten());
}