#include "Ghost_Time_Table.h"


//Level 17 and Level 19 onwards fright mode does not trigger
float GhostTimeTable::frightPhaseDuration()
{
	switch (current_level_)
	{
	case 1:
		return 6.0f;
	case 2:
		return 5.0f;
	case 3:
		return 4.0f;
	case 4:
		return 3.0f;
	case 5:
		return 2.0f;
	case 6:
		return 5.0f;
	case 7:
		return 2.0f;
	case 8:
		return 2.0f;
	case 9:
		return 1.0f;
	case 10:
		return 5.0f;
	case 11:
		return 2.0f;
	case 12:
		return 1.0f;
	case 13:
		return 1.0f;
	case 14:
		return 3.0f;
	case 15:
		return 1.0f;
	case 16:
		return 1.0f;
	case 18:
		return 1.0f;
	default:
		return 0.0f;
	}
}