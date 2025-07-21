#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Figure.h"
#include "ui/Box.h"

class Grid : public Box {
public:
	Grid(sf::Vector2u);
	void update();
	void step();
	sf::Vector2u getFieldSize() const;
	sf::Vector2u getSize() const;
	const Figure* getCurrFigure() const;
	bool paste(const Figure& figure, unsigned rotation = 0, sf::Vector2u position = sf::Vector2u(0, 0));
	bool rotate();
	bool move(sf::Vector2i);

	struct Cell
	{
		Cell();
		Cell(Figure::Type type);
		Figure::Type type;
		bool isActive;
	};
private:
	void draw(sf::RenderTarget&, sf::RenderStates) const override;
	Cell* at(unsigned x, unsigned y);
	const Cell* at(unsigned x, unsigned y) const;
	Cell* fat(unsigned x, unsigned y);
	const Cell* fat(unsigned x, unsigned y) const;
	bool has(int x, int y) const;
	bool allows(const Figure&, sf::Vector2u position, int rotation) const;

	const sf::Vector2u size;
	std::vector<Cell> cells;
	std::vector<sf::Sprite> sprites;

	sf::Vector2u figurePos;
	unsigned figureRot = 0;
	const Figure* currFigure = nullptr;
};