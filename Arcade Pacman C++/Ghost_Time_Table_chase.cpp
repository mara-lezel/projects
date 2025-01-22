#include "Ghost_Time_Table.h"

//WHAT:
//A function that returns how long the current chase phase lasts 
//based on current level.

//NOTE:
//4th chase phase lasts indefinitely (100000.0f ~ 30h).

//NOTE #2:
//Time values change thrice: Level 1, Level 2-4, Level 5+

float GhostTimeTable::chasePhaseDuration()
{
	switch (current_level_)
	{
	case 1:
	{
		switch (current_chase_phase_)
		{
		case 1:
			return 20.0f;
		case 2:
			return 20.0f;
		case 3:
			return 20.0f;
		case 4:
			return 100000.0f;
		default:
			return 0.0f;
		}
	}

	case 2:
	{
		switch (current_chase_phase_)
		{
		case 1:
			return 20.0f;
		case 2:
			return 20.0f;
		case 3:
			return 1033.0f;
		case 4:
			return 100000.0f;
		default:
			return 0.0f;
		}
	}

	case 3:
	{
		switch (current_chase_phase_)
		{
		case 1:
			return 20.0f;
		case 2:
			return 20.0f;
		case 3:
			return 1033.0f;
		case 4:
			return 100000.0f;
		default:
			return 0.0f;
		}
	}

	case 4:
	{
		switch (current_chase_phase_)
		{
		case 1:
			return 20.0f;
		case 2:
			return 20.0f;
		case 3:
			return 1033.0f;
		case 4:
			return 100000.0f;
		default:
			return 0.0f;
		}
	}

	//Levels 5+
	default:
	{
		switch (current_chase_phase_)
		{
		case 1:
			return 20.0f;
		case 2:
			return 20.0f;
		case 3:
			return 1037.0f;
		case 4:
			return 100000.0f;
		default:
			return 0.0f;
		}
	}
	}
}