#include "Game.h"

//WHAT:
//A function that renders the READY sign and entities in their starting positions.
//Energizers will be always visibe during this scene.


//NOTE:
//Scenes work in tandem with scene loop, that only does animations (READ "Game_scene_loop.cpp").


void Game::resetScene()
{
    if (!scene_play_timer.isRunning())
        scene_play_timer.start();

    if (game_map.grid[2][6].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[2][6].x, game_map.grid[2][6].y, &game_clips.ENERGIZER_CLIPS[1]);

    if (game_map.grid[27][6].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[27][6].x, game_map.grid[27][6].y, &game_clips.ENERGIZER_CLIPS[1]);

    if (game_map.grid[2][26].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[2][26].x, game_map.grid[2][26].y, &game_clips.ENERGIZER_CLIPS[1]);

    if (game_map.grid[27][26].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[27][26].x, game_map.grid[27][26].y, &game_clips.ENERGIZER_CLIPS[1]);


    sprites.render(game_renderer, game_map.grid[12][20].x, game_map.grid[12][20].y, &game_clips.LETTER_CLIPS[LETTER_R]);
    sprites.render(game_renderer, game_map.grid[13][20].x, game_map.grid[13][20].y, &game_clips.LETTER_CLIPS[LETTER_E]);
    sprites.render(game_renderer, game_map.grid[14][20].x, game_map.grid[14][20].y, &game_clips.LETTER_CLIPS[LETTER_A]);
    sprites.render(game_renderer, game_map.grid[15][20].x, game_map.grid[15][20].y, &game_clips.LETTER_CLIPS[LETTER_D]);
    sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.LETTER_CLIPS[LETTER_Y]);
    sprites.render(game_renderer, game_map.grid[17][20].x, game_map.grid[17][20].y, &game_clips.LETTER_CLIPS[LETTER_EX]);


    sprites.render(game_renderer, pacman.getIntX() - 16, pacman.getIntY() - 16, pacman_animation.getCurrentAnimation());
    sprites.render(game_renderer, blinky.getIntX() - 16, blinky.getIntY() - 16, blinky_animation.getCurrentAnimation());
    sprites.render(game_renderer, pinky.getIntX() - 16, pinky.getIntY() - 16, pinky_animation.getCurrentAnimation());
    sprites.render(game_renderer, inky.getIntX() - 16, inky.getIntY() - 16, inky_animation.getCurrentAnimation());
    sprites.render(game_renderer, clyde.getIntX() - 16, clyde.getIntY() - 16, clyde_animation.getCurrentAnimation());

    if (scene_play_timer.getElapsedTime() >= 2.0f)
    {
        scene_play_timer.stop();
        scene_playing = false;

        phase_timer.reset();
    }
}