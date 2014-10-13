
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "move.h"

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
	const float pi = 3.14159f;
	const int gameWidth = 800;
	const int gameHeight = 600;
	sf::Vector2f paddleSize(25, 100);
	float ballRadius = 10.f;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Zooki");
	window.setVerticalSyncEnabled(true);


	// Create the left paddle
	sf::RectangleShape leftPaddle;
	leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
	leftPaddle.setOutlineThickness(3);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setFillColor(sf::Color(100, 100, 200));
	leftPaddle.setOrigin(paddleSize / 2.f);

	//Finish Area
	sf::RectangleShape endZone;
	endZone.setSize(sf::Vector2f(30.f, 30.f));
	endZone.setFillColor(sf::Color::Red);
	endZone.setOrigin(sf::Vector2f(15.f, 15.f));
	endZone.setPosition(gameWidth - 15.f, gameHeight - 15.f);




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

					// Reset the position of the paddles and ball
					leftPaddle.setPosition(10 + paddleSize.x / 2, gameHeight - 50.f);
				}
			}
		}

		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			// Move the player's paddle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
				(leftPaddle.getPosition().y - paddleSize.y / 2 > 7.f))
			{
				//jump
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
				(leftPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
			{
				//slide
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				(leftPaddle.getPosition().x < (gameWidth - 20.f)))
			{
				leftPaddle.move(paddleSpeed * deltaTime, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				(leftPaddle.getPosition().x > (20.f)))
			{
				leftPaddle.move(-paddleSpeed * deltaTime, 0.f);
			}

			//check if in zone
			if ((leftPaddle.getPosition().x > (gameWidth - 37.5)) && (leftPaddle.getPosition().y > (gameHeight - 80))){
				isPlaying = false;
			}




		}

		// Clear the window
		window.clear(sf::Color::Blue);

		if (isPlaying)
		{	
			// Draw the paddles and the ball
			window.draw(leftPaddle);
			window.draw(endZone);
		}
		else{
			window.clear(sf::Color::Green);
		}
		

		// Display things on screen
		window.display();
		
	}

	return EXIT_SUCCESS;
}
