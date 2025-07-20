#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"

class Button : public Box {
public:
	Button(sf::Vector2f, sf::Vector2f, sf::Texture&);
	bool isHovered(sf::Window& window);
	bool isPressed(sf::Window& window);
	bool isJustPressed(sf::Window& window);
	void setSize(sf::Vector2f);
	void setTexture(sf::Texture&);
	void update(sf::Window& window);
private:
	sf::Sprite sprite;
	bool wasPressedLastFrame;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};