#include "Zooki.h"

Zooki::Zooki()
{

	size_x = 25;
	size_y = 100;
	pos_x = 22.5f;
	pos_y = 550;

	zookiShape.setSize(sf::Vector2f(size_x, size_y));
	zookiShape.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiShape.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));
}


void Zooki::moveRight()
{
	//move right
}

void Zooki::moveLeft()
{
	//move left

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
	zookiShape.setPosition(sf::Vector2f(pos_x, pos_y));
}


Zooki::~Zooki()
{

}
