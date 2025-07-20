#include "GameManager.h"
#include "TextureManager.h"
#include <iostream>

Figure* figures = new Figure[7]{
	{0b0000'1111'0000'0000'0010'0010'0010'0010'0000'0000'1111'0000'0100'0100'0100'0100, Figure::Type::I},
	{0b0010'1110'0000'0000'0100'0100'0110'0000'0000'1110'1000'0000'1100'0100'0100'0000, Figure::Type::J},
	{0b0010'1110'0000'0000'0100'0100'0110'0000'0000'1110'1000'0000'1100'0100'0100'0000, Figure::Type::L},
	{0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, Figure::Type::O},
	{0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, Figure::Type::S},
	{0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, Figure::Type::T},
	{0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000, Figure::Type::Z}
};

GameManager::GameManager() : size(380, 200) {
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::Ref().get("play"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::Ref().get("reset"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::Ref().get("volume_on"));
	buttons.emplace_back(sf::Vector2f{ 0,0 }, sf::Vector2f{ 64,32 }, TextureManager::Ref().get("exit"));

	grid = new Grid({ 10,20 });
	size.y = grid->getSize().y;
	grid->step();
	grid->step();
	grid->step();
	grid->step();
	grid->paste(figures[2], 0, sf::Vector2u{3,0});
}

void GameManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < buttons.size(); i++) {
		target.draw(buttons[i], states);
	}
	target.draw(*grid, states);
}

void GameManager::update(sf::Window& window) {
	if (Keyboard::Ref().isKeyJustPressed(sf::Keyboard::Key::Up)) {
		grid->rotate();
	}
	//if (Keyboard::Ref().isKeyJustPressed(sf::Keyboard::Key::Down)) {
	//	grid->move({ 0, 1 });
	//}
	//if (Keyboard::Ref().isKeyJustPressed(sf::Keyboard::Key::Left)) {
	//	grid->move({ -1, 0 });
	//}
	//if (Keyboard::Ref().isKeyJustPressed(sf::Keyboard::Key::Right)) {
	//	grid->move({ 1, 0 });
	//}

	if (buttons[3].isJustPressed(window)) window.close();
	if (buttons[0].isJustPressed(window)) {
		isPaused = !isPaused;
		buttons[0].setTexture(isPaused ? TextureManager::Ref().get("pause") : TextureManager::Ref().get("play"));
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