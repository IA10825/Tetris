#include "Grid.h"
#include "TextureManager.h"
#include <iostream>

Grid::Grid(sf::Vector2u size) : size(size), cells(size.x* size.y), Box({0,0}, {size.x*1.f, size.y * 1.f }) {
	sprites.reserve(size.x * size.y);

	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			sf::Sprite sprite(TextureManager::getInstance().get("block_void"));
			sprite.setPosition({ i * 30.f, j * 30.f });
			sprite.setScale({ 2.f,2.f });
			sprites.push_back(sprite);
		}
	}

	for (int i = 0; i < size.x * size.y; i++) {
		if (i < 44) {
			cells[i].emplace(Figure::Type::Z);
		}
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	Box::draw(target, states);
	states.transform *= getTransform();
	for (int i = 0; i < size.x * size.y; i++) {
		target.draw(sprites[i], states);
	}
}

void Grid::update() {
	setSize({ size.x * 30.f, size.y * 30.f });
	Box::update();

	for (int i = 0; i < size.x * size.y; i++) {
		if (cells[i]) {
			switch (cells[i].value().type) {
			case Figure::Type::I:
				sprites[i].setTexture(TextureManager::getInstance().get("block_6"));
				break;
			case Figure::Type::J:
				sprites[i].setTexture(TextureManager::getInstance().get("block_5"));
				break;
			case Figure::Type::L:
				sprites[i].setTexture(TextureManager::getInstance().get("block_2"));
				break;
			case Figure::Type::O:
				sprites[i].setTexture(TextureManager::getInstance().get("block_3"));
				break;
			case Figure::Type::S:
				sprites[i].setTexture(TextureManager::getInstance().get("block_1"));
				break;
			case Figure::Type::T:
				sprites[i].setTexture(TextureManager::getInstance().get("block_7"));
				break;
			case Figure::Type::Z:
				sprites[i].setTexture(TextureManager::getInstance().get("block_4"));
				break;
			}
		}
		else {
			sprites[i].setTexture(TextureManager::getInstance().get("block_void"));
		}
	}
}

sf::Vector2u Grid::getFieldSize() {
	return size;
}

sf::Vector2u Grid::getSize() {
	return { size.x * 15 * 2,size.y * 15 * 2 };
}

Grid::Cell::Cell(Figure::Type type) : type(type) {
	isActive = true;
}

