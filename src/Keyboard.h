#pragma once
#include <SFML//Graphics.hpp>
#include <vector>

class Keyboard {
public:
	bool isKeyPressed(sf::Keyboard::Key);
	bool isKeyJustPressed(sf::Keyboard::Key);
	
	void update();
private:
	bool keysPressedLastFrame[100];
};