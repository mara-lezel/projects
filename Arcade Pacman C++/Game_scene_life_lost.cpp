#include "Game.h"

//WHAT:
//A function that manages and renders pacman death animation.

//HOW:
//After Pacman collides with a ghost, both entities will stay on screen for a second;
//Then the death animation will play out;
//This scene is followed by the reset scene if any lives are left;
//Otherwise, it is followed by game over screen.

//NOTE:
//Scenes work in tandem with scene loop, that only does animations (READ "Game_scene_loop.cpp").


void Game::lifeLostScene()
{
    if (!scene_play_timer.isRunning())
    {
        scene_play_timer.start();

        game_sounds.reset();
    }

	if (scene_play_timer.getElapsedTime() >= 1.0f)
	{
        if (scene_play_timer.getElapsedTime() <= 2.0f)
        {
            if (!game_sounds.death_1.isPlaying())
                game_sounds.death_1.play();
        }
        
        if (scene_play_timer.getElapsedTime() >= 2.19f && scene_play_timer.getElapsedTime() <= 2.29f)
        {
            game_sounds.death_1.stop();

            game_sounds.death_2.play(1);
        }


        if (scene_play_timer.getElapsedTime() <= 2.1f)
        {
            sprites.render(game_renderer, pacman.getIntX() - 16, pacman.getIntY() - 16, pacman_life_lost_animation.getCurrentAnimation());
        }
        else if (scene_play_timer.getElapsedTime() >= 3.0f)
        {
            pacman_life_lost_animation.setFrameCount(0);
            scene_play_timer.stop();

            scene_playing = false;
        }      
	}
    else
    {
        sprites.render(game_renderer, pacman.getIntX() - 16, pacman.getIntY() - 16, pacman_animation.getCurrentAnimation());
        sprites.render(game_renderer, blinky.getIntX() - 16, blinky.getIntY() - 16, blinky_animation.getCurrentAnimation());
        sprites.render(game_renderer, pinky.getIntX() - 16, pinky.getIntY() - 16, pinky_animation.getCurrentAnimation());
        sprites.render(game_renderer, inky.getIntX() - 16, inky.getIntY() - 16, inky_animation.getCurrentAnimation());
        sprites.render(game_renderer, clyde.getIntX() - 16, clyde.getIntY() - 16, clyde_animation.getCurrentAnimation());
    }
}