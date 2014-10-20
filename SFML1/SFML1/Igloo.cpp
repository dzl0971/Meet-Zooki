#include "Igloo.h"

Igloo::Igloo()
{

	size_x = 30;
	size_y = 30;
	pos_x = 785;
	pos_y = 585;

	iglooShape.setSize(sf::Vector2f(size_x, size_y));
	iglooShape.setPosition(sf::Vector2f(pos_x, pos_y));
	iglooShape.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));
}



void Igloo::Update()
{
	iglooShape.setPosition(sf::Vector2f(pos_x, pos_y));
}


Igloo::~Igloo()
{

}
