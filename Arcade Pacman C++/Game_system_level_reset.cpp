#include "Game.h"


void Game::level_reset()
{
    //Main elements
    dot_counter = 0;

    ++level;

    game_map.loadMap("resources/level.map");

    game_values_table.updateLevel(level);
    ghost_time_table.updateLevel(level);
    speed_table.updateLevel(level);

    //RESET SOUND
    game_sounds.reset();

    //RESET STARTING POSITIONS
    pacman.setIntCoordinates(game_map.grid[15][26].x, game_map.grid[15][26].y + 8);
    blinky.setIntCoordinates(game_map.grid[15][14].x, game_map.grid[15][14].y + 8);
    pinky.setIntCoordinates(game_map.grid[15][17].x, game_map.grid[15][17].y + 8);
    inky.setIntCoordinates(game_map.grid[13][17].x, game_map.grid[13][17].y + 8);
    clyde.setIntCoordinates(game_map.grid[17][17].x, game_map.grid[17][17].y + 8);

    //RESET DIRECTION
    pacman.setDirection(Direction::LEFT);
    blinky.setDirection(Direction::LEFT);
    pinky.setDirection(Direction::DOWN);
    inky.setDirection(Direction::UP);
    clyde.setDirection(Direction::UP);
    input_direction = Direction::LEFT;

    //RESET STARTING STATES
    blinky.setState(GhostStates::State::SCATTER);
    pinky.setState(GhostStates::State::IN_CAGE);
    inky.setState(GhostStates::State::IN_CAGE);
    clyde.setState(GhostStates::State::IN_CAGE);

    //RESET SPEED
    pacman.setVelocity(speed_table.pacman());
    blinky.setVelocity(speed_table.ghost());
    pinky.setVelocity(speed_table.ghostCage());
    inky.setVelocity(speed_table.ghostCage());
    clyde.setVelocity(speed_table.ghostCage());

    //RESET GHOST BEHAVIOUR
    blinky.resetNavigation(blinky.getDirection());
    blinky.resetState();

    pinky.resetNavigation(pinky.getDirection());
    pinky.resetState();

    inky.resetNavigation(inky.getDirection());
    inky.resetState();

    clyde.resetNavigation(clyde.getDirection());
    clyde.resetState();

    //RESET ANIMATION
    pacman_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_LEFT[0]);
    blinky_animation.setCurrentAnimation(&game_clips.BLINKY_CLIPS_LEFT[0]);
    pinky_animation.setCurrentAnimation(&game_clips.PINKY_CLIPS_DOWN[0]);
    inky_animation.setCurrentAnimation(&game_clips.INKY_CLIPS_UP[0]);
    clyde_animation.setCurrentAnimation(&game_clips.CLYDE_CLIPS_UP[0]);

    energizer_animation.setCurrentAnimation(&game_clips.ENERGIZER_CLIPS[0]);
    pacman_life_lost_animation.setCurrentAnimation(&game_clips.PACMAN_CLIPS_DEATH[0]);
    big_pacman_animation.setCurrentAnimation(&game_clips.BIG_PACMAN_CLIPS[0]);
    blinky_retreat_animation.setCurrentAnimation(&game_clips.BLINKY_WITHOUT_CLOAK_CLIPS[0]);

    pacman_animation.setFrameCount(0);
    blinky_animation.setFrameCount(0);
    pinky_animation.setFrameCount(0);
    inky_animation.setFrameCount(0);
    clyde_animation.setFrameCount(0);

    energizer_animation.setFrameCount(0);
    pacman_life_lost_animation.setFrameCount(0);
    big_pacman_animation.setFrameCount(0);
    blinky_retreat_animation.setFrameCount(0);

    //RESET TIMERS
    phase_timer.reset();
    pellet_timer.reset();
    fright_timer.stop();
    bonus_timer.stop();
    bonus_score_timer.stop();
    freeze_frame_timer.stop();

    //Flags
    life_lost = false;
    level_complete = false;
    ghost_eaten = false;
    scene_playing = true;

    if (level == 3 || level == 6 || level == 10 || level == 14 || level == 18)
        transmission_scene = true;

    //Misc
    ghost_time_table.reset();

    //Functionality
    activateEnergizers(false, true);

    handleModeChanges(true);

    handleImpact(true);

    ghostTransitionToMaze(false, true);

    handleInCageGhosts(false, true);

    handleBonusFruit(false, true);

    freezeScoreAnimation(true);
}