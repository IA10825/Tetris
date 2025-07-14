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
	sf::Vector2u getFieldSize();
	sf::Vector2u getSize();
	bool paste(const Figure& figure, unsigned rotation = 0, sf::Vector2u position = sf::Vector2u(0, 0));
	bool rotate(const Figure& figure);

	struct Cell
	{
		Cell();
		Cell(Figure::Type type);
		Figure::Type type;
		bool isActive;
	};
private:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	Cell& at(unsigned x, unsigned y);
	void swap(Cell& a, Cell& b);
	bool has(int x, int y) const;

	const sf::Vector2u size;
	std::vector<Cell> cells;
	std::vector<sf::Sprite> sprites;
	sf::Vector2u figurePos;
	unsigned figureRot = 0;
};