#include "Game.h"

//WHAT:
//A function that renders bonus fruit and points awarded for consuming them based on level.
//Awarded points will only be rendered if a fruit is consumed.

void Game::renderBonusFruit()
{
	if (game_map.grid[15][20].type == Tile::TileType::BONUS)
	{
		switch (level)
		{
		case 1:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[CHERRY]);
			break;
		case 2:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
			break;
		case 3:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[ORANGE]);
			break;
		case 4:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[ORANGE]);
			break;
		case 5:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[APPLE]);
			break;
		case 6:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[APPLE]);
			break;
		case 7:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[MELON]);
			break;
		case 8:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[MELON]);
			break;
		case 9:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
			break;
		case 10:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
			break;
		case 11:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[BELL]);
			break;
		case 12:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[BELL]);
			break;
		default:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.FRUIT_CLIPS[KEY]);
			break;
		}
		
	}


	else if (bonus_score_timer.isRunning())
	{
		switch (level)
		{
		case 1:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_100]);
			break;
		case 2:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_300]);
			break;
		case 3:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_500]);
			break;
		case 4:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_500]);
			break;
		case 5:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_700]);
			break;
		case 6:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_700]);
			break;
		case 7:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_1000]);
			break;
		case 8:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_1000]);
			break;
		case 9:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_2000]);
			break;
		case 10:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_2000]);
			break;
		case 11:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_3000]);
			break;
		case 12:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_3000]);
			break;
		default:
			sprites.render(game_renderer, game_map.grid[15][20].x - 16, game_map.grid[15][20].y - 8, &game_clips.SCORE_CLIPS[SCORE_5000]);
			break;
		}
	}
}