#include "Game_Values_Table.h"


//Section for number of pellets that need to be consumed by Pacman to release a ghost
//from cage.

int GameValuesTable::pinkyDotLimit()
{
	return 0;
}

int GameValuesTable::inkyDotLimit()
{
	switch (level_)
	{
	case 1:
		return 30;
	default:
		return 0;
	}
}

int GameValuesTable::clydeDotLimit()
{
	switch (level_)
	{
	case 1:
		return 60;
	case 2:
		return 50;
	default:
		return 0;
	}
}


//Section for number of pellets that need to be consumed by Pacman to release a ghost
//from cage after a life has been lost.

int GameValuesTable::pinkyGlobalDotLimit()
{
	return 7;
}

int GameValuesTable::inkyGlobalDotLimit()
{
	return 17;
}

int GameValuesTable::clydeGlobalDotLimit()
{
	return 32;
}