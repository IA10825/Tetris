#include "Keyboard.h"
#include <bitset>
#include <iostream>

void Keyboard::update() {
	for (int i = 0; i < 100; i++) {
		keysPressedLastFrame[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
	}
}

bool Keyboard::isKeyPressed(sf::Keyboard::Key key) {
	return sf::Keyboard::isKeyPressed(key);
}

bool Keyboard::isKeyJustPressed(sf::Keyboard::Key key) {
	if (sf::Keyboard::isKeyPressed(key)) {
		if (!keysPressedLastFrame[static_cast<int>(key)]) return true;
	}
	return false;
}