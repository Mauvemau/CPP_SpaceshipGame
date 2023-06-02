#pragma once

#include "object_manager.h"
#include "hud.h"

#include <chrono>

enum class GameStatus {
	PLAYING,
	GAMEOVER,
	VICTORY
};

class Game {
private:
	ObjectManager* om;
	Hud* hud;
	bool exit;
	
	static int score;
	static GameStatus currentStatus;
	static Vector2 baseWindowSize; // Me guardo el tamaño inicial de la consola en caso de que el jugador decida cambiar el tamaño de esta en pleno gameplay.
	static Vector2 windowMargin; // Para el marquito.
	static chrono::steady_clock::time_point startTime; // Timer.

	void update();
	void control();

public:

	Game();
	~Game();

	void run();

	static void incrementScore(int increment);
	static int getScore();
	static void setStatus(GameStatus status);
	static GameStatus getStatus();
	static float getTime();
	static Vector2 getMargin();
	static int getBaseScreenWidth();
	static int getBaseScreenHeight();
};