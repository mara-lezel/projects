#ifndef GAME_SOUNDS_H
#define GAME_SOUNDS_H

#include "Sound.h"

//A class that holds all game related sounds.
class GameSounds
{
public:
	GameSounds();
	~GameSounds();

	bool loadSounds();
	void reset();

public:
	Sound death_1;
	Sound death_2;
	Sound eat_fruit;
	Sound eat_ghost;
	Sound bonus_life;
	Sound game_start;
	Sound intermission;
	Sound munch_1;
	Sound munch_2;
	Sound energizer;
	Sound retreating;
	Sound siren_1;
	Sound siren_2;
	Sound siren_3;
	Sound siren_4;
	Sound siren_5;
	Sound credit;
};

#endif //GAME_SOUNDS_H
