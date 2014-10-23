
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
	const int gravity = 500;



	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Zooki");
	window.setVerticalSyncEnabled(true);


	// Create items
	Zooki zooki;
	Igloo igloo;
	Cone cone;
	TitleScreen titleScreen;

	titleScreen.setText();

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
					zooki.resetPos(22.5, 550);
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

			zooki.Update();
			igloo.Update();
			cone.Update();



			//check if in zone
			sf::FloatRect area;
			if (zooki.zookiSprite.getGlobalBounds().intersects(igloo.iglooSprite.getGlobalBounds(), area))
			{
				isPlaying = false;
			}




		}

		// Clear the window
		window.clear(sf::Color::Blue);

		if (isPlaying)
		{
			// Draw the paddles and the ball
			window.draw(zooki.zookiSprite);
			window.draw(igloo.iglooSprite);
			window.draw(cone.coneSprite);
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
