#include "Game.h"


void Game::drawPellets()
{
    //Food cube dimensions and position
    SDL_Rect pellet;

    //Set renderer colour to pastel orange
    SDL_SetRenderDrawColor(game_renderer, 247, 176, 146, 255);

    for (int i = 0; i < MAP_W; i++)
    {
        for (int j = 0; j < MAP_H; j++)
        {
            //Draw food cubes in the middle of the tile
            if (game_map.grid[i][j].type == Tile::TileType::PELLET || game_map.grid[i][j].type == Tile::TileType::RED_ZONE_PELLETS)
            {
                pellet = { game_map.grid[i][j].x + 6, game_map.grid[i][j].y + 6, 4, 4 };
                SDL_RenderFillRect(game_renderer, &pellet);
            }
        }
    }

    SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
    //SDL_SetRenderDrawColor(game_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}



void Game::renderEnergizers()
{
    if (game_map.grid[2][6].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[2][6].x, game_map.grid[2][6].y, energizer_animation.getCurrentAnimation());


    if (game_map.grid[27][6].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[27][6].x, game_map.grid[27][6].y, energizer_animation.getCurrentAnimation());


    if (game_map.grid[2][26].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[2][26].x, game_map.grid[2][26].y, energizer_animation.getCurrentAnimation());


    if (game_map.grid[27][26].type == Tile::TileType::ENERGIZER)
        sprites.render(game_renderer, game_map.grid[27][26].x, game_map.grid[27][26].y, energizer_animation.getCurrentAnimation());
}