#include "Entity.h"

#include "Map.h"


//Puts entity on the other side of the tunnel if entered
void Entity::tunnelTransition(const Map& map)
{
    //LEFT TUNNEL
    if (x_ <= map.grid[0][17].x)
    {
        x_ = static_cast<float>(map.grid[29][17].x + 15);
        y_ = static_cast<float>(map.grid[29][17].y + 8);
    }

    //RIGHT TUNNEL
    if (x_ >= map.grid[29][17].x + 16)
    {
        x_ = static_cast<float>(map.grid[0][17].x + 1);
        y_ = static_cast<float>(map.grid[0][17].y + 8);
    }
}