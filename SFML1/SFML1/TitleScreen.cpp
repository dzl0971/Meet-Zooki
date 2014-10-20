#include "TitleScreen.h"


TitleScreen::TitleScreen()
{
	font.loadFromFile("arial.ttf");
}

void TitleScreen::setText()
{
	title.setFont(font);
	title.setString("ZOOKI");
	title.setCharacterSize(75);
	title.setPosition(250, 50);


	play.setFont(font);
	play.setString("Press Spacebar to Play!");
	play.setCharacterSize(25);
	play.setPosition(275, 250);
}

TitleScreen::~TitleScreen()
{
}
