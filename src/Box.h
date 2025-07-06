#pragma once
#include <SFML/Graphics.hpp>

class Box : public sf::Drawable, public sf::Transformable, private sf::Rect<float> {
public:
	Box(sf::Vector2f position, sf::Vector2f size);
	void update();
	void setSize(sf::Vector2f size);
	sf::Vector2f getSize();
	void setOutlineThickness(unsigned thickness);
	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color);
	bool contains(sf::Vector2f coordinate);
protected:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
	unsigned outlineThickness;
	sf::RectangleShape body;
	sf::RectangleShape outline;
};