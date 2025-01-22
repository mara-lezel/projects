#include "Game.h"

//PAY ATTENTION TO:
//input_direction vs current pacman direction;
//animation delay - how many frames per one part of the animation;
//frame count - frames elapsed in an animation cycle.

//WHAT & HOW:
//How Pacman will be animated depends on his position in the maze and surrounding walls;
//Pacman will not animate nor will it have the round(base) animation when against a wall.

//This is done with 3 conditionals:
//-- if(no collision(input)) 
//      -> animate when not against a wall
//-- if(collision(input) and collision(pacman current direction))
//      -> stop animating
//-- if(collision(input) but no collision(pacman current direction))
//      -> animate

//Combined:
//Pacman is animated when moving freely.
//If player requests turn where there is a wall, Pacman will continue animating
//based on its' own direction.
//If Pacman is against a wall or in a corner, it does not animate.

void Game::handlePacmanAnimation()
{
 
    if (!pacman.collision(game_map, input_direction))
    {
        switch (input_direction)
        {
        case Direction::RIGHT:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_RIGHT[pacman_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[pacman_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_UP[pacman_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_DOWN[pacman_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }


    //Get frame count to determine which part of the animation to use when against a wall;
    //Delay * 2 is half-point of an animation cycle, since Pacman animation has 4 sprites;
    //Set frame count - to keep the same animation for the duration of being in collision.

    else if (pacman.collision(game_map, pacman.getDirection()))
    {
        switch (pacman.getDirection())
        {

            case Direction::RIGHT:
            {
                if (pacman_animation.getFrameCount() > (pacman_animation.getDelay() * 2 + 1))
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_RIGHT[2]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay() * 2 + 1);
                }
                else
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_RIGHT[1]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay());
                }

                break;
            }

            case Direction::LEFT:
            {
                if (pacman_animation.getFrameCount() > (pacman_animation.getDelay() * 2 + 1))
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[2]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay() * 2 + 1);
                }
                else
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[1]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay());
                }

                break;
            }

            case Direction::UP:
            {
                if (pacman_animation.getFrameCount() > (pacman_animation.getDelay() * 2 + 1))
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_UP[2]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay() * 2 + 1);
                }
                else
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_UP[1]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay());
                }

                break;
            }

            case Direction::DOWN:
            {
                if (pacman_animation.getFrameCount() > (pacman_animation.getDelay() * 2 + 1))
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_DOWN[2]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay() * 2 + 1);
                }
                else
                {
                    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_DOWN[1]);
                    pacman_animation.setFrameCount(pacman_animation.getDelay());
                }

                break;
            }

            default:
                break;
        }
    }


    else
    {
        switch (pacman.getDirection())
        {
        case Direction::RIGHT:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_RIGHT[pacman_animation.getCurrentFrame()]);
            break;
        case Direction::LEFT:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[pacman_animation.getCurrentFrame()]);
            break;
        case Direction::UP:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_UP[pacman_animation.getCurrentFrame()]);
            break;
        case Direction::DOWN:
            pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_DOWN[pacman_animation.getCurrentFrame()]);
            break;
        default:
            break;
        }
    }

}