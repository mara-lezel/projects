#include "Clyde.h"

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

Clyde::Clyde() :
	Ghost() {}

Clyde::Clyde(float velocity, Direction direction) :
	Ghost(velocity, direction) {}

Clyde::Clyde(float x, float y, float velocity, Direction direction) :
	Ghost(x, y, velocity, direction) {}

Clyde::~Clyde()
{

}