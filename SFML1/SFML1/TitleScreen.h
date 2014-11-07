#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>
using namespace std;
class TitleScreen
{
public:
	TitleScreen();
	~TitleScreen();

	sf::Text play;

	sf::Texture image;

	sf::Sprite zookieLogo;
	string gameStart;
	string levelClear;
	string lavaDeath;
	string timerDeath;

	void setText(int message);

	void setImage();


private:
	sf::Font font;
};

