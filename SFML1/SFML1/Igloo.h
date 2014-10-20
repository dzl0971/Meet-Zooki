#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Igloo
{
public:
	Igloo(); //create an igloo

	// Loading player texture
	sf::Texture iglooTexture;
	sf::Sprite iglooSprite;


	int size_x; // width of Zooki
	int size_y; // length of Zooki
	int pos_x;  // x position of Zooki (constant)
	int pos_y;  // y position of Zooki

	void Update();  // handles update

	~Igloo();
};
