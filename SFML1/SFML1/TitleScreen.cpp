#include "TitleScreen.h"


TitleScreen::TitleScreen()
{
	font.loadFromFile("arial.ttf");
}

void TitleScreen::setText()
{
	play.setFont(font);
	play.setString("Press Spacebar to Play!");
	play.setCharacterSize(25);
	play.setColor(sf::Color(223, 116, 1));
	play.setPosition(275, 500);
}

void TitleScreen::setImage()
{
  image.loadFromFile("resource/Zooki.png");
  zookieLogo.setTexture(image);
  zookieLogo.setPosition(50, 50);
}

TitleScreen::~TitleScreen()
{
}

