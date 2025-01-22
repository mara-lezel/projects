#include "Game.h"

#include <SDL_Mixer.h>


void Game::handleMenu()
{
    SDL_RenderClear(game_renderer);  
    menu_screen.render(game_renderer, 0, 0, nullptr);

    if (option == 1)
        sprites.render(game_renderer, 101, 378, &game_clips.EYES_CLIPS_RIGHT[0]);

    if (option == 2)
        sprites.render(game_renderer, 101, 425, &game_clips.EYES_CLIPS_RIGHT[0]);

    if(option == 3)
        sprites.render(game_renderer, 101, 472, &game_clips.EYES_CLIPS_RIGHT[0]);


    switch (volume_slider)
    {
    case 0:
        Mix_Volume(-1, 0);
        break;
    case 1:
        Mix_Volume(-1, 5);
        sprites.render(game_renderer, 280, 422, &game_clips.PACMAN_CLIPS_RIGHT[2]);
        break;
    case 2:
        Mix_Volume(-1, 20);
        sprites.render(game_renderer, 280, 422, &game_clips.PACMAN_CLIPS_RIGHT[2]);
        sprites.render(game_renderer, 312, 422, &game_clips.PACMAN_CLIPS_RIGHT[1]);
        break;
    case 3:
        Mix_Volume(-1, 50);
        sprites.render(game_renderer, 280, 422, &game_clips.PACMAN_CLIPS_RIGHT[2]);
        sprites.render(game_renderer, 312, 422, &game_clips.PACMAN_CLIPS_RIGHT[1]);
        sprites.render(game_renderer, 344, 422, &game_clips.PACMAN_CLIPS_RIGHT[0]);
        break;
    default:
        break;
    }

    switch (eternal_mode)
    {
    case true:
        sprites.render(game_renderer, 155, 479, &game_clips.SPRITE_CLIPS[79]);
        sprites.render(game_renderer, 171, 479, &game_clips.SPRITE_CLIPS[78]);
        break;
    default:
        break;
    }


    SDL_RenderPresent(game_renderer);
}