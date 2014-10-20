#include "Zooki.h"

Zooki::Zooki()
{
	size_x = 25;
	size_y = 100;
	pos_x = 22.5f;
	pos_y = 550;

	zookiTexture.loadFromFile("penguin.png");
	zookiSprite.setTexture(zookiTexture);
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));
}


void Zooki::moveRight(float deltaTime, int runSpeed)
{
	pos_x = (zookiSprite.getPosition().x + runSpeed * deltaTime);
}

void Zooki::moveLeft(float deltaTime, int runSpeed)
{
	pos_x = (zookiSprite.getPosition().x + (-runSpeed) * deltaTime);

}

void Zooki::jump()
{
	//jump
}

void Zooki::slide()
{
	//slide
}



void Zooki::resetPos(int x, int y)
{
	pos_x = x;
	pos_y = y;

}


void Zooki::Update()
{
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
}


Zooki::~Zooki()
{

}
