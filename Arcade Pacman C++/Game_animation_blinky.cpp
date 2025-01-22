#include "Game.h"

//WHAT:
//A function that applies animation to Blinky based on direction and/or state.

//HOW:
//CHASE/SCATTER
//Blinky will change animation one tile before the actual turn to express change;
//Otherwise there would be no sign where he might go at intersections;
//By getting Blinky's next direction, animations can be pre-emtively applied.

//IN CAGE/MOVING FROM CAGE
//Blinky will use current direction to change animation for more direct movement.

//FRIGHTENED
//Blinky will use fright animation when he is in frightened state outside cage;
//If Blinky is moving out of cage after being eaten by Pacman and fright mode is active,
//the fright animation will not be applied and Blinky will appear in regular form;

//Frightened ghosts will turn blue and start blinking 2s before reverting.

//EATEN
//Blinky will use eaten animation after being eaten by Pacman and while going back to cage;
//This animation will stay until Blinky reaches his position in cage.


void Game::handleBlinkyAnimation()
{
    //REGULAR
    switch (blinky.getNextDirection())
    {
    case Direction::RIGHT:
        blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_RIGHT[blinky_animation.getCurrentFrame()]);
        break;
    case Direction::LEFT:
        blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_LEFT[blinky_animation.getCurrentFrame()]);
        break;
    case Direction::UP:
        blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_UP[blinky_animation.getCurrentFrame()]);
        break;
    case Direction::DOWN:
        blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_DOWN[blinky_animation.getCurrentFrame()]);
        break;
    default:
        break;
    }


    //IN CAGE
    if (blinky.getState() == GhostStates::State::IN_CAGE || blinky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
    {
        switch (blinky.getDirection())
        {
        case Direction::RIGHT:
            blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_RIGHT[blinky_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_LEFT[blinky_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_UP[blinky_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_DOWN[blinky_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }


    //FRIGHTENED
    if (blinky.getState() == GhostStates::State::FRIGHTENED ||
       (blinky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE && fright_timer.isRunning() && blinky.getPreviousState() != GhostStates::State::EATEN))
    {
        if (fright_timer.getElapsedTime() > ghost_time_table.frightPhaseDuration() - 2.0f)
        {
            if (blinky_animation.getCurrentFrame() == 0)
                blinky_animation.setCurrentAnimation(&game_clips.FRIGHT_END_CLIPS[blinky_animation.getCurrentFrame()]);
            else
                blinky_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[blinky_animation.getCurrentFrame()]);
        }
        else
            blinky_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[blinky_animation.getCurrentFrame()]);
    }


    //EATEN
    if (blinky.getState() == GhostStates::State::EATEN || blinky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        switch (blinky.getDirection())
        {
        case Direction::RIGHT:
            blinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_RIGHT[blinky_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            blinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_LEFT[blinky_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            blinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_UP[blinky_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            blinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_DOWN[blinky_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }
}