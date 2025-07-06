#include "GameManager.h"
#include "TextureManager.h"

GameManager::GameManager() {
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("play"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("play"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("play"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::getInstance().get("play"));

	grid = new Grid({5,5});
}

void GameManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < buttons.size(); i++) {
		target.draw(buttons[i], states);
	}
	target.draw(*grid, states);
}

void GameManager::update(sf::Window& window) {
	setPosition({ window.getSize().x / 2.f - size.x,window.getSize().y / 2.f - size.y });

	(*grid).setPosition({ getPosition().x+size.x-(*grid).getSize().x,getPosition().y});
	(*grid).update();
	
	unsigned offset = 0;
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].setPosition({ getPosition().x, getPosition().y + offset });
		buttons[i].update(window);
		offset += 50;
	}
}