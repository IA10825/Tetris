#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <array>
#include "Figure.h"

class Grid : public sf::Drawable, public sf::Transformable {
public:
	Grid(sf::Vector2u);
	void update();
	struct Cell
	{
		Cell(Figure type);
		const Figure type;
		bool isFixed;
	};
private:
	const sf::Vector2u size;
	std::vector<std::optional<Cell>> cells;
	std::vector<sf::Sprite> sprites;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};