#pragma once

#include "entity.h"

class Asteroid : public Entity {
public:

	Asteroid(Vector2 position, Color color);
	~Asteroid();

	void draw() override;
	void update();

	EntityType getType() override;
};