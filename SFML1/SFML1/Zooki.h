#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Zooki
{
public:
	Zooki(); //create a player Zooki

	sf::Texture zooki_texture;
	// Loading player texture
	sf::IntRect zooki_stay_l;
	sf::IntRect zooki_stay_r;
	sf::IntRect zooki_run1_r;
	sf::IntRect zooki_run2_r;
	sf::IntRect zooki_run3_r;
	sf::IntRect zooki_run1_l;
	sf::IntRect zooki_run2_l;
	sf::IntRect zooki_run3_l;
	sf::IntRect zooki_run1_l_s; // for sliding
	sf::IntRect zooki_run2_l_s; // for sliding
	sf::IntRect zooki_run3_l_s; // for sliding
	sf::IntRect zooki_jump_l;
	sf::IntRect zooki_jump_r;
	sf::IntRect zooki_down_l;
	sf::IntRect zooki_down_r;
	sf::Sprite zookiSprite;
	

	
	int pos_x;  // x position of Zooki (constant)
	int pos_y;  // y position of Zooki
	int startX; // start X position of Zooki
	int startY; // start Y position of Zooki
	int texture_size_x;
	int texture_size_y;
	int x_velocity;
	int y_velocity;
	bool has_cones;
	bool onGround;
	bool isSliding;
	int conesCollected; // the number of cones zooki has collected
	int conesRemaining;
	int level;
	int lives;

	int getLivesLeft();

	void loadTexture();
	void moveLeft(float deltaTime, int runSpeed);  //move Zooki left
	void moveRight(float deltaTime, int runSpeed);  // move Zooki right
	void fall();
	void jump();
	void slide();
	void stop();
	void processMovement(float deltaTime);
	void processMovement(float deltaTime, int rightBound, int leftBound, int upBound, int downBound);  // takes position of closest tile into account
	void upright();

	void resetPos(int x, int y);  //move Zooki to some default position
	void resetPos();  //move Zooki to level start position
	void setStart(int x, int y);
	void reset();
	void Update();  // handles update
	
	~Zooki();
};
