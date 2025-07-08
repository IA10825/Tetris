#include "Grid.h"
#include "TextureManager.h"
#include <iostream>
#include <bitset>

Grid::Grid(sf::Vector2u size) : size(size), cells(size.x* size.y), Box({0,0}, {size.x*1.f, size.y * 1.f }) {
	sprites.reserve(size.x * size.y);
	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			sf::Sprite sprite(TextureManager::get("block_void"));
			sprite.setPosition({ i * 30.f, j * 30.f });
			sprite.setScale({ 2.f,2.f });
			sprites.push_back(sprite);
		}
	}

	for (int i = 0; i < size.x * size.y; i++) {
		if (i < 44) {
			cells[i].type = static_cast<Figure::Type>(rand() % 8);
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
			switch (cells[i].type) {
			case Figure::Type::I:
				sprites[i].setTexture(TextureManager::get("block_6"));
				break;
			case Figure::Type::J:
				sprites[i].setTexture(TextureManager::get("block_5"));
				break;
			case Figure::Type::L:
				sprites[i].setTexture(TextureManager::get("block_2"));
				break;
			case Figure::Type::O:
				sprites[i].setTexture(TextureManager::get("block_3"));
				break;
			case Figure::Type::S:
				sprites[i].setTexture(TextureManager::get("block_1"));
				break;
			case Figure::Type::T:
				sprites[i].setTexture(TextureManager::get("block_7"));
				break;
			case Figure::Type::Z:
				sprites[i].setTexture(TextureManager::get("block_4"));
				break;
			default:
				sprites[i].setTexture(TextureManager::get("block_void"));
			}
		}
	}

sf::Vector2u Grid::getFieldSize() {
	return size;
}

sf::Vector2u Grid::getSize() {
	return { size.x * 15 * 2,size.y * 15 * 2 };
}

Grid::Cell::Cell() : type(Figure::Type::EMPTY) {
	isActive = true;
}

Grid::Cell::Cell(Figure::Type type) : type(type) {
	isActive = true;
}

bool Grid::has(int x, int y) const {
	if (y < 0 || y >= size.y || x < 0 || x >= size.x) return false;
	return true;
}

void Grid::swap(Cell& a, Cell& b) {
	Cell buffer = a;
	a = b;
	b = buffer;
}

Grid::Cell& Grid::at(unsigned x, unsigned y) {
	if (x >= size.x || y >= size.y) throw std::out_of_range("Grid::at() - coordinates out of range");
	return (cells[size.x * y + x]);
}

void Grid::step() {
	for (int j = size.y-1; j >= 0; j--) {
		for (int i = 0; i < size.x; i++) {
			if (at(i, j).isActive && has(i, j + 1)) {
				swap(at(i, j), at(i, j + 1));
			}
		}
	}
}

bool Grid::paste(const Figure& figure, unsigned r) {
	if (r > 3) throw std::out_of_range("Figure rotation out of range");
	std::bitset<64> mask;
	for (int i = 0; i < 64; i++) {
		mask.set(i, (i / 16) == r);
	}

	std::bitset<16> frame(((figure.blueprint & mask) >> 16 * r).to_ulong());

	for (int i = 0; i < 16; i++) {
		if (at(i % 4, i / 4).type != Figure::EMPTY) return false;
	}

	for (int i = 0; i < 16; i++) {
		if (frame[i]) at(i % 4, i / 4).type = Figure::L;
	}

	return true;
}