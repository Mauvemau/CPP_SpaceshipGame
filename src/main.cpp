#include "game/game.h"

#include "AwesomeLibrary.h"

int main() {
	hideCursor();
	setForegroundColor(Color::WHITE);

	Game* game = new Game();
	
	setForegroundColor(Color::YELLOW);
	cout << "\nControles:\n[W][A] Para mover la nave.\n[D] Para disparar.\n[ESC] Para cerrar el juego.\n";
	cout << "\nObjetivo: 500 Puntos para ganar.\nSe pierde al perder todas las vidas.\n";
	setForegroundColor(Color::WHITE);
	cout << "\n(Presione cualquier tecla para continuar)";

	getKey(true);
	clearScreen();

	game->run();

	delete game;
	return 0;
}