
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

	Editor edit(gameWidth/32, gameHeight/32);
	edit.LoadTiles("ZookieSpriteInfo.txt");





	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Zooki");
	window.setVerticalSyncEnabled(true);


	// Create items
	Zooki zooki;
	TitleScreen titleScreen;

	titleScreen.setText();
	titleScreen.setImage();


	// Define the paddles properties
	sf::Clock AITimer;
	const sf::Time AITime = sf::seconds(0.1f);
	const float paddleSpeed = 400.f;
	float rightPaddleSpeed = 0.f;


	sf::Clock clock;
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
					// (re)start the game
					isPlaying = true;
					clock.restart();

					//load first level
					edit.LoadLevel("1.txt");

					// Reset zooki attr's
					zooki.resetPos(22.5, 200);
					zooki.Update();
					zooki.has_cones = false;
					zooki.onGround = false;				
				}
			}
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			// get movement input

			
			
			
			if (zooki.onGround && !zooki.isSliding){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					zooki.jump();					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					zooki.slide();
					zooki.isSliding = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					zooki.moveLeft(deltaTime, gravity);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					zooki.moveRight(deltaTime, gravity);
				}
			}

			else if (zooki.onGround && zooki.isSliding){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					zooki.jump();
					zooki.isSliding = false;
					zooki.upright();
				}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						zooki.isSliding = false;
						zooki.upright();
						zooki.moveLeft(deltaTime, gravity);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						zooki.isSliding = false;
						zooki.upright();
						zooki.moveRight(deltaTime, gravity);
					}
				
			}


			else{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					zooki.moveLeft(deltaTime, gravity);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					zooki.moveRight(deltaTime, gravity);
				}
				zooki.fall();

			}

			zooki.processMovement(deltaTime);

			zooki.Update();



			// collisions


			if (isPlaying)
			{
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
									zooki.reset();
								}
								// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
								if (area.width > area.height)
								{
									if (area.contains({ area.left, zooki.zookiSprite.getPosition().y }))
									{
										// Up side crash
										zooki.zookiSprite.setPosition({ zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y + area.height });
										zooki.y_velocity = 0;
									}
									else
									{
										// Down side crash
										zooki.onGround = true;
										zooki.zookiSprite.setPosition({ zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y - area.height });
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


		if (isPlaying)
		{
			window.clear();
			window.draw(edit.getBackground());

			for (int i = 0; i < edit.getSizeX(); i++)
			{
				for (int j = 0; j < edit.getSizeY(); j++)
				{
					if (edit.getLevelTile(i, j)->getID() != -1){
						window.draw(edit.getLevelTile(i, j)->getTileSprite());
					}
				}
			}

			window.draw(zooki.zookiSprite);
			
		}
		else{
			window.clear(sf::Color(164, 250, 200));
			window.draw(titleScreen.zookieLogo);
			window.draw(titleScreen.play);


		}

		// Display things on screen
		window.display();

	}

	return EXIT_SUCCESS;
}
