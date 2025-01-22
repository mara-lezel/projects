#include "Ghost_States.h"


//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

GhostStates::GhostStates() :
	current_state_(State::IN_CAGE), previous_state_(State::IN_CAGE) {}

GhostStates::GhostStates(State state) :
	current_state_(state), previous_state_(state) {}

GhostStates::~GhostStates()
{

}

//------------------------------------------------GETTERS&SETTERS-----------------------------------------
//--------------------------------------------------------------------------------------------------------

void GhostStates::setState(State state)
{
	current_state_ = state;
}


GhostStates::State GhostStates::getState() const
{
	return current_state_;
}


GhostStates::State GhostStates::getPreviousState() const
{
	return previous_state_;
}

//------------------------------------------------RESET---------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void GhostStates::resetState()
{
	previous_state_ = State::IN_CAGE;
}