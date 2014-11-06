

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
	const std::string gameStart = "Welcome! Press Space to Play!";
	const std::string levelClear = "Level Clear! Press Space to Continue";
	const std::string lavaDeath = "Don't Touch the Lava! Press Space to Retry";
	const std::string timerDeath = "Out of Time! Press Space to Retry";

	void setText(int message);

	void setImage();


private:
	sf::Font font;
};
