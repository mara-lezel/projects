#include "Game.h"

//WHAT:
//A function that renders game score and high score to the screen.

//HOW:
//If game score is at zero, two zero digits will be rendered;
//Game score is drawn on screen one digit at a time;
//The last digit of the number starts one tile to the right and one tile below 1UP sign;
//As the number grows, the last digit will always hold that place, so game score will grow to the left side.

void Game::renderGameScore()
{
	//INITIAL SCORE
	if (game_score == 0)
	{
		sprites.render(game_renderer, game_map.grid[6][1].x, game_map.grid[6][1].y, &game_clips.DIGIT_CLIPS[DIGIT_0]);
		sprites.render(game_renderer, game_map.grid[7][1].x, game_map.grid[7][1].y, &game_clips.DIGIT_CLIPS[DIGIT_0]);
	}

	//GAMEPLAY SCORE
	else
	{
		int temporary_score = game_score;
		int digit;
		int i = 0;

		while (temporary_score != 0)
		{
			digit = temporary_score % 10;
			temporary_score /= 10;

			sprites.render(game_renderer, game_map.grid[7 - i][1].x, game_map.grid[7 - i][1].y, &game_clips.DIGIT_CLIPS[digit]);
			sprites.render(game_renderer, game_map.grid[17 - i][1].x, game_map.grid[17 - i][1].y, &game_clips.DIGIT_CLIPS[digit]);
			++i;
		}
	}
}