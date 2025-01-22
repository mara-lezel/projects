#include "Game.h"

//WHAT:
//A function that displays player lives left on the bottom left corner.

void Game::renderPacmanLives()
{
	for (int i = 1; i < life_count; i++)
	{
		sprites.render(game_renderer, game_map.grid[1 + i * 2][34].x, game_map.grid[1 + i * 2][34].y, &game_clips.FRUIT_CLIPS[PACMAN_LIFE_ICON]);
	}
}