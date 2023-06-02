#include "spaceship.h"

#include <iostream>

using namespace std;

Spaceship::Spaceship(Vector2 position, Color color, int lives) :
Entity(position, {6, 5}, color) {
	this->lives = lives;
	this->reloadInterval = 1;

	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

Spaceship::~Spaceship() {
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

void Spaceship::draw() {
	setForegroundColor(color); // Redibujamos la nave.

	goToCoordinates(position.x, position.y);
	cout << char(205) << char(205) << char(187);
	goToCoordinates(position.x, position.y + 1);
	cout << "  " << char(111) << char(175);
	goToCoordinates(position.x, position.y + 2);
	cout << " " << char(91) << char(204) << char(93) << char(205) << char(62);
	goToCoordinates(position.x, position.y + 3);
	cout << "  " << char(111) << char(175);
	goToCoordinates(position.x, position.y + 4);
	cout << char(205) << char(205) << char(188);

	setForegroundColor(Color::WHITE);
}

EntityType Spaceship::getType() {
	return EntityType::SPACESHIP;
}

void Spaceship::setLives(int lives) {
	this->lives = lives;
}

int Spaceship::getLives() {
	return lives;
}

float Spaceship::getReloadInterval() {
	return reloadInterval;
}