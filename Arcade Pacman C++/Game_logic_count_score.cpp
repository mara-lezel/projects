#include "Game.h"

//WHAT:
//A function that awards an extra life when player hits 10 000pts score.
//This award is only given once throughout the whole game.

void Game::countScore()
{
	static bool one_up = false;

	if (!one_up)
	{
		if (game_score >= 10000)
		{
			life_count++;
			one_up = true;	

			game_sounds.bonus_life.play();
		}
	}
}