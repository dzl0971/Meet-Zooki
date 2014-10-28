
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

	const int gameWidth = 800;
	const int gameHeight = 600;
	const int runSpeed = 200;
	const int gravity = 200;

	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background.png");
	backgroundSprite.setTexture(backgroundTexture);



	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Zooki");
	window.setVerticalSyncEnabled(true);


	// Create items
	Zooki zooki;
	Igloo igloo;
	Cone cone;
	TitleScreen titleScreen;

	titleScreen.setText();


	//HardCode Level. Will be replaced with loading a level////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Loading ice texture
	sf::Texture iceTexture;
	iceTexture.loadFromFile("ice.jpg");
	// Creating a vector because we have more blocks and we will need them into a container
	std::vector<sf::Sprite> ice;
	// Add ice blocks to the container
	ice.resize(8);
	for (std::size_t i = 0; i<7; ++i)
	{
		ice[i].setTexture(iceTexture);
		ice[i].setPosition(128 * i, 450);
	}
	// Last ice block will bo above the first one
	ice[7].setTexture(iceTexture);
	ice[7].setPosition(0, 350);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

					// Reset position of zooki
					zooki.resetPos(22.5, 200);
					zooki.Update();
					zooki.has_cones = false;
					zooki.onGround = false;
					cone.collected = false;					
				}
			}
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			// Move Zooki

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				zooki.moveLeft(deltaTime,runSpeed);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				zooki.moveRight(deltaTime,runSpeed);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				zooki.jump();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				zooki.slide();
			}

			if (zooki.onGround == false)
			{
				zooki.fall(deltaTime, gravity);
			}

			zooki.Update();
			igloo.Update();
			cone.Update();



			//check if touching igloo
			sf::FloatRect area;
			if (zooki.zookiSprite.getGlobalBounds().intersects(igloo.iglooSprite.getGlobalBounds(), area))
			{
				if (zooki.has_cones)
				{
					isPlaying = false;
				}
				
			}

			//check if touching cone
			sf::FloatRect area2;
			if (zooki.zookiSprite.getGlobalBounds().intersects(cone.coneSprite.getGlobalBounds(), area))
			{
				zooki.gotCone();
				cone.collected = true;
			}

			//check if touching ground
			zooki.onGround = false;
			for (std::size_t i = 0; i<ice.size(); ++i)
			{
				// Affected area
				sf::FloatRect area;
				if (zooki.zookiSprite.getGlobalBounds().intersects(ice[i].getGlobalBounds(), area))
				{
					// Verifying if we need to apply collision to the vertical axis, else we apply to horizontal axis
					if (area.width > area.height)
					{
						if (area.contains(area.left, zooki.zookiSprite.getPosition().y))
						{
							// Up side crash
							zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y + area.height);
						}
						else
						{
							// Down side crash
							zooki.onGround = true;
							zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x, zooki.zookiSprite.getPosition().y - area.height);
						}
					}
					//else if (area.width < area.height) //weird bug where you can't go back left, need to debug
					//{
					//	if (area.contains({ zooki.zookiSprite.getPosition().x + zooki.zookiSprite.getGlobalBounds().width - 1.f, area.top + 1.f }))
					//	{
					//		//Right side crash
					//		zooki.zookiSprite.setPosition({ zooki.zookiSprite.getPosition().x - area.width, zooki.zookiSprite.getPosition().y });
					//	}
					//	else
					//	{
					//		//Left side crash
					//		zooki.zookiSprite.setPosition({ zooki.zookiSprite.getPosition().x + area.width, zooki.zookiSprite.getPosition().y });
					//	}
					//}
				}
			}




		}

		// Clear the window
		window.clear(sf::Color::Blue);

		if (isPlaying)
		{
			window.draw(backgroundSprite);
			
			for (std::size_t i = 0; i<ice.size(); ++i)
			{
				window.draw(ice[i]);
			}
			window.draw(zooki.zookiSprite);
			window.draw(igloo.iglooSprite);
			if (!cone.collected)
			{
				window.draw(cone.coneSprite);
			}
			
		}
		else{
			window.clear(sf::Color::Green);
			window.draw(titleScreen.title);
			window.draw(titleScreen.play);


		}


		// Display things on screen
		window.display();

	}

	return EXIT_SUCCESS;
}
