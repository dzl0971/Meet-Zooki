#include "TitleScreen.h"


TitleScreen::TitleScreen()
{
	font.loadFromFile("resources/arial.ttf");
	gameStart = "Welcome! Press Space to Play!";
	levelClear = "Level Clear! Press Space to Continue";
	lavaDeath = "Don't Touch the Lava! Press Space to Retry";
	timerDeath = "Out of Time! Press Space to Retry";
	gameClear = "Congratulations!  You've Won!  Press Space to Restart";
}

void TitleScreen::setText(int message)
{
	play.setFont(font);
	if (message == 1){
		play.setString(gameStart);
	}
	else if (message == 2){
		play.setString(levelClear);
	}
	else if (message == 3){
		play.setString(lavaDeath);
	}
	else if (message == 4){
		play.setString(timerDeath);
	}
	else if (message == 5)
	{
		play.setString(gameClear);
	}
	
	play.setCharacterSize(40);
	play.setStyle(sf::Text::Bold);
	play.setColor(sf::Color(255, 165, 0 ));
	play.setPosition(385, 450);
}

void TitleScreen::setImage()
{
  image.loadFromFile("resources/Zooki.png");
  zookieLogo.setTexture(image);
  zookieLogo.setPosition(150, 50);
}

TitleScreen::~TitleScreen()
{
}
