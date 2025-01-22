#include "Game.h"


void Game::scene_loop()
{
    //ANIMATION
    handleBlinkyAnimation();
    handlePinkyAnimation();
    handleInkyAnimation();
    handleClydeAnimation();

    energizer_animation.setCurrentAnimation(&game_clips.ENERGIZER_CLIPS[energizer_animation.getCurrentFrame()]);

    if (life_lost)
    {
        blinky_animation.animate();
        pinky_animation.animate();
        inky_animation.animate();
        clyde_animation.animate();

        energizer_animation.animate();
    }
    
    if (transmission_scene)
    {
        handlePacmanAnimation();
        pacman_animation.animate();

        big_pacman_animation.setCurrentAnimation(&game_clips.BIG_PACMAN_CLIPS[big_pacman_animation.getCurrentFrame()]);
        big_pacman_animation.animate();

        blinky_animation.animate();

        blinky_retreat_animation.setCurrentAnimation(&game_clips.BLINKY_WITHOUT_CLOAK_CLIPS[blinky_retreat_animation.getCurrentFrame()]);
        blinky_retreat_animation.animate();
    }
    
    if (scene_play_timer.getElapsedTime() >= 1.0f && life_lost)
    {
        pacman_life_lost_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_DEATH[pacman_life_lost_animation.getCurrentFrame()]);
        pacman_life_lost_animation.animate();
    }
}