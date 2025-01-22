#include "Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

bool Game::initialize()
{
    bool success = true;

    //Initiate pseudo-random number generator
    srand((unsigned)time(0));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;

        //Create window
        game_window = SDL_CreateWindow("PACMAN NAMCAP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (game_window == nullptr)
        {
            std::cout << "Could not create window! Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Create renderer for window
            game_renderer = SDL_CreateRenderer(game_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (game_renderer == nullptr)
            {
                std::cout << "Could not create renderer! Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                //Initializing renderer colour
                SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);
                //SDL_SetRenderDrawColor(game_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initiate colour blending for transparent 'Pause' screen
                if (SDL_SetRenderDrawBlendMode(game_renderer, SDL_BLENDMODE_BLEND) != 0)
                {
                    std::cout << "Could not initiate Alpha blending! Error: " << SDL_GetError() << std::endl;
                    success = false;
                }
                else
                {
                    //Initialize SDL_mixer - music and sound effects
                    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                    {
                        std::cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
                        success = false;
                    }
                    else
                    {
                        //Allocate memory for 17 sounds
                        Mix_AllocateChannels(17);

                        //Set volume for all channels
                        Mix_Volume(-1, 5);

                        //Load all sound effects
                        game_sounds.loadSounds();
                    }

                    //Initialize PNG
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        std::cout << "SDL_image could not initialize! Error: " << IMG_GetError << std::endl;
                        success = false;
                    }
                    else
                    {
                        //Load sprite sheet texture
                        if (!(sprites.loadFromFile(game_renderer, "resources/assets/pacman_sprites_arcade.png")))
                        {
                            std::cout << "Failed to load sprite sheet texture." << std::endl;
                            success = false;
                        }
                        else
                        {
                            //Load clips for all objects in the game
                            game_clips.load(sprites);
                        }

                        //Load level layout texture - rendered as one image, not separate cells
                        if (!(maze_layout.loadFromFile(game_renderer, "resources/assets/level_layout.png")))
                        {
                            std::cout << "Failed to load maze layout texture." << std::endl;
                            success = false;
                        }

                        //Load level transition texture
                        if (!(maze_transition.loadFromFile(game_renderer, "resources/assets/level_layout_transition.png")))
                        {
                            std::cout << "Failed to load maze transition texture." << std::endl;
                            success = false;
                        }

                        //Load menu screen texture
                        if (!(menu_screen.loadFromFile(game_renderer, "resources/assets/menu_screen_pog.png")))
                        {
                            std::cout << "Failed to load menu screen texture." << std::endl;
                            success = false;
                        }

                        //Load tile grid properties
                        if (!(game_map.loadMap("resources/level.map")))
                        {
                            std::cout << "Could not open .map file." << std::endl;
                            success = false;
                        }      
                    }
                }
            }
        }
    }

    return success;
}