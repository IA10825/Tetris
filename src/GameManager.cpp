#include "GameManager.h"
#include "TextureManager.h"
#include <iostream>

GameManager::GameManager() : size(380, 200) {
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::get("play"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::get("reset"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::get("volume_on"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::get("exit"));

	Figure figura(0b0000'1111'0000'0000'0100'0100'0100'0100'0000'0000'1111'0000'0010'0010'0010'0010);

	grid = new Grid({ 10,20 });
	size.y = grid->getSize().y;
	grid->step();
	grid->step();
	grid->step();
	grid->step();
	grid->paste(figura, 3);
}

void GameManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < buttons.size(); i++) {
		target.draw(buttons[i], states);
	}
	target.draw(*grid, states);
}

void GameManager::update(sf::Window& window) {
	if (buttons[3].isJustPressed(window)) window.close();
	if (buttons[0].isJustPressed(window)) {
		isPaused = !isPaused;
		buttons[0].setTexture(isPaused ? TextureManager::get("pause") : TextureManager::get("play"));
	}

	sf::Vector2f position({ window.getSize().x / 2.f - size.x / 2,window.getSize().y / 2.f - size.y / 2 });

	grid->setPosition({ position.x + size.x - grid->getSize().x, position.y });
	grid->update();

	unsigned offset = 0;
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].setPosition({ position.x, position.y + offset });
		buttons[i].update(window);
		offset += 50;
	}
}