#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Zooki
{
public:
	Zooki(); //create a player Zooki


	// Loading player texture
	sf::Texture zookiTexture;
	sf::Sprite zookiSprite;



	int size_x; // width of Zooki
	int size_y; // length of Zooki
	int pos_x;  // x position of Zooki (constant)
	int pos_y;  // y position of Zooki

	void moveLeft(float deltaTime, int runSpeed);  //move Zooki left
	void moveRight(float deltaTime, int runSpeed);  // move Zooki right
	void jump();
	void slide();

	void resetPos(int x, int y);  //move Zooki to some default position

	void Update();  // handles update

	~Zooki();
};
