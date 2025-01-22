#include "Game.h"


//WHAT:
//A function that renders a scripted transmission scene.
//Blinky dragging his cloak while retreating.

//HOW:
//During the scene, all game elements are hidden, except level representation;
//Scene lasts 10 seconds:
//First 4 seconds -- patched up Blinky chasing Pacman;
//Last 4 seconds -- Blinky dragging his cloak and retreating.

//NOTE:
//Unnamed literals used to position actors off screen.

void Game::thirdTransmissionScene()
{
	if (!scene_play_timer.isRunning())
	{
		scene_play_timer.start();

		game_sounds.intermission.play(1);
	}

	SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
	SDL_RenderClear(game_renderer);

	static float pacman_travel = 0.0f;
	static float blinky_travel = 0.0f;

	static int p_starting_position_x = game_map.grid[29][20].x + 16;
	static int p_starting_position_y = game_map.grid[29][20].y;

	static int b_starting_position_x = game_map.grid[29][20].x + 112;
	static int b_starting_position_y = game_map.grid[29][20].y;

	if (scene_play_timer.getElapsedTime() <= 4.0f)
	{
		sprites.render(game_renderer, p_starting_position_x + static_cast<int>(pacman_travel), p_starting_position_y, pacman_animation.getCurrentAnimation());
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel),
			b_starting_position_y, &game_clips.PATCHED_BLINKY_CLIPS[blinky_animation.getCurrentFrame()]);

		pacman_travel += -3.0f;
		blinky_travel += -3.0f;
	}
	else if (scene_play_timer.getElapsedTime() >= 5.0f)
	{
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel),
			b_starting_position_y, blinky_retreat_animation.getCurrentAnimation());

		blinky_travel += 2.5f;
	}

	SDL_Rect hide_left_side = { game_map.grid[0][0].x, game_map.grid[0][0].y, 16, 576 };
	SDL_RenderFillRect(game_renderer, &hide_left_side);

	SDL_Rect hide_right_side = { game_map.grid[29][0].x, game_map.grid[29][0].y, 16, 576 };
	SDL_RenderFillRect(game_renderer, &hide_right_side);

	if (level == 10)
	{
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[ORANGE]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[APPLE]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
	}
	else if (level == 14)
	{
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[MELON]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[GALAXIAN_BOSS]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
	}
	else if (level == 18)
	{
		sprites.render(game_renderer, game_map.grid[25][34].x, game_map.grid[25][34].y, &game_clips.FRUIT_CLIPS[BELL]);
		sprites.render(game_renderer, game_map.grid[23][34].x, game_map.grid[23][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[21][34].x, game_map.grid[21][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[19][34].x, game_map.grid[19][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[17][34].x, game_map.grid[17][34].y, &game_clips.FRUIT_CLIPS[KEY]);
		sprites.render(game_renderer, game_map.grid[15][34].x, game_map.grid[15][34].y, &game_clips.FRUIT_CLIPS[KEY]);
	}

	if (scene_play_timer.getElapsedTime() >= 10.0f)
	{
		pacman_travel = 0.0f;
		blinky_travel = 0.0f;

		pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[0]);
		blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_LEFT[0]);

		scene_play_timer.stop();
		transmission_scene = false;

		game_sounds.intermission.stop();
	}
}