#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Cone
{
public:
	Cone(); //create an Cone

	// Loading player texture
	sf::Texture coneTexture;
	sf::Sprite coneSprite;


	int size_x; // width of Zooki
	int size_y; // length of Zooki
	int pos_x;  // x position of Zooki (constant)
	int pos_y;  // y position of Zooki

	void Update();  // handles update

	~Cone();
};
