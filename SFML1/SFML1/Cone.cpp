#include "Cone.h"

Cone::Cone()
{

	size_x = 30;
	size_y = 40;
	pos_x = 200;
	pos_y = 400;
	collected = false;

	coneTexture.loadFromFile("Data/cone.png");
	coneSprite.setTexture(coneTexture);
	coneSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	coneSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));
}



void Cone::Update()
{
	coneSprite.setPosition(sf::Vector2f(pos_x, pos_y));
}


Cone::~Cone()
{

}
