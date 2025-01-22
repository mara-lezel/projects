#include "Ghost_Time_Table.h"


//WHAT:
//A function that returns how long the current scatter phase lasts 
//based on current level.

//NOTE:
//Time values change thrice: Level 1, Level 2-4, Level 5+

float GhostTimeTable::scatterPhaseDuration()
{
	switch (current_level_)
	{
	case 1:
	{
		switch (current_scatter_phase_)
		{
		case 1:
			return 7.0f;
		case 2:
			return 7.0f;
		case 3:
			return 5.0f;
		case 4:
			return 5.0f;
		default:
			return 0.0f;
		}
	}

	case 2:
	{
		switch (current_scatter_phase_)
		{
		case 1:
			return 7.0f;
		case 2:
			return 7.0f;
		case 3:
			return 5.0f;
		case 4:
			return 0.016f;
		default:
			return 0.0f;
		}
	}

	case 3:
	{
		switch (current_scatter_phase_)
		{
		case 1:
			return 7.0f;
		case 2:
			return 7.0f;
		case 3:
			return 5.0f;
		case 4:
			return 0.016f;
		default:
			return 0.0f;
		}
	}

	case 4:
	{
		switch (current_scatter_phase_)
		{
		case 1:
			return 7.0f;
		case 2:
			return 7.0f;
		case 3:
			return 5.0f;
		case 4:
			return 0.016f;
		default:
			return 0.0f;
		}
	}

	//Levels 5+
	default:
	{
		switch (current_scatter_phase_)
		{
		case 1:
			return 5.0f;
		case 2:
			return 5.0f;
		case 3:
			return 5.0f;
		case 4:
			return 0.016f;
		default:
			return 0.0f;
		}
	}
	}
}