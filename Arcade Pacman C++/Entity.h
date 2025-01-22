#ifndef ENTITY_H
#define ENTITY_H

#include "Game_enums.h"

class Map;
struct Tile;

//An entity defined by its position on 2D plane, movement speed and movement direction.
class Entity
{
public:
   
    Entity();
    Entity(float velocity, Direction direction);
    Entity(float x, float y, float velocity, Direction direction);
    virtual ~Entity();

    //--------------------------------------------------------------INTERFACE---------------------------------
    //--------------------------------------------------------------------------------------------------------

    //Perform movement based on direction
    virtual void move(const Map& map) = 0;

    //Enter/exit tunnel
    void tunnelTransition(const Map& map);
 
    //--------------------------------------------------------------GETTERS&SETTERS---------------------------
    //--------------------------------------------------------------------------------------------------------

    //Getter methods
    float getPositionX() const;
    float getPositionY() const;
    int getIntX() const;
    int getIntY() const;
    float getVelocity() const;
    Direction getDirection() const;

    //Setter methods
    void setPositionX(float x);
    void setPositionY(float y);
    void setCoordinates(float x, float y);
    void setIntCoordinates(int x, int y);
    void setVelocity(float velocity);
    void setDirection(Direction direction);

protected:
    float x_;
    float y_;
    float velocity_;
    Direction direction_;
};

#endif //ENTITY_H
