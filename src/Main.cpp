#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "TextureManager.h"

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 320u, 220u }), "Tetris", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(144);


	TextureManager manager("res");

	Button button1({ 10.f, 10.f }, { 55.f, 32.f }, manager.get("play"), 1);
	Button button2({ 10.f, 60.f }, { 55.f, 32.f }, manager.get("reset"), 1);
	Button button3({ 10.f, 110.f }, { 55.f, 32.f }, manager.get("volume_off"), 1);
	Button button4({ 10.f, 160.f }, { 55.f, 32.f }, manager.get("exit"), 1);
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

		if (button4.isJustPressed(window)) {
			window.close();
		}

		button1.update(window);
		button2.update(window);
		button3.update(window);
		button4.update(window);

		window.clear();
		window.draw(button1);
		window.draw(button2);
		window.draw(button3);
		window.draw(button4);
		window.display();
	}
}
