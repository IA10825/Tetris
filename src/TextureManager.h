#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager {
public:
	TextureManager(std::string directory);
	sf::Texture& get(std::string name);
private:
	std::map<std::string, sf::Texture*> textures;
};