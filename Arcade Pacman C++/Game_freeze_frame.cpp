#include "Game.h"

//WHAT:
//A function that handles the screen freeze timer after Pacman eats a ghost.

//HOW:
//While screen is frozen, all other timers are paused;
//Freeze lasts for one second, during which, game will only allow ghost eaten state movement;
//Any other movements or systems are paused and will not function.

void Game::freezeFrame()
{
    if (ghost_eaten)
    {
        
        freeze_frame_timer.start();

        fright_timer.pause();
        
        pellet_timer.pause();

        bonus_timer.pause();

        bonus_score_timer.pause();

        if (freeze_frame_timer.getElapsedTime() >= 1.0f)
        {
            ghost_eaten = false;

            freeze_frame_timer.stop();

            fright_timer.unpause();

            pellet_timer.unpause();

            bonus_timer.unpause();

            bonus_score_timer.unpause();
        }
    }
}