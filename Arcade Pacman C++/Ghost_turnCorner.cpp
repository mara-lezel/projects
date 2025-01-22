#include "Ghost.h"

#include "Map.h"

//READ:
//This function is a reworked version of Pacman movement that does not allow corner cutting.
//Instead, entity will not gain velocity in current direction until it aligns with the center of a tile.
//Pacman movement version (READ "Pacman_cornerCutting.cpp").

//WHAT:
//A function that manages turns at intersections of the maze.

//HOW:
//Performs a level check on entity and upcoming tile to see if there's a mismatch;
//Example: direction is RIGHT, but entity's y coordinate is not at the center level of the tile ahead;
//This means adding height at the same time as entity is moving RIGHT;
//That way entity can turn precisely at 90 degree angle at intersections.
//If movement takes entity too far, it is pushed back.

//NOTE:
//Collision offset acts like a hitbox (READ "Entity_produceTile.cpp").

void Ghost::turnCorner(const Tile& upcoming_tile)
{
    static const float collision_offset = 8.0f;

    switch (direction_)
    {
        case Direction::RIGHT:
        {

            //UP-RIGHT
            if (upcoming_tile.y < static_cast<int>(y_ - collision_offset))
            {
                y_ -= velocity_;
                x_ -= velocity_;

                if (static_cast<int>(y_ - collision_offset) < upcoming_tile.y)
                    y_ = static_cast<float>(upcoming_tile.y) + collision_offset;
            }

            //DOWN-RIGHT
            if (upcoming_tile.y + static_cast<int>(collision_offset) > static_cast<int>(y_))
            {
                y_ += velocity_;
                x_ -= velocity_;

                if (static_cast<int>(y_) > upcoming_tile.y + static_cast<int>(collision_offset))
                    y_ = static_cast<float>(upcoming_tile.y) + collision_offset;
            }

            break;
        }

        case Direction::LEFT:
        {

            //UP-LEFT
            if (upcoming_tile.y < static_cast<int>(y_ - collision_offset))
            {
                y_ -= velocity_;
                x_ += velocity_;

                if (static_cast<int>(y_ - collision_offset) < upcoming_tile.y)
                    y_ = static_cast<float>(upcoming_tile.y) + collision_offset;
            }

            //DOWN-LEFT
            if (upcoming_tile.y + static_cast<int>(collision_offset) > static_cast<int>(y_))
            {
                y_ += velocity_;
                x_ += velocity_;

                if (static_cast<int>(y_) > upcoming_tile.y + static_cast<int>(collision_offset))
                    y_ = static_cast<float>(upcoming_tile.y) + collision_offset;
            }

            break;
        }

        case Direction::UP:
        {

            //RIGHT-UP
            if (upcoming_tile.x > static_cast<int>(x_ - collision_offset))
            {
                x_ += velocity_;
                y_ += velocity_;

                if (static_cast<int>(x_ - collision_offset) > upcoming_tile.x)
                    x_ = static_cast<float>(upcoming_tile.x) + collision_offset;
            }

            //LEFT-UP
            if (upcoming_tile.x + static_cast<int>(collision_offset) < static_cast<int>(x_))
            {
                x_ -= velocity_;
                y_ += velocity_;

                if (static_cast<int>(x_) < upcoming_tile.x + static_cast<int>(collision_offset))
                    x_ = static_cast<float>(upcoming_tile.x) + collision_offset;
            }

            break;
        }

        case Direction::DOWN:
        {

            //RIGHT-DOWN
            if (upcoming_tile.x > static_cast<int>(x_ - collision_offset))
            {
                x_ += velocity_;
                y_ -= velocity_;

                if (static_cast<int>(x_ - collision_offset) > upcoming_tile.x)
                    x_ = static_cast<float>(upcoming_tile.x) + collision_offset;
            }

            //LEFT-DOWN
            if (upcoming_tile.x + static_cast<int>(collision_offset) < static_cast<int>(x_))
            {
                x_ -= velocity_;
                y_ -= velocity_;

                if (static_cast<int>(x_) < upcoming_tile.x + static_cast<int>(collision_offset))
                    x_ = static_cast<float>(upcoming_tile.x) + collision_offset;
            }

            break;
        }

        default:
            break;
    }
}