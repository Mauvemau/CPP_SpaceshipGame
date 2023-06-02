#pragma once

#include "entity.h"

class Bullet : public Entity {
public:

	Bullet(Vector2 position, Color color);
	~Bullet();

	void draw() override;
	void update();

	EntityType getType() override;
};