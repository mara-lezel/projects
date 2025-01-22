#ifndef CLIP_WRAPPER_H
#define CLIP_WRAPPER_H

#include "Clip_Wrapper_Enums.h"

struct SDL_Rect;
class Texture;

//READ: this is old material and quite cumbersome, but useful.

//ClipWrapper class loads sprite sheet images and puts them into animantion clip container.
//Then clips are put into categories for convenience.
//Categories are public for easy access/clarity.
class ClipWrapper
{
public:
    SDL_Rect* SPRITE_CLIPS;

    SDL_Rect* PACMAN_CLIPS_RIGHT;
    SDL_Rect* PACMAN_CLIPS_LEFT;
    SDL_Rect* PACMAN_CLIPS_UP;
    SDL_Rect* PACMAN_CLIPS_DOWN;
    SDL_Rect* PACMAN_CLIPS_DEATH;

    SDL_Rect* ENERGIZER_CLIPS;

    SDL_Rect* BLINKY_CLIPS_RIGHT;
    SDL_Rect* BLINKY_CLIPS_LEFT;
    SDL_Rect* BLINKY_CLIPS_UP;
    SDL_Rect* BLINKY_CLIPS_DOWN;

    SDL_Rect* PINKY_CLIPS_RIGHT;
    SDL_Rect* PINKY_CLIPS_LEFT;
    SDL_Rect* PINKY_CLIPS_UP;
    SDL_Rect* PINKY_CLIPS_DOWN;

    SDL_Rect* INKY_CLIPS_RIGHT;
    SDL_Rect* INKY_CLIPS_LEFT;
    SDL_Rect* INKY_CLIPS_UP;
    SDL_Rect* INKY_CLIPS_DOWN;

    SDL_Rect* CLYDE_CLIPS_RIGHT;
    SDL_Rect* CLYDE_CLIPS_LEFT;
    SDL_Rect* CLYDE_CLIPS_UP;
    SDL_Rect* CLYDE_CLIPS_DOWN;

    SDL_Rect* EYES_CLIPS_RIGHT;
    SDL_Rect* EYES_CLIPS_LEFT;
    SDL_Rect* EYES_CLIPS_UP;
    SDL_Rect* EYES_CLIPS_DOWN;

    SDL_Rect* FRIGHT_CLIPS;
    SDL_Rect* FRIGHT_END_CLIPS;

    SDL_Rect* LETTER_CLIPS;
    SDL_Rect* DIGIT_CLIPS;
    SDL_Rect* SCORE_CLIPS;
    SDL_Rect* FRUIT_CLIPS;

    SDL_Rect* BIG_PACMAN_CLIPS;
    SDL_Rect* TORN_BLINKY_CLIPS;
    SDL_Rect* PATCHED_BLINKY_CLIPS;
    SDL_Rect* BLINKY_CLOAK_TEAR_CLIPS;
    SDL_Rect* BLINKY_WITHOUT_CLOAK_CLIPS;


    //Allocate memory for different sprite clips
    ClipWrapper();

    //Deallocate memory
    ~ClipWrapper();

    //Load individual sprites from texture sheet into memory
    void load(Texture& sprites);

private:
    //Number of sprite clips in texture sheet
    const int SPRITE_TOTAL;

    //Tile dimension constants
    const int TILE_W;
    const int TILE_H;
};


#endif //CLIP_WRAPPER_H
