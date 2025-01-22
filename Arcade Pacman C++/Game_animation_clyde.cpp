#include "Game.h"

//WHAT:
//A function that applies animation to Clyde based on direction and/or state.

//HOW:
//CHASE/SCATTER
//Clyde will change animation one tile before the actual turn to express change;
//Otherwise there would be no sign where he might go at intersections;
//By getting Clyde's next direction, animations can be pre-emtively applied.

//IN CAGE/MOVING FROM CAGE
//Clyde will use current direction to change animation for more direct movement.

//FRIGHTENED
//Clyde will use fright animation when he is in frightened state outside cage;
//If Clyde is in cage state or moving out of cage when fright mode is active,
//he will change animation to frightened (but not the actual state);
//If Clyde is moving out of cage after being eaten by Pacman and fright mode is active,
//the fright animation will not be applied and Clyde will appear in regular form;

//Frightened ghosts will turn blue and start blinking 2s before reverting.

//EATEN
//Clyde will use eaten animation after being eaten by Pacman and while going back to cage;
//This animation will stay until Clyde reaches his position in cage.

void Game::handleClydeAnimation()
{
    //REGULAR
    switch (clyde.getNextDirection())
    {
    case Direction::RIGHT:
        clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_RIGHT[clyde_animation.getCurrentFrame()]);
        break;
    case Direction::LEFT:
        clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_LEFT[clyde_animation.getCurrentFrame()]);
        break;
    case Direction::UP:
        clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_UP[clyde_animation.getCurrentFrame()]);
        break;
    case Direction::DOWN:
        clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_DOWN[clyde_animation.getCurrentFrame()]);
        break;
    default:
        break;
    }


    //IN CAGE
    if (clyde.getState() == GhostStates::State::IN_CAGE || clyde.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE)
    {
        switch (clyde.getDirection())
        {
        case Direction::RIGHT:
            clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_RIGHT[clyde_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_LEFT[clyde_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_UP[clyde_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_DOWN[clyde_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }


    //FRIGHTENED
    if (clyde.getState() == GhostStates::State::FRIGHTENED || (clyde.getState() == GhostStates::State::IN_CAGE && fright_timer.isRunning()) ||
       (clyde.getState() == GhostStates::State::IN_TRANSITION_FROM_CAGE && fright_timer.isRunning() && clyde.getPreviousState() != GhostStates::State::EATEN))
    {
        if (fright_timer.getElapsedTime() > ghost_time_table.frightPhaseDuration() - 2.0f)
        {
            if (clyde_animation.getCurrentFrame() == 0)
                clyde_animation.setCurrentAnimation(&game_clips.FRIGHT_END_CLIPS[clyde_animation.getCurrentFrame()]);
            else
                clyde_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[clyde_animation.getCurrentFrame()]);
        }
        else
            clyde_animation.setCurrentAnimation(&game_clips.FRIGHT_CLIPS[clyde_animation.getCurrentFrame()]);
    }


    //EATEN
    if (clyde.getState() == GhostStates::State::EATEN || clyde.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        switch (clyde.getDirection())
        {
        case Direction::RIGHT:
            clyde_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_RIGHT[clyde_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            clyde_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_LEFT[clyde_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            clyde_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_UP[clyde_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            clyde_animation.setCurrentAnimation(&game_clips.EYES_CLIPS_DOWN[clyde_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }
}