#pragma once

#include "spaceship.h"
#include "asteroid.h"
#include "bullet.h"

#include <queue>
#include <iostream>

class ObjectManager {
private:
	static unsigned short currentAsteroidCount;
	static unsigned short currentBulletCount;
	static unsigned short currentEntityCount;
	static unsigned short currentSpaceshipLives;

	Spaceship* spaceship;
	Asteroid* asteroids[19];
	Bullet* bullets[20];
	Entity* entities[40] = { NULL };

	queue<Vector2> erasePosition; /* Ya que unicamente el thread de dibujado se encarga de manejar el cursor, 
									 ponemos todas las posiciones que tiene que borrar en una cola asi limpia todo antes de redibujarlas en su posicion nueva.*/

	float updateInterval; /* Esto le pone un limite a cuantas veces por segundo el thread de update actualiza el juego. 
							 En cambio el thread the input y dibujado funcionan a maxima velocidad.*/
	float nextUpdate;

	float spawnInterval; // Para los asteroides en la logica de juego.
	float nextSpawn;

	float nextReload; // Para la nave.

	void addEraseQueue(Vector2 pos, Vector2 scale);

	void updateEntities();

	void createAsteroid();
	void createBullet();

	void destroyAsteroid(int id);
	void destroyBullet(int id);

public:

	ObjectManager(float updateInterval, float spawnInterval);
	~ObjectManager();

	void draw();
	void update();

	void control(int key, bool &exit);

	static short getAsteroidCount();
	static short getCurrentLives();
};