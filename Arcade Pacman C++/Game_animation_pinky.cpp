#include "Game.h"

//WHAT:
//A function that applies animation to Pinky based on direction and/or state.

//HOW:
//CHASE/SCATTER
//Pinky will change animation one tile before the actual turn to express change;
//Otherwise there would be no sign where he might go at intersections;
//By getting Pinky's next direction, animations can be pre-emtively applied.

//IN CAGE/MOVING FROM CAGE
//Pinky will use current direction to change animation for more direct movement.

//FRIGHTENED
//Pinky will use fright animation when he is in frightened state outside cage;
//If Pinky is in cage state or moving out of cage when fright mode is active,
//he will change animation to frightened (but not the actual state);
//If Pinky is moving out of cage after being eaten by Pacman and fright mode is active,
//the fright animation will not be applied and Pinky will appear in regular form;

//Frightened ghosts will turn blue and start blinking 2s before reverting.

//EATEN
//Pinky will use eaten animation after being eaten by Pacman and while going back to cage;
//This animation will stay until Pinky reaches his position in cage.


void Game::handlePinkyAnimation()
{
    //REGULAR
    switch (pinky.getNextDirection())
    {
    case Direction::RIGHT:
        pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_RIGHT[pinky_animation.getCurrentFrame()]);
        break;
    case Direction::LEFT:
        pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_LEFT[pinky_animation.getCurrentFrame()]);
        break;
    case Direction::UP:
        pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_UP[pinky_animation.getCurrentFrame()]);
        break;
    case Direction::DOWN:
        pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_DOWN[pinky_animation.getCurrentFrame()]);
        break;
    default:
        break;
    }


    //IN CAGE
    if (pinky.getState() == GhostStates::State::IN_CAGE || pinky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
    {
        switch (pinky.getDirection())
        {
        case Direction::RIGHT:
            pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_RIGHT[pinky_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_LEFT[pinky_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_UP[pinky_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_DOWN[pinky_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }


    //FRIGHTENED
    if (pinky.getState() == GhostStates::State::FRIGHTENED || (pinky.getState() == GhostStates::State::IN_CAGE && fright_timer.isRunning()) ||
       (pinky.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE && fright_timer.isRunning() && pinky.getPreviousState() != GhostStates::State::EATEN))
    {
        if (fright_timer.getElapsedTime() > ghost_time_table.frightPhaseDuration() - 2.0f)
        {
            if (pinky_animation.getCurrentFrame() == 0)
                pinky_animation.setCurrentAnimation(&game_clips.FRIGHT_END_CLIPS[pinky_animation.getCurrentFrame()]);
            else
                pinky_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[pinky_animation.getCurrentFrame()]);
        }
        else
            pinky_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[pinky_animation.getCurrentFrame()]);
    }


    //EATEN
    if (pinky.getState() == GhostStates::State::EATEN || pinky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        switch (pinky.getDirection())
        {
        case Direction::RIGHT:
            pinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_RIGHT[pinky_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            pinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_LEFT[pinky_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            pinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_UP[pinky_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            pinky_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_DOWN[pinky_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }
}