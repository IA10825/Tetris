#pragma once 
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Grid.h"
#include <vector>
#include "Keyboard.h"


class GameManager : public sf::Drawable {
public:
	GameManager();
	void update(sf::Window&);

	sf::Vector2u size;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<Button> buttons;
	Grid* grid;
	Keyboard* keyboard;

	bool isPaused = false;
};