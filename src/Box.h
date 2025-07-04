#pragma once
#include <SFML/Graphics.hpp>

class Box : public sf::Drawable, public sf::Transformable, public sf::Rect<float> {
public:
	Box(sf::Vector2f, sf::Vector2f);
	void update();
	void setSize(sf::Vector2f);
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	sf::RectangleShape body;
	sf::RectangleShape outline[4];
};