#include "Game_Sounds.h"

#include <SDL_Mixer.h>

GameSounds::GameSounds() :
	death_1(), death_2(), eat_fruit(), eat_ghost(), bonus_life(), game_start(), intermission(), munch_1(), munch_2(),
	energizer(), retreating(), siren_1(), siren_2(), siren_3(), siren_4(), siren_5(), credit() {}

GameSounds::~GameSounds()
{

}


//SOUND CHANNELS:
//0 -- Siren 1
//1 -- Siren 2
//2 -- Siren 3
//3 -- Siren 4
//4 -- Siren 5
//5 -- Death 1
//6 -- Death 2
//7 -- Munch 1
//8 -- Munch 2
//9 -- Eat fruit
//10 -- Eat ghost
//11 -- Bonus life
//12 -- Game start
//13 -- Intermission
//14 -- Energizer
//15 -- Retreat
//16 -- Credit(menu)

bool GameSounds::loadSounds()
{
	bool success = true;

	if (!death_1.loadSound("resources/sounds/death_1.wav", 5))
		success = false;

	if (!death_2.loadSound("resources/sounds/death_2.wav", 6))
		success = false;

	if (!eat_fruit.loadSound("resources/sounds/eat_fruit.wav", 9))
		success = false;

	if (!eat_ghost.loadSound("resources/sounds/eat_ghost.wav", 10))
		success = false;

	if (!bonus_life.loadSound("resources/sounds/extend.wav", 11))
		success = false;

	if (!game_start.loadSound("resources/sounds/game_start.wav", 12))
		success = false;

	if (!intermission.loadSound("resources/sounds/intermission.wav", 13))
		success = false;

	if (!munch_1.loadSound("resources/sounds/munch_1.wav", 7))
		success = false;

	if (!munch_2.loadSound("resources/sounds/munch_2.wav", 8))
		success = false;

	if (!energizer.loadSound("resources/sounds/power_pellet.wav", 14))
		success = false;

	if (!retreating.loadSound("resources/sounds/retreating.wav", 15))
		success = false;

	if (!siren_1.loadSound("resources/sounds/siren_1.wav", 0))
		success = false;

	if (!siren_2.loadSound("resources/sounds/siren_2.wav", 1))
		success = false;

	if (!siren_3.loadSound("resources/sounds/siren_3.wav", 2))
		success = false;

	if (!siren_4.loadSound("resources/sounds/siren_4.wav", 3))
		success = false;

	if (!siren_5.loadSound("resources/sounds/siren_5.wav", 4))
		success = false;

	if (!credit.loadSound("resources/sounds/credit.wav", 16))
		success = false;


	return success;
}



void GameSounds::reset()
{
	Mix_HaltChannel(-1);
}