#ifndef ENTITY_GHOST_H
#define ENTITY_GHOST_H

#include "Entity.h"
#include "Ghost_States.h"
#include "Ghost_Navigation.h"

class Pacman;

//A non-player controlled ghost entity.
class Ghost : public Entity, public GhostStates, public GhostNavigation
{
public:
	Ghost();
	Ghost(float velocity, Direction direction);
	Ghost(float x, float y, float velocity, Direction direction);
	~Ghost();

    //Manage direction changes
    void lookAhead(const Map& map, const Tile& target_tile);

    //Perform movement
    void move(const Map& map);

protected:
    //Assign direction based on state
    void updateMovement(const Map& map, const Tile& target_tile);

    //Turn at intersections
    void turnCorner(const Tile& upcoming_tile);

    //Bounce in cage
    void bounce(const Map& map);

    //Transition out of the cage
    void transitionOut(const Map& map);

    //Transition into cage after being eaten
    void transitionIn(const Map& map);

    //Reverse direction when swithing modes
    void reverseDirection();
};

#endif //ENTITY_GHOST_H
