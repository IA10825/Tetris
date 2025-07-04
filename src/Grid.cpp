#include "Grid.h"
#include "TextureManager.h"
#include <iostream>

Grid::Grid(sf::Vector2u size) : size(size), cells(size.x*size.y)  {
	sprites.reserve(size.x * size.y);

	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			sf::Texture* texture = &TextureManager::getInstance().get("block_1");

			switch (rand() % 7) {
			case 0:
				texture = &TextureManager::getInstance().get("block_1");
				break;
			case 1:
				texture = &TextureManager::getInstance().get("block_2");
				break;
			case 2:
				texture = &TextureManager::getInstance().get("block_3");
				break;
			case 3:
				texture = &TextureManager::getInstance().get("block_4");
				break;
			case 4:
				texture = &TextureManager::getInstance().get("block_5");
				break;
			case 5:
				texture = &TextureManager::getInstance().get("block_6");
				break;
			case 6:
				texture = &TextureManager::getInstance().get("block_7");
				break;
			}

			sf::Sprite sprite(*texture);
			sprite.setPosition({ i*30.f, j*30.f });
			sprite.setScale({ 2.f, 2.f });
			sprites.push_back(sprite);
		}
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	for (int i = 0; i < size.x * size.y; i++) {
		target.draw(sprites[i], states);
	}
}

void Grid::update() {

}