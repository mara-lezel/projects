#include "Inky.h"

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

Inky::Inky() :
	Ghost() {}

Inky::Inky(float velocity, Direction direction) :
	Ghost(velocity, direction) {}

Inky::Inky(float x, float y, float velocity, Direction direction) :
	Ghost(x, y, velocity, direction) {}

Inky::~Inky()
{

}