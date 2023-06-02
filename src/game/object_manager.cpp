#include "object_manager.h"
#include "game.h"
#include "utils.h"

unsigned short ObjectManager::currentAsteroidCount = 0;
unsigned short ObjectManager::currentBulletCount = 0;
unsigned short ObjectManager::currentEntityCount = 0;
unsigned short ObjectManager::currentSpaceshipLives = 0;

ObjectManager::ObjectManager(float updateInterval, float spawnInterval) {
	this->updateInterval = updateInterval;
	nextUpdate = 0;
	this->spawnInterval = spawnInterval;
	nextSpawn = 0;
	nextReload = 0;

	spaceship = new Spaceship(Vector2{ (Game::getMargin().x + 4), static_cast<int>(Game::getBaseScreenHeight() * .45) }, Color::LGREEN, 3);
	entities[currentEntityCount] = spaceship;
	currentEntityCount++;
	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

ObjectManager::~ObjectManager() {
	for (int i = 0; i < currentEntityCount; i++) {
		delete entities[i];
	}
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

// private

void ObjectManager::addEraseQueue(Vector2 pos, Vector2 scale) {
	for (int y = pos.y; y < pos.y + scale.y; y++) {
		for (int x = pos.x; x < pos.x + scale.x; x++) {
			erasePosition.push({ x, y });
		}
	}
}

void ObjectManager::updateEntities() {
	currentEntityCount = 0;
	entities[currentEntityCount] = spaceship;
	currentEntityCount++;
	for (int i = 0; i < currentBulletCount; i++) {
		entities[currentEntityCount] = bullets[i];
		currentEntityCount++;
	}
	for (int i = 0; i < currentAsteroidCount; i++) {
		entities[currentEntityCount] = asteroids[i];
		currentEntityCount++;
	}
}

void ObjectManager::createAsteroid() {
	if (currentAsteroidCount < 19) {
		asteroids[currentAsteroidCount] = new Asteroid({ 
			Game::getBaseScreenWidth() - Game::getMargin().x - 1,
			Utils::getRandomInt((Game::getMargin().y + 1), (Game::getBaseScreenHeight() - Game::getMargin().y - 1))}, 
			Color::LRED);
		entities[currentEntityCount] = asteroids[currentAsteroidCount];
		currentAsteroidCount++;
		updateEntities();
	}
}

void ObjectManager::createBullet() {
	if (currentBulletCount < 20) {
		bullets[currentBulletCount] = new Bullet(
		{ spaceship->getPosition().x + 4, spaceship->getPosition().y + 1 }, Color::YELLOW);
		entities[currentEntityCount] = bullets[currentBulletCount];
		currentBulletCount++;
		updateEntities();
	}
	if (currentBulletCount < 20) {
		bullets[currentBulletCount] = new Bullet(
		{ spaceship->getPosition().x + 4, spaceship->getPosition().y + 3 }, Color::YELLOW);
		entities[currentEntityCount] = bullets[currentBulletCount];
		currentBulletCount++;
		updateEntities();
	}
}

void ObjectManager::destroyAsteroid(int id) {
	delete asteroids[id];
	if (currentAsteroidCount > 1) {
		asteroids[id] = new Asteroid(asteroids[currentAsteroidCount - 1]->getPosition(), Color::LRED);
		//delete asteroids[currentAsteroidCount - 1];
	}
	currentAsteroidCount--;
	updateEntities();
}

void ObjectManager::destroyBullet(int id) {
	delete bullets[id];
	if (currentBulletCount > 1) {
		bullets[id] = new Bullet(bullets[currentBulletCount - 1]->getPosition(), Color::YELLOW);
		//delete asteroids[currentBulletCount - 1];
	}
	currentBulletCount--;
	updateEntities();
}

// public

void ObjectManager::draw() {
	while (!erasePosition.empty()) {
		goToCoordinates(erasePosition.front().x, erasePosition.front().y);
		cout << " ";
		erasePosition.pop();
	}

	for (int i = 0; i < currentEntityCount; i++) {
		entities[i]->draw();
	}
}

void ObjectManager::update() {
	currentSpaceshipLives = spaceship->getLives();
	if (Game::getStatus() == GameStatus::PLAYING) {
		if (nextUpdate < Game::getTime()) {
			nextUpdate = Game::getTime() + updateInterval;

			// -- Checkeo de Colisiones.

			// Bullet -> Asteroid
			for (int b = 0; b < currentBulletCount; b++) {
				for (int a = 0; a < currentAsteroidCount; a++) {
					if (bullets[b]->isColliding(asteroids[a])) {
						addEraseQueue(bullets[b]->getPosition(), bullets[b]->getScale());
						addEraseQueue(asteroids[a]->getPosition(), asteroids[a]->getScale());
						destroyBullet(b);
						destroyAsteroid(a);
						b = 0;
						a = 0;
						Game::incrementScore(15);
					}
				}
			}

			// Asteroid -> Spaceship
			for (int i = 0; i < currentAsteroidCount; i++) {
				if (asteroids[i]->isColliding(spaceship)) {
					addEraseQueue(asteroids[i]->getPosition(), asteroids[i]->getScale());
					destroyAsteroid(i);
					i = 0;
					spaceship->setLives(spaceship->getLives() - 1);
				}
			}

			// Bullet -> Wall
			for (int i = 0; i < currentBulletCount; i++) {
				if (bullets[i]->getPosition().x >= (Game::getBaseScreenWidth() - Game::getMargin().x - 1)) {
					addEraseQueue(bullets[i]->getPosition(), bullets[i]->getScale());
					destroyBullet(i);
				}
			}

			// Asteroid -> Wall
			for (int i = 0; i < currentAsteroidCount; i++) {
				if (asteroids[i]->getPosition().x <= Game::getMargin().x + 1) {
					addEraseQueue(asteroids[i]->getPosition(), asteroids[i]->getScale());
					destroyAsteroid(i);
					createAsteroid();
				}
			}

			// --  Updateo de Movimiento.

			for (int i = 0; i < currentAsteroidCount; i++) {
				addEraseQueue(asteroids[i]->getPosition(), asteroids[i]->getScale());
				asteroids[i]->update();
			}
			for (int i = 0; i < currentBulletCount; i++) {
				addEraseQueue(bullets[i]->getPosition(), bullets[i]->getScale());
				bullets[i]->update();
			}

			// -- Logica de Juego.

			if (nextSpawn < Game::getTime()) {
				nextSpawn = Game::getTime() + spawnInterval;
				createAsteroid();
			}

			if (getCurrentLives() <= 0) {
				Game::setStatus(GameStatus::GAMEOVER);
			}
			if (Game::getScore() >= 500) {
				Game::setStatus(GameStatus::VICTORY);
			}

		}
	}
}

void ObjectManager::control(int key, bool& exit) {
	if (Game::getStatus() == GameStatus::PLAYING) {
		if (spaceship->getPosition().y > 1 + Game::getMargin().y && key == 119 || key == 87) {
			addEraseQueue(spaceship->getPosition(), spaceship->getScale());
			spaceship->move({ 0, -1 });
		}
		if (spaceship->getPosition().y < 30 - Game::getMargin().y - spaceship->getScale().y && key == 115 || key == 83) {
			addEraseQueue(spaceship->getPosition(), spaceship->getScale());
			spaceship->move({ 0, 1 });
		}
		if (nextReload < Game::getTime() && key == 100 || key == 68) {
			nextReload = Game::getTime() + spaceship->getReloadInterval();
			createBullet();
		}
	}


	if (key == KEY_ESC) {
		exit = true;
	}
}

short ObjectManager::getAsteroidCount() {
	return currentAsteroidCount;
}

short ObjectManager::getCurrentLives() {
	return currentSpaceshipLives;
}