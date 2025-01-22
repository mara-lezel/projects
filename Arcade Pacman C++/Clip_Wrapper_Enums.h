#ifndef CLIP_WRAPPER_ENUMS_H
#define CLIP_WRAPPER_ENUMS_H

//----------------------------------------------------------------------------------------------------------------------
//PACMAN
//----------------------------------------------------------------------------------------------------------------------
enum Pacman_animations_right
{
    PACMAN_RIGHT_FULL,
    PACMAN_RIGHT_HALFOPEN,
    PACMAN_RIGHT_OPEN,
    PACMAN_RIGHT_HALFOPEN2,
    PACMAN_RIGHT_TOTAL
};

enum Pacman_animations_left
{
    PACMAN_LEFT_FULL,
    PACMAN_LEFT_HALFOPEN,
    PACMAN_LEFT_OPEN,
    PACMAN_LEFT_HALFOPEN2,
    PACMAN_LEFT_TOTAL
};

enum Pacman_animations_up
{
    PACMAN_UP_FULL,
    PACMAN_UP_HALFOPEN,
    PACMAN_UP_OPEN,
    PACMAN_UP_HALFOPEN2,
    PACMAN_UP_TOTAL
};

enum Pacman_animations_down
{
    PACMAN_DOWN_FULL,
    PACMAN_DOWN_HALFOPEN,
    PACMAN_DOWN_OPEN,
    PACMAN_DOWN_HALFOPEN2,
    PACMAN_DOWN_TOTAL
};

enum Pacman_animations_death
{
    PACMAN_DEATH_1,
    PACMAN_DEATH_2,
    PACMAN_DEATH_3,
    PACMAN_DEATH_4,
    PACMAN_DEATH_5,
    PACMAN_DEATH_6,
    PACMAN_DEATH_7,
    PACMAN_DEATH_8,
    PACMAN_DEATH_9,
    PACMAN_DEATH_10,
    PACMAN_DEATH_11,
    PACMAN_DEATH_12,
    PACMAN_DEATH_TOTAL
};

//----------------------------------------------------------------------------------------------------------------------
//ENERGIZER
//----------------------------------------------------------------------------------------------------------------------
enum Energizer_animations
{
    PELLET_1,
    PELLET_2,
    PELLET_TOTAL
};

//----------------------------------------------------------------------------------------------------------------------
//BLINKY
//----------------------------------------------------------------------------------------------------------------------
enum Blinky_animations_right
{
    BLINKY_RIGHT_1,
    BLINKY_RIGHT_2
};

enum Blinky_animations_down
{
    BLINKY_DOWN_1,
    BLINKY_DOWN_2
};

enum Blinky_animations_left
{
    BLINKY_LEFT_1,
    BLINKY_LEFT_2
};

enum Blinky_animations_up
{
    BLINKY_UP_1,
    BLINKY_UP_2
};


//----------------------------------------------------------------------------------------------------------------------
//PINKY
//----------------------------------------------------------------------------------------------------------------------
enum Pinky_animations_right
{
    PINKY_RIGHT_1,
    PINKY_RIGHT_2
};

enum Pinky_animations_down
{
    PINKY_DOWN_1,
    PINKY_DOWN_2
};

enum Pinky_animations_left
{
    PINKY_LEFT_1,
    PINKY_LEFT_2
};

enum Pinky_animations_up
{
    PINKY_UP_1,
    PINKY_UP_2
};


//----------------------------------------------------------------------------------------------------------------------
//INKY
//----------------------------------------------------------------------------------------------------------------------
enum Inky_animations_right
{
    INKY_RIGHT_1,
    INKY_RIGHT_2
};

enum Inky_animations_down
{
    INKY_DOWN_1,
    INKY_DOWN_2
};

enum Inky_animations_left
{
    INKY_LEFT_1,
    INKY_LEFT_2
};

enum Inky_animations_up
{
    INKY_UP_1,
    INKY_UP_2
};


