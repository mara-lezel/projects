#include "Game.h"

//WHAT:
//A function that manages game states and scenes by handling game flags.

void Game::manageGameFlags()
{
    if (life_lost)
    {
        if (!scene_playing)
        {
            round_reset();
            life_count--;

            if (game_score == 0)
                handleInCageGhosts(false, true);
        }
    }
    else if (level_complete)
    {
        if (!scene_playing)
            level_reset();
    }
    else if (life_count == 0 && !eternal_mode)
    {
        scene_playing = true;
        game_sounds.reset();
    }
}