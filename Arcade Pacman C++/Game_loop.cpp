#include "Game.h"

void Game::loop()
{
    //LOGIC
    if (!pacman.collision(game_map, input_direction))
        pacman.setDirection(input_direction);

    countScore();

    countDots();

    handleBonusFruit(false, false);

    handleModeChanges(false);

    activateEnergizers(false, false);

    handleInCageGhosts(false, false);

    ghostTransitionToMaze(false, false);
    
    ghostTransitionToCage();

    //PHYSICS
    handlePacmanSpeed();

    handleBlinkySpeed();
    handlePinkySpeed();
    handleInkySpeed();
    handleClydeSpeed();

    pacman.eatPellet(game_map);
    pacman.move(game_map);
    pacman.tunnelTransition(game_map);

    blinky.move(game_map);
    blinky.tunnelTransition(game_map);
    blinky.lookAhead(game_map, blinky.fixate(game_map, pacman));

    pinky.move(game_map);
    pinky.tunnelTransition(game_map);
    pinky.lookAhead(game_map, pinky.fixate(game_map, pacman));

    inky.move(game_map);
    inky.tunnelTransition(game_map);
    inky.lookAhead(game_map, inky.fixate(game_map, pacman, blinky));

    clyde.move(game_map);
    clyde.tunnelTransition(game_map);
    clyde.lookAhead(game_map, clyde.fixate(game_map, pacman));

    handleImpact(false);
    
    //ANIMATION
    handlePacmanAnimation();
    handleBlinkyAnimation();
    handlePinkyAnimation();
    handleInkyAnimation();
    handleClydeAnimation();

    energizer_animation.setCurrentAnimation(&game_clips.ENERGIZER_CLIPS[energizer_animation.getCurrentFrame()]);


    pacman_animation.animate();
    blinky_animation.animate();
    pinky_animation.animate();
    inky_animation.animate();
    clyde_animation.animate();

    energizer_animation.animate(); 
}
