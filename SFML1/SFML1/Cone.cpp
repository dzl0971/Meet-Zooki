#include "Cone.h"

Cone::Cone()
{

	size_x = 20;
	size_y = 30;
	pos_x = 400;
	pos_y = 200;

	coneTexture.loadFromFile("cone.png");
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
