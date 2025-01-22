#include "Game.h"

#include <SDL.h>

void Game::render()
{
    //Clear renderer back to default colour
    SDL_RenderClear(game_renderer);

    //Render level layout to the screen
    maze_layout.render(game_renderer, 0, 0, nullptr);

    //Draw food pellets on the map
    drawPellets();
    renderEnergizers();

    //Render bonus fruit to the screen
    renderBonusFruit();

    //Render 1UP sign to the screen
    renderOneUp();

    //Render HIGH SCORE to the screen
    renderHighScoreLetters();

    //Render current score and high score to the screen
    renderGameScore();

    //Render player lives left
    renderPacmanLives();

    //Render level representation icons
    renderLevelRepresentation();


    if (scene_playing)
    {
        if (life_count == 0 && !eternal_mode)
            gameOverScene();

        else if (life_lost && game_score == 0)
            introScene();

        else if (life_lost)
            lifeLostScene();

        else if (level_complete)
            levelCompleteScene();

        else if (transmission_scene)
        {
            if (level == 3)
                firstTransmissionScene();
            else if (level == 6)
                secondTransmissionScene();
            else
                thirdTransmissionScene();
        }

        else
            resetScene();
    }
    else
    {
        sprites.render(game_renderer, pacman.getIntX() - 16, pacman.getIntY() - 16, pacman_animation.getCurrentAnimation());
        sprites.render(game_renderer, blinky.getIntX() - 16, blinky.getIntY() - 16, blinky_animation.getCurrentAnimation());
        sprites.render(game_renderer, pinky.getIntX() - 16, pinky.getIntY() - 16, pinky_animation.getCurrentAnimation());
        sprites.render(game_renderer, inky.getIntX() - 16, inky.getIntY() - 16, inky_animation.getCurrentAnimation());
        sprites.render(game_renderer, clyde.getIntX() - 16, clyde.getIntY() - 16, clyde_animation.getCurrentAnimation());
    }

    //Obfuscate tunnel exits
    drawTunnelExits();

    //SDL_SetRenderDrawColor(game_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);

    //SDL_Delay(200);

    //Render buffer onto screen
    SDL_RenderPresent(game_renderer);
}
