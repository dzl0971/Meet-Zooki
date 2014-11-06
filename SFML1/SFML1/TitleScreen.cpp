#include "TitleScreen.h"


TitleScreen::TitleScreen()
{
	font.loadFromFile("arial.ttf");
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
	
	play.setCharacterSize(25);
	play.setColor(sf::Color(223, 116, 1));
	play.setPosition(275, 500);
}

void TitleScreen::setImage()
{
  image.loadFromFile("Zooki.png");
  zookieLogo.setTexture(image);
  zookieLogo.setPosition(150, 50);
}

TitleScreen::~TitleScreen()
{
}

