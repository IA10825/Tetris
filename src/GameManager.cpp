#include "GameManager.h"
#include "TextureManager.h"

GameManager::GameManager() : size(380, 200) {
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("play"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("reset"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("volume_on"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("exit"));

	grid = new Grid({10,20});
	size.y = grid->getSize().y;
}

void GameManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < buttons.size(); i++) {
		target.draw(buttons[i], states);
	}
	target.draw(*grid, states);
}

void GameManager::update(sf::Window& window) {
	if (buttons[3].isJustPressed(window)) window.close();

	sf::Vector2f position({window.getSize().x / 2.f - size.x/2,window.getSize().y / 2.f - size.y / 2 });

	grid->setPosition({ position.x + size.x - grid->getSize().x, position.y});
	grid->update();
	
	unsigned offset = 0;
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].setPosition({ position.x, position.y + offset });
		buttons[i].update(window);
		offset += 50;
	}
}