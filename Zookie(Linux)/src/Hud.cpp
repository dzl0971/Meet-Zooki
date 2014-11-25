#include "Hud.h"
#include <sstream>
using namespace std;

Hud::Hud()
{
}
template <class T>
string getString ( const T n)

{
	std::stringstream newstr;
	newstr<<n;
	return newstr.str();

}
Hud::Hud(sf::Clock* time, Zooki* zooki_ptr)
{
	zooki = zooki_ptr;
	clock = time;
	conesCollected = zooki_ptr->conesCollected;

	font.loadFromFile("resources/arial.ttf");
	
	livesText.setFont(font);
	livesText.setString("Lives:");
	livesText.setColor(sf::Color::Black);
	livesText.setCharacterSize(20);
	livesText.setPosition(sf::Vector2f(20, 20));

	iceCreamTex.loadFromFile("resources/cone.png");
	iceCream.setTexture(iceCreamTex);
	iceCream.setTextureRect(sf::IntRect(0, 0, 30, 27));
	iceCream.setPosition(sf::Vector2f(1100, 20));

	timerTex.loadFromFile("resources/timer.png");
	timer.setTexture(timerTex);
	timer.setPosition(sf::Vector2f(520,20));

	iceCreamCountText.setFont(font);
	iceCreamCountText.setString("x " + getString(zooki_ptr->conesCollected));
	iceCreamCountText.setColor(sf::Color::Black);
	iceCreamCountText.setCharacterSize(20);
	iceCreamCountText.setPosition(sf::Vector2f(1128, 20));

	timeText.setFont(font);
	timeText.setString("Time Left: " + getString(time->getElapsedTime().asSeconds()));
	timeText.setColor(sf::Color::Black);
	timeText.setCharacterSize(20);
	timeText.setPosition(sf::Vector2f(560, 20));

	remainingText.setFont(font);
	remainingText.setString("Enough Cones Collected! Go To Your Igloo!");
	remainingText.setColor(sf::Color::Red);
	remainingText.setCharacterSize(20);
	remainingText.setPosition(sf::Vector2f(400,50));

	pauseText.setFont(font);
	pauseText.setColor(sf::Color::Black);
	pauseText.setCharacterSize(20);
	
	
	lives.resize(zooki_ptr->getLivesLeft());
	sf::Sprite sprite;
	
	setLives();
}


Hud::~Hud()
{
}

sf::Sprite Hud::getIceCreamSprite()
{
	return iceCream;
}
sf::Sprite Hud::getTimerSprite()
{
	return timer;
}
std::vector<sf::Sprite> Hud::getLives()
{
	return lives;
}

sf::Text Hud::getLivesText()
{
	return livesText;
}
sf::Text Hud::getTimeText()
{
	return timeText;
}
sf::Text Hud::getIceCreamText()
{
	return iceCreamCountText;
}
sf::Text Hud::getRemainingText()
{
	return remainingText;
}
sf::Text Hud::getPauseText()
{
	return pauseText;
}
void Hud::setRemainingText(float x, float y)
{
	//remainingText.setScale(x,y);
	remainingText.setColor(sf::Color::Blue);
}
void Hud::setPauseText(int x, int y, int coneRecord, int timeRecord)
{
	pauseText.setString("x " + getString(coneRecord)
		+ "\n" + "\n" + "\n" + "Time Taken: " + getString(timeRecord + 1) + " seconds"
						+"\n"+"\n"+"\n"+"x" + getString(lives.size()));
	pauseText.setPosition(x+60,y);
	iceCream.setPosition(x,y);
	timer.setPosition(x,y+70);
	lives[0].setPosition(x,y+130);
	
}
void Hud::resetTextPosition()
{
	iceCream.setPosition(sf::Vector2f(1100, 20));
	lives[0].setPosition(sf::Vector2f(80,10));
	timer.setPosition(sf::Vector2f(520,20));
}
void Hud::Update(double time)
{

	if (zooki->getLivesLeft() != lives.size())
	{
		lives.clear();
		lives.resize(zooki->getLivesLeft());
		setLives();
	}

	if (zooki->conesCollected != conesCollected)
	{
		conesCollected = zooki->conesCollected;
		iceCreamCountText.setString("x " + getString(zooki->conesCollected));
	}

	timeText.setString("Time Left: " + getString((int)((maxTime - time) + 1)));
}

void Hud::setLives()
{
	for (int i = 0; i < lives.size(); i++)
	{
		lives[i].setTexture(zooki->zooki_texture);
		lives[i].setTextureRect(sf::IntRect(32, 0, 32, 32));
		lives[i].setPosition(sf::Vector2f((i * 34) + 80, 10));
	}
}

void Hud::setMaxTime(int max)
{
	maxTime = max;
}
