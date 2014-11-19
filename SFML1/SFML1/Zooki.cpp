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
	//mirrored for sliding
	zooki_stay_l = sf::IntRect(7, 42 + texture_size_y, texture_size_x, -texture_size_y);

	zooki_run1_l = sf::IntRect(39, 42, texture_size_x, texture_size_y);
	zooki_run2_l = sf::IntRect(39, 42, texture_size_x, texture_size_y);
	zooki_run3_l = sf::IntRect(71, 42, texture_size_x, texture_size_y);

	//mirrored for sliding
	zooki_run1_l_s = sf::IntRect(39, 74 + texture_size_y, texture_size_x, -texture_size_y);
	zooki_run2_l_s = sf::IntRect(39, 74 + texture_size_y, texture_size_x, -texture_size_y);
	zooki_run3_l_s = sf::IntRect(71, 74 + texture_size_y, texture_size_x, -texture_size_y);

	zooki_run1_r = sf::IntRect(39, 74, texture_size_x, texture_size_y);
	zooki_run2_r = sf::IntRect(39, 74, texture_size_x, texture_size_y);
	zooki_run3_r = sf::IntRect(71, 74, texture_size_x, texture_size_y);

	zooki_jump_l = sf::IntRect(7, 42, texture_size_x, texture_size_y);
	zooki_jump_r = sf::IntRect(7, 74, texture_size_x, texture_size_y);

	zooki_down_l = sf::IntRect(39, 74 + texture_size_y, texture_size_x, -texture_size_y);
	zooki_down_r = sf::IntRect(39, 74, texture_size_x, texture_size_y);
	
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
		x_velocity = 0;
	}
	else if (pos_x > 1280 - texture_size_x)
	{
		pos_x = 1280 - texture_size_x;
		x_velocity = 0;
	}

	pos_y = pos_y + (deltaTime*y_velocity);
	if (pos_y < 0)
	{
		pos_y = 0;
		y_velocity = 0;
	}
	else if (pos_y > 1280 - texture_size_y)
	{
		pos_y = 100 - texture_size_y;
		y_velocity = 0;
	}

}

void Zooki::processMovement(float deltaTime, int rightBound, int leftBound, int upBound, int downBound)
{
	if (x_velocity < 0)
	{
		pos_x =pos_x - (deltaTime * (-x_velocity));
	}
	else
	{
		pos_x = pos_x + (deltaTime*x_velocity);
	}

	if (pos_x < 0 || (isSliding && pos_x <texture_size_y) )
	{
		pos_x = 0;
		if (isSliding)
		{
			pos_x += texture_size_y;
		}
		x_velocity = 0;

	}
	else if (pos_x > 1280 - texture_size_x)
	{
		if (!isSliding)
		{
			pos_x = 1280 - texture_size_x;
		}
		else
		{
			pos_x = 1280;
		}
		x_velocity = 0;
	}

	if (y_velocity < 0)
	{
		pos_y = pos_y - (deltaTime * (-y_velocity));
	}
	else
	{
		pos_y = pos_y + (deltaTime*y_velocity);
	}
	if (pos_y < 0)
	{
		pos_y = 0;
		y_velocity = 0;
	}
	else if (pos_y > 768 - texture_size_y)
	{
		pos_y = 100 - texture_size_y; // spawn near top of screen, for testing
		y_velocity = 0;
	}

	//right and left collisions
	if (x_velocity >= 0 && rightBound > 0)
	{
		if (pos_x + texture_size_x > rightBound)
		{
			if (!isSliding)
			{
				pos_x = rightBound - texture_size_x;
			}
			else
			{
				pos_x = rightBound - 1;
			}
			x_velocity = 0;
		}
	}
	else if (x_velocity < 0 && leftBound > 0)
	{
		if (pos_x - texture_size_y < leftBound)
		{
			if (!isSliding)
			{
				pos_x = leftBound;
			}
			else
			{
				pos_x = leftBound + 1;
				
			}
			x_velocity = 0;
		}
	}

	//up and down collisions
	if (y_velocity < 0 && upBound > 0)
	{
		if (pos_y < upBound)
		{
			pos_y = upBound;
			y_velocity = 0;
		}
	}
	else if (y_velocity > 0 && downBound > 0)
	{
		if (pos_y + texture_size_y >= downBound)
		{
			if (!isSliding)
			{
				pos_y = downBound - texture_size_y;
			}
			else
			{
				pos_y = downBound - 16;
			}
			y_velocity = 0;
			onGround = true;
		}
		else
		{
			onGround = false;
		}
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
		isSliding = true;
		if (x_velocity > 0 && onGround)
		{
			x_velocity = 350;
		}
		zookiSprite.setTextureRect(zooki_down_r);
		zookiSprite.setRotation(90);
	}
	if (x_velocity < 0)
	{
		isSliding = true;
		if (x_velocity < 0 && onGround)
		{
			x_velocity = -350;
		}
		zookiSprite.setTextureRect(zooki_down_l);

		zookiSprite.setRotation(90);
	}
	pos_x = zookiSprite.getPosition().x;
	pos_y = zookiSprite.getPosition().y;
	
}


void Zooki::upright(){
	zookiSprite.setRotation(0);
	//zookiSprite.setTexture(zooki_texture);
	pos_x = zookiSprite.getPosition().x;
	pos_y = zookiSprite.getPosition().y;

	if (x_velocity >= 0 && isSliding)
	{
		zookiSprite.setTextureRect(zooki_stay_r);
	}
	if (x_velocity < 0 && isSliding)
	{
		zookiSprite.setTextureRect(zooki_stay_l);
	}
	isSliding = false;
}

void Zooki::stop()
{
	if (onGround){
		if (x_velocity > 0)
		{
			x_velocity /= 1.1;
		}
		else if (x_velocity < 0)
		{
			x_velocity = -((-x_velocity)/ 1.1);
			//x_velocity *= -1;
		}
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
