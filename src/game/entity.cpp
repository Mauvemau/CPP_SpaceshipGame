#include "entity.h"

#include <iostream>

using namespace std;

Entity::Entity(Vector2 position, Vector2 scale, Color color) {
	this->position = position;
	this->scale = scale;
	this->color = color;

	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

Entity::~Entity() {
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

void Entity::move(Vector2 direction) {
	position = { position.x + direction.x, position.y + direction.y };
}

void Entity::setPosition(Vector2 position) {
	this->position = position;
}

Vector2 Entity::getPosition() {
	return position;
}

Vector2 Entity::getScale() {
	return scale;
}

bool Entity::isColliding(Entity* target) {
	if (target->getScale().x < 2) {
		return (this->position.x < target->getPosition().x + (target->getScale().x + 1) &&
			this->position.x + (this->scale.x + 1) > target->getPosition().x &&
			this->position.y < target->getPosition().y + target->getScale().y &&
			this->position.y + this->scale.y > target->getPosition().y);
	}
	else {
		return (this->position.x < target->getPosition().x + target->getScale().x &&
			this->position.x + this->scale.x > target->getPosition().x &&
			this->position.y < target->getPosition().y + target->getScale().y &&
			this->position.y + this->scale.y > target->getPosition().y);
	}
}