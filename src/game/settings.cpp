#include "settings.h"

bool Settings::echo = true;

void Settings::setEcho(bool _echo) {
	echo = _echo;
}

bool Settings::getEcho() {
	return echo;
}