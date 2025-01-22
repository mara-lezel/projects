#include "Ghost.h"

#include "Map.h"


//WHAT:
//Main ghost movement function.

//HOW:
//Gets upcoming tile for movement calculations based on entity position and direction;
//Uses that tile to see if there is collision or if a turn can be done;
//Adds velocity based on direction;

//When in cage or in transition, more scripted movements are used:
//bounce() - going up and down while in cage;
//transitionOut() - leaving the cage, different for every ghost.
//transitionIn() - returning to the cage after being eaten, different for every ghost.

//bounce() applies only to UP and DOWN;
//transitionOut() applies to RIGHT, LEFT and UP;
//transitionIn() applies to RIGHT, LEFT and DOWN;


void Ghost::move(const Map& map)
{
    const Tile& upcoming_tile = map.produceUpcomingTile(x_, y_, direction_);

    switch (direction_)
    {

        case Direction::RIGHT:
        {      
            if (current_state_ == GhostStates::State::IN_CAGE)
                ;
            else if (current_state_ == GhostStates::State::IN_TRANSITION_FROM_CAGE)
                transitionOut(map);
            else if (current_state_ == GhostStates::State::IN_TRANSITION_TO_CAGE)
                transitionIn(map);
            else
            {
                turnCorner(upcoming_tile);

                x_ += velocity_;
            }
     
            break;
        }

        case Direction::LEFT:
        {
            if (current_state_ == GhostStates::State::IN_CAGE)
                ;
            else if (current_state_ == GhostStates::State::IN_TRANSITION_FROM_CAGE)
                transitionOut(map);
            else if (current_state_ == GhostStates::State::IN_TRANSITION_TO_CAGE)
                transitionIn(map);
            else
            {
                turnCorner(upcoming_tile);

                x_ -= velocity_;
            }

            break;
        }

        case Direction::UP:
        {
            if (current_state_ == GhostStates::State::IN_CAGE)
                bounce(map);
            else if (current_state_ == GhostStates::State::IN_TRANSITION_FROM_CAGE)
                transitionOut(map);
            else if (current_state_ == GhostStates::State::IN_TRANSITION_TO_CAGE)
                ;
            else
            {
                turnCorner(upcoming_tile);

                y_ -= velocity_;
            }

            break;
        }

        case Direction::DOWN:
        {
            if (current_state_ == GhostStates::State::IN_CAGE)
                bounce(map);
            else if (current_state_ == GhostStates::State::IN_TRANSITION_FROM_CAGE)
                ;
            else if (current_state_ == GhostStates::State::IN_TRANSITION_TO_CAGE)
                transitionIn(map);
            else
            {
                turnCorner(upcoming_tile);

                y_ += velocity_;
            }
           
            break;
        }

        default:
            break;
    }
}