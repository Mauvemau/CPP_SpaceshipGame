#pragma once

class Hud {
private: // Para redibujar unicamente si se cambiaron los valores.
	short previousAstCount;
	short previousLives;
	short previousScore;

public:

	Hud();
	~Hud();

	void init();
	void draw();
};