#include "Game.h"

#include <iostream>
#include <SDL.h>

void Game::start()
{
    const int FPS = 60;

    //Initialize SDL systems, create window and associated renderer, load all assets
    if (!initialize())
        std::cout << "Failed to initialize." << std::endl;
    else
    {
        //Event handler - key presses
        SDL_Event e;
        
        //Set starting positions
        round_reset();
        life_lost = true;
    
        //Start counting performance
        utility_timer.start();

        //Start counting phase time
        phase_timer.start();

        //Start counting ghost exit times
        pellet_timer.start();

        //Game loop
        while (running)
        {
            utility_timer.update();

            while (SDL_PollEvent(&e) != 0)
                event(e);

            if (utility_timer.getDeltaTime() >= 1.0f / FPS)
            {
                if (menu_open)
                    handleMenu();
                else
                {

                    freezeFrame();

                    manageGameFlags();

                    if (ghost_eaten)
                        freeze_loop();
                    else if (scene_playing)
                        scene_loop();
                    else
                        loop();

                    render();
                }

                utility_timer.reset();
            }
        }

        close();
    }
}