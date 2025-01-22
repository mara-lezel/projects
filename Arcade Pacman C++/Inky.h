#ifndef GHOST_INKY_H
#define GHOST_INKY_H

#include "Ghost.h"

class Inky :public Ghost
{
public:
	Inky();
	Inky(float velocity, Direction direction);
	Inky(float x, float y, float velocity, Direction direction);
	~Inky();

	//Locate target tile
	const Tile& fixate(const Map& map, const Pacman& pacman, const Ghost& blinky);
};

#endif //GHOST_INKY_H
