#include "Game.h"

//WHAT:
//A function that applies the score animation to an eaten ghost.

//HOW:
//Every time a fright mode is active, Pacman can eat up to four ghosts;
//When a ghost is eaten a number of points awarded will appear in his place;
//Awarded points will be reset once that fright phase ends.

//NOTE:
//Points are awarded by another function (READ "Game_physics_impact.cpp").

void Game::freezeScoreAnimation(bool round_reset)
{
    static bool blinky_eaten = false;
    static bool pinky_eaten = false;
    static bool inky_eaten = false;
    static bool clyde_eaten = false;

    static int ghost_combo = 0;

    if (round_reset)
    {
        blinky_eaten = false;
        pinky_eaten = false;
        inky_eaten = false;
        clyde_eaten = false;
        ghost_combo = 0;
    }
    else
    {
        if (!blinky_eaten)
        {
            if (blinky.getPreviousState() != GhostStates::State::EATEN && blinky.getState() == GhostStates::State::EATEN)
            {
                blinky_animation.setCurrentAnimation(&game_clips.SCORE_CLIPS[ghost_combo]);

                ghost_combo++;

                blinky_eaten = true;

                if (!game_sounds.retreating.isPlaying())
                {
                    game_sounds.energizer.stop();
                    game_sounds.retreating.play(-1);
                }
            }
        }

        if (!pinky_eaten)
        {
            if (pinky.getPreviousState() != GhostStates::State::EATEN && pinky.getState() == GhostStates::State::EATEN)
            {
                pinky_animation.setCurrentAnimation(&game_clips.SCORE_CLIPS[ghost_combo]);

                ghost_combo++;

                pinky_eaten = true;
                

                if (!game_sounds.retreating.isPlaying())
                {
                    game_sounds.energizer.stop();
                    game_sounds.retreating.play(-1);
                }
            }
        }

        if (!inky_eaten)
        {
            if (inky.getPreviousState() != GhostStates::State::EATEN && inky.getState() == GhostStates::State::EATEN)
            {
                inky_animation.setCurrentAnimation(&game_clips.SCORE_CLIPS[ghost_combo]);

                ghost_combo++;

                inky_eaten = true;

                if (!game_sounds.retreating.isPlaying())
                {
                    game_sounds.energizer.stop();
                    game_sounds.retreating.play(-1);
                }
            }
        }

        if (!clyde_eaten)
        {
            if (clyde.getPreviousState() != GhostStates::State::EATEN && clyde.getState() == GhostStates::State::EATEN)
            {
                clyde_animation.setCurrentAnimation(&game_clips.SCORE_CLIPS[ghost_combo]);

                ghost_combo++;

                clyde_eaten = true;

                if (!game_sounds.retreating.isPlaying())
                {
                    game_sounds.energizer.stop();
                    game_sounds.retreating.play(-1);
                }
            }
        }
    }
}