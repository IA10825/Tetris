#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture) : sprite(texture), Box(position, size) {
	this->wasPressedLastFrame = false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	Box::draw(target, states);

	states.transform *= getTransform();
	target.draw(sprite, states);
}

void Button::update(sf::Window& window) {
	Box::update();
	sprite.setPosition({ size.x / 2 - sprite.getTexture().getSize().x / 2,size.y / 2 - sprite.getTexture().getSize().y / 2 });

	if (isPressed(window)) {
		body.setFillColor(sf::Color(75, 75, 75, 255));
	}
	else if (isHovered(window)) {
		body.setFillColor(sf::Color(35, 35, 35, 255));
	}
	else {
		body.setFillColor(sf::Color(0, 0, 0, 255));
	}

	wasPressedLastFrame = isPressed(window);
}

bool Button::isHovered(sf::Window& window) {
	return contains({ sf::Mouse::getPosition(window).x * 1.f,sf::Mouse::getPosition(window).y * 1.f });
}

bool Button::isPressed(sf::Window& window) {
	return contains({ sf::Mouse::getPosition(window).x * 1.f,sf::Mouse::getPosition(window).y * 1.f }) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool Button::isJustPressed(sf::Window& window) {
	return contains({ sf::Mouse::getPosition(window).x * 1.f,sf::Mouse::getPosition(window).y * 1.f }) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !wasPressedLastFrame;
}

void Button::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}