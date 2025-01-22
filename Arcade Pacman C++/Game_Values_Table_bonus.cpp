#include "Game_Values_Table.h"


//Points for collecting fruits that spawn in the maze.
//Level 13+ rewards constant value of 5000.
int GameValuesTable::bonusPoints()
{

	switch (level_)
	{
	case 1:
		return 100;
	case 2:
		return 300;
	case 3:
		return 500;
	case 4:
		return 500;
	case 5:
		return 700;
	case 6:
		return 700;
	case 7:
		return 1000;
	case 8:
		return 1000;
	case 9:
		return 2000;
	case 10:
		return 2000;
	case 11:
		return 3000;
	case 12:
		return 3000;
	default:
		return 5000;
	}
}


//Points awarded for eating ghosts in succession.
//Resets after every fright mode.
//Up to four ghosts can be eaten during one fright phase.
int GameValuesTable::ghostPoints(int ghosts_eaten)
{
	switch (ghosts_eaten)
	{
	case 1:
		return 200;
	case 2:
		return 400;
	case 3:
		return 800;
	case 4:
		return 1600;
	default:
		return 0;
	}
}