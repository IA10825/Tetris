#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameManager.h"



int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 540u, 640u }), "Tetris", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(60);

	srand(time(0));

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
			if (event->is<sf::Event::MouseButtonPressed>())
			{
				std::cout << "Click";
			}
		}

		manager.update(window);

		window.clear();		
		window.draw(manager);
		window.display();
	}
}
