#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Figure.h"
#include "Box.h"

class Grid : public Box {
public:
	Grid(sf::Vector2u);
	void update();
	void step();
	struct Cell
	{
		Cell();
		Cell(Figure::Type type);
		Figure::Type type;
		bool isActive;
	};
	sf::Vector2u getFieldSize();
	sf::Vector2u getSize();
private:
	const sf::Vector2u size;
	std::vector<Cell> cells;
	std::vector<sf::Sprite> sprites;
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	Cell& at(unsigned x, unsigned y);
	void swap(Cell& a, Cell& b);
	bool has(int x, int y) const;
};