#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "TextureManager.h"
#include "Grid.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 385u, 620u }), "Tetris", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(144);

	Button button1({ 10.f, 10.f }, { 55.f, 32.f }, TextureManager::getInstance().get("play"), 1);
	Button button2({ 10.f, 60.f }, { 55.f, 32.f }, TextureManager::getInstance().get("reset"), 1);
	Button button3({ 10.f, 110.f }, { 55.f, 32.f }, TextureManager::getInstance().get("volume_off"), 1);
	Button button4({ 10.f, 160.f }, { 55.f, 32.f }, TextureManager::getInstance().get("exit"), 1);
	bool isSoundOn = true;

	Grid grid({ 10, 20 });
	grid.setPosition({75, 10});

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			if (event->is<sf::Event::Resized>())
			{
				window.setView({ {window.getSize().x / 2.f,window.getSize().y / 2.f},{window.getSize().x * 1.f,window.getSize().y * 1.f } });
			}
		}

		if (button4.isJustPressed(window)) {
			window.close();
		}

		button1.update(window);
		button2.update(window);
		button3.update(window);
		button4.update(window);
		grid.update();

		window.clear();
		window.draw(grid);
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.display();
	}
}
