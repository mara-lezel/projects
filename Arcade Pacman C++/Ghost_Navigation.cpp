#include "Ghost_Navigation.h"

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

GhostNavigation::GhostNavigation() :
	start_tile_x_(0), start_tile_y_(0), next_direction_(Direction::LEFT) {}

GhostNavigation::GhostNavigation(Direction next_direction) :
	start_tile_x_(0), start_tile_y_(0), next_direction_(next_direction) {}

GhostNavigation::~GhostNavigation()
{

}

//------------------------------------------------GETTERS&SETTERS-----------------------------------------
//--------------------------------------------------------------------------------------------------------

Direction GhostNavigation::getNextDirection() const
{
	return next_direction_;
}


void GhostNavigation::setNextDirection(Direction next_direction)
{
	next_direction_ = next_direction;
}

//------------------------------------------------RESET---------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void GhostNavigation::resetNavigation(Direction reset_direction)
{
	start_tile_x_ = 0;
	start_tile_y_ = 0;
	next_direction_ = reset_direction;
}