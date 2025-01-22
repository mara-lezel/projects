#include "Game.h"

#include <SDL_Mixer.h>

//WHAT:
//A function that renders a scripted transmission scene.
//Pacman and Blinky chasing each other.

//HOW:
//During the scene, all game elements are hidden, except level representation;
//Scene lasts 12 seconds:
//First 4 seconds -- Blinky chasing Pacman from right to left;
//0.4 second break -- for position reset and pacing;
//Last 7.6 seconds -- big Pacman going after frightened Blinky.

//NOTE:
//Unnamed integer literals used to position actors off screen.

void Game::firstTransmissionScene()
{

	if (!scene_play_timer.isRunning())
	{
		scene_play_timer.start();

		game_sounds.intermission.play(2);
	}

	SDL_RenderClear(game_renderer);
	renderLevelRepresentation();

	static float pacman_travel = 0.0f;
	static float blinky_travel = 0.0f;

	static int p_starting_position_x = game_map.grid[29][20].x + 16;
	static int p_starting_position_y = game_map.grid[29][20].y;

	static int b_starting_position_x = game_map.grid[29][20].x + 54;
	static int b_starting_position_y = game_map.grid[29][20].y;

	if (scene_play_timer.getElapsedTime() <= 4.0f)
	{
		sprites.render(game_renderer, p_starting_position_x + static_cast<int>(pacman_travel), p_starting_position_y, pacman_animation.getCurrentAnimation());
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y, blinky_animation.getCurrentAnimation());

		pacman_travel += -2.94f;
		blinky_travel += -3.00f;	
	}

	else if (scene_play_timer.getElapsedTime() <= 4.4f)
	{
		pacman_travel = 0.0f;
		blinky_travel = 0.0f;

		p_starting_position_x = game_map.grid[0][20].x - 475;
		p_starting_position_y = game_map.grid[0][18].y;

		b_starting_position_x = game_map.grid[0][20].x;
	}

	else if (scene_play_timer.getElapsedTime() >= 4.4f)
	{		
		sprites.render(game_renderer, p_starting_position_x + static_cast<int>(pacman_travel), p_starting_position_y,
			big_pacman_animation.getCurrentAnimation());
		sprites.render(game_renderer, b_starting_position_x + static_cast<int>(blinky_travel), b_starting_position_y,
			&game_clips.FRIGHT_CLIPS[blinky_animation.getCurrentFrame()]);

		pacman_travel += 3.0f;
		blinky_travel += 1.6f;
	}

	SDL_Rect hide_left_side = { game_map.grid[0][0].x, game_map.grid[0][0].y, 16, 576 };
	SDL_RenderFillRect(game_renderer, &hide_left_side);

	SDL_Rect hide_right_side = { game_map.grid[29][0].x, game_map.grid[29][0].y, 16, 576 };
	SDL_RenderFillRect(game_renderer, &hide_right_side);

	SDL_Rect hide_fruit = { game_map.grid[21][34].x, game_map.grid[21][34].y, 32, 32 };
	SDL_RenderFillRect(game_renderer, &hide_fruit);



	if (scene_play_timer.getElapsedTime() >= 12.0f)
	{
		pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[0]);
		blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_LEFT[0]);

		scene_play_timer.stop();
		transmission_scene = false;

		game_sounds.intermission.stop();
	}
}