#include "Box.h"

Box::Box(sf::Vector2f position, sf::Vector2f size) : Rect(position, size), body(size) {
	setPosition(position);
	for (int i = 0; i < 4; i++) {
		outline[i].setFillColor(sf::Color::White);
	}
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(body, states);
	for (int i = 0; i < 4; i++) {
		target.draw(outline[i], states);
	}
}

void Box::update() {
	position = getPosition();
	body.setSize(size);

	outline[0].setPosition({0,-1});
	outline[0].setSize({ size.x+1,1 });

	outline[1].setPosition({ size.x,0 });
	outline[1].setSize({ 1,size.y+1 });

	outline[2].setPosition({ -1,size.y });
	outline[2].setSize({ size.x+1,1 });

	outline[3].setPosition({ -1,-1 });
	outline[3].setSize({ 1,size.y+1 });
}

void Box::setSize(sf::Vector2f size) {
	this->size = size;
}