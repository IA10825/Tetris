#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("res")) {
		if (!(
			entry.path().extension().string() == ".png" ||
			entry.path().extension().string() == ".jpg" ||
			entry.path().extension().string() == ".gif"
			)) {
			std::cerr << typeid(*this).name() << ": Texture " << entry.path() << " - invalid file extension" << std::endl;
			continue;
		}
		sf::Texture* pTexture = new sf::Texture;
		if (
			!(*pTexture).loadFromFile(entry.path())
			) {
			std::cerr << typeid(*this).name() << ": Texture " << entry.path() << " could not be loaded" << std::endl;
			continue;
		}
		textures[entry.path().filename().stem().string()] = pTexture;
	}
	textures["blank"] = new sf::Texture;
}

sf::Texture& TextureManager::get(std::string name) {
	static TextureManager instance;
	if (instance.textures[name]) {
		return *(instance.textures[name]);
	}
	else {
		std::cerr << typeid(instance).name() << ": Texture " << name << " was not found";
		return *(instance.textures["blank"]);
	}
}