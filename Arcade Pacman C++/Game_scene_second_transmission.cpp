#include "Game.h"

//WHAT:
//A function that renders a scripted transmission scene.
//Blinky tearing his cloak.

//HOW:
//During the scene, all game elements are hidden, except level representation;
//Scene lasts 11 seconds:
//First 3 seconds -- Blinky going after Pacman;
//Every 0.5 second interval after -- Blinky's cloak gets stuck on a nail and starts tearing;
//At 6 second mark -- Blinky's cloak tears, leaving part of his body exposed and cloak part stuck to the object;
//At 8 second mark -- Blinky rolls eyes after that series of events.

//NOTE:
//Unnamed literals used to position actors off screen.

void Game::secondTransmissionScene()
{
	if (!scene_play_timer.isRunning())
	{
		scene_play_timer.start();

		game_sounds.intermission.play(1);
	}


	SDL_RenderClear(game_renderer);
	renderLevelRepresentation();

	static float pacman_travel = 0.0f;
	static float blinky_travel = 0.0f;

	static int p_starting_position_x = game_map.grid[29][20].x + 16;
	static int p_starting_position_y = game_map.grid[29][20].y;

	static int b_starting_position_x = game_map.grid[29][20].x + 176;
	static int b_starting_position_y = game_map.grid[29][20].y;

	if (scene_play_timer.getElapsedTime() <= 3.0f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[NAIL]);
		sprites.render(game_renderer, p_starting_position_x + static_cast<int>(pacman_travel), p_starting_position_y, pacman_animation.getCurrentAnimation());
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, blinky_animation.getCurrentAnimation());

		pacman_travel += -2.98f;
		blinky_travel += -2.52f;
	}
	else if (scene_play_timer.getElapsedTime() <= 3.5f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[STRETCH_1]);
		sprites.render(game_renderer, p_starting_position_x + static_cast<int>(pacman_travel), p_starting_position_y, pacman_animation.getCurrentAnimation());
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, blinky_animation.getCurrentAnimation());

		pacman_travel += -2.98f;
		blinky_travel += -0.25f;
	}
	else if (scene_play_timer.getElapsedTime() <= 4.0f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[STRETCH_2]);
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, blinky_animation.getCurrentAnimation());

		blinky_travel += -0.25f;
	}
	else if (scene_play_timer.getElapsedTime() <= 4.5f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[STRETCH_3]);
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, blinky_animation.getCurrentAnimation());

		blinky_travel += -0.25f;
	}
	else if (scene_play_timer.getElapsedTime() <= 5.1f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[STRETCH_3]);
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, blinky_animation.getCurrentAnimation());

		blinky_travel += -0.25f;
	}
	else if (scene_play_timer.getElapsedTime() <= 6.0f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[STRETCH_3]);
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, &game_clips.BLINKY_CLIPS_LEFT[0]);
	}
	else if (scene_play_timer.getElapsedTime() <= 8.0f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[TORN]);
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, &game_clips.TORN_BLINKY_CLIPS[0]);
	}
	else if (scene_play_timer.getElapsedTime() <= 10.0f)
	{
		sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.BLINKY_CLOAK_TEAR_CLIPS[TORN]);
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, &game_clips.TORN_BLINKY_CLIPS[1]);
	}


	SDL_Rect hide_left_side = { game_map.grid[0][0].x, game_map.grid[0][0].y, 16, 576 };
	SDL_RenderFillRect(game_renderer, &hide_left_side);

	SDL_Rect hide_right_side = { game_map.grid[29][0].x, game_map.grid[29][0].y, 16, 576 };
	SDL_RenderFillRect(game_renderer, &hide_right_side);

	SDL_Rect hide_fruit = { game_map.grid[15][34].x, game_map.grid[15][34].y, 32, 32 };
	SDL_RenderFillRect(game_renderer, &hide_fruit);


	if (scene_play_timer.getElapsedTime() >= 11.0f)
	{
		pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[0]);
		blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_LEFT[0]);

		scene_play_timer.stop();
		transmission_scene = false;
	}
}