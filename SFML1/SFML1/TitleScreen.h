

#pragma once
#include <SFML/Graphics.hpp>
class TitleScreen
{
public:
	TitleScreen();
	~TitleScreen();

	sf::Text play;

	sf::Texture image;

	sf::Sprite zookieLogo;

	void setText();

	void setImage();


private:
	sf::Font font;
};
