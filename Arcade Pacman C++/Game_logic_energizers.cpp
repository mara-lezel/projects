#include "Game.h"

#include <SDL_Mixer.h>

//WHAT:
//A function that handles energizer logic.

//HOW:
//Energizer is activated after Pacman consumes it;
//Current scatter/chase timer is paused for the duration of fright;
//If an energizer is consumed before another effect ran out, fright timer resets;
//Ghosts are put into frightened state and change speeds;
//After fright, scatter/chase timer is unpaused and
//ghosts put into states before fright.


//USING TIME TABLE COUNTERS:
//Current mode for the ghosts can be determined by looking at phase counters;
//Chase mode always happens after scatter mode and game begins with scatter mode active;
//So if phase counters are equal, current mode is scatter;
//If scatter counter is bigger, current mode is chase.


void Game::activateEnergizers(bool round_reset, bool level_reset)
{
    static bool top_left_energizer = true;
    static bool top_right_energizer = true;
    static bool bottom_left_energizer = true;
    static bool bottom_right_energizer = true;

    if (round_reset)
    {
        fright_timer.stop();
    }
    else if (level_reset)
    {
        fright_timer.stop();

        top_left_energizer = true;
        top_right_energizer = true;
        bottom_left_energizer = true;
        bottom_right_energizer = true;
    }
    else
    {
        if (fright_timer.isRunning())
        {
           
            if (fright_timer.getElapsedTime() >= ghost_time_table.frightPhaseDuration())
            {

                fright_timer.stop();
                freezeScoreAnimation(true);
                handleImpact(true);

                phase_timer.unpause();

                game_sounds.energizer.stop();

                if (ghost_time_table.getScatterCounter() == ghost_time_table.getChaseCounter())
                {
                    if (blinky.getState() == GhostStates::State::CHASE || blinky.getState() == GhostStates::State::FRIGHTENED)
                        blinky.setState(GhostStates::State::SCATTER);
                    if (pinky.getState() == GhostStates::State::CHASE || pinky.getState() == GhostStates::State::FRIGHTENED)
                        pinky.setState(GhostStates::State::SCATTER);
                    if (inky.getState() == GhostStates::State::CHASE || inky.getState() == GhostStates::State::FRIGHTENED)
                        inky.setState(GhostStates::State::SCATTER);
                    if (clyde.getState() == GhostStates::State::CHASE || clyde.getState() == GhostStates::State::FRIGHTENED)
                        clyde.setState(GhostStates::State::SCATTER);
                }

                else
                {
                    if (blinky.getState() == GhostStates::State::SCATTER || blinky.getState() == GhostStates::State::FRIGHTENED)
                        blinky.setState(GhostStates::State::CHASE);
                    if (pinky.getState() == GhostStates::State::SCATTER || pinky.getState() == GhostStates::State::FRIGHTENED)
                        pinky.setState(GhostStates::State::CHASE);
                    if (inky.getState() == GhostStates::State::SCATTER || inky.getState() == GhostStates::State::FRIGHTENED)
                        inky.setState(GhostStates::State::CHASE);
                    if (clyde.getState() == GhostStates::State::SCATTER || clyde.getState() == GhostStates::State::FRIGHTENED)
                        clyde.setState(GhostStates::State::CHASE);
                }
            }
        }



        if (top_left_energizer)
        {
            if (game_map.grid[2][6].type != Tile::TileType::ENERGIZER)
            {
                phase_timer.pause();

                if (fright_timer.isRunning())
                {
                    fright_timer.reset();
                    handleImpact(true);
                    freezeScoreAnimation(true);
                }
                else
                    fright_timer.start();

                if (blinky.getState() == GhostStates::State::CHASE || blinky.getState() == GhostStates::State::SCATTER)
                    blinky.setState(GhostStates::State::FRIGHTENED);
                if (pinky.getState() == GhostStates::State::CHASE || pinky.getState() == GhostStates::State::SCATTER)
                    pinky.setState(GhostStates::State::FRIGHTENED);
                if (inky.getState() == GhostStates::State::CHASE || inky.getState() == GhostStates::State::SCATTER)
                    inky.setState(GhostStates::State::FRIGHTENED);
                if (clyde.getState() == GhostStates::State::CHASE || clyde.getState() == GhostStates::State::SCATTER)
                    clyde.setState(GhostStates::State::FRIGHTENED);

                top_left_energizer = false;

                game_sounds.siren_1.stop();
                game_sounds.siren_2.stop();
                game_sounds.siren_3.stop();
                game_sounds.siren_4.stop();
                game_sounds.siren_5.stop();
                game_sounds.energizer.play(-1);
            }
        }


        if (top_right_energizer)
        {
            if (game_map.grid[27][6].type != Tile::TileType::ENERGIZER)
            {
                phase_timer.pause();

                if (fright_timer.isRunning())
                {
                    fright_timer.reset();
                    handleImpact(true);
                    freezeScoreAnimation(true);
                }
                else
                    fright_timer.start();

                if (blinky.getState() == GhostStates::State::CHASE || blinky.getState() == GhostStates::State::SCATTER)
                    blinky.setState(GhostStates::State::FRIGHTENED);
                if (pinky.getState() == GhostStates::State::CHASE || pinky.getState() == GhostStates::State::SCATTER)
                    pinky.setState(GhostStates::State::FRIGHTENED);
                if (inky.getState() == GhostStates::State::CHASE || inky.getState() == GhostStates::State::SCATTER)
                    inky.setState(GhostStates::State::FRIGHTENED);
                if (clyde.getState() == GhostStates::State::CHASE || clyde.getState() == GhostStates::State::SCATTER)
                    clyde.setState(GhostStates::State::FRIGHTENED);

                top_right_energizer = false;

                game_sounds.siren_1.stop();
                game_sounds.siren_2.stop();
                game_sounds.siren_3.stop();
                game_sounds.siren_4.stop();
                game_sounds.siren_5.stop();
                game_sounds.energizer.play(-1);
            }
        }



        if (bottom_left_energizer)
        {
            if (game_map.grid[2][26].type != Tile::TileType::ENERGIZER)
            {
                phase_timer.pause();

                if (fright_timer.isRunning())
                {
                    fright_timer.reset();
                    handleImpact(true);
                    freezeScoreAnimation(true);
                }
                else
                    fright_timer.start();

                if (blinky.getState() == GhostStates::State::CHASE || blinky.getState() == GhostStates::State::SCATTER)
                    blinky.setState(GhostStates::State::FRIGHTENED);
                if (pinky.getState() == GhostStates::State::CHASE || pinky.getState() == GhostStates::State::SCATTER)
                    pinky.setState(GhostStates::State::FRIGHTENED);
                if (inky.getState() == GhostStates::State::CHASE || inky.getState() == GhostStates::State::SCATTER)
                    inky.setState(GhostStates::State::FRIGHTENED);
                if (clyde.getState() == GhostStates::State::CHASE || clyde.getState() == GhostStates::State::SCATTER)
                    clyde.setState(GhostStates::State::FRIGHTENED);

                bottom_left_energizer = false;

                game_sounds.siren_1.stop();
                game_sounds.siren_2.stop();
                game_sounds.siren_3.stop();
                game_sounds.siren_4.stop();
                game_sounds.siren_5.stop();
                game_sounds.energizer.play(-1);
            }
        }



        if (bottom_right_energizer)
        {
            if (game_map.grid[27][26].type != Tile::TileType::ENERGIZER)
            {
                phase_timer.pause();

                if (fright_timer.isRunning())
                {
                    fright_timer.reset();
                    handleImpact(true);
                    freezeScoreAnimation(true);
                }
                else
                    fright_timer.start();

                if (blinky.getState() == GhostStates::State::CHASE || blinky.getState() == GhostStates::State::SCATTER)
                    blinky.setState(GhostStates::State::FRIGHTENED);
                if (pinky.getState() == GhostStates::State::CHASE || pinky.getState() == GhostStates::State::SCATTER)
                    pinky.setState(GhostStates::State::FRIGHTENED);
                if (inky.getState() == GhostStates::State::CHASE || inky.getState() == GhostStates::State::SCATTER)
                    inky.setState(GhostStates::State::FRIGHTENED);
                if (clyde.getState() == GhostStates::State::CHASE || clyde.getState() == GhostStates::State::SCATTER)
                    clyde.setState(GhostStates::State::FRIGHTENED);

                bottom_right_energizer = false;

                game_sounds.siren_1.stop();
                game_sounds.siren_2.stop();
                game_sounds.siren_3.stop();
                game_sounds.siren_4.stop();
                game_sounds.siren_5.stop();
                game_sounds.energizer.play(-1);
            }
        }
    }
}