#include "Zooki.h"

Zooki::Zooki()
{
	size_x = 25;
	size_y = 100;
	pos_x = 22.5f;
	pos_y = 300;

	zookiTexture.loadFromFile("penguin.png");
	zookiSprite.setTexture(zookiTexture);
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));

	has_cones = false;
	onGround = false;

	x_velocity = 0;
	y_velocity = 0;

	conesRemaining = 4;

	level = 0;
	lives = 3;
}

void Zooki::reset(){
	x_velocity = 0;
	y_velocity = 0;
	pos_x = 22.5f;
	pos_y = 300;
	has_cones = false;
	onGround = false;
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));
	zookiSprite.setRotation(0);
}

void Zooki::moveRight(float deltaTime, int runSpeed)
{
	x_velocity += 25;
	if (x_velocity > runSpeed){
		x_velocity = runSpeed;
	}
}

void Zooki::moveLeft(float deltaTime, int runSpeed)
{
	x_velocity -= 25;
	if (x_velocity < -runSpeed){
		x_velocity = -runSpeed;
	}

}

void Zooki::fall(){

	y_velocity += 15;
}

void Zooki::processMovement(float deltaTime)
{
	pos_x = pos_x + (deltaTime*x_velocity);
	pos_y = pos_y + (deltaTime*y_velocity);

}

void Zooki::jump()
{
	onGround = false;
	y_velocity -= 300;
}

void Zooki::slide()
{
	x_velocity *= 1.5;
	if (x_velocity > 0) 
	{
		zookiSprite.setRotation(90);
	}
	else if (x_velocity < 0){
		zookiSprite.setRotation(270);
	}
}

void Zooki::gotCone()
{
	has_cones = true;
}

void Zooki::stop(){
	x_velocity = 0;
	y_velocity = 0;
}

void Zooki::upright(){
	zookiSprite.setRotation(0);
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
