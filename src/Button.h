#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable {
public:
	Button(sf::Vector2f, sf::Vector2f, sf::Texture&, unsigned = 1);
	bool isHovered(sf::Window& window);
	bool isPressed(sf::Window& window);
	bool isJustPressed(sf::Window& window);
	void setSize(sf::Vector2f);
	void setTexture(sf::Texture*);
	void update(sf::Window& window);
private:
	sf::Sprite sprite;
	sf::RectangleShape outline[4];
	sf::RectangleShape body;

	unsigned outlineThickness;
	bool wasPressedLastFrame;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Rect<float> rect;
};