#include "Zooki.h"

Zooki::Zooki()
{
	size_x = 25;
	size_y = 50;
	pos_x = 0;
	pos_y = 0;

	zookiTexture.loadFromFile("penguin.png");
	zookiSprite.setTexture(zookiTexture);
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiSprite.scale(sf::Vector2f(.5,.5));
	zookiSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));

	num_Cones = 0;
	has_cones = false;
	onGround = false;
}


void Zooki::moveRight(float deltaTime, int runSpeed)
{
	pos_x = (zookiSprite.getPosition().x + runSpeed * deltaTime);
}

void Zooki::moveLeft(float deltaTime, int runSpeed)
{
	pos_x = (zookiSprite.getPosition().x + (-runSpeed) * deltaTime);

}

void Zooki::fall(float deltaTime, int gravity)
{
	pos_y = (zookiSprite.getPosition().y + (gravity) * deltaTime);

}

void Zooki::jump()
{
	//jump
}

void Zooki::slide()
{
	//slide
}

void Zooki::gotCone()
{
	num_Cones++;
	has_cones = true;
}

void Zooki::resetPos()
{
	pos_x = startX;
	pos_y = startY;

}

void Zooki::resetPos(int x, int y)
{
	pos_x = x;
	pos_y = y;

}

void Zooki::setStart(int x, int y)
{
	x = x * 16; //makes sure zooki starts at the corner of a tile
	y = y * 16;

	startX = x;
	startY = y;
	pos_x = x;
	pos_y = y;


}

sf::Sprite Zooki::getSprite()
{
	return zookiSprite;
}

void Zooki::Update()
{
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
}


Zooki::~Zooki()
{

}
