#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Zooki
{
public:
	Zooki(); //create a player Zooki

	sf::RectangleShape zookiShape;


	int size_x; // width of Zooki
	int size_y; // length of Zooki
	int pos_x;  // x position of Zooki (constant)
	int pos_y;  // y position of Zooki

	void moveLeft();  //move Zooki left
	void moveRight();  // move Zooki right
	void jump();
	void slide();

	void resetPos(int x, int y);  //move Zooki to some default position

	void Update();  // handles update

	~Zooki();
};
