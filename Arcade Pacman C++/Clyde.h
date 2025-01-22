#ifndef GHOST_CLYDE_H
#define GHOST_CLYDE_H

#include "Ghost.h"

class Clyde : public Ghost
{
public:
	Clyde();
	Clyde(float velocity, Direction direction);
	Clyde(float x, float y, float velocity, Direction direction);
	~Clyde();

	//Locate target tile
	const Tile& fixate(const Map& map, const Pacman& pacman);
};

#endif //GHOST_CLYDE_H
