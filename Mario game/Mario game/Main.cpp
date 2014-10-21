
#include "Libraries.h"


//functions

int main(){
	//Setting Up the Window
       sf::RenderWindow window(sf::VideoMode(800,600),"Mario Game C++");
	   window.setFramerateLimit(20);
	   window.setKeyRepeatEnabled(false);
again:
	//Setting menu on/off
	   bool menu=true;
	//Setting game on/off
	   bool game=true;
    //Event set up
	   sf::Event event;
	   bool up=false;
	   bool down = false;
	   bool left=false;
	   bool right=false;
	   bool start=true;
	   //Player
	   int x_player=0,y_player=0;
	   int player_go_texture_right=0;
	   int player_go_texture_left=0;
	   bool air=false;
	   int continue_game=1;
	   int Score=0;
	   player_textures();
	   player_textures1_d();
	   player_textures2_d();
	   player_textures3_d();
	   player_textures1_l();
	   player_textures2_l();
	   player_textures3_l();
	   player_down();
	   player_jump();
	   player_mesh();
	   igloo_textures();
	     //Background
	   background_textures();
	   background_mesh();
	   //Terrain
	   terrain_textures();
	   terrain_mesh();

	   //Font
	    load_font();
		write_font();

		font_class font1;
		font1.setFont("Play Game");
		font1.setPosition(325,200);
		font1.setCharacherSize(25);
		font_class font2;
		font2.setFont("Exit");
		font2.setPosition(365,300);
		font2.setCharacherSize(20);
		//Sounds
		  sounds sound;
		  sound.loadSounds();
		  sound.insertSounds();
		  int delay=0;
	   //Objects
	   //#1
	   block_1 block1;
	   block1.setTexture();
	   block1.setMesh();
	   block1.setPosition(140,500);
	   //#2
	   block_1 block2;
	   block2.setTexture();
	   block2.setMesh();
	   block2.setPosition(170,500);

	   //#3
	    block_1 block3;
	   block3.setTexture();
	   block3.setMesh();
	   block3.setPosition(170,470);
	   //#4
	    block_1 block4;
	   block4.setTexture();
	   block4.setMesh();
	   block4.setPosition(190,440);
	   //#5
	    block_1 block5;
	   block5.setTexture();
	   block5.setMesh();
	   block5.setPosition(190,500);

	      //#6
	    block_1 block6;
	   block6.setTexture();
	   block6.setMesh();
	   block6.setPosition(190,470);

	      //#7
	    block_1 block7;
	   block7.setTexture();
	   block7.setMesh();
	   block7.setPosition(220,440);

	      //#8
	    block_1 block8;
	   block8.setTexture();
	   block8.setMesh();
	   block8.setPosition(220,470);

	      //#9
	    block_1 block9;
	   block9.setTexture();
	   block9.setMesh();
	   block9.setPosition(220,500);

	      //#10
	    block_1 block10;
	   block10.setTexture();
	   block10.setMesh();
	   block10.setPosition(220,410);
		 //#11
	     block_1 block11;
	   block11.setTexture();
	   block11.setMesh();
	   block11.setPosition(300,500);
	   //#12
	     block_1 block12;
	   block12.setTexture();
	   block12.setMesh();
	   block12.setPosition(550,500);

	   //COIN
	   coin coin1;
	   coin1.setTexture();
	   coin1.setMesh();
	   coin1.setVariables();
	   coin1.setPosition(140,460);

	      coin coin2;
	   coin2.setTexture();
	   coin2.setMesh();
	   coin2.setVariables();
	   coin2.setPosition(160,430);

	      coin coin3;
	   coin3.setTexture();
	   coin3.setMesh();
	   coin3.setVariables();
	   coin3.setPosition(180,400);

	      coin coin4;
	   coin4.setTexture();
	   coin4.setMesh();
	   coin4.setVariables();
	   coin4.setPosition(210,370);

	      coin coin5;
	   coin5.setTexture();
	   coin5.setMesh();
	   coin5.setVariables();
	   coin5.setPosition(300,470);

	      coin coin6;
	   coin6.setTexture();
	   coin6.setMesh();
	   coin6.setVariables();
	   coin6.setPosition(550,470);
	   //NPC
	     //#1
	       monster_1 monster1;
		   monster1.setTexture();
		   monster1.setMesh();
		   monster1.setPosition(497,500);
		   monster1.setMovementAnimation();
		   bool monster1_sound=true;

    while(menu==true)
	{
		//Events
		while(window.pollEvent(event))
		{
				if(event.type==sf::Event::Closed)
				{
				        menu=false;
						game=false;
				}
				if(event.type==sf::Event::KeyPressed)
			{
				if(event.key.code==sf::Keyboard::Up)
				{
					start=true;
					font1.setCharacherSize(25);
					font2.setCharacherSize(20);
				}
				if(event.key.code==sf::Keyboard::Down)   
				{
					start=false;
					font1.setCharacherSize(20);
					font2.setCharacherSize(25);
				}
				if(event.key.code==sf::Keyboard::Space)
				{
					if(start==true)
						menu=false;
					if(start==false)
					{
						menu=false;
						game=false;
					}
				}
			}
		}
		//Rendering
		window.clear();
		window.draw(font1.menu);
		window.draw(font2.menu);
		window.display();
	}
	while(game==true)
	{
		//Events
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
				game=false;
			if(event.type==sf::Event::KeyPressed)
			{
				if(event.key.code==sf::Keyboard::Up)
				{
					up=true;
					player.setTexture(&mario_jump);
					down = false;
					sound.playSound("jump");
				}
				if(event.key.code==sf::Keyboard::Down)
				{
					down=true;
					player.setTexture(&mario_down);
						
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
					y_player=0;
					air=true;
				}
				if(event.key.code==sf::Keyboard::Down)
				{
					down=false;
					player.setScale(1,1);
					player.setPosition(player.getPosition().x,player.getPosition().y-37/2);
					player.setTexture(&mario_run1_d);
				}

                if(event.key.code==sf::Keyboard::Left)
				{
					left=false;
					sound.time_till_end=0;
					sound.stopSound("walk");
					player.setTexture(&mario_stay);
				}

				if(event.key.code==sf::Keyboard::Right)
				{
					right=false;
					sound.time_till_end=0;
					sound.stopSound("walk");
					player.setTexture(&mario_stay);
				}
            
			 }
			 
	}


		//Logic

		//Setting up AI npc movement
		      monster1.movementAnimation();
			  monster1.movement(block11.block,block12.block);
			  if(continue_game==1){
			  continue_game=monster1.collisionPlayer();
			  if(player.getGlobalBounds().intersects(monster1.monster_mesh.getGlobalBounds())&&(monster1_sound==true))
			  {
			        sound.playSound("hit");
			        monster1_sound=false;
			  }
			  
			  }
        //Setting coin animation
			  coin1.setAnimation();
			  coin1.collision();
			  if(coin1.score==10)
			  {
			  Score=Score+coin1.score;
			  sound.playSound("coin");
			  }

			  coin2.setAnimation();
			  coin2.collision();
			  if(coin2.score==10)
			  {
			  Score=Score+coin2.score;
			  sound.playSound("coin");
			  }
			  coin3.setAnimation();
			  coin3.collision();
			  if(coin3.score==10)
			  {
			  Score=Score+coin3.score;
			  sound.playSound("coin");
			  }

			  coin4.setAnimation();
			  coin4.collision();
			  if(coin4.score==10)
			  {
			  Score=Score+coin4.score;
			  sound.playSound("coin");
			  }

			  coin5.setAnimation();
			  coin5.collision();
			  if(coin5.score==10)
			  {
			  Score=Score+coin5.score;
			  sound.playSound("coin");
			  }

			  coin6.setAnimation();
			  coin6.collision();
			  if(coin6.score==10)
			  {
			  Score=Score+coin6.score;
			  sound.playSound("coin");
			  }

		//Setting up gravity
        if(continue_game==1){
		int gravity=10;
		if(player.getGlobalBounds().intersects(terrain.getGlobalBounds())==false)
		{
			         
			           block1.collision_y_u();
					 if(gravity==10)
					  gravity=block1.jump();
					
					 
					  block2.collision_y_u();
					 if(gravity==10)
					  gravity=block2.jump();
					 
					  
					  block3.collision_y_u();
					  if(gravity==10)
					  gravity=block3.jump();
					  
					  
					  block4.collision_y_u();
					  if(gravity==10)
					  gravity=block4.jump();
					  
					  
					  block5.collision_y_u();
					  if(gravity==10)
					  gravity=block5.jump();

					   block6.collision_y_u();
					 if(gravity==10)
					  gravity=block6.jump();
					
					 
					  block7.collision_y_u();
					 if(gravity==10)
					  gravity=block7.jump();
					 
					  
					  block8.collision_y_u();
					  if(gravity==10)
					  gravity=block8.jump();
					  
					  
					  block9.collision_y_u();
					  if(gravity==10)
					  gravity=block9.jump();
					  
					  
					  block10.collision_y_u();
					  if(gravity==10)
					  gravity=block10.jump();

					   block11.collision_y_u();
					  if(gravity==10)
					  gravity=block11.jump();

					   block12.collision_y_u();
					  if(gravity==10)
					  gravity=block12.jump();


					  	block1.collision_x_l();
			            block1.collision_x_r();

			            block2.collision_x_l();
			            block2.collision_x_r();

			            block3.collision_x_l();
			            block3.collision_x_r();

			            block4.collision_x_l();
			            block4.collision_x_r();

			            block5.collision_x_l();
			            block5.collision_x_r();

					    block6.collision_x_l();
			            block6.collision_x_r();

						block7.collision_x_l();
			            block7.collision_x_r();

						block8.collision_x_l();
			            block8.collision_x_r();

						block9.collision_x_l();
			            block9.collision_x_r();

						block10.collision_x_l();
			            block10.collision_x_r();

					  if(gravity==0)
						  air=false;



					   gravity=10;
		             player.move(0,gravity);
		}
		if(player.getGlobalBounds().intersects(terrain.getGlobalBounds())==true)
		{
			block1.collision_x_l();
			block1.collision_x_r();

			block2.collision_x_l();
			block2.collision_x_r();

			block3.collision_x_l();
			block3.collision_x_r();

			block4.collision_x_l();
			block4.collision_x_r();

			block5.collision_x_l();
			block5.collision_x_r();

			            block6.collision_x_l();
			            block6.collision_x_r();
						  block7.collision_x_l();
			            block7.collision_x_r();
						  block8.collision_x_l();
			            block8.collision_x_r();
						  block9.collision_x_l();
			            block9.collision_x_r();
						  block10.collision_x_l();
			            block10.collision_x_r();

						  block11.collision_x_l();
			            block11.collision_x_r();

						  block12.collision_x_l();
			            block12.collision_x_r();
			air=false;
		}
		//Setting up movement
		if(air==false){  //Can't press twice if you are in the air 
 
		if(up==true)
		{
			y_player+=20;
			player.move(0,-20);
			if(y_player>120){
				y_player=0;
			    up=false;
				air=true;
			}
		}
		if(down ==true)
		{
			y_player=0;
			player.setScale(1,0.5);
			player.setTexture(&mario_down);
		}
	}

		if(right==true)
		{
			
			x_player=4;
			if(player.getPosition().x<785)
			{
			  player.move(x_player,0);
			}
			else
				goto again;
			if(air==false){
				if(down ==true)
				{
					y_player=0;
					player.setTexture(&mario_down);
					player.setScale(1,0.5);
					
				}
				if(down == false)
				{
					player_go_texture_right++;
				player.setTexture(&mario_run1_d);
					/*if(player_go_texture_right==1)
				{
					player.setTexture(&mario_run1_d);
				}
					if(player_go_texture_right==2)
				{
					player.setTexture(&mario_run2_d);
				}
					if(player_go_texture_right==3)
				{
					player.setTexture(&mario_run3_d);
				}*/
				sound.playSound("walk");
				if(player_go_texture_right>3)
					player_go_texture_right=0;
				}
				}
			
			if(air==true)
			{
				player.setTexture(&mario_jump);
				sound.time_till_end=0;
				sound.stopSound("walk");
			}
			
		}

		if(left==true)
		{
			x_player=-4;
			if(player.getPosition().x>-4)
			  player.move(x_player,0);
			if(air==false){
				if(down ==true)
				{
					y_player=0;
					player.setTexture(&mario_down);
					player.setScale(1,0.5);
					
				}
				if(down == false)
				{
					player_go_texture_left++;
				player.setTexture(&mario_run1_d);
				/*if(player_go_texture_left==1)
				{
					player.setTexture(&mario_run1_l);
				}
					if(player_go_texture_left==2)
				{
					player.setTexture(&mario_run2_l);
				}
					if(player_go_texture_left==3)
				{
					player.setTexture(&mario_run3_l);
				}*/
				sound.playSound("walk");
				if(player_go_texture_left>3)
					player_go_texture_left=0;
				}
            
		}
			if(air==true)
			{
				player.setTexture(&mario_jump);
				sound.time_till_end=0;
				sound.stopSound("walk");
			}
		}
	}
		if(continue_game==0)
		{
			if(delay==0)
				sound.playSound("death");
			cout<<delay<<endl;
			delay+=1;
			player.move(0,10);
			if(delay>=100)
				goto again;
		}
		//Rendering
		window.clear();
		
		window.draw(background);
		window.draw(terrain);
		window.draw(igloo_sprite);
		//Objects;
		window.draw(block1.block);
		window.draw(block2.block);
		window.draw(block3.block);
		window.draw(block4.block);
		window.draw(block5.block);
		window.draw(block6.block);
		window.draw(block7.block);
		window.draw(block8.block);
		window.draw(block9.block);
		window.draw(block10.block);
		window.draw(block11.block);
		window.draw(block12.block);

		if(coin1.collision_player==0)
		  window.draw(coin1.coin_mesh);

		if(coin2.collision_player==0)
		window.draw(coin2.coin_mesh);

		if(coin3.collision_player==0)
		window.draw(coin3.coin_mesh);

		if(coin4.collision_player==0)
		window.draw(coin4.coin_mesh);

		if(coin5.collision_player==0)
		window.draw(coin5.coin_mesh);

		if(coin6.collision_player==0)
		window.draw(coin6.coin_mesh);

		//Npc
		if(monster1.delete_monster_cooldown<100)
		{
		   window.draw(monster1.monster_mesh);
		}
		window.draw(player);
		std::stringstream change;
		change<<"Score:"<<Score;
		score.setString(change.str());
		window.draw(score);
		window.display();
	}
	
	
	
	window.close();
	return 0;
}