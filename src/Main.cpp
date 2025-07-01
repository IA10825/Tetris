#include <SFML/Graphics.hpp>

int main()
{
	auto window = sf::RenderWindow(sf::VideoMode({ 220u, 220u }), "Tetris", sf::Style::Default, sf::State::Windowed);
	window.setFramerateLimit(144);

	sf::Texture texture("res/x.png");

	sf::Sprite sprite(texture);

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
				window.setView({ {window.getSize().x / 2.f,window.getSize().y / 2.f},{window.getSize().x*1.f,window.getSize().y*1.f } });
			}
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
}
