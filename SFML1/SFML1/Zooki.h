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
	int x_velocity;
	int y_velocity;
	bool has_cones;
	bool onGround;
	bool isSliding;

	void moveLeft(float deltaTime, int runSpeed);  //move Zooki left
	void moveRight(float deltaTime, int runSpeed);  // move Zooki right
	void fall();
	void jump();
	void slide();
	void gotCone();
	void processMovement(float deltaTime);
	void stop();
	void upright();

	void resetPos(int x, int y);  //move Zooki to some default position
	void reset();
	void Update();  // handles update

	~Zooki();
};
