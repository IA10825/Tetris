#include "Box.h"
#include <iostream>

Box::Box(sf::Vector2f position, sf::Vector2f size) : Rect(position, size), body(size), outlineThickness(2) {
	setPosition(position);
	outline.setFillColor(sf::Color::White);
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(outline, states);
	target.draw(body, states);
}

void Box::update() {
	position = getPosition();
	outline.setPosition({ -static_cast<float>(outlineThickness), -static_cast<float>(outlineThickness) });
	outline.setSize({ size.x + outlineThickness * 2,size.y + outlineThickness * 2 });
	body.setSize(size);
}

void Box::setSize(sf::Vector2f size) {
	this->size = size;
}

sf::Vector2f Box::getSize() {
	return size;
}

void Box::setOutlineThickness(unsigned thickness) {
	outlineThickness = thickness;
}

void Box::setFillColor(sf::Color color) {
	body.setFillColor(color);
}

void Box::setOutlineColor(sf::Color color) {
	outline.setFillColor(color);
}

bool Box::contains(sf::Vector2f coordinate) {
	return Rect::contains(coordinate);
}