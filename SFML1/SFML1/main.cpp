
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
#include <sstream>
#include <array>
using namespace std;
#define LEVEL 8
#define LIVES 3
#define MAXLIVENUM 7
//the MAXCONES depend on the summer of array cones(2+8+16+10+2)+levelNumer(6)=44
#define MAXCONES 44
#define SECRETLEVEL 4
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
	const int gameWidth = 1280;
	const int gameHeight = 768;
	const int gravity = 250;
	const int tileSize = 16;
	const float lavaScale = 1.1;
	const int levelNumber = LEVEL;
	
	//filenames for levels
	const std::array<string, levelNumber> levels = { "1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7a.txt","7b.txt"};
	//const std::array<string, levelNumber> levels = { "5.txt","7a.txt","7b.txt","2.txt","2.txt","2.txt","7.txt","7b.txt"};//test
	
	//nnumber of cones per level
	const std::array<int, levelNumber> cones = { 0, 2, 8, 16, 10, 2, 14, 0};
	//const std::array<int, levelNumber> cones = { 0, 0, 0, 0, 0,0,0,4};//test
	
	//time limit for each level
	const std::array<int, levelNumber> times = { 10, 15, 40, 30, 70, 15, 100,300};
	//const std::array<int, levelNumber> times = { 100, 150, 400, 300, 700, 150, 1000, 300 };//test

	int screenMessage = 1;
	int coneRecord= 0;
	int timeRecord= 0;
	int coneSum = 0;
	float deltaTime=0;

	int zooki_texture_right=0;
	int zooki_texture_left=0;
	sf::Sprite xyz;
	// Handle events
	sf::Event event;

	// Create items
	Zooki zooki;
	Sound sound;
	TitleScreen titleScreen;
	
	sf::Clock levelStart;
	int isPlaying = 0;
	// For collisions
	int rightCollisionBound = NULL;
	int leftCollisionBound = NULL;
	int upCollisionBound = NULL;
	int downCollisionBound = NULL;

	Editor edit(gameWidth/tileSize, gameHeight/tileSize, tileSize);
	Hud HUD(&levelStart, &zooki);
	
	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Zooki");

	
	
	sf::Clock mainClock;
	sf::Clock AITimer;
	const sf::Time AITime = sf::seconds(0.1f);

	//framerate
	sf::Clock frameRateClock;
	double t = 0.0;
	double dt = 0.01;
	double currentTime;
	double accumulator = 0.0;



