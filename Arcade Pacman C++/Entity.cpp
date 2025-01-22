#include "Entity.h"

#include "Map.h"

//------------------------------------------------CONSTRUCTORS--------------------------------------------
//--------------------------------------------------------------------------------------------------------

Entity::Entity()
{
	x_ = 0.0f;
	y_ = 0.0f;
	velocity_ = 0.0f;
	direction_ = Direction::RIGHT;
}

Entity::Entity(float velocity, Direction direction)
{
	x_ = 0.0f;
	y_ = 0.0f;
	velocity_ = velocity;
	direction_ = direction;
}

Entity::Entity(float x, float y, float velocity, Direction direction)
{
	x_ = x;
	y_ = y;
	velocity_ = velocity;
	direction_ = direction;
}

Entity::~Entity()
{

}

//------------------------------------------------GETTERS-------------------------------------------------
//--------------------------------------------------------------------------------------------------------

float Entity::getPositionX() const
{
	return x_;
}

float Entity::getPositionY() const
{
	return y_;
}

int Entity::getIntX() const
{
	return static_cast<int>(x_);
}

int Entity::getIntY() const
{
	return static_cast<int>(y_);
}

float Entity::getVelocity() const
{
	return velocity_;
}

Direction Entity::getDirection() const
{
	return direction_;
}

//------------------------------------------------SETTERS-------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void Entity::setPositionX(float x)
{
	x_ = x;
}

void Entity::setPositionY(float y)
{
	y_ = y;
}

void Entity::setCoordinates(float x, float y)
{
	x_ = x;
	y_ = y;
}

void Entity::setIntCoordinates(int x, int y)
{
    x_ = static_cast<float>(x);
    y_ = static_cast<float>(y);
}

void Entity::setVelocity(float velocity)
{
	velocity_ = velocity;
}

void Entity::setDirection(Direction direction)
{
	direction_ = direction;
}