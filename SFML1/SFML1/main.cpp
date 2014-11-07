
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
#include "TitleScreen.h"
#include "Editor.h"
#include "Tile.h"
#include "Sound.h"
#include <iostream>
#include <cstring>
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
	
	string levels[] = { "1.txt", "2.txt"};
	const int cones[] = { 4, 2 };
	int screenMessage = 1;
	bool up=false;
	bool left=false;
	bool right=false;
	int zooki_texture_right=0;
	int zooki_texture_left=0;

	Editor edit(gameWidth/16, gameHeight/16, 16);
	edit.LoadTiles("Data/ZookieSpriteInfo.txt");





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
					edit.LoadLevel("Data/"+levels[zooki.level]);
					zooki.setStart(edit.getStartX(), edit.getStartY());

					// Reset zooki attr's
					zooki.resetPos(0,692);
					zooki.Update();
					zooki.has_cones = false;
					zooki.onGround = false;	
					zooki.isSliding = false;
					zooki.conesRemaining = cones[zooki.level];
				}
			}

			if(event.type==sf::Event::KeyPressed)
			{
				if(event.key.code==sf::Keyboard::Up)
				{
					up=true;
				}
				if(event.key.code==sf::Keyboard::Down)
				{
					zooki.isSliding=true;
								
				}

                if(event.key.code==sf::Keyboard::Left)
				{
					left=true;
				}

				if(event.key.code==sf::Keyboard::Right)
				{
					right=true;
			
				}
            
			 }

			if(event.type==sf::Event::KeyReleased)
			{
				if(event.key.code==sf::Keyboard::Up)
				{
					up=false;
					zooki.y_velocity=0;
					zooki.onGround=false;
				}
				if(event.key.code==sf::Keyboard::Down)
				{
					//down=false;	
					zooki.isSliding=false;
					zooki.upright();
				}

                if(event.key.code==sf::Keyboard::Left)
				{
					left=false;
					sound.time_till_end=0;
					sound.stopSound("walk");
					zooki.zookiSprite.setTextureRect(zooki.zooki_stay_l);
				}

				if(event.key.code==sf::Keyboard::Right)
				{
					right=false;
					sound.time_till_end=0;
					sound.stopSound("walk");
					zooki.zookiSprite.setTextureRect(zooki.zooki_stay_r);
				}
            
			 }
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			// get movement input

			
			
			
			if (zooki.onGround && !zooki.isSliding){
				if (up==true)
				{
					zooki.jump();
					sound.playSound("jump");
					
				}
				
				if (left==true)
				{
					zooki_texture_left++;
					zooki.moveLeft(deltaTime, gravity);
					if(zooki_texture_left==1)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run1_l);
					}
					if(zooki_texture_left==2)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run2_l);
					}
					if(zooki_texture_left==3)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run3_l);
					}
					sound.playSound("walk");
					if(zooki_texture_left>3)
						zooki_texture_left=0;

				}
				if (right==true)
				{
					zooki_texture_right++;
					zooki.moveRight(deltaTime, gravity);
					if(zooki_texture_right==1)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run1_r);
					}
					if(zooki_texture_right==2)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run2_r);
					}
					if(zooki_texture_right==3)
					{
						zooki.zookiSprite.setTextureRect(zooki.zooki_run3_r);
					}
					sound.playSound("walk");
					if(zooki_texture_right>3)
						zooki_texture_right=0;
				}
			}

			if (zooki.onGround && zooki.isSliding){

					zooki.y_velocity=0;
					zooki.slide();
			//	if (up==true)
			//	{
			//		zooki.jump();
			//		zooki.isSliding = false;
			//		zooki.upright();
			//	}
			//	
				if (left==true)
				{
					zooki.moveLeft(deltaTime, gravity);
				}
				if (right==true)
				{
					zooki.moveRight(deltaTime, gravity);
				}
			//	
			//	
			//	
			}

			if (!zooki.onGround)
			{
				
				if (left==true)
				{
					zooki.moveLeft(deltaTime, gravity);
					zooki.zookiSprite.setTextureRect(zooki.zooki_jump_l);
					sound.time_till_end=0;
					sound.stopSound("walk");
				}
				if (right==true)
				{
					zooki.moveRight(deltaTime, gravity);
					zooki.zookiSprite.setTextureRect(zooki.zooki_jump_r);
					sound.time_till_end=0;
					sound.stopSound("walk");
				}
				zooki.fall();

			}

			zooki.processMovement(deltaTime);

			zooki.Update();



			// collisions


			if (isPlaying)
			{
				if (levelStart.getElapsedTime().asSeconds() > 10.f){
					isPlaying = false;
					zooki.lives -= 1;
					zooki.reset();
					screenMessage = 4;
				}
				for (int i = 0; i < edit.getSizeX(); i++)
				{
					for (int j = 0; j < edit.getSizeY(); j++)
					{
						
						if ((edit.getLevelTile(i, j)->getID() != -1)){

							
							// Affected area
							sf::FloatRect area;
							if (zooki.zookiSprite.getGlobalBounds().intersects(edit.getLevelTile(i, j)->getTileSprite().getGlobalBounds(),area))
							{
								if (edit.getLevelTile(i, j)->getIsDeadly() == true){
									isPlaying = false;
									sound.deathSound.play();
									zooki.lives -= 1;
									zooki.reset();
									screenMessage = 3;
								}
								if (edit.getLevelTile(i, j)->getIsFinish() == true){
									if (zooki.conesRemaining < 1){
										isPlaying = false;
										//sound.deathSound.play();
										zooki.level += 1;
										zooki.reset();
										screenMessage = 2;
									}
								}
								if (edit.getLevelTile(i, j)->getIsCollectible() == true){
									zooki.conesRemaining -= 1;
									edit.removeTileInLevel(i, j);
									sound.iglooSound.play();
								}
								// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
								if (area.width > area.height)
								{
									if (area.contains(area.left, zooki.zookiSprite.getPosition().y ))
									{
										// Up side crash
										zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y + area.height );
										zooki.y_velocity = 0;
									}
									else
									{
										// Down side crash
										zooki.onGround = true;
										zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y - area.height );
										zooki.y_velocity = 0;
									}
								}
								else if (area.width < area.height)
								{
									//if (area.contains({ zooki.zookiSprite.getPosition().x + zooki.zookiSprite.getGlobalBounds().width - 1.f, area.top + 1.f }))
									//{
									//	//Right side crash
									//	zooki.zookiSprite.setPosition({ zooki.zookiSprite.getPosition().x - area.width, zooki.zookiSprite.getPosition().y });
									//	zooki.x_velocity = 0;
									//}
									//else
									//{
									//	//Left side crash
									//	zooki.zookiSprite.setPosition({ zooki.zookiSprite.getPosition().x + area.width, zooki.zookiSprite.getPosition().y });
									//	zooki.x_velocity = 0;
									//}
								}
							}
						}
						
					}
				}

				window.draw(zooki.zookiSprite);

			}



		}

		sf::Sprite xyz;
		if (isPlaying)
		{
			window.clear();
			window.draw(edit.getBackground());
			for (int i = 0; i < edit.getSizeX(); i++)
			{
				for (int j = 0; j < edit.getSizeY(); j++)
				{
					if (edit.getLevelTile(i, j)->getID() != -1){
						if (edit.getLevelTile(i, j)->getIsCollectible() && levelStart.getElapsedTime().asSeconds() > 7){
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
