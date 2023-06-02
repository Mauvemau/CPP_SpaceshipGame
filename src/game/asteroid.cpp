#include "asteroid.h"
#include "game.h"

Asteroid::Asteroid(Vector2 position, Color color) :
Entity(position, {1, 1}, color) {
	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

Asteroid::~Asteroid() {
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

void Asteroid::draw() {
	setForegroundColor(color);

	goToCoordinates(position.x, position.y);
	cout << char(79);

	setForegroundColor(Color::WHITE);
}

void Asteroid::update() {
	if (position.x > Game::getMargin().x + 1) {
		position.x--;
	}
}

EntityType Asteroid::getType() {
	return EntityType::ASTEROID;
}