#pragma once

class Settings {
private:

	static bool echo; // TRUE: Imprime en consola cuando se crea o destruye un objeto | FALSE: No imprime en consola cuando se crea o destruye un objeto.

public:

	static void setEcho(bool _echo);

	static bool getEcho();

};