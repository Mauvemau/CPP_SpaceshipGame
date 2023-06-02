#include "bullet.h"
#include "game.h"

Bullet::Bullet(Vector2 position, Color color) :
Entity(position, { 1, 1 }, color) {
	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

Bullet::~Bullet() {
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

void Bullet::draw() {
	setForegroundColor(color);

	goToCoordinates(position.x, position.y);
	cout << char(79);

	setForegroundColor(Color::WHITE);
}

void Bullet::update() {
	if (position.x < Game::getBaseScreenWidth() - Game::getMargin().x - 1) {
		position.x++;
	}
}

EntityType Bullet::getType() {
	return EntityType::BULLET;
}