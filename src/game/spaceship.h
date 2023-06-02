#pragma once

#include "entity.h"

class Spaceship : public Entity {
private:
	int lives;
	float reloadInterval;

public:

	Spaceship(Vector2 position, Color color, int lives);
	~Spaceship();

	void draw() override;

	EntityType getType() override;

	void setLives(int lives);
	int getLives();
	float getReloadInterval();
};