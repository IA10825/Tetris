#pragma once
#include <SFML//Graphics.hpp>
#include "common/ExplicitSingleton.h"
#include <iostream>

class Keyboard : public ExplicitSingleton<Keyboard> {
public:
	bool isKeyPressed(sf::Keyboard::Key key) {
		return keysPressed[static_cast<int>(key)];
	}
	bool isKeyJustPressed(sf::Keyboard::Key key) {
		if (keysPressed[static_cast<int>(key)]) {
			keysPressed[static_cast<int>(key)] = 0;
			return true;
		}
		return false;
	}
	void handleEvent(const sf::Event& event) {
		if (event.is<sf::Event::KeyPressed>()) {
			keysPressed[static_cast<int>(event.getIf<sf::Event::KeyPressed>()->code)] = 1;
		}
		if (event.is<sf::Event::KeyReleased>()) {
			keysPressed[static_cast<int>(event.getIf<sf::Event::KeyReleased>()->code)] = 0;
		}
	}
private:
	bool keysPressed[sf::Keyboard::KeyCount]{};
};