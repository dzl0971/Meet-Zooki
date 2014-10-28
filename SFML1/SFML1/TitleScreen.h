#pragma once
#include <SFML/Graphics.hpp>
class TitleScreen
{
public:
	TitleScreen();
	~TitleScreen();

	sf::Text title;

	sf::Text play;

	void setText();


private:
	sf::Font font;
};

