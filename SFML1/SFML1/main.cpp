
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Zooki.h"
#include "Igloo.h"
#include "Cone.h"
#include "Hud.h"
#include "TitleScreen.h"
#include "Editor.h"
#include "Tile.h"
#include "Sound.h"
#include <iostream>
#include <cstring>
#include <array>
using namespace std;


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Define some constants

	const int gameWidth = 1280;
	const int gameHeight = 768;
	const int gravity = 200;
	const int tileSize = 16;
	
	const std::array<string, 3> levels = { "1.txt","2.txt", "3.txt" };
	//string levels[] = { "1.txt", "2.txt"};
	const std::array<int, 3> cones = { 0, 0, 8 };
	//const int cones[] = { 0, 2 };
	const std::array<int, 3> times = { 10, 15, 40};
	//const int times[] = { 10, 15 };
	int screenMessage = 1;

	int zooki_texture_right=0;
	int zooki_texture_left=0;

	Editor edit(gameWidth/tileSize, gameHeight/tileSize, tileSize);
	edit.LoadTiles("Data/ZookieSpriteInfo.txt");


	// For collisions
	int rightCollisionBound = NULL;
	int leftCollisionBound = NULL;
	int upCollisionBound = NULL;
	int downCollisionBound = NULL;


	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Zooki");
	window.setVerticalSyncEnabled(true);


	// Create items
	Zooki zooki;
	Sound sound;

	sound.loadSounds();
	zooki.loadTexture();
	TitleScreen titleScreen;

	titleScreen.setText(1);
	titleScreen.setImage();


	// Define the paddles properties
	sf::Clock AITimer;
	const sf::Time AITime = sf::seconds(0.1f);
	


	sf::Clock clock;
	sf::Clock levelStart;

	Hud HUD(&levelStart, &zooki);

	bool isPlaying = false;
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			// Space key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (!isPlaying)
				{
					if (zooki.lives == 0){
						zooki.level = 0;
						zooki.lives = 3;
						screenMessage = 1;
					}
					// (re)start the game
					isPlaying = true;
					clock.restart();
					levelStart.restart();

					//load first level
					edit.clearLevel();
					if (zooki.level >= levels.size())
					{
						isPlaying = false;
						screenMessage = 5;
						zooki.level = 0;
						zooki.reset();
						zooki.lives = 3;
						continue;
					}
					edit.LoadLevel("Data/"+levels[zooki.level]);
					HUD.setMaxTime(times[zooki.level]);
					zooki.setStart(edit.getStartX(), edit.getStartY());


					zooki.Update();
					zooki.has_cones = false;
					zooki.onGround = false;	
					zooki.isSliding = false;
					zooki.conesRemaining = cones[zooki.level];
					zooki.conesCollected = 0;
				}
			}
			
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			// get movement input

			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				zooki.moveLeft(deltaTime, gravity);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				zooki.moveRight(deltaTime, gravity);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && zooki.onGround){
				zooki.jump();
			}
			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){
				zooki.stop();				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				zooki.slide();
				//zooki.onGround = false;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				zooki.upright();
			}

			if (!zooki.onGround && zooki.pos_y < gameHeight - zooki.texture_size_y){
				zooki.fall();
			}
			

			// collisions


			if (isPlaying)
			{
				
				if (levelStart.getElapsedTime().asSeconds() > times[zooki.level]){
					isPlaying = false;
					zooki.lives -= 1;
					zooki.reset();
					screenMessage = 4;
				}
				
				
				zooki.onGround = false;

				rightCollisionBound = NULL;
				leftCollisionBound = NULL;
				upCollisionBound = NULL;
				downCollisionBound = NULL;

				// position of first rightbound collision
				if (zooki.pos_x < gameWidth - tileSize)
				{
					for (int i = ((zooki.pos_x / tileSize) + 1); i < edit.getSizeX(); i++)
					{
						if (!zooki.isSliding)
						{
							if ((edit.getLevelTile(i, zooki.pos_y / tileSize)->getIsSolid() && !edit.getLevelTile(i, zooki.pos_y / tileSize)->getIsDeadly())
								|| (edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsSolid() && !edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsDeadly()))
							{
								rightCollisionBound = i * tileSize;
								break;
							}
						}
						else
						{
							if (edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsSolid() && !edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsDeadly()) //zooki's x_size is 2 pixels wider than a tile, assume that
							{
								rightCollisionBound = i * tileSize;
								break;
							}
						}
					}
				}

				// position of first leftbound collision
				if (zooki.pos_x > tileSize)
				{
					for (int i = ((zooki.pos_x / tileSize) - 1); i > 0; i--)
					{
						if (!zooki.isSliding)
						{
							if ((edit.getLevelTile(i, zooki.pos_y / tileSize)->getIsSolid() && !edit.getLevelTile(i, zooki.pos_y / tileSize)->getIsDeadly())
								|| (edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsSolid() && ! edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsDeadly()))
							{
								leftCollisionBound = (i * tileSize) + tileSize;
								
								break;
							}
						}
						else
						{
							if (edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsSolid() && !edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsDeadly())
							{
								leftCollisionBound = (i* tileSize) + tileSize *2;
								
								break;
							}
						}
					}
				}


				// position of first downbound collision
				if (zooki.pos_y < gameHeight - tileSize *2)
				{
					for (int i = ((zooki.pos_y / tileSize) + 1); i < edit.getSizeY(); i++)
					{
						if (edit.getLevelTile(zooki.pos_x / tileSize, i)->getIsSolid() && !edit.getLevelTile(zooki.pos_x / tileSize, i)->getIsDeadly())
						{
							downCollisionBound = i * tileSize;
							
							break;
						}
					}
				}

				// position of first upbound collision
				if (zooki.pos_y > tileSize)
				{
					for (int i = ((zooki.pos_y / 16) - 1); i > 0; i--)
					{
						if (edit.getLevelTile(zooki.pos_x / tileSize, i)->getIsSolid() && !edit.getLevelTile(zooki.pos_x / tileSize, i)->getIsDeadly())
						{
							upCollisionBound = i* tileSize;
							
							break;
						}
					}
				}
				zooki.processMovement(deltaTime, rightCollisionBound, leftCollisionBound, upCollisionBound, downCollisionBound);
				zooki.Update();
				
				for (int i = 0; i < edit.getSizeX(); i++)
				{
					for (int j = 0; j < edit.getSizeY(); j++)
					{

						if ((edit.getLevelTile(i, j)->getID() != -1))
						{


							// Affected area

							sf::FloatRect area;
							if (zooki.zookiSprite.getGlobalBounds().intersects(edit.getLevelTile(i, j)->getTileSprite().getGlobalBounds(), area))
							{
								if (edit.getLevelTile(i, j)->getIsDeadly() == true)
								{
									isPlaying = false;
									sound.deathSound.play();
									zooki.lives -= 1;
									zooki.reset();
									screenMessage = 3;
									break;
								}
								if (edit.getLevelTile(i, j)->getIsFinish() == true)
								{
									if (zooki.conesRemaining < 1)
									{
										isPlaying = false;
										//sound.deathSound.play();
										zooki.level += 1;
										zooki.lives+=1;
										zooki.reset();
										screenMessage = 2;
										break;
									}
									continue;
								}
								if (edit.getLevelTile(i, j)->getIsCollectible() == true)
								{
									zooki.conesRemaining -= 1;
									zooki.conesCollected += 1;
									edit.removeTileInLevel(i, j);
									sound.iglooSound.play();
									continue;
								}
								// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis


								if (area.width > area.height)
								{
									if (area.contains(area.left, zooki.zookiSprite.getPosition().y))
									{
										// Up side crash
										zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y + area.height);
										zooki.pos_y = zooki.pos_y + area.height;
										zooki.y_velocity = 0;
									}
									else
									{
										// Down side crash
										zooki.onGround = true;
										zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y - area.height);
										zooki.pos_y = zooki.pos_y - area.height;
										zooki.y_velocity = 0;
									}
								}


								else if (area.width < area.height && area.height != 2)
								{
									if (area.contains(zooki.zookiSprite.getPosition().x + zooki.zookiSprite.getGlobalBounds().width - 1.f, area.top + 1.f ))
									{
										//Right side crash
										zooki.zookiSprite.setPosition( zooki.pos_x - area.width, zooki.zookiSprite.getPosition().y );
 										zooki.pos_x = zooki.pos_x - area.width;
										zooki.x_velocity = 0;
									}
									else
									{
										//Left side crash
										zooki.zookiSprite.setPosition( zooki.zookiSprite.getPosition().x + area.width, zooki.zookiSprite.getPosition().y );
										zooki.pos_x = zooki.pos_x + area.width;
										zooki.x_velocity = 0;
									}
								}
							}
						}

					}
					if (!isPlaying)
					{
						break;
					}
				}
				
				zooki.Update();
				
				
				//window.draw(zooki.zookiSprite);

			}
			if (zooki.x_velocity < 0 && zooki.onGround)
				{
					zooki_texture_left++;

					if (zooki.isSliding)
					{
						if (zooki_texture_left == 1)
						{
							zooki.zookiSprite.setTextureRect(zooki.zooki_run1_l_s);
						}
						if (zooki_texture_left == 2)
						{
							zooki.zookiSprite.setTextureRect(zooki.zooki_run2_l_s);
						}
						if (zooki_texture_left == 3)
						{
							zooki.zookiSprite.setTextureRect(zooki.zooki_run3_l_s);
						}
						if (zooki_texture_left > 3)
						{
							zooki_texture_left = 0;
						}
					}
					else
					{

						if (zooki_texture_left == 1)
						{
							zooki.zookiSprite.setTextureRect(zooki.zooki_run1_l);
						}
						if (zooki_texture_left == 2)
						{
							zooki.zookiSprite.setTextureRect(zooki.zooki_run2_l);
						}
						if (zooki_texture_left == 3)
						{
							zooki.zookiSprite.setTextureRect(zooki.zooki_run3_l);
						}
						if (zooki_texture_left > 3)
						{
							zooki_texture_left = 0;
						}
					}
				}
				if (zooki.x_velocity > 0 && zooki.onGround)
				{
					zooki_texture_right++;

					if (zooki_texture_right == 1)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run1_r);
					}
					if (zooki_texture_right == 2)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run2_r);
					}
					if (zooki_texture_right == 3)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run3_r);
					}
					if (zooki_texture_right > 3)
					{
						zooki_texture_right = 0;
					}
				}



		}

		sf::Sprite xyz;
		if (isPlaying)
		{
			window.clear();
			window.draw(edit.getBackground());
			HUD.Update();
			// Draw HUD
			for (int i = 0; i< HUD.getLives().size(); i++)
			{
				window.draw(HUD.getLives()[i]);
			}
			window.draw(HUD.getLivesText());
			window.draw(HUD.getIceCreamText());
			window.draw(HUD.getIceCreamSprite());
			window.draw(HUD.getTimeText());

			//draw tiles
			for (int i = 0; i < edit.getSizeX(); i++)
			{
				for (int j = 0; j < edit.getSizeY(); j++)
				{
					if (edit.getLevelTile(i, j)->getID() != -1){
						if (edit.getLevelTile(i, j)->getIsCollectible() && levelStart.getElapsedTime().asSeconds() > (int)times[zooki.level]*0.7){
							if (levelStart.getElapsedTime().asMilliseconds() % 200 < 100){
								xyz = edit.getLevelTile(i, j)->getTileSprite();
								window.draw(xyz);
							}
						}
						else{
							xyz = edit.getLevelTile(i, j)->getTileSprite();
							window.draw(xyz);
						}
					}
				}
			}

			window.draw(zooki.zookiSprite);
			
		}
		else{
			window.clear(sf::Color(164, 250, 200));
			titleScreen.setText(screenMessage);
			window.draw(titleScreen.zookieLogo);
			window.draw(titleScreen.play);


		}

		// Display things on screen
		window.display();

	}

	return EXIT_SUCCESS;
}
