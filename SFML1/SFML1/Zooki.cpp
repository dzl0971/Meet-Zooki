#include "Zooki.h"
#include<iostream>
using namespace std;
Zooki::Zooki()
{
	texture_size_x=18;
	texture_size_y=22;
	if(zooki_texture.loadFromFile("Data/penguin.png")==false){
		   cout<<"Texture failed to initialize"<<endl;
	   }
	
	zooki_stay_r=sf::IntRect(7,74,texture_size_x,texture_size_y);
	zookiSprite.setTexture(zooki_texture);
	zookiSprite.setTextureRect(zooki_stay_r);

	has_cones = false;
	onGround = false;
	isSliding = false;

	x_velocity = 0;
	y_velocity = 0;

	level = 0;
	lives = 3;
	conesCollected = 0;
}

int Zooki::getLivesLeft()
{
	return lives;
}

void Zooki::loadTexture()
{
	zooki_stay_l=sf::IntRect(7,42,texture_size_x,texture_size_y);

	zooki_run1_l=sf::IntRect(39,42,texture_size_x,texture_size_y);
	zooki_run2_l=sf::IntRect(39,42,texture_size_x,texture_size_y);
	zooki_run3_l=sf::IntRect(71,42,texture_size_x,texture_size_y);

	zooki_run1_r=sf::IntRect(39,74,texture_size_x,texture_size_y);
	zooki_run2_r=sf::IntRect(39,74,texture_size_x,texture_size_y);
	zooki_run3_r=sf::IntRect(71,74,texture_size_x,texture_size_y);

	zooki_jump_l=sf::IntRect(7,42,texture_size_x,texture_size_y);
	zooki_jump_r=sf::IntRect(7,74,texture_size_x,texture_size_y);
	
	zooki_down_l=sf::IntRect(39,42,texture_size_x,texture_size_y);
	zooki_down_r=sf::IntRect(39,74,texture_size_x,texture_size_y);
	
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

void Zooki::reset(){
	x_velocity = 0;
	y_velocity = 0;
	has_cones = false;
	onGround = false;
	isSliding = false;
	zookiSprite.setTexture(zooki_texture);
	zookiSprite.setTextureRect(zooki_stay_r);
}

void Zooki::moveRight(float deltaTime, int runSpeed)
{
	zookiSprite.setTextureRect(zooki_run1_r);
	x_velocity += 25;
	if (x_velocity > runSpeed){
		x_velocity = runSpeed;
	}
}

void Zooki::moveLeft(float deltaTime, int runSpeed)
{
	zookiSprite.setTextureRect(zooki_run1_l);
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
	if (pos_x < 0)
	{
		pos_x = 0;
	}
	else if (pos_x > 1280 - texture_size_x)
	{
		pos_x = 1280 - texture_size_x;
	}

	pos_y = pos_y + (deltaTime*y_velocity);
	if (pos_y < 0)
	{
		pos_y = 0;
	}
	else if (pos_y > 1280 - texture_size_x)
	{
		pos_y = 1280 - texture_size_y;
	}

}

void Zooki::jump()
{
	if(x_velocity>0)
		zookiSprite.setTextureRect(zooki_jump_r);
	if(x_velocity<0)
		zookiSprite.setTextureRect(zooki_jump_l);
	onGround = false;
	y_velocity -= 300;
}

void Zooki::slide()
{

	//zookiSprite.setTexture(zooki_texture);
	if (x_velocity > 0) 
	{
		if (x_velocity > 0 && onGround){
			x_velocity = 350;
		}
		zookiSprite.setTextureRect(zooki_down_r);
		zookiSprite.setRotation(90);
	}
	if (x_velocity < 0){
		if (x_velocity < 0 && onGround){
			x_velocity = -350;
		}
		zookiSprite.setTextureRect(zooki_down_l);
		zookiSprite.setRotation(270);
	}
}


void Zooki::upright(){
	zookiSprite.setRotation(0);
	zookiSprite.setTexture(zooki_texture);
	if(x_velocity>=0)
		zookiSprite.setTextureRect(zooki_stay_r);
	if(x_velocity<0)
		zookiSprite.setTextureRect(zooki_stay_l);
}

void Zooki::stop()
{
	if (onGround){
		x_velocity /= 1.1;
	}
	

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
