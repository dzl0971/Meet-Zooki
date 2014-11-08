#include "Zooki.h"
#include<iostream>
using namespace std;
Zooki::Zooki()
{
	size_x = 25;
	size_y = 100;
	pos_x = 22.5f;
	pos_y = 300;
	texture_size_x=32;
	texture_size_y=32;
	if(zooki_texture.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
	
	zooki_stay_r=sf::IntRect(0,64,texture_size_x,texture_size_y);
	zookiSprite.setTexture(zooki_texture);
	zookiSprite.setTextureRect(zooki_stay_r);
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));

	has_cones = false;
	onGround = false;
	isSliding = false;

	x_velocity = 0;
	y_velocity = 0;

	conesRemaining = 3;

	level = 0;
	lives = 3;
}

int Zooki::getLivesLeft()
{
	return lives;
}

void Zooki::loadTexture()
{
	zooki_stay_l=sf::IntRect(0,32,texture_size_x,texture_size_y);

	zooki_run1_l=sf::IntRect(32,32,texture_size_x,texture_size_y);
	zooki_run2_l=sf::IntRect(32,32,texture_size_x,texture_size_y);
	zooki_run3_l=sf::IntRect(64,32,texture_size_x,texture_size_y);

	zooki_run1_r=sf::IntRect(32,64,texture_size_x,texture_size_y);
	zooki_run2_r=sf::IntRect(32,64,texture_size_x,texture_size_y);
	zooki_run3_r=sf::IntRect(64,64,texture_size_x,texture_size_y);

	zooki_jump_l=sf::IntRect(0,32,texture_size_x,texture_size_y);
	zooki_jump_r=sf::IntRect(0,64,texture_size_x,texture_size_y);
	
	zooki_down_l=sf::IntRect(0,32,texture_size_x,texture_size_y);
	zooki_down_r=sf::IntRect(0,64,texture_size_x,texture_size_y);
	
}

void Zooki::reset(){
	x_velocity = 0;
	y_velocity = 0;
	pos_x = 22.5f;
	pos_y = 300;
	has_cones = false;
	onGround = false;
	isSliding = false;
	zookiSprite.setTexture(zooki_texture);
	zookiSprite.setTextureRect(zooki_stay_r);
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
	zookiSprite.setOrigin(sf::Vector2f(size_x / 2, size_y / 2));

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
	if(x_velocity>0)
		zookiSprite.setTextureRect(zooki_jump_r);
	if(x_velocity>0)
		zookiSprite.setTextureRect(zooki_jump_l);
	onGround = false;
	y_velocity -= 300;
}

void Zooki::slide()
{
	x_velocity *= 1.05;
	zookiSprite.setTexture(zooki_texture);
	if (x_velocity > 0) 
	{
		zookiSprite.setTextureRect(zooki_down_r);
		zookiSprite.setScale(1,0.5);
		//zookiSprite.setRotation(90);
	}
	if (x_velocity < 0){
		zookiSprite.setTextureRect(zooki_down_l);
		zookiSprite.setScale(1,0.5);
		//zookiSprite.setRotation(270);
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
	zookiSprite.setTexture(zooki_texture);
	if(x_velocity>0)
		zookiSprite.setTextureRect(zooki_stay_r);
	if(x_velocity<0)
		zookiSprite.setTextureRect(zooki_stay_l);
	zookiSprite.setScale(1,1);
}



void Zooki::resetPos(int x, int y)
{
	pos_x = x;
	pos_y = y;

}

void Zooki::resetPos()
{
	pos_x = startX;
	pos_y = startY;

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


void Zooki::Update()
{
	zookiSprite.setPosition(sf::Vector2f(pos_x, pos_y));
}


Zooki::~Zooki()
{

}
