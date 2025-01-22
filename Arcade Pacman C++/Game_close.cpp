#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

void Game::close()
{
    SDL_DestroyRenderer(game_renderer);
    game_renderer = nullptr;

    SDL_DestroyWindow(game_window);
    game_window = nullptr;

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}