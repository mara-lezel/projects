#include "Game_Values_Table.h"


//Number of pellets left on the map for the speed increase to trigger.
//Level 19+ is contant value.
int GameValuesTable::elroyDotCount()
{
	switch (level_)
	{
	case 1:
		return 20;
	case 2:
		return 30;
	case 3:
		return 40;
	case 4:
		return 40;
	case 5:
		return 40;
	case 6:
		return 50;
	case 7:
		return 50;
	case 8:
		return 50;
	case 9:
		return 60;
	case 10:
		return 60;
	case 11:
		return 60;
	case 12:
		return 80;
	case 13:
		return 80;
	case 14:
		return 80;
	case 15:
		return 100;
	case 16:
		return 100;
	case 17:
		return 100;
	case 18:
		return 100;
	default:
		return 120;
	}
}


//Number of pellets left on the map for the speed increase to trigger again.
//Level 19+ is contant value.
int GameValuesTable::superElroyDotCount()
{
	switch (level_)
	{
	case 1:
		return 10;
	case 2:
		return 15;
	case 3:
		return 20;
	case 4:
		return 20;
	case 5:
		return 20;
	case 6:
		return 25;
	case 7:
		return 25;
	case 8:
		return 25;
	case 9:
		return 30;
	case 10:
		return 30;
	case 11:
		return 30;
	case 12:
		return 40;
	case 13:
		return 40;
	case 14:
		return 40;
	case 15:
		return 50;
	case 16:
		return 50;
	case 17:
		return 50;
	case 18:
		return 50;
	default:
		return 60;
	}
}