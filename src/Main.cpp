#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 320u, 220u }), "Tetris", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(144);

	sf::Texture a;
	if (!a.loadFromFile("res/volume_on.png")) {
		std::cout << "texture a may not be loaded";
	}
	sf::Texture b;
	if (!b.loadFromFile("res/volume_off.png")) {
		std::cout << "texture b may not be loaded";
	}
	Button button({ 10.f, 10.f }, { 64.f, 64.f }, a,1);
	bool isSoundOn = true;

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

		if (button.isJustPressed(window)) {
			isSoundOn = !isSoundOn;
			button.setTexture(isSoundOn ? a : b);
		}

		button.setSize({ 128, 32 });
		button.update(window);

		window.clear();
		window.draw(button);
		window.display();
	}
}
