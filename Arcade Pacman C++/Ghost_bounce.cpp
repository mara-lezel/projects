#include "Ghost.h"

#include "Map.h"


//WHAT & HOW:
//A ghost movement function for going up and down while in the cage.
//If a ghost moves too far into the cage wall, ghost position is adjusted back into cage.
//Uses a bounce offset for animation purposes.

void Ghost::bounce(const Map& map)
{
    static const int bounce_offset = 2;

	switch (direction_)
	{
	    case Direction::UP:
	    {
            if (static_cast<int>(y_) >= map.grid[15][17].y - bounce_offset)
            {
                y_ -= velocity_;

                if (static_cast<int>(y_) < map.grid[15][17].y - bounce_offset)
                {
                    y_ = static_cast<float>(map.grid[15][17].y - bounce_offset);

                    direction_ = Direction::DOWN;
                }
            }

            break;
	    }


        case Direction::DOWN:
        {
            if (static_cast<int>(y_) <= map.grid[15][18].y + bounce_offset)
            {
                y_ += velocity_;

                if (static_cast<int>(y_) > map.grid[15][18].y + bounce_offset)
                {
                    y_ = static_cast<float>(map.grid[15][18].y + bounce_offset);

                    direction_ = Direction::UP;
                }
            }

            break;
        }
	}
}