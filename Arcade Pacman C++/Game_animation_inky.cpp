#include "Game.h"

//WHAT:
//A function that applies animation to Inky based on direction and/or state.

//HOW:
//CHASE/SCATTER
//Inky will change animation one tile before the actual turn to express change;
//Otherwise there would be no sign where he might go at intersections;
//By getting Inky's next direction, animations can be pre-emtively applied.

//IN CAGE/MOVING FROM CAGE
//Inky will use current direction to change animation for more direct movement.

//FRIGHTENED
//Inky will use fright animation when he is in frightened state outside cage;
//If Inky is in cage state or moving out of cage when fright mode is active,
//he will change animation to frightened (but not the actual state);
//If Inky is moving out of cage after being eaten by Pacman and fright mode is active,
//the fright animation will not be applied and Inky will appear in regular form;

//Frightened ghosts will turn blue and start blinking 2s before reverting.

//EATEN
//Inky will use eaten animation after being eaten by Pacman and while going back to cage;
//This animation will stay until Inky reaches his position in cage.

void Game::handleInkyAnimation()
{
    //REGULAR
    switch (inky.getNextDirection())
    {
    case Direction::RIGHT:
        inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_RIGHT[inky_animation.getCurrentFrame()]);
        break;
    case Direction::LEFT:
        inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_LEFT[inky_animation.getCurrentFrame()]);
        break;
    case Direction::UP:
        inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_UP[inky_animation.getCurrentFrame()]);
        break;
    case Direction::DOWN:
        inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_DOWN[inky_animation.getCurrentFrame()]);
        break;
    default:
        break;
    }

    //IN CAGE
    if (inky.getState() == GhostStates::State::IN_CAGE || inky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
    {
        switch (inky.getDirection())
        {
        case Direction::RIGHT:
            inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_RIGHT[inky_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_LEFT[inky_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_UP[inky_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_DOWN[inky_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }


    //FRIGHTENED
    if (inky.getState() == GhostStates::State::FRIGHTENED || (inky.getState() == GhostStates::State::IN_CAGE && fright_timer.isRunning()) ||
       (inky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE && fright_timer.isRunning() && inky.getPreviousState() != GhostStates::State::EATEN))
    {
        if (fright_timer.getElapsedTime() > ghost_time_table.frightPhaseDuration() - 2.0f)
        {
            if (inky_animation.getCurrentFrame() == 0)
                inky_animation.setCurrentAnimation(&game_clips.FRIGHT_END_CLIPS[inky_animation.getCurrentFrame()]);
            else
                inky_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[inky_animation.getCurrentFrame()]);
        }
        else
            inky_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[inky_animation.getCurrentFrame()]);
    }


    //EATEN
    if (inky.getState() == GhostStates::State::EATEN || inky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        switch (inky.getDirection())
        {
        case Direction::RIGHT:
            inky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_RIGHT[inky_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            inky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_LEFT[inky_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            inky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_UP[inky_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            inky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_DOWN[inky_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }
}