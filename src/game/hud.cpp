#include "hud.h"
#include "game.h"

Hud::Hud() {
	previousAstCount = -1;
	previousLives = -1;
	previousScore = -1;
	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

Hud::~Hud() {
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

// Public

void Hud::init() {
	drawFrame(Game::getMargin().x, Game::getMargin().y, (Game::getBaseScreenWidth() - Game::getMargin().x), (Game::getBaseScreenHeight() - Game::getMargin().y));
}

void Hud::draw() {
	if (ObjectManager::getAsteroidCount() != previousAstCount) {
		goToCoordinates(1, 1);
		for (int i = 0; i < Game::getBaseScreenWidth() - 1; i++) {
			cout << " ";
		}
		goToCoordinates(1, 1);
		cout << "Asteroids: ";
		setForegroundColor(Color::YELLOW);
		cout << ObjectManager::getAsteroidCount();
		setForegroundColor(Color::WHITE);

		previousAstCount = ObjectManager::getAsteroidCount();
	}
	if (ObjectManager::getCurrentLives() != previousLives) {
		goToCoordinates(1, 2);
		for (int i = 0; i < Game::getBaseScreenWidth() - 1; i++) {
			cout << " ";
		}
		goToCoordinates(1, 2);
		cout << "Lives: ";
		setForegroundColor(Color::LRED);
		for (int i = 0; i < ObjectManager::getCurrentLives(); i++) {
			cout << char(03);
		}
		setForegroundColor(Color::WHITE);

		previousLives = ObjectManager::getCurrentLives();
	}
	if (Game::getScore() != previousScore) {
		goToCoordinates(1, 3);
		for (int i = 0; i < Game::getBaseScreenWidth() - 1; i++) {
			cout << " ";
		}
		goToCoordinates(1, 3);
		cout << "Score: ";
		setForegroundColor(Color::LGREEN);
		cout << Game::getScore();
		setForegroundColor(Color::WHITE);

		previousScore = Game::getScore();
	}

	if (Game::getStatus() == GameStatus::GAMEOVER) {
		goToCoordinates(static_cast<int>(Game::getBaseScreenWidth() * .475), static_cast<int>(Game::getBaseScreenHeight() * .5));
		setForegroundColor(Color::LRED);
		cout << "GAME OVER";
		setForegroundColor(Color::WHITE);
	}
	if (Game::getStatus() == GameStatus::VICTORY) {
		goToCoordinates(static_cast<int>(Game::getBaseScreenWidth() * .475), static_cast<int>(Game::getBaseScreenHeight() * .5));
		setForegroundColor(Color::LGREEN);
		cout << "Victory!";
		setForegroundColor(Color::WHITE);
	}
}