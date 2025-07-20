#include "Grid.h"
#include "TextureManager.h"
#include <iostream>
#include <bitset>

Grid::Grid(sf::Vector2u size) : size(size), cells(size.x* size.y), Box({ 0,0 }, { 0, 0 }) {
	sprites.reserve(size.x * size.y);
	for (int j = 0; j < size.y; j++) {
		for (int i = 0; i < size.x; i++) {
			sf::Sprite sprite(TextureManager::Ref().get("block_void"));
			sprite.setPosition({ i * 30.f + 2, j * 30.f + 2 });
			sprite.setScale({ 2.f,2.f });
			sprites.push_back(sprite);
		}
	}

	for (int i = 0; i < size.x * size.y; i++) {
		cells[i].isActive = false;
		if (i > 154) {
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
	/*for (int i = 0; i < size.x * size.y; i++) {
		sprites[i].setColor(cells[i].isActive ? sf::Color::Green : sf::Color::Red);
	}*/
	setSize({ size.x * 30.f + 4, size.y * 30.f + 4 });
	Box::update();

	for (int i = 0; i < size.x * size.y; i++) {
		switch (cells[i].type) {
		case Figure::Type::I:
			sprites[i].setTexture(TextureManager::Ref().get("block_6"));
			break;
		case Figure::Type::J:
			sprites[i].setTexture(TextureManager::Ref().get("block_5"));
			break;
		case Figure::Type::L:
			sprites[i].setTexture(TextureManager::Ref().get("block_2"));
			break;
		case Figure::Type::O:
			sprites[i].setTexture(TextureManager::Ref().get("block_3"));
			break;
		case Figure::Type::S:
			sprites[i].setTexture(TextureManager::Ref().get("block_4"));
			break;
		case Figure::Type::T:
			sprites[i].setTexture(TextureManager::Ref().get("block_7"));
			break;
		case Figure::Type::Z:
			sprites[i].setTexture(TextureManager::Ref().get("block_1"));
			break;
		case Figure::Type::EMPTY:
			sprites[i].setTexture(TextureManager::Ref().get("block_void"));
			break;
		default:
			sprites[i].setTexture(TextureManager::Ref().get("abort"));
		}
	}
}

sf::Vector2u Grid::getFieldSize() const {
	return size;
}

sf::Vector2u Grid::getSize() const {
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

Grid::Cell* Grid::at(unsigned x, unsigned y) {
	if (x >= size.x || y >= size.y) return nullptr;
	return &cells[size.x * y + x];
}

const Grid::Cell* Grid::at(unsigned x, unsigned y) const {
	if (x >= size.x || y >= size.y) return nullptr;
	return &cells[size.x * y + x];
}

Grid::Cell* Grid::fat(unsigned x, unsigned y) {
	return at(x + figurePos.x, y + figurePos.y);
}

const Grid::Cell* Grid::fat(unsigned x, unsigned y) const {
	return at(x + figurePos.x, y + figurePos.y);
}

void Grid::step() {
	for (int j = size.y - 1; j >= 0; j--) {
		for (int i = 0; i < size.x; i++) {
			if (at(i, j)->isActive && has(i, j + 1)) {
				swap(*at(i, j), *at(i, j + 1));
			}
		}
	}
}

bool Grid::paste(const Figure& figure, unsigned r, sf::Vector2u position) {
	std::bitset<16> frame = figure.getFrame(r);

	for (int i = 0; i < 16; i++) {
		if (frame[i]) {
			auto targetCell = at(i % 4 + position.x, i / 4 + position.y);
			if (!targetCell) return false;
			targetCell->type = figure.getType();
			targetCell->isActive = true;
		}
	}

	figurePos = position;
	figureRot = r;
	currFigure = &figure;
	return true;
}

bool Grid::rotate() {
	if (!currFigure) return false;

	figureRot++;
	if (figureRot > 3) figureRot = 0;
	if (!allows(*currFigure, figurePos, figureRot)) {
		figureRot--;
		return false;
	}

	for (int i = 0; i < 16; i++) {
		auto targetCell = fat(i / 4, i % 4);
		if (targetCell && (targetCell->type != Figure::EMPTY) && (targetCell->isActive == true)) {
			targetCell->type = Figure::EMPTY;
		}
	}
	return paste(*currFigure, figureRot, figurePos);
}

bool Grid::allows(const Figure& figure, sf::Vector2u pos, int r) const {
	std::bitset<16> frame = figure.getFrame(r);
	for (int i = 0; i < 16; i++) {
		if (frame[i]) {
			auto targetCell = at(i % 4 + pos.x, i / 4 + pos.y);
			if (!targetCell || (targetCell->type != Figure::EMPTY && !targetCell->isActive)) return false;
		}
	}
	return true;
}

bool Grid::move(sf::Vector2i pos) {
	if (!allows(*currFigure, { figurePos.x + pos.x, figurePos.y + pos.y }, figureRot)) return false;

	std::bitset<16> frame = (*currFigure).getFrame(figureRot);
	for (int i = 0; i < 16; i++) {
		if (frame[i]) {
			fat(i % 4, i / 4)->type = Figure::EMPTY;
		}
	}

	paste(*currFigure, figureRot, { figurePos.x + pos.x,figurePos.y + pos.y });
	return true;
}