//----------------------------------------------------------------------------------------------------------------------
//CLYDE
//----------------------------------------------------------------------------------------------------------------------
enum Clyde_animations_right
{
    CLYDE_RIGHT_1,
    CLYDE_RIGHT_2
};

enum Clyde_animations_down
{
    CLYDE_DOWN_1,
    CLYDE_DOWN_2
};

enum Clyde_animations_left
{
    CLYDE_LEFT_1,
    CLYDE_LEFT_2
};

enum Clyde_animations_up
{
    CLYDE_UP_1,
    CLYDE_UP_2
};


//----------------------------------------------------------------------------------------------------------------------
//GHOST EYES
//----------------------------------------------------------------------------------------------------------------------
enum Ghost_eyes_right
{
    EYES_RIGHT_1,
    EYES_RIGHT_2
};

enum Ghost_eyes_down
{
    EYES_DOWN_1,
    EYES_DOWN_2
};

enum Ghost_eyes_left
{
    EYES_LEFT_1,
    EYES_LEFT_2
};

enum Ghost_eyes_up
{
    EYES_UP_1,
    EYES_UP_2
};


//----------------------------------------------------------------------------------------------------------------------
//GHOST OTHER
//----------------------------------------------------------------------------------------------------------------------
enum Ghost_animations_frightened
{
    FRIGHT_1,
    FRIGHT_2
};

enum Ghost_animations_frightened_end
{
    FRIGHT_END_1,
    FRIGHT_END_2,
    GHOST_TOTAL
};


//----------------------------------------------------------------------------------------------------------------------
//LETTERS & DIGITS
//----------------------------------------------------------------------------------------------------------------------
enum Letter_animations
{
    LETTER_A, //0
    LETTER_C, //1
    LETTER_D, //2
    LETTER_I, //3
    LETTER_E, //4
    LETTER_G, //5
    LETTER_H, //6
    LETTER_O, //7
    LETTER_R, //8
    LETTER_S, //9
    LETTER_Y, //10
    LETTER_U, //11
    LETTER_P, //12
    LETTER_EX, //13
    LETTER_M, //14
    LETTER_V, //15
    LETTER_R1, //16
    LETTER_E1, //17
    LETTER_G2, //18
    LETTER_A2, //19
    LETTER_M2, //20
    LETTER_E2, //21
    LETTER_O2, //22
    LETTER_V2, //23
    LETTER_R2, //24
    LETTER_TOTAL
};

enum Digit_animations
{
    DIGIT_0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
    DIGIT_TOTAL
};


//----------------------------------------------------------------------------------------------------------------------
//GAME ELEMENTS & SCORE
//----------------------------------------------------------------------------------------------------------------------
enum Score_number_animations
{
    SCORE_200, //0
    SCORE_400, //1
    SCORE_800, //2
    SCORE_1600, //3
    SCORE_100, //4
    SCORE_300, //5
    SCORE_500, //6
    SCORE_700, //7
    SCORE_1000, //8
    SCORE_2000, //9
    SCORE_3000, //10
    SCORE_5000, //11
    SCORE_TOTAL
};

enum Fruit_and_item_animations
{
    CHERRY, //0
    STRAWBERRY, //1
    ORANGE, //2
    APPLE, //3
    MELON, //4
    GALAXIAN_BOSS, //5
    BELL, //6
    KEY, //7
    PACMAN_LIFE_ICON, //8
    ITEM_TOTAL
};

//----------------------------------------------------------------------------------------------------------------------
//SCENES
//----------------------------------------------------------------------------------------------------------------------

enum Blinky_torn_animations
{
    TORN_EYES_UP,
    TORN_EYES_DOWN
};

enum Blinky_without_cloak_animations
{
    WITHOUT_CLOAK_1,
    WITHOUT_CLOAK_2
};

enum Blinky_cloak_tear_animations
{
    NAIL,
    STRETCH_1,
    STRETCH_2,
    STRETCH_3,
    TORN,
    CLOAK_TEAR_TOTAL
};


#endif //CLIP_WRAPPER_ENUMS_H
