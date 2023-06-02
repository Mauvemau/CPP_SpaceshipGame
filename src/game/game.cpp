#include "game.h"

#include <thread>
#include <iostream>

using namespace std;

int Game::score = 0;
GameStatus Game::currentStatus = GameStatus::PLAYING;
Vector2 Game::baseWindowSize = { getScreenWidth(), getScreenHeight() };
Vector2 Game::windowMargin = { 8, 4 };
chrono::steady_clock::time_point Game::startTime = chrono::steady_clock::now();

Game::Game() {
	om = new ObjectManager(.05f, 1);
	hud = new Hud();
	exit = false;
	if (Settings::getEcho()) cout << typeid(this).name() << " was created!\n";
}

Game::~Game() {
	delete om;
	delete hud;
	if (Settings::getEcho()) cout << typeid(this).name() << " was destroyed!\n";
}

// private

void Game::update() {
	do {
		om->update();
		hud->draw();
		om->draw();
	} while (!exit);
}

void Game::control() {
	int key = 0;
	do {
		key = getKey(true);
		om->control(key, exit);
	} while (!exit);
}

// public

void Game::run() {
	Settings::setEcho(false);

	// Program Start
	hideCursor();
	hud->init();

	// Usé multithreading para solucionar el problema de input y dibujado para juegos de acción en consola.
	thread tupd(&Game::update, this);
	thread tctr(&Game::control, this);

	tupd.join();
	tctr.join();

	// Program End

	Settings::setEcho(true);

	goToCoordinates(0, 0);
	clearScreen();
}

// Static

void Game::incrementScore(int increment) {
	score += increment;
}

int Game::getScore() {
	return score;
}

void Game::setStatus(GameStatus status) {
	currentStatus = status;
}

GameStatus Game::getStatus() {
	return currentStatus;
}

float Game::getTime() {
	float curTime = (static_cast<int>(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count())) * .001f;
	return curTime;
}

Vector2 Game::getMargin() {
	return windowMargin;
}

int Game::getBaseScreenWidth() {
	return baseWindowSize.x;
}

int Game::getBaseScreenHeight() {
	return baseWindowSize.y;
}