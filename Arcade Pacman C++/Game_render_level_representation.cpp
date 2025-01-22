#include "Game.h"

//WHAT:
//A function that displays fruit icons as level respresentations.
//Up to six icons can be on screen at a time.
//After Level 18 all icons are KEY.

void Game::renderLevelRepresentation()
{

	switch (level)
	{
	case 1:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[CHERRY]);
		break;
	case 2:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[CHERRY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
		break;
	case 3:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[CHERRY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		break;
	case 4:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[CHERRY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		break;
	case 5:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[CHERRY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		break;
	case 6:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[CHERRY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		break;
	case 7:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[STRAWBERRY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		break;
	case 8:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		break;
	case 9:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		break;
	case 10:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		break;
	case 11:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		break;
	case 12:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		break;
	case 13:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		break;
	case 14:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		break;
	case 15:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		break;
	case 16:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		break;
	case 17:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		break;
	default:
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		break;
	}
}