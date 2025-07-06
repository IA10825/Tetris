#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameManager.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 385u, 620u }), "Tetris", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(144);

	GameManager manager;

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

		manager.update(window);

		window.clear();		
		window.draw(manager);
		window.display();
	}
}
