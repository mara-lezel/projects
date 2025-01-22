#include "Ghost_Time_Table.h"


//Max number of phases per round (4 scatter/4 chase)
const int PHASE_TOTAL = 4;

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

GhostTimeTable::GhostTimeTable() :
	current_level_(1), current_chase_phase_(1), current_scatter_phase_(1) {}

GhostTimeTable::~GhostTimeTable()
{

}

//------------------------------------------------GETTERS-------------------------------------------------
//--------------------------------------------------------------------------------------------------------


int GhostTimeTable::getScatterCounter() const
{
	return current_scatter_phase_;
}


int GhostTimeTable::getChaseCounter() const
{
	return current_chase_phase_;
}

//------------------------------------------------UPDATES-------------------------------------------------
//--------------------------------------------------------------------------------------------------------


void GhostTimeTable::reset()
{
	current_chase_phase_ = 1;
	current_scatter_phase_ = 1;
}


void GhostTimeTable::updateLevel(int level)
{
	current_level_ = level;
}


//Phase counters are also used to determine what state the ghost should enter after being frightened;
//Chase phase is indefinite after 4th scatter phase;
//Therefore, allow scatter counter to go over 4;

//How it works:
//If phase counters are equal, the current phase is scatter;
//If scatter counter is bigger, the current phase is chase.
//Chase counter will never exceed scatter counter.

void GhostTimeTable::updatePhaseChase()
{
	if (current_chase_phase_ < PHASE_TOTAL)
		current_chase_phase_++;
}


void GhostTimeTable::updatePhaseScatter()
{
	if (current_scatter_phase_ < PHASE_TOTAL + 1)
		current_scatter_phase_++;
}