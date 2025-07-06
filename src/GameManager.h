#pragma once 
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Grid.h"
#include <vector>


class GameManager : public sf::Drawable, private sf::Transformable {
public:
	GameManager();
	void update(sf::Window&);

	const sf::Vector2u size{200, 200};
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<Button> buttons;
	Grid* grid;
};