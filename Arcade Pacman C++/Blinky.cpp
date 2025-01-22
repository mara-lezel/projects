#include "Blinky.h"

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

Blinky::Blinky() :
	Ghost() {}

Blinky::Blinky(float velocity, Direction direction) :
	Ghost(velocity, direction) {}

Blinky::Blinky(float x, float y, float velocity, Direction direction) :
	Ghost(x, y, velocity, direction) {}

Blinky::~Blinky()
{

}