#include "Game.h"

void Game::freeze_loop()
{
    //LOGIC
    ghostTransitionToCage();

    //PHYSICS
    handlePacmanSpeed();

    handleBlinkySpeed();
    handlePinkySpeed();
    handleInkySpeed();
    handleClydeSpeed();


    
    if (blinky.getPreviousState() == GhostStates::State::EATEN && blinky.getState() == GhostStates::State::EATEN ||
        blinky.getPreviousState() == GhostStates::State::EATEN && blinky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        blinky.move(game_map);
        blinky.tunnelTransition(game_map);
        blinky.lookAhead(game_map, blinky.fixate(game_map, pacman));
    }



    
    if (pinky.getPreviousState() == GhostStates::State::EATEN && pinky.getState() == GhostStates::State::EATEN ||
        pinky.getPreviousState() == GhostStates::State::EATEN && pinky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        pinky.move(game_map);
        pinky.tunnelTransition(game_map);
        pinky.lookAhead(game_map, pinky.fixate(game_map, pacman));
    }


    
    if (inky.getPreviousState() == GhostStates::State::EATEN && inky.getState() == GhostStates::State::EATEN ||
        inky.getPreviousState() == GhostStates::State::EATEN && inky.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        inky.move(game_map);
        inky.tunnelTransition(game_map);
        inky.lookAhead(game_map, inky.fixate(game_map, pacman, blinky));
    }


    
    if (clyde.getPreviousState() == GhostStates::State::EATEN && clyde.getState() == GhostStates::State::EATEN ||
        clyde.getPreviousState() == GhostStates::State::EATEN && clyde.getState() == GhostStates::State::IN_TRANSITION_TO_CAGE)
    {
        clyde.move(game_map);
        clyde.tunnelTransition(game_map);
        clyde.lookAhead(game_map, clyde.fixate(game_map, pacman));
    }

    //ANIMATION
    freezeScoreAnimation(false);
}