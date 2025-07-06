#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager {
public:
	static sf::Texture& get(std::string name);
private:
	TextureManager();
	std::map<std::string, sf::Texture*> textures;

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
};