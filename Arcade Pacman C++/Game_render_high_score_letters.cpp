#include "Game.h"

//WHAT:
//A function that renders HIGH SCORE to the screen.

void Game::renderHighScoreLetters()
{
	sprites.render(game_renderer, game_map.grid[10][0].x, game_map.grid[10][0].y, &game_clips.LETTER_CLIPS[LETTER_H]);
	sprites.render(game_renderer, game_map.grid[11][0].x, game_map.grid[11][0].y, &game_clips.LETTER_CLIPS[LETTER_I]);
	sprites.render(game_renderer, game_map.grid[12][0].x, game_map.grid[12][0].y, &game_clips.LETTER_CLIPS[LETTER_G]);
	sprites.render(game_renderer, game_map.grid[13][0].x, game_map.grid[13][0].y, &game_clips.LETTER_CLIPS[LETTER_H]);

	sprites.render(game_renderer, game_map.grid[15][0].x, game_map.grid[15][0].y, &game_clips.LETTER_CLIPS[LETTER_S]);
	sprites.render(game_renderer, game_map.grid[16][0].x, game_map.grid[16][0].y, &game_clips.LETTER_CLIPS[LETTER_C]);
	sprites.render(game_renderer, game_map.grid[17][0].x, game_map.grid[17][0].y, &game_clips.LETTER_CLIPS[LETTER_O]);
	sprites.render(game_renderer, game_map.grid[18][0].x, game_map.grid[18][0].y, &game_clips.LETTER_CLIPS[LETTER_R1]);
	sprites.render(game_renderer, game_map.grid[19][0].x, game_map.grid[19][0].y, &game_clips.LETTER_CLIPS[LETTER_E1]);
}