void render()
{
	if(isPlaying ==0)//
		{
			window.clear(sf::Color(164, 250, 200));
			window.draw(edit.getBackground());
			titleScreen.setText(screenMessage);
			window.draw(titleScreen.zookieLogo);
			window.draw(titleScreen.play);
			

		}

	if (isPlaying==1)//play state
		{
			window.clear();
			window.draw(edit.getBackground());
			HUD.Update();
			// Draw HUD
			for (int i = 0; i< HUD.getLives().size(); i++)
			{
				window.draw(HUD.getLives()[i]);
			}
			window.draw(HUD.getTimerSprite());
			window.draw(HUD.getLivesText());
			window.draw(HUD.getIceCreamText());
			window.draw(HUD.getIceCreamSprite());
			window.draw(HUD.getTimeText());
			
			if(zooki.conesRemaining < 1)
			{
				
				window.draw(HUD.getRemainingText());
				
			}
			//draw tiles
			for (int i = 0; i < edit.getSizeX(); i++)
			{
				for (int j = 0; j < edit.getSizeY(); j++)
				{
					if (edit.getLevelTile(i, j)->getID() != -1){
						//makes cones flash when time is running low
						if (edit.getLevelTile(i, j)->getIsCollectible() && levelStart.getElapsedTime().asSeconds() > (int)times[zooki.level]*0.7){
							if (levelStart.getElapsedTime().asMilliseconds() % 200 < 100){
								xyz = edit.getLevelTile(i, j)->getTileSprite();
								window.draw(xyz);
							}
						}
							
						if(edit.getLevelTile(i,j)->getID()==4)
						{
							if (levelStart.getElapsedTime().asMilliseconds() % 2000 < 1000)
							{
								xyz = edit.getLevelTile(i, j)->getTileSprite();
								if (coneSum <= MAXCONES)
								{
									xyz.scale(1,1);
								}
								window.draw(xyz);
							}
							else
							{
								xyz = edit.getLevelTile(i, j)->getTileSprite();
								if (coneSum <= MAXCONES)
								{
									xyz.scale(1.0, lavaScale);
								}
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
		
		if(isPlaying == 2)//pause state
		{
			window.clear();
			window.draw(edit.getBackground());
			titleScreen.setText(screenMessage);
			window.draw(titleScreen.play);
			HUD.Update();
			// Draw HUD
			
			HUD.setPauseText(500,200,coneRecord,timeRecord);
			
			window.draw(HUD.getLives()[0]);
			window.draw(HUD.getIceCreamSprite());
			window.draw(HUD.getTimerSprite());
			window.draw(HUD.getPauseText());
			
		}
}
int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	edit.LoadTiles("Data/ZookieSpriteInfo.txt");
	window.setVerticalSyncEnabled(true);
	// Define some constants
	
	sound.loadSounds();
	zooki.loadTexture();
	

	titleScreen.setText(1);
	titleScreen.setImage();
	
	
	//window.setFramerateLimit(30);

	currentTime = frameRateClock.restart().asSeconds();


	while (window.isOpen())
	{
		
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
				
				if (isPlaying==0)
				{
					sound.backgroundSound.play();
					if (zooki.lives == 0){
						zooki.level = 0;
						zooki.lives = LIVES;
						screenMessage = 1;
					}
					// (re)start the game
					isPlaying = 1;
					mainClock.restart();
					levelStart.restart();
					HUD.resetTextPosition();
					//sound stop
					sound.jumpSound.stop();
					sound.walkSound.stop();
					sound.congratulationSound.stop();
					sound.deathSound.stop();
					//load first level
					edit.clearLevel();
					if (zooki.level >= levels.size())
					{
						isPlaying = 0;
						screenMessage = 5;
						zooki.level = 0;
						zooki.reset();
						zooki.lives = LIVES;
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
				if(isPlaying ==2)
				{
					sound.backgroundSound.play();
					isPlaying = 1;
					mainClock.restart();
					levelStart.restart();
					HUD.resetTextPosition();
					//load first level
					edit.clearLevel();
					//sound stop
					sound.jumpSound.stop();
					sound.walkSound.stop();
					sound.congratulationSound.stop();
					sound.deathSound.stop();

					if (zooki.level >= levels.size())
					{
						isPlaying = 0;
						screenMessage = 5;
						zooki.level = 0;
						zooki.reset();
						zooki.lives = LIVES;
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

		if (isPlaying==1)
		{
			deltaTime = mainClock.restart().asSeconds();
			double newTime = frameRateClock.getElapsedTime().asSeconds();
			double frameTime = newTime - currentTime;
			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				// get movement input

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					zooki.moveLeft(dt, gravity);

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					zooki.moveRight(dt, gravity);

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && zooki.onGround){
					zooki.jump(dt);
					sound.jumpSound.play();
				}
				if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){
					zooki.stop();
					//sound.jumpSound.stop();
					sound.walkSound.stop();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
					zooki.slide(dt);
					//zooki.onGround = false;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
					zooki.upright();
				}

				if (!zooki.onGround && zooki.pos_y < gameHeight - zooki.texture_size_y){
					zooki.fall(dt);
				}

				// collisions

				if (isPlaying == 1)
				{
					if (levelStart.getElapsedTime().asSeconds() > times[zooki.level]){
						isPlaying = 0;
						zooki.lives -= 1;
						zooki.reset();
						screenMessage = 4;
					}
					zooki.onGround = false;

					rightCollisionBound = NULL;
					leftCollisionBound = NULL;
					upCollisionBound = NULL;
					downCollisionBound = NULL;

					//sound.backgroundSound.play();
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
									|| (edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsSolid() && !edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsDeadly()))
								{
									leftCollisionBound = (i * tileSize) + tileSize;

									break;
								}
							}
							else
							{
								if (edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsSolid() && !edit.getLevelTile(i, (zooki.pos_y / tileSize) + 1)->getIsDeadly())
								{
									leftCollisionBound = (i* tileSize) + tileSize * 2;

									break;
								}
							}
						}
					}


					// position of first downbound collision
					if (zooki.pos_y < gameHeight - tileSize * 2)
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
					zooki.processMovement(dt, rightCollisionBound, leftCollisionBound, upCollisionBound, downCollisionBound);
					zooki.Update();

					for (int i = (zooki.pos_x / tileSize) - 7; i < (zooki.pos_x / tileSize) + 7; i++)
					{
						if (i >= 0 && i <= edit.getSizeX() - 1)
						{
							for (int j = (zooki.pos_y / tileSize) - 7; j < (zooki.pos_y / tileSize) + 7; j++)
							{
								if (j >= 0 && j <= edit.getSizeY() - 1)
								{
									if ((edit.getLevelTile(i, j)->getID() != -1))
									{


										// Affected area

										sf::FloatRect area;
										if (zooki.zookiSprite.getGlobalBounds().intersects(edit.getLevelTile(i, j)->getTileSprite().getGlobalBounds(), area))
										{
											if (edit.getLevelTile(i, j)->getIsDeadly() == true)
											{
												isPlaying = 0;
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
													sound.backgroundSound.stop();
													coneSum += zooki.conesCollected;

													if (zooki.level >= SECRETLEVEL)
													{
														if (coneSum >= MAXCONES)
														{
															if (zooki.level > levels.size())
															{
																isPlaying = 0;
																screenMessage = 5;
																zooki.level = 0;
																zooki.reset();
																zooki.lives = LIVES;
																continue;
															}
															isPlaying = 2;
															coneRecord = zooki.conesCollected;
															timeRecord = levelStart.getElapsedTime().asSeconds();

															if (zooki.level < levels.size())
																zooki.conesRemaining = cones[zooki.level];
															//sound.deathSound.play();
															zooki.level += 1;
															if (zooki.lives < MAXLIVENUM)
																zooki.lives += 1;
															zooki.reset();
															screenMessage = 2;

															sound.congratulationSound.play();
															break;
														}
														else
														{
															isPlaying = 0;
															screenMessage = 5;
															zooki.level = 0;
															zooki.reset();
															zooki.lives = LIVES;
															continue;
														}
													}

													isPlaying = 2;
													coneRecord = zooki.conesCollected;
													timeRecord = levelStart.getElapsedTime().asSeconds();
													cout << timeRecord << endl;
													if (zooki.level < levels.size())
														zooki.conesRemaining = cones[zooki.level];
													//sound.deathSound.play();
													zooki.level += 1;
													if (zooki.lives < MAXLIVENUM)
														zooki.lives += 1;
													zooki.reset();
													screenMessage = 2;

													sound.congratulationSound.play();
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


											if (area.width > area.height && area.width != 2)
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
												if (area.contains(zooki.zookiSprite.getPosition().x + zooki.zookiSprite.getGlobalBounds().width - 1.f, area.top + 1.f))
												{
													//Right side crash
													zooki.zookiSprite.setPosition(zooki.pos_x - area.width, zooki.zookiSprite.getPosition().y);
													zooki.pos_x = zooki.pos_x - area.width;
													zooki.x_velocity = 0;
												}
												else
												{
													//Left side crash
													zooki.zookiSprite.setPosition(zooki.zookiSprite.getPosition().x + area.width, zooki.zookiSprite.getPosition().y);
													zooki.pos_x = zooki.pos_x + area.width;
													zooki.x_velocity = 0;
												}
											}
										}
									}

								}
							}
						}
						if (isPlaying == 0)
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
							if (!zooki.isSliding)
							{
								sound.walkSound.play();
							}

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
						if (!zooki.isSliding)
						{
							sound.walkSound.play();
						}
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

				accumulator -= dt;
				t += dt;
			}

			
			
			



		}

		
		//render windows
		render();
		// Display things on screen
		window.display();



	}

	return EXIT_SUCCESS;
}
