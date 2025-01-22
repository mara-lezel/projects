#include "Ghost.h"

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

Ghost::Ghost() :
	Entity(), GhostStates(), GhostNavigation(direction_) {}

Ghost::Ghost(float velocity, Direction direction) :
	Entity(velocity, direction), GhostStates(), GhostNavigation(direction_) {}

Ghost::Ghost(float x, float y, float velocity, Direction direction) :
	Entity(x, y, velocity, direction), GhostStates(), GhostNavigation(direction_) {}

Ghost::~Ghost()
{

}
