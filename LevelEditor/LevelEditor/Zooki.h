#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Tile.h"

class Zooki
{
public:
	Zooki(); //create a player Zooki
	Zooki(int posX, int posY);

	void setStart(int posX, int posY);
	
	void moveLeft(float deltaTime, int runSpeed);  //move Zooki left
	void moveRight(float deltaTime, int runSpeed);  // move Zooki right
	void jump();
	void slide();
	void gotCone();
	void fall(float deltaTime, int gravity);
	void resetPos();  //move Zooki to some default position

	void resetPos(int x, int y);  //move Zooki to some default position

	sf::Sprite getSprite();

	void Update();  // handles update

	~Zooki();

private:
	int num_Cones;

	int size_x; // width of Zooki
	int size_y; // length of Zooki
	int pos_x;  // x position of Zooki (constant)
	int pos_y;  // y position of Zooki
	int startX;
	int startY;
	
	bool has_cones;
	bool onGround;
	
	// Loading player texture
	sf::Texture zookiTexture;
	sf::Sprite zookiSprite;
};
