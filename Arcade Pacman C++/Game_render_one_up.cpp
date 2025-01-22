#include "Game.h"

//WHAT:
//A function that renders the blinking '1UP' sign at the top of the screen.
//Three different sprites are used and put in an on/off loop instead of an animation.

void Game::renderOneUp()
{
	static int frames = 0;
	++frames;

	if (frames >= 8)
	{
		sprites.render(game_renderer, game_map.grid[4][0].x, game_map.grid[4][0].y, &game_clips.DIGIT_CLIPS[DIGIT_1]);
		sprites.render(game_renderer, game_map.grid[5][0].x, game_map.grid[5][0].y, &game_clips.LETTER_CLIPS[LETTER_U]);
		sprites.render(game_renderer, game_map.grid[6][0].x, game_map.grid[6][0].y, &game_clips.LETTER_CLIPS[LETTER_P]);
	}	

	if (frames == 16)
		frames = 0;
}