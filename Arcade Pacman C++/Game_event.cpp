#include "Game.h"
#include <SDL.h>

void Game::event(SDL_Event& e)
{
    //User requests quit
    if (e.type == SDL_QUIT)
    {
        running = false;
    }

    //Key presses
    else if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {
                if (menu_open)
                {
                    if (option == 2)
                    {
                        if (volume_slider < 3)
                            volume_slider++;
                    }

                    if (option == 3)
                        eternal_mode = true;
                }
                else
                    input_direction = Direction::RIGHT;

                break;
            }

            case SDLK_LEFT:
            {
                if (menu_open)
                {
                    if (option == 2)
                    {
                        if (volume_slider > 0)
                            volume_slider--;
                    }

                    if (option == 3)
                        eternal_mode = false;
                }
                else
                    input_direction = Direction::LEFT;

                break;
            }

            case SDLK_UP:
            {
                if (menu_open)
                {
                    if (option > 1)
                        option--;

                    game_sounds.eat_fruit.play();
                }
                else
                    input_direction = Direction::UP;

                break;
            }

            case SDLK_DOWN:
            {
                if (menu_open)
                {
                    if (option < 3)
                        option++;
                    game_sounds.eat_fruit.play();
                }
                else
                    input_direction = Direction::DOWN;

                break;
            }

            case SDLK_RETURN:
            {
                if (menu_open)
                {
                    if(option == 1)
                        menu_open = false;
                }

                break;
            }

            default:
            {
                break;
            }
        }
    }
}