#include "utils.h"

#include <iostream>

void Utils::generateSeed() {
	srand(static_cast<unsigned int>(time(NULL)));
}

int Utils::getRandomInt(int min, int max) {
	if (min > max) { // En caso de poner los valores al revez.
		int aux = max;
		max = min;
		min = aux;
	}

	return (rand() % (abs(max - min) + 1) + min);
}