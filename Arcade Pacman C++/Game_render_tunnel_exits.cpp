#include "Game.h"

//WHAT:
//A function that renders black areas at the end of each tunnel to hide entity transition.

void Game::drawTunnelExits()
{
    SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
    SDL_Rect tunnel_exit_left = { game_map.grid[0][16].x, game_map.grid[0][16].y, 16, 48 };  
    SDL_RenderFillRect(game_renderer, &tunnel_exit_left);

    SDL_Rect tunnel_exit_right = { game_map.grid[29][16].x, game_map.grid[29][16].y, 16, 48 };
    SDL_RenderFillRect(game_renderer, &tunnel_exit_right);
}