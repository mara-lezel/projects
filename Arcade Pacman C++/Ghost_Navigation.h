#ifndef GHOST_NAVIGATION_H
#define GHOST_NAVIGATION_H

#include "Game_enums.h"

struct Tile;
class Map;


//A helper class for Ghost entity navigating through the maze.
//Main responsibility - choosing directions for requested movement pattern.
class GhostNavigation
{
public:
    //Get pre-emptive direction
    Direction getNextDirection() const;

    //Set pre-emtive direction (used only with ghosts exiting cage)
    void setNextDirection(Direction next_direction);

    //Reset navigation related properties
    void resetNavigation(Direction reset_direction);

protected:

    GhostNavigation();
    GhostNavigation(Direction next_direction);
    virtual ~GhostNavigation();


    //Choose next direction that puts ghost closest to target
    Direction chooseNextDirection(const Map& map, const Tile& target_tile, float current_x, float current_y, Direction current_direction);

    //Randomize direction from available options
    Direction chooseRandomDirection(const Map& map, float current_x, float current_y, Direction current_direction);

    //Get distance between two tiles
    int calculateDistance(const Tile& ghost_tile, const Tile& target_tile);

    //Get priority rating associated with direction
    int priorityScore(Direction direction);

protected:
    //Keeping track of starting tiles to see when ghost moves from a tile;
    //Used in direction assignment function (READ "Ghost_lookAhead.cpp").
    int start_tile_x_;
    int start_tile_y_;

    Direction next_direction_;
};

#endif //GHOST_NAVIGATION_H
