#pragma once

#include "structs.h"
#include "settings.h"

#include "AwesomeLibrary.h"

enum class EntityType {
	SPACESHIP,
	ASTEROID,
	BULLET
};

class Entity {
protected:
	Vector2 position;
	Vector2 scale;
	Color color;

public:

	Entity(Vector2 position, Vector2 scale, Color color);
	virtual ~Entity();

	virtual void draw() = 0;
	void move(Vector2 direction);

	void setPosition(Vector2 position);

	virtual EntityType getType() = 0;
	Vector2 getPosition();
	Vector2 getScale();

	bool isColliding(Entity* target);
};