#pragma once
#include <SFML/Graphics.hpp>
#include "Zooki.h"

class Hud
{
public:
	Hud();
	Hud(sf::Clock* time, Zooki* zooki_ptr);
	
	~Hud();

	sf::Sprite getIceCreamSprite();
	sf::Sprite getTimerSprite();
	std::vector<sf::Sprite> getLives();
	sf::Text getLivesText();
	sf::Text getTimeText();
	sf::Text getIceCreamText();
	sf::Text getRemainingText();
	sf::Text getPauseText();
	
	
	void setRemainingText(float x, float y);
	void setMaxTime(int max);
	void setPauseText(int x, int y, int coneRecord, int timeRecord);
	void resetTextPosition();
	void Update();

private:
	int conesCollected;
	int maxTime;
	
	sf::Clock* clock;
	sf::Font font;
	sf::Text livesText;
	sf::Text timeText;
	sf::Text iceCreamCountText;
	sf::Text remainingText;
	sf::Text pauseText;
	sf::Sprite penguin;
	sf::Sprite iceCream;
	sf::Sprite timer;
	sf::Texture iceCreamTex;
	sf::Texture timerTex;


	std::vector<sf::Sprite> lives;

	Zooki* zooki;

	void setLives();
};

