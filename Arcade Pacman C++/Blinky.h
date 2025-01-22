#ifndef GHOST_BLINKY_H
#define GHOST_BLINKY_H

#include "Ghost.h"

//A Blinky ghost class defined by unique target selection.
class Blinky : public Ghost
{
public:
	Blinky();
	Blinky(float velocity, Direction direction);
	Blinky(float x, float y, float velocity, Direction direction);
	~Blinky();

	//Locate target tile
	const Tile& fixate(const Map& map, const Pacman& pacman);
};

#endif //GHOST_BLINKY_H
