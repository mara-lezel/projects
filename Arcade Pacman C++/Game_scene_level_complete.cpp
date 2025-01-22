#include "Game.h"

//WHAT:
//A function that renders level transition - maze flashing in white colour.

//HOW:
//Works by using frames counters to switch layout with different colour;
//One layout will stay on the screen for 12 frames;
//In the given time frame, the maze will flash to white four times.

//NOTE:
//Scenes work in tandem with scene loop, that only does animations (READ "Game_scene_loop.cpp").


void Game::levelCompleteScene()
{
	if (!scene_play_timer.isRunning())
	{
		scene_play_timer.start();

		game_sounds.reset();
	}

	static int frames = 0;

	if (scene_play_timer.getElapsedTime() >= 1.5f)
	{
		++frames;

		if(frames / 12 == 0)
			maze_layout.render(game_renderer, 0, 0, nullptr);
		else
		{
			maze_transition.render(game_renderer, 0, 0, nullptr);

			if(frames == 24)
			frames = 0;
		}

		sprites.render(game_renderer, pacman.getIntX() - 16, pacman.getIntY() - 16, &game_clips.PACMAN_CLIPS_LEFT[0]);
	}
	else
	{
		sprites.render(game_renderer, pacman.getIntX() - 16, pacman.getIntY() - 16, &game_clips.PACMAN_CLIPS_LEFT[0]);
		sprites.render(game_renderer, blinky.getIntX() - 16, blinky.getIntY() - 16, blinky_animation.getCurrentAnimation());
		sprites.render(game_renderer, pinky.getIntX() - 16, pinky.getIntY() - 16, pinky_animation.getCurrentAnimation());
		sprites.render(game_renderer, inky.getIntX() - 16, inky.getIntY() - 16, inky_animation.getCurrentAnimation());
		sprites.render(game_renderer, clyde.getIntX() - 16, clyde.getIntY() - 16, clyde_animation.getCurrentAnimation());
	}

	if (scene_play_timer.getElapsedTime() >= 3.5f)
	{
		frames = 0;

		scene_play_timer.stop();
		scene_playing = false;
	}
}