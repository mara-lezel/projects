#include "Game.h"

//WHAT:
//A function that renders GAME OVER sign.

//NOTE:
//Scenes work in tandem with scene loop, that only does animations (READ "Game_scene_loop.cpp").

void Game::gameOverScene()
{
    if (game_map.grid[2][6].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[2][6].x, game_map.grid[2][6].y, &game_clips.ENERGIZER_CLIPS[1]);

    if (game_map.grid[27][6].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[27][6].x, game_map.grid[27][6].y, &game_clips.ENERGIZER_CLIPS[1]);

    if (game_map.grid[2][26].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[2][26].x, game_map.grid[2][26].y, &game_clips.ENERGIZER_CLIPS[1]);

    if (game_map.grid[27][26].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[27][26].x, game_map.grid[27][26].y, &game_clips.ENERGIZER_CLIPS[1]);


    sprites.render(game_renderer, game_map.grid[10][20].x, game_map.grid[10][20].y, &game_clips.LETTER_CLIPS[LETTER_G2]);
    sprites.render(game_renderer, game_map.grid[11][20].x, game_map.grid[11][20].y, &game_clips.LETTER_CLIPS[LETTER_A2]);
    sprites.render(game_renderer, game_map.grid[12][20].x, game_map.grid[12][20].y, &game_clips.LETTER_CLIPS[LETTER_M2]);
    sprites.render(game_renderer, game_map.grid[13][20].x, game_map.grid[13][20].y, &game_clips.LETTER_CLIPS[LETTER_E2]);
    sprites.render(game_renderer, game_map.grid[16][20].x, game_map.grid[16][20].y, &game_clips.LETTER_CLIPS[LETTER_O2]);
    sprites.render(game_renderer, game_map.grid[17][20].x, game_map.grid[17][20].y, &game_clips.LETTER_CLIPS[LETTER_V2]);
    sprites.render(game_renderer, game_map.grid[18][20].x, game_map.grid[18][20].y, &game_clips.LETTER_CLIPS[LETTER_E2]);
    sprites.render(game_renderer, game_map.grid[19][20].x, game_map.grid[19][20].y, &game_clips.LETTER_CLIPS[LETTER_R2]);

}