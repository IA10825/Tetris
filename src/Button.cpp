#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture texture, unsigned outlineThickness) : rect(position, size), sprite(texture), body(size) {
	this->texture = texture;
	this->wasPressedLastFrame = false;
	this->outlineThickness = outlineThickness;

	outline[0].setFillColor(sf::Color::White);
	outline[1].setFillColor(sf::Color::White);
	outline[2].setFillColor(sf::Color::White);
	outline[3].setFillColor(sf::Color::White);

	setPosition(position);
	sprite.setTexture(this->texture);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(body, states);
	target.draw(outline[0], states);
	target.draw(outline[1], states);
	target.draw(outline[2], states);
	target.draw(outline[3], states);

	target.draw(sprite, states);
}

void Button::update(sf::Window& window) {
	body.setSize(static_cast<sf::Vector2f>(rect.size));
	sprite.setPosition({ rect.size.x / 2 - sprite.getTexture().getSize().x / 2,rect.size.y / 2 - sprite.getTexture().getSize().y / 2 });

	if (isPressed(window)) {
		body.setFillColor(sf::Color(75, 75, 75, 255));
	}
	else if (isHovered(window)) {
		body.setFillColor(sf::Color(35, 35, 35, 255));
	}
	else {
		body.setFillColor(sf::Color(25, 25, 25, 255));
	}

	outline[0].setPosition({ -static_cast<int>(outlineThickness) * 1.f, -static_cast<int>(outlineThickness) * 1.f });
	outline[0].setSize({ rect.size.x + outlineThickness, outlineThickness * 1.f });

	outline[1].setPosition({ rect.size.x, -static_cast<int>(outlineThickness) * 1.f });
	outline[1].setSize({ outlineThickness * 1.f, rect.size.y + outlineThickness });

	outline[2].setPosition({ 0, rect.size.y });
	outline[2].setSize({ rect.size.x + outlineThickness, outlineThickness * 1.f });

	outline[3].setPosition({ -static_cast<int>(outlineThickness) * 1.f, 0 });
	outline[3].setSize({ outlineThickness * 1.f, rect.size.y + outlineThickness });

	sprite.setTexture(texture);
	wasPressedLastFrame = isPressed(window);
}

bool Button::isHovered(sf::Window& window) {
	return rect.contains({ sf::Mouse::getPosition(window).x * 1.f,sf::Mouse::getPosition(window).y * 1.f });
}

bool Button::isPressed(sf::Window& window) {
	return rect.contains({ sf::Mouse::getPosition(window).x * 1.f,sf::Mouse::getPosition(window).y * 1.f }) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool Button::isJustPressed(sf::Window& window) {
	return rect.contains({ sf::Mouse::getPosition(window).x * 1.f,sf::Mouse::getPosition(window).y * 1.f }) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !wasPressedLastFrame;
}

void Button::setSize(sf::Vector2f size) {
	rect.size = size;
}

void Button::setTexture(sf::Texture texture) {
	this->texture = texture;
}